@echo off
setlocal
chcp 65001 >nul
title Unde se duce spatiul pe disc

set "ROOT=%~1"

echo.
echo ============================================
echo   UNDE SE DUCE SPATIUL PE DISC
echo ============================================
echo.
if "%ROOT%"=="" (
  echo Se scaneaza discul C:
) else (
  echo Se scaneaza: %ROOT%
)
echo.
echo Masoara fiecare folder cu tot ce are in el, apoi compara
echo totalul cu cat zice Windows ca e ocupat.
echo.
echo Dureaza intre 3 si 15 minute. Nu inchide fereastra.
echo Pentru raport complet: click-dreapta - Run as administrator.
echo.

powershell -NoProfile -ExecutionPolicy Bypass -Command "$linii = Get-Content -LiteralPath '%~f0' | Where-Object { $_.StartsWith(':::') } | ForEach-Object { $_.Substring(3) }; $bloc = [ScriptBlock]::Create(($linii -join [char]10)); & $bloc '%ROOT%'"

echo.
echo Apasa o tasta pentru a inchide.
pause >nul
endlocal
exit /b

:::param($Root)
:::$ErrorActionPreference = 'SilentlyContinue'
:::if (-not $Root) { $Root = 'C:\' }
:::$prag = 100MB
:::$raport = Join-Path ([Environment]::GetFolderPath('Desktop')) 'raport-spatiu.txt'
:::$out = New-Object System.Collections.ArrayList
:::function Scrie($t) { [void]$out.Add($t); Write-Host $t }
:::
:::$stare = @{ foldere = 0; sarite = 0; urmatorul = 20000 }
:::$n1 = @{}
:::$n23 = @{}
:::$mari = New-Object System.Collections.ArrayList
:::$excluse = @((Join-Path $env:WINDIR 'WinSxS'))
:::
:::function Masoara($dir, $nivel) {
:::  $suma = [long]0
:::  $stare.foldere++
:::  if ($stare.foldere -ge $stare.urmatorul) {
:::    Write-Host ('  ... ' + $stare.foldere + ' foldere scanate')
:::    $stare.urmatorul = $stare.urmatorul + 20000
:::  }
:::  try { $fisiere = $dir.GetFiles() } catch { $stare.sarite++; $fisiere = @() }
:::  foreach ($f in $fisiere) {
:::    $suma = $suma + $f.Length
:::    if ($f.Length -ge $prag) { [void]$mari.Add($f) }
:::  }
:::  try { $subdir = $dir.GetDirectories() } catch { $stare.sarite++; $subdir = @() }
:::  foreach ($sd in $subdir) {
:::    if ($sd.Attributes -band [IO.FileAttributes]::ReparsePoint) { continue }
:::    if ($excluse -contains $sd.FullName) { continue }
:::    $suma = $suma + (Masoara $sd ($nivel + 1))
:::  }
:::  if ($nivel -eq 1) { $n1[$dir.FullName] = $suma }
:::  if ($nivel -eq 2 -or $nivel -eq 3) { $n23[$dir.FullName] = $suma }
:::  $suma
:::}
:::
:::$litera = ([System.IO.Path]::GetPathRoot($Root)).Substring(0, 2)
:::$disc = Get-CimInstance Win32_LogicalDisk -Filter ("DeviceID='" + $litera + "'")
:::$eDiscIntreg = ($Root.TrimEnd('\') -eq $litera)
:::$admin = ([Security.Principal.WindowsPrincipal][Security.Principal.WindowsIdentity]::GetCurrent()).IsInRole([Security.Principal.WindowsBuiltInRole]::Administrator)
:::$tot = [double]$disc.Size
:::$lib = [double]$disc.FreeSpace
:::
:::Scrie ''
:::Scrie ('=== SPATIU PE DISCUL ' + $litera + ' ===')
:::Scrie ('folosit {0,9:N1} GB   liber {1,9:N1} GB   din {2,9:N1} GB   ({3:N1}{4} ocupat)' -f (($tot - $lib)/1GB), ($lib/1GB), ($tot/1GB), (($tot - $lib)*100/$tot), [char]37)
:::Scrie ''
:::if ($admin) { Scrie 'Ruleaza CA ADMINISTRATOR - vede tot discul.' } else { Scrie 'Ruleaza FARA drepturi de administrator - unele foldere vor fi sarite.' }
:::Scrie ('Scanez: ' + $Root)
:::Write-Host ''
:::
:::$masurat = Masoara (New-Object System.IO.DirectoryInfo($Root)) 0
:::$baza = $masurat
:::if ($baza -le 0) { $baza = 1 }
:::
:::Scrie ''
:::Scrie ('=== FOLDERELE DIN ' + $Root + ' - TOTAL RECURSIV ===')
:::$i = 1
:::foreach ($e in ($n1.GetEnumerator() | Sort-Object -Property Value -Descending)) {
:::  if ($e.Value -lt 100MB) { continue }
:::  Scrie ('{0,2}. {1,9:N2} GB  {2,5:N1}{3}  {4}' -f $i, ($e.Value/1GB), ($e.Value*100/$baza), [char]37, $e.Key)
:::  $i++
:::}
:::
:::Scrie ''
:::Scrie '=== TOP 30 SUBFOLDERE (nivel 2 si 3) - TOTAL RECURSIV ==='
:::$i = 1
:::foreach ($e in ($n23.GetEnumerator() | Sort-Object -Property Value -Descending | Select-Object -First 30)) {
:::  Scrie ('{0,2}. {1,9:N2} GB  {2,5:N1}{3}  {4}' -f $i, ($e.Value/1GB), ($e.Value*100/$baza), [char]37, $e.Key)
:::  $i++
:::}
:::
:::Scrie ''
:::Scrie ('=== TOP 25 FISIERE PESTE 100 MB (din ' + $mari.Count + ' gasite) ===')
:::$i = 1
:::foreach ($f in ($mari | Sort-Object -Property Length -Descending | Select-Object -First 25)) {
:::  Scrie ('{0,2}. {1,8:N2} GB  {2}' -f $i, ($f.Length/1GB), $f.FullName)
:::  $i++
:::}
:::
:::Scrie ''
:::Scrie '=== BILANT ==='
:::Scrie ('Masurat de script     : {0,9:N2} GB   in {1} foldere' -f ($masurat/1GB), $stare.foldere)
:::Scrie ('Foldere fara acces    : {0}' -f $stare.sarite)
:::if ($eDiscIntreg) {
:::  $folosit = $tot - $lib
:::  $dif = $masurat - $folosit
:::  Scrie ('Ocupat dupa Windows   : {0,9:N2} GB' -f ($folosit/1GB))
:::  Scrie ('Diferenta             : {0,9:N2} GB' -f ($dif/1GB))
:::  Scrie ''
:::  if ($dif -gt 0) {
:::    Scrie 'Scriptul a numarat MAI MULT decat e pe disc. Normal: hard link-urile'
:::    Scrie 'NTFS sunt acelasi fisier fizic vazut din mai multe locuri, si fiecare'
:::    Scrie 'loc il numara din nou. Folderele de sistem sunt pline de ele.'
:::  } else {
:::    Scrie 'Scriptul a numarat MAI PUTIN decat e pe disc. Diferenta sta in'
:::    Scrie 'folderele fara acces - in primul rand System Volume Information,'
:::    Scrie 'unde stau punctele de restaurare (System Restore).'
:::  }
:::}
:::Scrie ''
:::Scrie 'Nota: C:\Windows\WinSxS e sarit dinadins - are zeci de GB pe hartie,'
:::Scrie 'dar aproape tot sunt hard link-uri catre System32, nu spatiu real.'
:::if (-not $admin) {
:::  Scrie 'Ruleaza ca administrator pentru un raport complet.'
:::}
:::
:::Scrie ''
:::Scrie 'ATENTIE: hiberfil.sys, pagefile.sys si swapfile.sys sunt fisiere de sistem - NU se sterg.'
:::
:::Scrie ''
:::Scrie '=== LOCURI CARE SE UMPLU DE OBICEI ==='
:::$suspecti = @($env:TEMP, "$env:WINDIR\Temp", "$env:WINDIR\SoftwareDistribution\Download", "$env:USERPROFILE\Downloads", "$env:LOCALAPPDATA\Packages", "$env:LOCALAPPDATA\Microsoft\Edge\User Data", "$env:LOCALAPPDATA\Google\Chrome\User Data", "$env:USERPROFILE\.nuget", "$env:USERPROFILE\AppData\Local\NuGet")
:::foreach ($p in $suspecti) {
:::  if (Test-Path -LiteralPath $p) {
:::    $s = (Get-ChildItem -LiteralPath $p -Recurse -File -Force -ErrorAction SilentlyContinue | Measure-Object -Property Length -Sum).Sum
:::    if (-not $s) { $s = 0 }
:::    Scrie ('{0,8:N2} GB  {1}' -f ($s/1GB), $p)
:::  }
:::}
:::
:::$out | Out-File -LiteralPath $raport -Encoding UTF8
:::Write-Host ''
:::Write-Host ('Raport salvat in: ' + $raport)
