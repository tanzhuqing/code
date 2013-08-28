struct CMenuItem 
{
	CString  m_MenuText;
	UINT     m_ImageIndex;
	int      m_MenuType;
};

class CCustomMenu:CMenu{
private:
	int   m_ItemCount;
	CMenuItem   *m_MenuList;
	int    m_Index;
	COLORREF     m_BkColor;
	COLORREF     m_SelTopColor;
	BOOL   m_RandColor;
	
protected:	
	CCustomMenu();
    ~CCustomMenu();

public:
	void GetAllItemCount(HMENU hMenu, int &ItemCount,BOOL FirstFind);
	BOOL AttachMenu(HMENU hMenu);
	BOOL SetMenuItemInfo(CMenu *pMenu, BOOL Toped);
	int GetTopMenuWidth();
	HRGN GetClienMenuRgn();
	void SetMenuItemText(CDC *pDC,LPSTR strMenuText,CRect Rect);
    void DrawTopMenuBk(CDC *pDC,CRect Rect,BOOL  State);
	void DrawSepMenu(CDC *pDC, CRect Rect);
	void DrawMenuBk(CDC *pDC, CRect Rect, COLORREF SrcColor, COLORREF DesColor, BOOL State);
	void MeasureItem(LPMEASUREITEMSTRUCT lpStruct);
    void DrawItem(LPDRAWITEMSTRUCT lpStruct);


}; 