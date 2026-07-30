# Code Review — david-recapitulare-matrici (lecția 29.07.2026)

Review pentru exercițiile **d)** (ștergeri: linia+coloana elementelor cu exact 3 cifre egale) și **j)** (inserări: după a doua coloană cu pătrat perfect, răsturnatul elementelor). Commit reviewuit: `99775fd`.

Structura pe `functii.h` (unelte reutilizabile) + `solutii.h` (rezolvările) e o idee foarte bună — exact așa se construiește o „bibliotecă de bac". Funcțiile de bază (`citireMatrice`, `afisareMatrice`, `stergereLinie`, `stergereColoana`, `inserareColoana`, `oglindit`) sunt corecte.

---

## 🔴 Critice

### B1 — `solutii.h:49` — paranteza pusă greșit face testul de pătrat perfect mereu adevărat

```cpp
if(isNumarPp(v[i][j]==1))
```

`v[i][j]==1` se evaluează **întâi** și dă `0` sau `1`. Apoi se verifică dacă `0` sau `1` e pătrat perfect — și ambele sunt (`0=0²`, `1=1²`). Deci condiția e adevărată pentru **orice** element, orice coloană „conține pătrat perfect", iar `poz` devine mereu coloana cu indexul 1, indiferent de matrice.

**De ce nu s-a văzut la testare:** rezultatul greșit arată plauzibil pe `data.txt` (chiar există pătrate perfecte devreme în matrice). Un bug care dă răspuns *aparent corect* pe un singur test e cel mai periculos tip — de-asta la bac testezi și cu o matrice în care știi că răspunsul e „NU".

### B2 — `solutii.h:26-29` — `i--` la `i=0` duce la citire în afara matricei (`v[-1][j]`)

```cpp
stergereLinie(v,n,m,i);
stergereColoana(v,n,m,j);
i--;
j--;
```

Când elementul cu proprietatea e pe **linia 0** (în `data.txt` chiar e: `111` la poziția `(0,0)`), `i--` face `i=-1` și bucla interioară continuă cu `v[-1][j]` — citire înainte de începutul matricei. În C++ asta e *undefined behavior*: programul citește gunoi din memorie și „merge" din noroc, nu pentru că e corect.

**Mecanismul:** `i--`/`j--` sunt gândite să compenseze `i++`/`j++` din `for`, dar `j--` e compensat imediat de `j++` al buclei interioare (deci bucla interioară **continuă**, nu se reia), în timp ce `i--` mută citirea pe linia de deasupra chiar în acel moment. Cele două decrementări nu fac ce par să facă.

### B3 — `solutii.h:20-33` — ștergerea în timpul parcurgerii pierde coloane când două elemente-țintă sunt pe aceeași linie

Enunțul d) cere: linia și coloana **tuturor** elementelor cu proprietatea. Dacă pe aceeași linie sunt două astfel de elemente, de ex. `111` la `(0,1)` și `222` la `(0,3)`: la primul, ștergi linia 0 și coloana 1; al doilea dispare odată cu linia — coloana lui (3) **nu se mai șterge niciodată**, deși enunțul o cere.

**Mecanismul:** decizia „ce șterg" și acțiunea „șterg" sunt amestecate în aceeași parcurgere, deci fiecare ștergere schimbă terenul pentru deciziile următoare. Soluția standard: **întâi marchezi, apoi ștergi** — o trecere completă peste matricea originală care doar notează liniile/coloanele de șters (vectori de frecvență `linieDeSters[100]`, `colDeSters[100]`), apoi ștergerile propriu-zise, **de la coada matricei spre început** (ca indecșii nemarcați să nu se deplaseze). Asta elimină și B2 automat — nu mai există `i--`/`j--`.

---

## 🟡 Importante

### M1 — `functii.h:105-106` — `sqrt` pe numere reale poate rata pătrate perfecte

```cpp
int r=sqrt(n);
if(r*r==n)
```

`sqrt` lucrează în virgulă mobilă și poate returna `4.9999...` pentru `sqrt(25)`; conversia la `int` taie la `4`, iar `4*4==25` e fals — un pătrat perfect declarat „nu". Pe valorile mici de la bac aproape niciodată nu se vede, dar verificarea robustă costă un rând:

```cpp
int r=sqrt(n);
return r*r==n || (r+1)*(r+1)==n;
```

De reținut și că `isNumarPp(0)` și `isNumarPp(1)` returnează `true` — exact asta a mascat B1.

### M2 — `main.cpp:5-6` — soluțiile nu sunt apelate

`main` a rămas pe un test de laborator (`isNumarPp(23)`); `solutied()` și `solutiej()` nu rulează. La predare/bac, `main` trebuie să demonstreze cerința.

---

## 🟢 Cleanups

### C1 — `functii.h:112` — `rastoarnaColoana(..., int&m, ...)` primește `m` prin referință dar nu-l modifică

Referința semnalează cititorului „funcția asta schimbă `m`" — aici e semnal fals. Regula: referință doar când modifici (`stergereLinie` cu `int&n` — da; aici — `int m` simplu, sau deloc, că nu e folosit).

### C2 — `solutii.h:66` — mesajul afișat e `"Nu exista"`, enunțul cere exact `"NU"`

La bac/evaluator automat, mesajul se copiază literal din enunț.

### C3 — `bin/`, `obj/`, `*.exe`, `*.depend` sunt comise în git

Artefactele de build se regenerează la fiecare compilare și diferă de la o mașină la alta. Un `.gitignore` cu `bin/`, `obj/`, `*.depend`, `*.layout` ține repo-ul doar cu sursă.

### C4 — `functii.h:58-76, 102-111` — funcțiile `bool` folosesc `int ok` intermediar

`treiCifre` poate returna direct din buclă (`if(f[i]==3) return true;` … `return false;`), iar `isNumarPp` poate fi un singur `return`. Nu e greșit, dar variabila-semafor ascunde momentul în care răspunsul e deja cunoscut.

---

## Before / After (critice)

| # | Before (actual) | After (corect) |
|---|---|---|
| B1 | `if(isNumarPp(v[i][j]==1))` | `if(isNumarPp(v[i][j]))` |
| B2+B3 | ștergere direct în parcurgere:<br>`if(treiCifre(v[i][j])==1) {`<br>`  stergereLinie(v,n,m,i);`<br>`  stergereColoana(v,n,m,j);`<br>`  i--; j--;`<br>`}` | marchezi, apoi ștergi:<br>`int lin[100]{}, col[100]{};`<br>`for(int i=0;i<n;i++)`<br>`  for(int j=0;j<m;j++)`<br>`    if(treiCifre(v[i][j])) { lin[i]=1; col[j]=1; }`<br>`for(int i=n-1;i>=0;i--) if(lin[i]) stergereLinie(v,n,m,i);`<br>`for(int j=m-1;j>=0;j--) if(col[j]) stergereColoana(v,n,m,j);` |

Observație la B2+B3: ștergerile se fac de la indexul mare spre mic tocmai ca pozițiile încă nemarcate să nu se deplaseze sub tine — același motiv pentru care `inserareColoana` copiază de la `m-1` în jos.

---

## Q&A — verifică-ți înțelegerea

1. La B1: ce valoare primește efectiv `isNumarPp` când `v[i][j]` este `444`, și de ce rezultatul e `true`?
2. La B3: pentru matricea cu `111` la `(0,1)` și `222` la `(0,3)`, ce coloane rămân după codul actual și ce coloane ar trebui să rămână conform enunțului?
3. De ce în varianta mark-then-delete ștergerile se fac de la sfârșit (`i=n-1` spre `0`) și nu de la început?
