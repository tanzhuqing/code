#include<iostream>

using namespace std; 
const int DefaultSize = 100;

 
template<typename Type> class SeqList{
                  public:
                      SeqList(int sz = DefaultSize):m_nmaxsize(sz),m_ncurrentsize(-1){
                                  if(sz>0)
                                    m_elements = new Type[m_nmaxsize];
                                  }
                  
                  ~SeqList(){
                             delete[] m_elements;
                             }
                  int Length() const{
                      return m_ncurrentsize+1;
                      }
                  int Find(Type x) const;
                  int IsElement(Type x) const;
                  int Insert(Type x, int i);
                  int Remove(Type x);
                  int IsEmpty(){
                      return m_ncurrentsize == -1;
                      }
                  int IsFull(){
                      return m_ncurrentsize == m_nmaxsize-1;
                      }
                  Type Get(int i){
                       return i<0||i>m_ncurrentsize?(cout<<" can't find the element "<<endl,0):m_elements[i];
                       }
                  void Print();
                  
                  private:
                          Type *m_elements;
                          const int m_nmaxsize;
                          int m_ncurrentsize;
};

template<typename Type> int SeqList<Type>::Find(Type x) const{
                  for(int i=0;i<m_ncurrentsize;i++)
                  if(m_elements[i] == x)
                  return i;
                  cout<<" can't find the element you want to find "<< endl;
                  return -1;
                  }

template<typename Type>int SeqList<Type>::IsElement(Type x) const{
                  if(Find(x) == -1)
                  return 0;
                  return 1;
                  }

template <typename Type>int SeqList<Type>::Insert(Type x, int i){
         if(i<0||i>m_ncurrentsize+1||m_ncurrentsize == m_nmaxsize-1){
                                                    cout<<" the operate is illegal "<<endl;
                                                    return 0;
                                                    }
         m_ncurrentsize++;
         for(int j=m_ncurrentsize;j>i;j--){
                 m_elements[j] = m_elements[j-1];
                 
                 }
                 m_elements[i] = x;
                 return 1;
         }

template<typename Type> int SeqList<Type>::Remove(Type x){
                  int size = m_ncurrentsize;
                  for(int i=0;i<m_ncurrentsize;){
                          if(m_elements[i] == x){
                                         for(int j=i;j<m_ncurrentsize;j++){
                                                 m_elements[j] = m_elements[j+1];
                                                 } 
                                                 m_ncurrentsize--;
                                                 continue;
                                           }
                                           i++;
                          }
                          if(size == m_ncurrentsize){
                                  cout<<" can't find the element you want to remove "<<endl;
                                  return 0;
                                  }
                                  return 1;
                  }
template<typename Type>void SeqList<Type>::Print(){
                  for(int i=0;i<m_ncurrentsize;i++)
                    cout<<i+1<<" :\t "<<m_elements[i]<<endl;
                    cout<<endl<<endl;
                  }
