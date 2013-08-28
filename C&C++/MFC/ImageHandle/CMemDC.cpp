class CMemDC:public CDC   //定义内存画布
{
private:
	CBitmap*  m_pbmp;           // 定义位图对象指针
	CBitmap*  m_poldbmp;         //定义位图对象指针
	CDC*      m_pDC;            //定义设备上下文指针
	CRect     m_Rect;           //定义区域对象



public:
	CMemDC(CDC* pDC, const CRect& rect):CDC(){                           //构造函数
		CreateCompatible(pDC);                                      //创建一个兼容的设备上下文
		
		m_pbmp = new CBitmap;                                                           //创建位图对象
        m_poldbmp->CreateCompatibleBitmap(pDC,rect.Width(),rect.Height());  //创建位图
		m_poldbmp =SelectObject(m_pbmp);                                //选中位图对象
	    m_pDC = pDC;                                               //设置成员变量
		m_Rect = rect;

	                       	//将目标区域绘制在内存画布上
		this->BitBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),pDC,m_Rect.left,m_Rect.top,SRCCOPY);
	}

	~CMemDC(){
                               //在内存画布释放时将内存画布的内容绘制在目标区域中
		m_pDC->BitBlt(m_Rect.left,m_Rect.top,m_Rect.Width(),m_Rect.Height(),this,m_Rect.left,m_Rect.top,SRCCOPY);
		SelectObject(m_poldbmp);  //选中之前选中的位图对象
		if (m_poldbmp != NULL)   //判断位图对象是否为空
		{
			delete m_poldbmp;      //释放位图对象
		}
		DeleteObject(this);  //释放设备上下文
	}
};