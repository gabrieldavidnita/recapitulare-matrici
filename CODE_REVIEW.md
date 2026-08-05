# Code Review — david-recapitulare-matrici

## Runda 3 (2026-08-05, commit `f13779a` „terminare tema")

Tema e **completă**: toate problemele din foaie au acum o soluție (`d, e, f, g, h, j, k, l, m, p, q, r`). Am compilat cu `-Wall -Wextra` și am rulat fiecare soluție pe fișiere `data.txt` construite anume ca să **diferențieze** o implementare corectă de una greșită. Mai jos sunt rezultatele reale, nu presupuneri.

### Ce e corect — și de ce contează

| Enunț | Verdict | Ce ai făcut bine |
|---|---|---|
| **h)** ștergere linii neordonate | ✅ | `while(i<n)` cu `i++` **doar** pe ramura else — exact fixul din B3, aplicat singur, fără să ți-l spun. Testat cu 2 linii neordonate consecutive: le șterge pe ambele. |
| **m)** inserare după coloane valide | ✅ | `j=j+2` ca să sari peste coloana proaspăt inserată — altfel bucla ar fi procesat la infinit propriul rezultat. |
| **k)** inserare dublul liniei | ✅ | `inserareLinie(a,n,m,poz+1)` apoi suprascriere — folosești unealta din `functii.h`, nu rescrii deplasarea. |
| **q)** interschimbare min/max | ✅ | Mesaj identic cu enunțul, iar pe ramura de eroare **nu** mai afișezi matricea. |
| **r)** sortare linii după prima coloană | ✅ | Sortare prin `interschimbareLinii` — linia se mută întreagă, nu doar prima coloană. |
| **g)** ștergere element cu frecvență maximă | ✅ | |
| **e)** al doilea număr prim | ✅ (logica) | Contorul `ct` cu `if(ct==2)` — corect. |
| **l)** tie-break pe ultima coloană | ✅ | `if(nr>=maxim)` cu `>=` — ai citit atent „se va lua in considerare **ultima** coloana". Criteriul de selecție e însă greșit (B8). |

Progresul între runde e vizibil: în runda 1 ștergeai în timpul parcurgerii, acum ai două soluții (`h`, `m`) unde controlezi corect indexul într-o structură care se schimbă sub tine. Restul bug-urilor sunt de un singur tip: **codul nu spune ce spune enunțul**.

---

### Status constatări runda 2

| # | Constatare | Status |
|---|---|---|
| B4 | flag-uri inversate `delC`/`delL` | ❌ **rămas** — `functii.h:207-219` |
| B5 | ștergere de la început, nu de la coadă | ❌ **rămas** — `functii.h:207-219` |
| B6 | `solutiep` ia ultima linie crescătoare | ❌ **rămas** — `solutii.h:74-80` |
| M3 | `isNumarPp` compară `double` cu `==` | ❌ rămas — `functii.h:114` |
| M4 | `data.txt` prietenos cu bug-urile | ❌ rămas — fișier neschimbat |
| M2 | `main` nu apelează soluțiile | 🔁 parțial — `main.cpp:5` apelează `solutiee()`, dar hardcodat, o singură soluție |
| C1 | `int&m` nefolosit în `rastoarnaColoana` | ❌ rămas — confirmat de `-Wunused-parameter` |
| C2 | mesaj `"Nu exista"` vs `"NU EXISTA"` | ❌ rămas, și s-a propagat în `solutiee` |
| C3 | artefacte de build în git | ❌ rămas — `f13779a` a re-comis `bin/Debug/*.exe`, `obj/Debug/main.o`, `.layout`, `.depend` |
| C5 | `int n` nefolosit în `main` | ✅ dispărut |
| C6 | stil de acolade inconsistent | ❌ rămas |

**B4, B5 și B6 sunt neatinse de 3 runde.** Nu e o problemă de capacitate — e că nu ai un test care să te contrazică. Vezi M4.

---

## 🔴 Critice

### B7 — `solutii.h:129,132` — `k` e folosit fără să fie citit vreodată

Enunțul f) spune explicit: *„cel mai rar cifra k in componenta elementelor (**k citit de la tastatura**)"*.

```cpp
int a[100][100],n,m,k;          // linia 129 — k declarat, niciodată inițializat
int poz=0;
citireMatrice(a,n,m);
int minim=aparitiiCifraLinie(a,m,0,k);   // linia 132 — k citit ca valoare
```

Compilatorul spune direct:

```
./solutii.h:132:40: warning: variable 'k' is uninitialized when used here [-Wuninitialized]
```

**Mecanismul:** `int k;` local nu înseamnă „k=0". Înseamnă „rezervă 4 octeți pe stivă și lasă înăuntru ce era acolo de la funcția precedentă". În C++ asta e *undefined behavior*: programul poate să ștergă linia potrivită pentru `k=0` azi și altă linie mâine, pe alt compilator sau după ce mai adaugi o funcție. La rularea mea a nimerit `k=0` — deci a părut că merge, ceea ce e cel mai periculos mod de a fi greșit.

Ai deja tiparul corect nicăieri în proiect, pentru că **nici o soluție nu citește de la tastatură**. Aceasta e prima care trebuie.

---

### B8 — `solutii.h:220,223,226` — `solutieL` numără *cifra* maximă, enunțul cere *elementul* maxim

Enunțul l): *„coloana pe care se afla cele mai multe **elemente de maxim**"* — adică elemente egale cu maximul matricei.

```cpp
int cifraMaxima=cifraMaximaMatrice(a,n,m);              // linia 220 — cifra 0-9, nu elementul
int maxim=aparitiiCifraColoana(a,n,0,cifraMaxima);      // linia 223
...
int nr=aparitiiCifraColoana(a,n,j,cifraMaxima);         // linia 226
```

Ai amestecat două noțiuni pe care enunțul le distinge: *„elemente de maxim"* (elemente egale cu maximul) vs *„**cifra** minima dintre toate elementele"* (o cifră). Valoarea inserată — `cifraMinima` — e corectă. Criteriul de alegere a coloanei nu e.

**Rulat pe matricea de test:**

```
90 19 13        maximul matricei = 90, e de 2 ori pe coloana 0
90 29 23        cifra maxima = 9, apare de 3 ori pe coloana 1
31 39 33
```

| | Coloana aleasă | Rezultat |
|---|---|---|
| Corect (enunț) | 0 — are 2 elemente egale cu 90 | coloana de `0` inserată în stânga lui `90 90 31` |
| Codul tău | 1 — are 3 cifre de `9` | `90 0 19 13 / 90 0 29 23 / 31 0 39 33` |

Pe `data.txt` actual bug-ul e invizibil, din nou (M4).

---

### B4 + B5 — `functii.h:207-219` — flag-uri inversate + ștergere în ordinea greșită *(neatins din runda 2)*

Reconfirmat prin rulare. Cu `444` la poziția `(0,3)` — în afara diagonalei:

```
11 12 13 444          →  corect:  15 16 17          codul tău:  12 13 444
15 16 17 18                       19 20 21                      16 17 18
19 20 21 22                                                     20 21 22
```

Codul șterge **coloana 0** și nicio linie, iar `444` — elementul care a declanșat totul — rămâne în matrice. Două cauze suprapuse:

1. `delL` marchează linii dar e citit la ștergerea coloanelor, și invers (B4).
2. Bucla `for(int i=0;i<n;i++)` cu `delC[3]` pe o matrice cu `n=3` nu ajunge niciodată la indexul 3 (B5) — flag-urile de la coadă se pierd când `n` scade sub condiția `i<n`.

Fixul e în tabelul Before/After de mai jos, neschimbat din runda 2.

---

### B6 — `solutii.h:74-80` — `solutiep` ia *ultima* linie crescătoare *(neatins din runda 2)*

Reconfirmat prin rulare, cu liniile 0 și 2 ambele crescătoare:

```
11 22 33 44           corect: interschimbă linia 0 cu 1
99 88 77 66           codul tău: a interschimbat linia 2 cu 3
21 41 61 81
55 55 55 55
```

Ieșirea reală: `11 22 33 44 / 99 88 77 66 / 55 55 55 55 / 21 41 61 81`. Enunțul p) spune *„**prima** linie ce are elementele in ordine crescatoare"*.

---

## 🟡 Importante

### M5 — `solutii.h:114-123` — `solutiee` afișează matricea și pe ramura „NU EXISTA"

```cpp
if(ct<2)
{
    cout<<"Nu exista";
}
else
{
    stergereLinie(v,n,m,linie);
    stergereColoana(v,n,m,coloana);
}
afisareMatrice(v,n,m);      // linia 123 — în afara if/else, rulează pe ambele ramuri
```

Rulat pe o matrice fără două numere prime, ieșirea e `Nu exista10 12 \n14 16`. În `solutieq` ai făcut exact invers și corect: acolo `afisareMatrice` e **înăuntrul** ramurii else. Aliniază-le.

Bonus: mesajul din enunț e `"NU EXISTA"` (C2, a treia rundă).

### M6 — funcții duplicate în `functii.h` — două surse de adevăr pentru aceeași regulă

| Pereche | Linii | Diferență |
|---|---|---|
| `numerePareLinie` / `numarPareLinie` | 239-250 / 320-333 | niciuna — corpuri identice |
| `isLinieCrescatoare` / `linieCrescatoare` | 134-145 / 296-306 | doar stilul (`ok=0` fără ieșire vs `return 0` imediat) |

`solutiek` folosește `numarPareLinie`, `solutiep` folosește `isLinieCrescatoare`, `solutieh` folosește `linieCrescatoare`. **Mecanismul problemei:** când vei corecta o regulă (de ex. „crescător" să însemne strict crescător), o vei corecta într-un singur loc și jumătate din soluții vor rămâne pe varianta veche. Bug-ul care apare atunci e greu de găsit, pentru că funcția *pe care te uiți* e corectă.

Păstrează câte una din fiecare pereche, cu numele mai bun, și șterge cealaltă.

### M4 — `data.txt` nu poate infirma nimic *(a treia rundă)*

Fișierul e neschimbat din runda 1. Pe el, B4, B5, B6 și B8 trec toate. Am avut nevoie de 4 fișiere de test diferite ca să le arăt — fiecare construit după aceeași regulă:

> Un test bun nu confirmă că merge. Un test bun e cel care **ar da alt rezultat** dacă implementarea e greșită.

Concret, pentru fiecare bug: element-țintă în afara diagonalei (B4), două linii de șters, una spre coadă (B5), două linii crescătoare (B6), coloana cu maximul ≠ coloana cu cifra maximă (B8).

---

## 🟢 Cleanups

- **C7** `functii.h:335-379` — `cifraMaximaMatrice` / `cifraMinimaMatrice` folosesc `while(x>0)`: elementul `0` nu contribuie nicio cifră. Pe valori 10-90 nu se vede, dar `cifraMinima` a unei matrici care conține `0` ar trebui să fie `0`.
- **C8** `functii.h:228-236` — `isNumarPrim` continuă bucla după ce a găsit un divizor (`ok=0` în loc de `return false`). Corect ca rezultat, dar face muncă inutilă; `linieCrescatoare` de la linia 296 arată tiparul bun.
- **C9** `functii.h:68-86` — `treiCifre` e declarată `bool` dar întoarce `int ok` (C4, rundele anterioare).
- **C10** `functii.h:431-441` — `coloanaValidaM` e fidelă enunțului m), dar cere numere cu **cel puțin 10 cifre**, ceea ce nu încape pe `int` și e în afara intervalului 10-90 al problemei. Implementarea e bună; ține minte doar că soluția `m` nu poate fi verificată pe datele problemei.
- **C11** `main.cpp:5` — un singur apel hardcodat. Un `switch` peste litera problemei (`d`, `e`, `f`, …) ți-ar da un mod de a rula orice soluție fără să recompilezi de fiecare dată — și te-ar forța să le mai rulezi o dată pe toate.
- **C3** — `bin/Debug/recapitulare-matrici.exe`, `obj/Debug/main.o`, `.layout`, `.depend` sunt din nou în commit. Un `.gitignore` cu `bin/`, `obj/`, `*.layout`, `*.depend` rezolvă definitiv.

---

## Before / After — critice

| # | Before (actual) | After (corect) |
|---|---|---|
| **B7** | `int a[100][100],n,m,k;`<br>`citireMatrice(a,n,m);`<br>`int minim=aparitiiCifraLinie(a,m,0,k);` | `int a[100][100],n,m,k;`<br>`citireMatrice(a,n,m);`<br>`cout<<"k=";`<br>`cin>>k;`<br>`int minim=aparitiiCifraLinie(a,m,0,k);` |
| **B8** | `int cifraMaxima=cifraMaximaMatrice(a,n,m);`<br>`int maxim=aparitiiCifraColoana(a,n,0,cifraMaxima);`<br>`for(int j=1;j<m;j++){`<br>`  int nr=aparitiiCifraColoana(a,n,j,cifraMaxima);` | `int maximElement=elementMaximMatrice(a,n,m);`<br>`int maxim=aparitiiElementColoana(a,n,0,maximElement);`<br>`for(int j=1;j<m;j++){`<br>`  int nr=aparitiiElementColoana(a,n,j,maximElement);` |
| **B4+B5** | `for(int i=0;i<n;i++)`<br>`  if(delC[i]) stergereLinie(a,n,m,i);`<br>`for(int j=0;j<m;j++)`<br>`  if(delL[j]) stergereColoana(a,n,m,j);` | `for(int i=n-1;i>=0;i--)`<br>`  if(delL[i]) stergereLinie(a,n,m,i);`<br>`for(int j=m-1;j>=0;j--)`<br>`  if(delC[j]) stergereColoana(a,n,m,j);` |
| **B6** | `for(int i=0; i<n-1; i++)`<br>`  if(isLinieCrescatoare(v,m,i)==1)`<br>`    poz=i;` | `for(int i=0; i<n-1 && poz==-1; i++)`<br>`  if(isLinieCrescatoare(v,m,i)==1)`<br>`    poz=i;` |
| **M5** | `else { stergereLinie(...); stergereColoana(...); }`<br>`afisareMatrice(v,n,m);` | `else { stergereLinie(...); stergereColoana(...);`<br>`  afisareMatrice(v,n,m); }` |

Cele două funcții noi de care are nevoie B8 (în `functii.h`, în stilul celorlalte):

```cpp
int elementMaximMatrice(int a[100][100],int n,int m)
{
    int maxim=a[0][0];
    for(int i=0;i<n;i++)
        for(int j=0;j<m;j++)
            if(a[i][j]>maxim)
                maxim=a[i][j];
    return maxim;
}

int aparitiiElementColoana(int a[100][100],int n,int coloana,int x)
{
    int nr=0;
    for(int i=0;i<n;i++)
        if(a[i][coloana]==x)
            nr++;
    return nr;
}
```

---

## Q&A — verifică-ți înțelegerea (runda 3)

1. În `solutief`, dacă `k` nu e citit de nicăieri, de ce programul totuși *rulează* și șterge o linie — și de ce faptul că a mers la tine pe CodeBlocks nu înseamnă că va merge la fel la corectare?

2. În `solutieL`, ce diferență de sens există între „elementele de maxim dintr-o coloană" și „aparițiile cifrei maxime într-o coloană"? Construiește o matrice 3×3 în care cele două criterii aleg coloane **diferite** și spune ce coloană alege enunțul.

3. `solutieh` șterge corect liniile pe măsură ce parcurge, dar `stergeExact3CifreEgale` nu. Ce face bucla din `solutieh` (`while` + `i++` doar pe else) și de ce aceeași idee, aplicată de la coadă spre început (`for(int i=n-1;i>=0;i--)`), rezolvă și problema din `stergeExact3CifreEgale`?

4. `numerePareLinie` și `numarPareLinie` fac același lucru. Dacă mâine se schimbă definiția lui „element par" și corectezi doar una, care soluție (`k`, `p` sau `h`) rămâne pe varianta veche și de ce ți-ar fi greu să găsești bug-ul?

---

## ▶ De rezolvat, în ordine

1. **B7** (`solutief` — citește `k`) — 2 linii, e blocant pentru UB.
2. **B4+B5** (`stergeExact3CifreEgale`) — a treia rundă; fixul e scris literal mai sus.
3. **B6** (`solutiep`) — o singură condiție de buclă.
4. **B8** (`solutieL`) — cele două funcții noi + înlocuirea criteriului.
5. **M4** — un `data.txt` care poate infirma. Fă-l **înainte** de fix-uri, ca să vezi testul picând, apoi trecând.
6. M5, M6, apoi cleanups.

---

## Runda 2 (2026-07-30, commit `0bcf19c` + `4c797c3`) — arhivă

### 🔴 Critice (runda 2)

- **B4** `functii.h:197-208` — flag-urile inversate: `delL` marchează liniile, dar e folosit la ștergerea coloanelor (și invers). Pentru un element la `(0,3)`, codul șterge linia 3 și coloana 0. Testul n-a prins-o pentru că `444` era la `(2,2)`, pe diagonală.
- **B5** `functii.h:197-208` — ștergerea de la început spre sfârșit deplasează indecșii sub flag-uri. Flag-urile se referă la matricea *originală*; prima ștergere invalidează restul. Fix: de la coadă spre început, ca la `inserareColoana`.
- **B6** `solutii.h:74-80` — `solutiep` găsește *ultima* linie crescătoare; enunțul cere *prima*. Pattern-ul corect era deja în `solutiej`.

### 🟡 Importante (runda 2)

- **M3** `functii.h:112-115` — `isNumarPp` compară `double` cu `==`. Fix robust în întregi: `int r=sqrt(n); return r*r==n || (r+1)*(r+1)==n;`. Separat, `n!=0` exclude greșit `0=0²`.
- **M4** `data.txt` — datele de test sunt prietenoase cu bug-urile.

### 🟢 Cleanups (runda 2)

- **C5** `main.cpp` — `int n;` declarat și nefolosit. ✅ rezolvat.
- **C6** `functii.h` — stil de acolade inconsistent (K&R vs Allman) în `stergeExact3CifreEgale`.

---

## Runda 1 (2026-07-30, commit `99775fd`) — arhivă

- 🔴 **B1** `solutii.h:49` — `if(isNumarPp(v[i][j]==1))`: comparația se evalua întâi (0/1), iar 0 și 1 sunt ambele pătrate perfecte → condiția era mereu adevărată. ✅ corectat.
- 🔴 **B2** — la element pe linia 0, `i--` ducea la citire `v[-1][j]` (undefined behavior). ✅ dispărut.
- 🔴 **B3** — ștergerea în timpul parcurgerii pierdea coloane când două elemente-țintă erau pe aceeași linie; fix predat: mark-then-delete cu ștergeri de la coadă.
- 🟡 **M1** — `sqrt` float precision în `isNumarPp`.
- 🟡 **M2** — `main` nu apela soluțiile.
- 🟢 **C1** referință `int&m` nefolosită în `rastoarnaColoana` · **C2** mesaj `"Nu exista"` vs `"NU EXISTA"` · **C3** artefacte de build în git · **C4** variabile-semafor `int ok` în funcții `bool`.
