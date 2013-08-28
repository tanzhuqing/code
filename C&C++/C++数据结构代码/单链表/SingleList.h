#include "ListNode.h"

template<typename Type> class SingleList{
  public:
	SingleList():head(new ListNode<Type>()){}
	~SingleList(){
		MakeEmpty();
		delete head;
	}

	public:
		void MakeEmpty();
		int Length();
		ListNode<Type> *Find(Type value,int n);
		ListNode<Type> *Find(int n);
		bool Insert(Type item,int n=0);
		Type Remove(int n=0);
		bool RemoveAll(Type item);
		Type Get(int n);
		void Print();
	private:
		ListNode<Type> *head;

};
template<typename Type> void SingleList<Type>::MakeEmpty(){
	ListNode<Type> *pdel;
	while(head->m_pnext != NULL){
		pdel = head->m_pnext;
		head->m_pnext = pdel->m_pnext;
		delete pdel;
	}
}

template<typename Type>int SingleList<Type>::Length(){
	ListNode<Type> *pmove = head->m_pnext;
	int count = 0;
  while (pmove != NULL)
  {
	  pmove = pmove->m_pnext;
	  count++;
  }
  return count;


}
template<typename Type> ListNode<Type>* SingleList<Type>::Find(int n){
	if (n<0)
	{
		cout<<"The n is out of boundary "<<endl;
		return NULL;
	}
	ListNode<Type> *pmove = head->m_pnext;
	for (int i=0;i<n&&pmove;i++)
	{
		pmove = pmove->m_pnext;
	}
	if (pmove == NULL)
	{
		cout<<"The n is out of boundary "<<endl;
		return NULL;
	}
	return pmove;
}

template<typename Type>ListNode<Type>* SingleList<Type>::Find(Type value,int n){
	if (n<1)
	{
		cout<<"The n is illegal"<<endl;
		return NULL;
	}
	ListNode<Type> *pmove = head;
	int count = 0;
    while (count != n && pmove)
	{
		pmove = pmove->m_pnext;
		if (pmove->m_data == value)
		{
			count++;
		}
	}
	if (pmove == NULL)
	{
		cout<<"can't find the element "<<endl;
		return NULL;
	}
	return pmove;
}

template<typename Type>bool SingleList<Type>::Insert(Type item,int n){
	if (n<0)
	{
		cout<<"The n is illegal"<<endl;
		return 0;
	}
	ListNode<Type> *pmove = head;
	ListNode<Type> *pnode = new ListNode<Type>(item);
	if (pnode == NULL)
	{
		cout<<"Application error!"<<endl;
		return 0;
	}
	for (int i=0;i<n&&pmove;i++)
	{
		pmove = pmove->m_pnext;
	}
	if (pmove == NULL)
	{
		cout<<"The n is illegal"<<endl;
		return 0;
	}
	pnode->m_pnext = pmove->m_pnext;
	pmove->m_pnext = pnode;
	return 1;
}
template<typename Type>bool SingleList<Type>::RemoveAll(Type item){
	ListNode<Type> *pmove = head;
	ListNode<Type> *pdel = head->m_pnext;
	while (pdel != NULL)
	{
		if (pdel->m_data == item)
		{
			pmove->m_pnext = pdel->m_pnext;
			delete pdel;
			pdel= pmove->m_pnext;
			continue;
		}
		pmove= pmove->m_pnext;
		pdel = pdel->m_pnext;
	}
	return 1;
}

template<typename Type>Type SingleList<Type>::Remove(int n ){
	if (n<0)
	{
		cout<<"can't find the element"<<endl;
		exit(1);
	}
	ListNode<Type> *pmove = head,*pdel;
	for (int i=0;i<n&&pmove->m_pnext;i++)
	{
		pmove=pmove->m_pnext;
	}
	if (pmove->m_pnext == NULL)
	{
		cout<<"can't find the element"<<endl;
		exit(1);
	}
	pdel = pmove->m_pnext;
	pmove->m_pnext = pdel->m_pnext;
	Type temp = pdel->m_data;
	delete pdel;
	return temp;
}

template<typename Type>Type SingleList<Type>::Get(int n){
	if (n<0)
	{
		cout<<"The n is out of boundary"<<endl;
		exit(1);
	}
	ListNode<Type> *pmove = head->m_pnext;
	for (int i=0;i<n;i++)
	{
		pmove=pmove->m_pnext;
		if (NULL==pmove)
		{
			cout<<"The n is out of boundary"<<endl;
			exit(1);
		}
	}
	return pmove->m_data;
}

template<typename Type>void SingleList<Type>::Print(){
	ListNode<Type> *pmove = head->m_pnext;
	cout<<"head";
	while (pmove)
	{
		cout<<"---->"<<pmove->m_data;
		pmove = pmove->m_pnext;
	}
	cout<<"---> over"<<endl<<endl<<endl;
}