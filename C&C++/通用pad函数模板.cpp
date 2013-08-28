#include<string>
#include<iostream>

using namespace std;

template<typename  T>
void pad(basic_string<T>& s,typename basic_string<T>::size_type n,T c){
     if(n > s.length())
     s.append(n - s.length(),c);
     }
int main(){
    string s = "Appendix A";
    wstring ws = L"Acknowledgements";
    
    pad(s,20,'*');
    pad(ws,20,L'*');
    
    wcout<<ws<<std::endl;
    }
