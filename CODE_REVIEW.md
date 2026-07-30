# Code Review — david-recapitulare-matrici

## Runda 2 (2026-07-30, commit `0bcf19c` „rezolvare code review" + `4c797c3` ex. p)

### Status constatări runda 1

| # | Constatare | Status |
|---|---|---|
| B1 | paranteza `isNumarPp(v[i][j]==1)` | ✅ corectat: `isNumarPp(v[i][j])==1` |
| B2 | `i--` → citire `v[-1][j]` | ✅ dispărut — `solutied` deleagă acum spre `stergeExact3CifreEgale` |
| B3 | ștergere în timpul parcurgerii | 🔁 abordarea mark-then-delete e preluată corect ca idee, dar implementarea are 2 bug-uri noi (B4, B5) |
| M1 | `sqrt` float precision | 🔁 rescris, dar tot pe comparație de `double` (M3) |
| M2 | `main` nu apelează soluțiile | ❌ rămas — `main` testează `isNumarPp(25)` |
| C2 | mesaj `"Nu exista"` vs `"NU"` | ❌ rămas |
| C3 | `bin/`, `obj/` în git | ❌ rămas (acum a intrat și `recapitulare-matrici.layout`) |

Progres real: delegarea `solutied` → funcție dedicată e exact structura corectă, iar tabelele de trace din comentarii arată disciplină bună de verificare. Bug-urile noi sunt toate de același tip — merită înțeles o singură dată, bine.

---

### 🔴 Critice (noi)

#### B4 — `functii.h:197-208` — flag-urile sunt inversate: liniile se șterg după `delC`, coloanele după `delL`

```cpp
for(int i=0;i<n;i++){
    if(delC[i]){
        stergereLinie(a,n,m,i);
    }
}
for(int j=0;j<m;j++)
{
    if(delL[j])
    {
        stergereColoana(a,n,m,j);
    }
}
```

`delL` marchează **liniile**, dar e folosit la ștergerea **coloanelor** (și invers). Efectul: pentru un element cu proprietatea la `(0,3)`, codul șterge linia 3 și coloana 0 — exact pe dos.

**De ce testul n-a prins asta:** în `data.txt` singurul element cu 3 cifre egale e `444` la `(2,2)` — pe diagonală, unde indexul de linie și cel de coloană sunt egali, deci inversarea e invizibilă. Un test care poate prinde bug-ul are nevoie de un element-țintă **în afara diagonalei** (ex. `444` la `(0,3)`).

#### B5 — `functii.h:197-208` — ștergerea de la început spre sfârșit deplasează indecșii sub flag-uri

Flag-urile `delL`/`delC` sunt legate de indecșii matricei **originale**. Prima ștergere mută toate liniile de sub ea cu o poziție în sus, deci de la acel moment `delL[3]` nu mai vorbește despre linia care e acum la indexul 3. Exemplu: de șters liniile 1 și 3 din 5 → ștergi linia 1, vechea linie 3 urcă la indexul 2, iar la `i=3` ștergi vechea linie 4. În plus, `n` scade în timp ce condiția e `i<n`, deci flag-urile de la coadă pot să nu mai fie atinse deloc.

Fixul e cel din runda 1, aplicat literal: **de la coadă spre început** —

```cpp
for(int i=n-1;i>=0;i--)
    if(delL[i]) stergereLinie(a,n,m,i);
for(int j=m-1;j>=0;j--)
    if(delC[j]) stergereColoana(a,n,m,j);
```

Mecanismul: ștergând de la indexul mare spre mic, tot ce se deplasează e **sub** poziția curentă — pozițiile încă neprocesate (mai mici) rămân exact unde erau. Același motiv pentru care `inserareColoana` copiază de la `m-1` în jos.

#### B6 — `solutii.h:74-80` — `solutiep` găsește *ultima* linie crescătoare, enunțul cere *prima*

```cpp
for(int i=0; i<n-1; i++)
{
    if(isLinieCrescatoare(v,m,i)==1)
    {
       poz=i;
    }
}
```

Bucla nu se oprește la prima potrivire, deci `poz` e suprascris la fiecare linie crescătoare găsită. Cu liniile 0 și 2 ambele crescătoare, codul interschimbă linia 2 cu 3, nu linia 0 cu 1. Pattern-ul corect e deja în `solutiej`: `for(int i=0; i<n-1 && poz==-1; i++)`.

**De ce testul n-a prins asta:** în `data.txt` există o singură linie crescătoare (linia 0) — cu o singură potrivire, „prima" și „ultima" coincid.

---

### 🟡 Importante (noi)

#### M3 — `functii.h:102-105` — `isNumarPp` compară în continuare `double` cu `==`

```cpp
return  n!=0&&sqrt(n)==(int)sqrt(n);
```

E aceeași verificare ca înainte, exprimată altfel: dacă `sqrt(25)` iese `4.9999...`, `(int)` taie la `4`, comparația pică și `25` e declarat ne-pătrat. Problema era *virgula mobilă*, nu forma condiției — fixul robust rămâne cel în întregi:

```cpp
int r=sqrt(n);
return r*r==n || (r+1)*(r+1)==n;
```

Separat: `n!=0` scoate 0 din pătratele perfecte, deși `0=0²`. Pe enunț (valori 10–90) nu contează, dar ca definiție e greșită.

#### M4 — `data.txt` — datele de test sunt „prietenoase" cu bug-urile

Un singur element-țintă, așezat pe diagonală; o singură linie crescătoare. Ambele bug-uri critice noi (B4, B6) trec neobservate pe acest fișier. Regula de testare: după ce merge cazul simplu, construiește un test care *ar da rezultate diferite* între implementarea corectă și una greșită — element în afara diagonalei, două linii/coloane de șters, două linii crescătoare.

---

### 🟢 Cleanups (noi)

- **C5** `main.cpp:5` — `int n;` declarat și nefolosit; `main` tot nu demonstrează soluțiile (vezi M2).
- **C6** `functii.h:184` — `stergeExact3CifreEgale` are stil de acolade diferit de restul fișierului (K&R vs Allman) — alege unul singur pe proiect.

---

### Before / After (critice, runda 2)

| # | Before (actual) | After (corect) |
|---|---|---|
| B4+B5 | `for(int i=0;i<n;i++)`<br>`  if(delC[i]) stergereLinie(a,n,m,i);`<br>`for(int j=0;j<m;j++)`<br>`  if(delL[j]) stergereColoana(a,n,m,j);` | `for(int i=n-1;i>=0;i--)`<br>`  if(delL[i]) stergereLinie(a,n,m,i);`<br>`for(int j=m-1;j>=0;j--)`<br>`  if(delC[j]) stergereColoana(a,n,m,j);` |
| B6 | `for(int i=0; i<n-1; i++)`<br>`  if(isLinieCrescatoare(v,m,i)==1)`<br>`    poz=i;` | `for(int i=0; i<n-1 && poz==-1; i++)`<br>`  if(isLinieCrescatoare(v,m,i)==1)`<br>`    poz=i;` |

---

### Q&A — verifică-ți înțelegerea (runda 2)

1. Pentru `444` la poziția `(0,3)`, ce linie și ce coloană șterge codul actual din `stergeExact3CifreEgale` și de ce testul cu `444` la `(2,2)` nu putea prinde asta?
2. Dacă `delL[1]` și `delL[3]` sunt `true` (n=5), ce linii ajunge să șteargă bucla `for(int i=0;i<n;i++)` și de ce varianta `for(int i=n-1;i>=0;i--)` le șterge pe cele corecte?
3. În `solutiep`, ce se întâmplă dacă liniile 0 și 2 sunt ambele crescătoare, și cu ce condiție de buclă (deja folosită în `solutiej`) se oprește căutarea la prima?

---

## Runda 1 (2026-07-30, commit `99775fd`) — arhivă

Constatările inițiale, păstrate pentru istoric; statusul lor e în tabelul de mai sus.

- 🔴 **B1** `solutii.h:49` — `if(isNumarPp(v[i][j]==1))`: comparația se evalua întâi (0/1), iar 0 și 1 sunt ambele pătrate perfecte → condiția era mereu adevărată, `poz` devenea mereu coloana 1.
- 🔴 **B2** — la element pe linia 0, `i--` ducea la `i=-1` și citire `v[-1][j]` (undefined behavior).
- 🔴 **B3** — ștergerea în timpul parcurgerii pierdea coloane când două elemente-țintă erau pe aceeași linie; fix predat: mark-then-delete cu ștergeri de la coadă.
- 🟡 **M1** — `sqrt` float precision în `isNumarPp`.
- 🟡 **M2** — `main` nu apela soluțiile.
- 🟢 **C1** referință `int&m` nefolosită în `rastoarnaColoana` · **C2** mesaj `"Nu exista"` vs `"NU"` · **C3** artefacte de build în git · **C4** variabile-semafor `int ok` în funcții `bool`.
