## 10% din nota finală — temă/teme + activitate

### Complexitate + sortări + extra

#### Definiții (notații asimptotice)
- **Big-O**: \( f \in O(g) \) dacă există \( c > 0 \) și \( n_0 > 0 \) astfel încât  
  \( f(n) \le c \cdot g(n) \) pentru orice \( n \ge n_0 \).
- **Omega**: \( f \in \Omega(g) \) — „\(\ge\)” (limită inferioară asimptotică)
- **Theta**: \( f \in \Theta(g) \) — „=” (limită strânsă asimptotică)
- **little-o**: \( f \in o(g) \) — „<” (strict mai mic asimptotic)
- **little-omega**: \( f \in \omega(g) \) — „>” (strict mai mare asimptotic)

#### Exemple
1. \( 100n \in O(n) \)
2. \( 2^{n+1} \in O(2^n) \)
3. \( 2^{2n} \notin O(2^n) \)
4. \( n \in O(n\log n) \)
5. \( n \in o(n^2) \)
6. \( 100n \notin o(1000n) \)

---

## Sortări

1. **Insertion Sort** — timp: \( O(n^2) \), memorie: \( O(n) \)
2. **Selection Sort** — timp: \( O(n^2) \), memorie: \( O(n) \)
3. **Bubble Sort** — timp: \( O(n^2) \), memorie: \( O(n) \)
4. **Bogo Sort** — timp: \( O(n!) \), memorie: \( O(n) \)
5. **Counting Sort** — timp: \( O(n + V_{MAX}) \), memorie: \( O(n + V_{MAX}) \)
6. **Merge Sort** — timp: \( O(n\log n) \), memorie: \( O(n) \)
7. **Radix Sort** — timp: \( O(n\log n) \)
8. **Quick Sort** — timp mediu: \( O(n\log n) \), worst-case: \( O(n^2) \)
9. **TimSort** — timp: \( O(n\log n) \)