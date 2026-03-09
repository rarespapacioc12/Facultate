// #include <iostream>

// void f(int x) {x = x * 2;}
// void g(int *x) {*x = *x + 30;}
// void h(int &x) {x = x + 50;}

// int main(){
//     int x = 10;
//     f(x);
//     std::cout << "x = " << x << '\n'; // 10
//     g(&x);
//     std::cout << "x = " << x << '\n'; // 40
//     h(x);
//     std::cout << "x = " << x << '\n'; // 90
// }

// #include<iostream>

// #define SIZE 100

// class stack{
//     int stck[SIZE];
//     int tos;
// public:
//     void init();
//     void push(int i);
//     int pop();
// };

// void stack::init(){
//     tos = 0;
// }

// void stack::push(int i){
//     if(tos == SIZE){
//         std::cout << "Stack is full.\n";
//         return;
//     }
//     stck[tos++] = i;
// }

// int stack::pop(){
//     if(tos == 0){
//         std::cout << "Stack is empty.\n";
//         return -1;
//     }
//     return stck[--tos];
// }

// int main(){
//     stack stack1, stack2;
//     stack1.init();
//     stack2.init();
//     stack1.push(1);
//     stack2.push(2);
//     stack1.push(3);
//     stack2.push(4);
//     std::cout << stack1.pop() << '\n'; // 3
//     std::cout << stack1.pop() << '\n'; // 1
//     std::cout << stack2.pop() << '\n'; // 4
//     std::cout << stack2.pop() << '\n'; // 2

//     return 0;
// }