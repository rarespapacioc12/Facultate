// 5.1.1 Problem 1 - SumeSecv

// #include <iostream>
// #include <vector>
// #include <climits>
// #include <algorithm>

// long long n, q, *v;

// int main(){
//     std::ios::sync_with_stdio(false);
//     std::cin.tie(nullptr);
//     std::cout.tie(nullptr);

//     std::cin >> n;

//     v = new long long[n + 1];
//     for(int i = 1; i <= n; ++i){
//         std::cin >> v[i];
//         v[i] += v[i - 1];
//     }
	
//     std::cin >> q;
    
//     long long mx = LLONG_MIN;

//     for(int l, r; q--;){
//         std::cin >> l >> r;
//         if(l > r)
//             std::swap(l, r);
//         mx = std::max(mx, v[r] - v[l - 1]);
//     }

//     std::cout << mx;
// }

// 5.1.2 Problem 2 - Two Sum II

// #include <iostream>
// #include <vector>

// int n, target, *v;

// int main(){
//     std::cin >> n >> target;

//     v = new int[n];
//     for(int i = 0; i < n; ++i)
//         std::cin >> v[i];
    
//     int i = 0, j = n - 1;
//     while(i <= j){
//         if(v[i] + v[j] > target)
//             --j;
//         else if(v[i] + v[j] < target)
//             ++i;
//         else{
//             std::cout << i << ' ' << j << '\n';
//             return 0;
//         }
//     }

//     std::cout << "Target sum not found.\n";
// }

// 5.1.3 Problem 3 - Search in Matrix II

// Solutie O(n)

// #include <iostream>

// int n, x, **A;

// int main(){
//     std::cin >> n >> x;

//     A = new int*[n];
//     for(int i = 0; i < n; ++i)
//         A[i] = new int[n];
    
//     for(int i = 0; i < n; ++i)
//         for(int j = 0; j < n; ++j)
//             std::cin >> A[i][j];
    
//     int i = n - 1, j = n - 1;
//     while(i >= 0 and j >= 0){
//         if(A[i][0] > x){
//             --i;
//         }
//         else if(A[i][j] > x){
//             --j;
//         }
//         else if(A[i][j] == x){
//             std::cout << i << ' ' << j << '\n';
//             return 0;
//         }
//         else{
//             if(A[i][j + 1] <= x)
//                 j++;
//             else{
//                 --i;
//                 ++j;
//             }
//         }
//     }
//     std::cout << "Not found\n";
// }

// SAU

// Solutie O(nlogn)

// #include <iostream>

// int n, x, **A;

// int bs(int st, int dr, int* v, int target){
//     if(st == dr){
//         if(v[st] == target)
//             return st;
//         return -1;
//     }
//     else{
//         int m = (st + dr) / 2;
//         if(target < v[m])
//             return bs(st, m - 1, v, target);
//         else if(target > v[m])
//             return bs(m + 1, dr, v, target);
//         else
//             return m;
//     }
// }

// int main(){
//     std::cin >> n >> x;

//     A = new int*[n];
//     for(int i = 0; i < n; ++i)
//         A[i] = new int[n];
    
//     for(int i = 0; i < n; ++i)
//         for(int j = 0; j < n; ++j)
//             std::cin >> A[i][j];
    
//     for(int i = 0; i < n; ++i){
//         int t = bs(0, n - 1, A[i], x);
//         if(t != -1){
//             std::cout << i << ' ' << t << '\n';
//             return 0;
//         }
//     }
//     std::cout << "Not found\n";
// }

// 5.1.4 Problem 4 - Statistici de ordine

// #include <fstream>
// #include <iomanip>
// #include <algorithm>

// int partitie(int *v, int st, int dr){
//     int pivotIndex = rand() % (dr - st + 1) + st;
//     std::swap(v[pivotIndex], v[dr]);
//     int pivot = v[dr];
//     int i = st - 1;
//     for(int j = st; j < dr; ++j){
//         if(v[j] <= pivot){
//             ++i;
//             std::swap(v[i], v[j]);
//         }
//     }
//     std::swap(v[i + 1], v[dr]);
//     return (i + 1);
// }

// int kmin(int* v, int st, int dr, int k){
//     while(st <= dr){
//         int pivot = partitie(v, st, dr);

//         if(pivot == k - 1)
//             return v[pivot];
//         else if(pivot > k - 1)
//             dr = pivot - 1;
//         else
//             st = pivot + 1;
//     }
//     return -1;
// }

// int n, k;
// int* v;

// std::ifstream fin("sdo.in");
// std::ofstream fout("sdo.out");

// int main(){
//     srand(time(0));
//     fin >> n >> k;
//     v = new int[n];
//     for(int i = 0; i < n; ++i)
//         fin >> v[i];

//     fout << kmin(v, 0, n - 1, k);
// }

// 5.2.1 Problem 1

// #include <iostream>

// int get_msb(int x){
//     int t = 0;
//     while ((1 << t) < x) {
//         ++t;
//     }
//     return t;
// }

// template <typename T>
// class Vector{
//     T *v;
//     int size, capacity;
// public:
//     Vector(){
//         v = nullptr;              
//         capacity = size = 0;
//     }

//     Vector(const int n){
//         if (n <= 0) {             
//             v = nullptr;
//             size = capacity = 0;
//             return;
//         }
//         int t = get_msb(n);
//         capacity = 1 << t;        
//         v = new T[capacity];
//         size = n;
//     }

//     void push_back(const T& el){  
//         if(capacity == size){
//             capacity = (capacity == 0 ? 1 : capacity << 1);

//             T *new_v = new T[capacity];
//             for(int i = 0; i < size; ++i) {   
//                 new_v[i] = v[i];
//             }
//             delete[] v;
//             v = new_v;
//         }

//         v[size] = el;   
//         ++size;
//     }

//     void pop_back(){    
//         if(size == 0){
//             std::cout << "Vector is empty!";
//             return;
//         }
//         --size;
//     }

//     ~Vector(){
//         delete[] v;
//     }
// };


// 5.2.2 Problem 2

// #include <iostream>
// #include <unordered_set>
// #include <vector>
// #include <random>

// template<typename T>
// class Structura{
//     std::unordered_multiset<T> data;
//     std::vector<T> v;
//     int size;

//     std::mt19937 rng; // generator

// public:
//     Structura()
//         : size(0),
//           rng(std::random_device{}()) // seed bun
//     {}

//     void insert(T x){
//         data.insert(x);
//         v.push_back(x);
//         ++size;
//     }

//     void pop(){
//         if (size == 0) {
//             std::cout << "Structura e goala!\n";
//             return;
//         }

//         std::uniform_int_distribution<int> dist(0, size - 1);

//         T t = v[dist(rng)];
//         auto u = data.find(t);
//         while(u == data.end()){
//             t = v[dist(rng)];
//             u = data.find(t);
//         }

//         std::cout << t << '\n';
//         data.erase(u);
//     }
// };

// int main(){
//     Structura<int> S;
//     S.insert(3);
//     S.insert(5);
//     S.insert(6);
//     S.insert(2);
//     S.insert(5);
//     S.insert(67);
//     S.insert(42);
//     S.pop();
//     S.pop();
// }

// 5.3.1 Problem 1 + 5.3.2 Problem 2

// #include <iostream>

// struct Node{
//     int data;
//     Node* next, *prev;

//     Node(int value){
//         data = value;
//         prev = nullptr;
//         next = nullptr;
//     }
// };

// class LinkedList{
// public:
//     Node* head;
//     Node* tail;
// public:
//     LinkedList(){
//         head = tail = nullptr;
//     }

//     void push_back(int x){
//         if(head == nullptr){
//             head = new Node(x);
//             head->next = tail;
//         }
//         else if(tail == nullptr){
//             tail = new Node(x);
//             tail->prev = head;
//             head->next = tail;
//         }
//         else{
//             Node* t = new Node(x);
//             tail->next = t;
//             t->prev = tail;
//             tail = t;
//         }
//     }

//     void pop_back(){
//         if(head == nullptr){
//             std::cout << "Empty list!\n";
//             return;
//         }
//         else if(tail == nullptr){
//             delete head;
//             head = tail = nullptr;
//         }
//         else if(head->next == tail){
//             delete tail;
//             tail = nullptr;
//             head->next = nullptr;
//         }
//         else{
//             Node* t = tail->prev;
//             t->next = nullptr;
//             delete tail;
//             tail = t;
//         }
//     }

//     void push_front(int x){
//         if(head == nullptr){
//             head = new Node(x);
//             head->next = tail;
//         }
//         else if(tail == nullptr){
//             tail = head;
//             head = new Node(x);
//             tail->prev = head;
//             head->next = tail;
//         }
//         else{
//             Node* t = new Node(x);
//             t->next = head;
//             head->prev = t;
//             head = t;
//         }
//     }

//     void pop_front(){
//         if(head == nullptr){
//             std::cout << "Empty list!\n";
//             return;
//         }
//         else if(tail == nullptr){
//             delete head;
//             head = tail = nullptr;
//         }
//         else if(head->next == tail){
//             delete head;
//             head = tail;
//             tail = nullptr;
//             head->prev = nullptr;
//         }
//         else{
//             Node* t = head->next;
//             t->prev = nullptr;
//             delete head;
//             head = t;
//         }
//     }

//     Node* find_by_index(int index){
//         if(index < 0){
//             std::cout << "Index out of bounds!\n";
//             return nullptr;
//         }
//         Node* t = head;
//         int i = 0;
//         while(t != nullptr and i < index){
//             ++i;
//             t = t->next;
//         }
//         if(t == nullptr){
//             std::cout << "Index out of bounds!\n";
//             return nullptr;
//         }
//         else{
//             return t;
//         }
//     }

//     Node* find_by_value(int value){
//         Node* t = head;
//         while(t != nullptr and t->data != value){
//             t = t->next;
//         }
//         if(t == nullptr){
//             std::cout << "Value not in list!\n";
//             return nullptr;
//         }
//         else{
//             return t;
//         }
//     }

//     void insert_at(int value, int poz){
//         if(poz < 0){
//             std::cout << "Position out of bounds!\n";
//             return;
//         }
//         Node* t = head;
//         int i = 0;
//         while(t != nullptr and i < poz){
//             ++i;
//             t = t->next;
//         }
//         if(t == nullptr){
//             if(i == poz){
//                 push_back(value);
//             }
//             else{
//                 std::cout << "Position out of bounds!\n";
//             }
//             return;
//         }
//         Node* u = new Node(value);
//         u->prev = t->prev;
//         u->next = t;
//         t->prev = u;
//         if(u->prev)
//             u->prev->next = u;
//         else
//             head = u;
//     }

//     void erase_at(int poz){
//         if(poz < 0){
//             std::cout << "Position out of bounds!\n";
//             return;
//         }
//         Node* t = head;
//         int i = 0;
//         while(t != nullptr and i < poz){
//             ++i;
//             t = t->next;
//         }
//         if(t == nullptr){
//             std::cout << "Position out of bounds!\n";
//             return;
//         }
//         Node* a = t->prev;
//         Node* b = t->next;
//         if(a == nullptr){
//             pop_front();
//         }
//         else if(b == nullptr){
//             pop_back();
//         }
//         else{
//             a->next = b;
//             b->prev = a;
//             delete t;
//         }
//     }

//     void detect_cycle(){
//         Node* slow = head;
//         Node* fast = head;

//         while(fast != nullptr && fast->next != nullptr){
//             slow = slow->next;
//             fast = fast->next->next;
//             if(slow == fast){
//                 slow = head;
//                 while(slow != fast){
//                     slow = slow->next;
//                     fast = fast->next;
//                 }
//                 //now slow points at the starting point of the cycle
//                 std::cout << "Start node of cycle has value " << slow->data;
//                 Node* t = slow->next;
//                 int length = 1; //acounting for start
//                 while(t != slow){
//                     t = t->next;
//                     ++length; // basically accounting for the previous t
//                 }
//                 std::cout << " and the cycle has length " << length << '\n';
//                 return;
//             }
//         }

//         std::cout << "No cycle found\n";
//     }

//     friend std::ostream& operator<<(std::ostream& os, const LinkedList& L){
//         Node* t = L.head;
//         if(t == nullptr)
//             return os;
//         while(t->next != nullptr){
//             os << t->data << ' ';
//             t = t->next;
//         }
//         os << t->data << '\n';
//         return os;
//     }

//     ~LinkedList() {
//         while(head != nullptr){
//             pop_front();
//         }
//     }
// };

// LinkedList L;

// int main(){
//     L.push_back(3);
//     L.push_back(2);
//     L.push_back(1);
//     std::cout << L;
//     L.pop_back();
//     std::cout << L;
//     L.push_front(-1);
//     L.push_front(-2);
//     L.pop_front();
//     std::cout << L;
// }

// 5.4.1 Problem 1 - Candies
// Solution here: https://leetcode.com/problems/maximum-candies-allocated-to-k-children/submissions/1940028279/

// 5.4.2 Problem 2

// #include <iostream>

// const double bulan = 1e-5;

// double n;

// int main(){
//     std::cin >> n;

//     double st = 0, dr = n;

//     while(dr - st >= bulan){
//         double m = (st + dr) / 2;
//         if(m * m > n)
//             dr = m;
//         else
//             st = m;
//     }

//     std::cout << st;
// }

// 5.5.1 Problem 1 - LRU Cache

// https://leetcode.com/problems/lru-cache/submissions/1940285105/

// 5.5.2 Problem 2 - Find Any Duplicate

// #include <bits/stdc++.h>
// using namespace std;


// int findDuplicate(const vector<int>& v) {
//     int slow = v[0], fast = v[v[0]];
    
//     while(slow != fast){
//         slow = v[slow];
//         fast = v[v[fast]];
//     }
    
//     slow = 0;
    
//     while(slow != fast){
//         slow = v[slow];
//         fast = v[fast];
//     }
    
//     return slow;
// }

// int main() {
//     int N;
//     cin >> N;
    
//     vector<int> v;
//     for (int i = 0; i <= N; ++i) {
//         int val;
//         cin >> val;
//         v.push_back(val);
//     }
    
//     cout << findDuplicate(v) << "\n";
//     return 0;
// }