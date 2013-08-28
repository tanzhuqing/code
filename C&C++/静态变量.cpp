#include <iostream>

using namespace std;

void func(){
     static int i = 0;
     cout<<"static i = "<<++i<<endl;
     }
     
     
void func1(){
     int j = 0;
     cout<<"j = "<<++j<<endl;
     }
int main(){
    for(int x = 0;x<10;x++)
   {
             func();
    func1();
    }
 system("pause");
    }
