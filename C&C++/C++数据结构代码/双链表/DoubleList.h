#include "NodeList.h"

template<typename Type>class DoubleList{
    public:
		DoubleList():head(new ListNode<Type>()){
			head->m_pprior = head;
			head->m_pnext = head;
		}
		~DoubleList(){
			MakeEmpty();
			delete head;
		}
	public:
		void MakeEmpty();
		int Length();
		ListNode<Type> *Find(int n=0);
		ListNode<Type> *FindData(Type item);
		bool Insert(Type item,int n=0);
		Type Remove(int n=0);
		Type Get(int n=0);
		void Print();
	private:
		ListNode<Type> *head;
			
};

template<typename Type> void DoubleList<Type>::MakeEmpty(){
	ListNode<Type> *pmove = head->m_pnext,*pdel;
	while(pmove != head){
    pdel = pmove;
	pmove = pdel->m_pnext;
	delete pdel;
	}
	head->m_pnext = head;
	head->m_pprior = head;
}
template<typename Type> int DoubleList<Type>::Length(){
	ListNode<Type> *pprior = head->m_pprior,*pnext = head->m_pnext;
	int count = 0;
	while (1)
	{
		if (pprior->m_pnext == pnext)
		{
			break;
		}
		if (pprior == pnext && pprior !=head)
		{
			count++;
			break;
		}
		count+=2;
		pprior=pprior->m_pprior;
		pnext=pnext->m_pnext;
	}
	return count;
}

template<typename Type> ListNode<Type>*DoubleList<Type>::Find(int n){
	if (n<0)
	{
		cout<<"The n is out of boundary"<<endl;
		return NULL;
	}
	ListNode<Type> *pmove = head->m_pnext;
	for (int i=0;i<n;i++)
	{
		pmove = pmove->m_pnext;
		if (pmove == head)
		{
			cout<<"The  n is out of boundary"<<endl;
			return NULL
		}
	}
	return pmove;
}

template<typename Type> bool DoubleList<Type>::Insert(Type item,int n){
	if (n<0)
	{
		cout<<"The n is out of boundary"<<endl;
		return 0;
	}
	ListNode<Type> *newnode = new ListNode<Type>(item),*pmove = head;
	if (newnode ==NULL)
	{
		cout<<"Application Error!"<<endl;
		exit(1);
	}
	for (int i=0;i<n;i++)
	{
		pmove = pmove->m_pnext;
		if (pmove == head)
		{
			cout<<"The n is out of boundary"<<endl;
			return 0;
		}
	}
	newnode->m_pnext = pmove->m_pnext;
	newnode->m_pprior = pmove;
	pmove->m_pnext = newnode;
	newnode->m_pnext->m_pprior = newnode;
	return 1;
}

template<typename Type>Type DoubleList<Type>::Remove(int n){
	if (n<0)
	{
		cout<<"The n is out of boundary"<<endl;
		exit(1);
	}
	ListNode<Type>*pmove = head,*pdel;
	for (int i=0;i<n;i++)
	{
		pmove = pmove->m_pnext;
		if (pmove == head)
		{
			cout<<"The n is out of boundary"<<endl;
			exit(1);
		}
	}
	pdel = pmove;
	pmove->m_pprior->m_pnext = pdel->m_pnext;
	pmove->m_pnext->m_pprior = pdel->m_pprior;
	Type temp = pdel->m_data;
	delete pdel;
	return temp;
}

template<typename Type>Type DoubleList<Type>::Get(int n){
	if (n<0)
	{
		cout<<"The n is out of boundary"<<endl;
		exit(1);
	}
	ListNode<Type>*pmove = head;
	for (int i=0;i<n;i++)
	{
		pmove=pmove->m_pnext;
		if (pmove == head)
		{
			cout<<"The n is out of boundary"<<endl;
			exit(1);
		}
	}
	return pmove->m_data;
}
template<typename Type>void DoubleList<Type>::Print(){
	ListNode<Type>*pmove = head->m_pnext;
	cout<<"head ";
	while (pmove != head)
	{
		cout<<"--->"<<pmove->m_data;
		pmove=pmove->m_pnext;
	}
	cout<<"---> over"<<endl<<endl<<endl;
}

template<typename Type>ListNode<Type>* DoubleList<Type>::FindData(Type item){
	ListNode<Type>*pprior = head->m_pprior,*pnext = head->m_pnext;
	while (pprior->m_pnext!=pnext && pprior != pnext)
	{
		if (pprior->m_data == item)
		{
			return pprior;
		}
		if (pnext->m_data == item)
		{
			return pnext;
		}
		pprior=pprior->m_pprior;
		pnext=pnext->m_pnext;
	}
	cout<<"Can't find the element "<<endl;
	return NULL;
}