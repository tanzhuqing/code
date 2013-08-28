template<typename Type> class DoubleList;
template<typename Type> class ListNode{
	private:
		friend class DoubleList<Type>;
		ListNode():m_pprior(NULL),m_pnext(NULL){}
		ListNode(const Type item,ListNode<Type> *prior=NULL,ListNode<Type> *next = NULL):m_data(item),m_pprior(prior),m_pnext(next){}
		~ListNode(){
			m_pprior = NULL;
			m_pnext = NULL;
		}
	public:
		Type GetData();
	private:
		Type m_data;
		ListNode *m_pprior;
		ListNode *m_pnext;
};

template<typename Type> Type ListNode<Type>::GetData(){
	return this->m_data;
}