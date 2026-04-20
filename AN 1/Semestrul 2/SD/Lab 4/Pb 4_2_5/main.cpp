// https://leetcode.com/problems/find-median-from-data-stream/submissions/1975346197/
/*
Ideea mea e sa tin 2 heapuri:
- p1 care este un max-heap
- p2 care este un min-heap
La fiecare pas, am grija ca diferenta in modul dintre marimile lor sa fie maxim 1
Cand am de afisat mediana, am 2 cazuri practic:
- daca heapurile au marime egala, atunci am nr par de elemente deci fac media varfurilor
- daca au marimi diferite, atunci mediana e varful heapului mai mare
Sperand din suflet ca priority_queue are top() in O(1), 
ajung la O(1) pe mediana si O(logN) pe insert
*/