#include<iostream>
using namespace std;
int main(){
    int a[10];
    int* ip=a;
    for(int i=0;i<10;i++)
      {
            ip[i]=i*10;
           cout<<"ip["<<i<<"]="<<ip[i]<<endl;
       }
    system("pause");
    }
