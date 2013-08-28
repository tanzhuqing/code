template<typename Type> class SingleList;
template<typename Type> class ListNode{
private:
	friend typename SingleList<Type>;
	ListNode():m_pnext(NULL){}
	ListNode(const Type item,ListNode<Type> *next = NULL):m_data(item),m_pnext(next){}
	~ListNode(){
		m_pnext = NULL;
	}
public:
	Type GetData();
	friend ostream& operator<< (ostream&,ListNode<Type>&);

private:
	Type m_data;
	ListNode *m_pnext;
};

template<typename Type> Type ListNode<Type>::GetData(){
	return this->m_data;
}

template<typename Type> ostream& operator<<(ostream& os, ListNode<Type>& out){
	os<<out.m_data;
	return os;
}