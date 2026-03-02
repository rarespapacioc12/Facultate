# Sortări

## Algoritmi de sortare prin comparație

### QuickSort
- **Complexitate timp:** `O(n log n)` (mediu), `O(n^2)` (worst-case)
- **Memorie suplimentară:** `O(log n)` sau `O(n)`, în funcție de adâncimea apelurilor pe stivă (recursie)

### MergeSort
- **Complexitate timp:** `O(n log n)` (garantat)
- **Memorie suplimentară:** `O(n)`

### HeapSort
- **Complexitate timp:** `O(n log n)`
- **Memorie suplimentară:** `O(1)` (in-place)

### TimSort
- **Idee:** combinație de **MergeSort + InsertionSort**

### IntroSort
- **Idee:** combinație de **QuickSort + HeapSort + InsertionSort**
  - pornește ca QuickSort
  - dacă recursia devine prea adâncă, trece pe HeapSort (evită `O(n^2)`)
  - folosește InsertionSort pentru subsecvențe mici

---

## Algoritmi bazați pe numărare

### Counting Sort
- **Complexitate timp:** `O(n + max)`
- **Când e foarte bun:**
  - pentru **numere naturale mici**
  - pentru **numere reale cu puține zecimale** (ex: interval `9 .. 9.99` → înmulțești cu `100`)
  - pentru **intervale mici** (ex: CNP-uri / date apropiate), când `max - min <= 10^6`–`10^7`  
    - ideal când `max - min <= n`

### Bucket Sort
- **Bun când:** distribuția este **aproape uniformă**
- **Trade-off:** numărul de bucket-uri vs. “adâncimea” (cât de pline devin bucket-urile)

### Radix Sort
- **Caz particular de Bucket Sort**
- Variante:
  - **LSD** („nu vă drogați copii” — Marius Dumitran)
  - **MSD** (Bucket Sort cu 10 bucket-uri dacă lucrezi în baza 10)
- **Complexitate:** `O(n · log_10(max))` (pentru baza 10)