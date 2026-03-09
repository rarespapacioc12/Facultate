# Const și pointeri în C/C++

## Ideea principală:
În declarațiile cu pointeri, const se leagă de elementul cel mai apropiat de el.

Asta înseamnă că uneori este constantă valoarea indicată,
iar alteori este constant pointerul însuși.

==================================================
1. const int* u;
==================================================

Se mai poate scrie și:

int const* u;

Cele două declarații sunt echivalente.

## Semnificație:
- u este un pointer la un int constant
- poți schimba adresa memorată în u
- nu poți modifica valoarea spre care pointează u prin acest pointer

## Exemplu:

int a = 10;
int b = 20;

const int* u = &a;   // sau int const* u = &a;

u = &b;              // OK
//*u = 30;           // EROARE

## Concluzie:
- u nu este constant
- *u este constant

==================================================
2. int* const w = &d;
==================================================

Aici const este legat de w.

## Semnificație:
- w este un pointer constant la int
- adresa stocată în w nu mai poate fi schimbată după inițializare
- valoarea spre care pointează poate fi modificată

## Exemplu:

int d = 1;
int e = 2;

int* const w = &d;

*w = 100;    // OK
//w = &e;    // EROARE

## Concluzie:
- w este constant
- *w nu este constant

==================================================
3. const int* const x = &d;
==================================================

Se mai poate scrie și:

int const* const x = &d;

## Semnificație:
- x este un pointer constant la un int constant
- nu poți schimba adresa din x
- nu poți modifica valoarea indicată prin x

## Exemplu:

int d = 1;
int e = 2;

const int* const x = &d;

//*x = 5;   // EROARE
//x = &e;   // EROARE

## Concluzie:
- x este constant
- *x este constant

==================================================
4. Tabel recapitulativ
==================================================

1) const int* p
- Ce este constant: valoarea indicată (*p)
- Ce poți schimba: adresa din p
- Ce nu poți schimba: valoarea spre care pointează p
- Explicație: p este pointer la int constant

2) int const* p
- Ce este constant: valoarea indicată (*p)
- Ce poți schimba: adresa din p
- Ce nu poți schimba: valoarea spre care pointează p
- Explicație: identic cu const int* p

3) int* const p = &x
- Ce este constant: pointerul p
- Ce poți schimba: valoarea lui *p
- Ce nu poți schimba: adresa stocată în p
- Explicație: p este pointer constant la int

4) const int* const p = &x
- Ce este constant: și pointerul p, și valoarea indicată (*p)
- Ce poți schimba: nimic din relația pointerului
- Ce nu poți schimba: nici adresa din p, nici valoarea indicată prin p
- Explicație: pointer constant la int constant

5) int const* const p = &x
- Ce este constant: și pointerul p, și valoarea indicată (*p)
- Ce poți schimba: nimic din relația pointerului
- Ce nu poți schimba: nici adresa din p, nici valoarea indicată prin p
- Explicație: identic cu const int* const p

==================================================
5. Regula rapidă
==================================================

const se leagă de elementul cel mai apropiat:

- const int* p   -> int este constant
- int* const p   -> p este constant
- const int* const p -> și int, și p sunt constante

==================================================
6. Cum citești corect declarațiile
==================================================

const int* u
- u este pointer la const int

int* const w
- w este pointer constant la int

const int* const x
- x este pointer constant la const int

==================================================
7. Exemple scurte
==================================================

## Exemplul 1: pointer la valoare constantă

int a = 10, b = 20;
const int* p = &a;

p = &b;     // OK
//*p = 5;   // EROARE

## Exemplul 2: pointer constant

int a = 10, b = 20;
int* const p = &a;

*p = 5;     // OK
//p = &b;   // EROARE

## Exemplul 3: pointer constant la valoare constantă

int a = 10, b = 20;
const int* const p = &a;

//*p = 5;   // EROARE
//p = &b;   // EROARE

==================================================
8. Liniile din slide explicate
==================================================

const int* u;
int const* v;

Acestea sunt identice ca semnificație:
- u este pointer la int constant
- v este pointer la int constant

int d = 1;
int* const w = &d;

Aici:
- w este un pointer constant
- w trebuie inițializat la declarare
- w va arăta mereu către d
- valoarea lui d poate fi modificată prin w

const int* const x = &d;   // (1)
int const* const x2 = &d;  // (2)

(1) și (2) sunt echivalente:
- pointer constant
- către un int constant

==================================================
9. Schema mentală simplă
==================================================

Întreabă-te mereu două lucruri:

1. Poate pointerul să se mute?
2. Poate fi modificată valoarea indicată?

Apoi:

- const int*      -> nu modifici valoarea
- int* const      -> nu muți pointerul
- const int* const -> nici valoarea, nici pointerul

==================================================
10. Rezumat foarte scurt
==================================================

- const int* p
  pointer la valoare constantă

- int* const p
  pointer constant la valoare modificabilă

- const int* const p
  pointer constant la valoare constantă
