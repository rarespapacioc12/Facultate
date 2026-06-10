# Exemple de teste și explicații

Aici ai 3 exemple de teste (intrare / ieșire) pentru problema selecției echipei de muncitori.

---

### TEST 1

**Descriere**: Un caz simplu în care toți muncitorii au toleranțe destul de mari pentru a încăpea în aceeași echipă maximă.

`stdin`
```text
3
0 2
1 1
2 0
```

`stdout`
```text
3
```

**Explicație**: 
- Muncitorul 0 vrea maxim 0 mai slabi și maxim 2 mai buni (se potrivește pe rangul 1 din 3).
- Muncitorul 1 vrea maxim 1 mai slab și maxim 1 mai bun (se potrivește pe rangul 2 din 3).
- Muncitorul 2 vrea maxim 2 mai slabi și maxim 0 mai buni (se potrivește pe rangul 3 din 3).
Toți 3 pot forma echipa maximă.

---

### TEST 2

**Descriere**: Nu toți pot încăpea. Mulți muncitori au exigențe foarte resticte în legătură cu câți oameni sunt mai slabi sau mai buni ca ei.

`stdin`
```text
4
0 1
0 1
1 1
1 0
```

`stdout`
```text
2
```

**Explicație**: 
Pentru o echipă de 3, restricțiile fiecăruia nu s-ar alinia deloc corespunzător. Se poate obține o echipă de exact 2 persoane, de exemplu luând muncitorul 0 (pe prima poziție: cere maxim 0 slabi și 1 bun => OK) și muncitorul 2 (pe a doua poziție: cere maxim 1 slab și 1 bun => OK). Al doilea muncitor și cel de-al patrulea nu s-au putut potrivi în echipă.

---

### TEST 3

**Descriere**: Fiecare muncitor va refuza complet să lucreze dacă are chiar și o singură persoană mai slabă sau mai bună lângă el.

`stdin`
```text
5
0 0
0 0
0 0
0 0
0 0
```

`stdout`
```text
1
```

**Explicație**:
Orice muncitor selectat într-o echipă mai mare de 1 ar avea lângă el alți muncitori (mai recenți sau mai buni), nerespectându-și condiția de 0 și 0. Astfel, echipa cea mai mare are doar 1 membru (o putem forma cu oricare dintre ei).