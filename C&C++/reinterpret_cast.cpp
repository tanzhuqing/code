#include<iostream>
using namespace std;
const int sz = 100;

struct X{ int a[sz];};

void print(X* x){
     for(int i=0;i<sz;i++)
     cout<< x->a[i] <<' ';
     cout<<endl<<"--------------------"<<endl;
     
     }
     
int main(){
    X x;
    print(&x);
    int* xp=reinterpret_cast<int*>(&x);
    for(int* i=xp;i<xp+sz;i++)
    *i=0;
    
    print(reinterpret_cast<X*>(xp));
    
    print(&x);
    
    system("pause");
    }     
