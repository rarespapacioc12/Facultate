// Se dau n siruri de caractere de lungime maxim m. Grupati-le pe cele egale
// Brut: comparari - O(n^2*m)
// Brut: sortam sirurile - O(mnlogn)
// Optim: hash-uim stringurile si le sortam - O(nlogn)

// Se da un sir de caractere s si un text t.
// Gasiti aparitiile lui s in t
// Brut: sliding window -> O(|t|*|s|)
// Optim: h_s = h(s, p, m) + sume partiale - Rabin Karp -> O(|t| + |s|)
// sau KMP
// pi[i] = lg maxima a unui prefix propriu si a unui sufix al sirului [0...i]


/*
z[i] = lungimea maxima a unui prefix propriu p pe [0...i-1] care e prefix si pe [i...n - 1]
z[0] = 0
[l, r) cel mai din dreapta interval de forma (j, j + z[j] + 1)
for(i = 1, n - 1)
if(i < r){
z[i] = min(r - i, z[i - l]);
}
while(i + z[i] < n && s[z[i]] == s[i + z[i]]){
z[i]++;
}
if(i + z[i] > r){
l = i;
r = i + z[i];
}
*/