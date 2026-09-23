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
  echo Se scaneaza TOATE discurile fixe.
) else (
  echo Se scaneaza: %ROOT%
)
echo.
echo Cauta fisierele de peste 100 MB si arata in ce foldere stau.
echo Dureaza intre 2 si 10 minute. Nu inchide fereastra.
echo.

powershell -NoProfile -ExecutionPolicy Bypass -Command "$linii = Get-Content -LiteralPath '%~f0' | Where-Object { $_.StartsWith(':::') } | ForEach-Object { $_.Substring(3) }; $bloc = [ScriptBlock]::Create(($linii -join [char]10)); & $bloc '%ROOT%'"

echo.
echo Apasa o tasta pentru a inchide.
pause >nul
endlocal
exit /b

:::param($Root)
:::$ErrorActionPreference = 'SilentlyContinue'
:::$prag = 100MB
:::$raport = Join-Path ([Environment]::GetFolderPath('Desktop')) 'raport-spatiu.txt'
:::$out = New-Object System.Collections.ArrayList
:::function Scrie($t) { [void]$out.Add($t); Write-Host $t }
:::
:::$discuri = Get-CimInstance Win32_LogicalDisk -Filter 'DriveType=3'
:::if ($Root) { $tinte = @($Root) } else { $tinte = @($discuri | ForEach-Object { $_.DeviceID + '\' }) }
:::
:::Scrie ''
:::Scrie '=== SPATIU PE DISCURI ==='
:::foreach ($d in $discuri) {
:::  $tot = [double]$d.Size
:::  $lib = [double]$d.FreeSpace
:::  if ($tot -le 0) { continue }
:::  Scrie ('{0}  folosit {1,8:N1} GB   liber {2,8:N1} GB   din {3,8:N1} GB   ({4,5:N1}{5} ocupat)' -f $d.DeviceID, (($tot - $lib)/1GB), ($lib/1GB), ($tot/1GB), (($tot - $lib)*100/$tot), [char]37)
:::}
:::
:::Scrie ''
:::Scrie ('Scanez: ' + ($tinte -join '   '))
:::
:::$mari = @()
:::foreach ($t in $tinte) {
:::  $mari += Get-ChildItem -LiteralPath $t -Recurse -File -Force -ErrorAction SilentlyContinue | Where-Object { $_.Length -ge $prag }
:::}
:::
:::if ($mari.Count -eq 0) {
:::  Scrie ''
:::  Scrie 'Nu s-a gasit niciun fisier peste 100 MB.'
:::} else {
:::  $mari = $mari | Sort-Object -Property Length -Descending
:::  $totalMari = ($mari | Measure-Object -Property Length -Sum).Sum
:::
:::  $grupe = $mari | Group-Object -Property DirectoryName | ForEach-Object {
:::    [PSCustomObject]@{
:::      Folder = $_.Name
:::      Nr = $_.Count
:::      Bytes = ($_.Group | Measure-Object -Property Length -Sum).Sum
:::    }
:::  } | Sort-Object -Property Bytes -Descending
:::
:::  Scrie ''
:::  Scrie ('=== FOLDERELE CU CELE MAI MARI FISIERE ({0} foldere, {1:N1} GB in total) ===' -f $grupe.Count, ($totalMari/1GB))
:::  $i = 1
:::  foreach ($g in ($grupe | Select-Object -First 30)) {
:::    Scrie ('{0,2}. {1,8:N2} GB  {2,5:N1}{3}  {4,3} fisiere  {5}' -f $i, ($g.Bytes/1GB), ($g.Bytes*100/$totalMari), [char]37, $g.Nr, $g.Folder)
:::    $i++
:::  }
:::
:::  Scrie ''
:::  Scrie 'CEL MAI INCARCAT FOLDER:'
:::  Scrie ('   {0}' -f $grupe[0].Folder)
:::  Scrie ('   {0:N2} GB in {1} fisiere de peste 100 MB' -f ($grupe[0].Bytes/1GB), $grupe[0].Nr)
:::
:::  Scrie ''
:::  Scrie ('=== TOP 30 FISIERE ({0} gasite peste 100 MB) ===' -f $mari.Count)
:::  $i = 1
:::  foreach ($f in ($mari | Select-Object -First 30)) {
:::    Scrie ('{0,2}. {1,8:N2} GB  {2}' -f $i, ($f.Length/1GB), $f.FullName)
:::    $i++
:::  }
:::}
:::
:::Scrie ''
:::Scrie 'ATENTIE: hiberfil.sys, pagefile.sys si swapfile.sys sunt fisiere de sistem - NU se sterg.'
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
