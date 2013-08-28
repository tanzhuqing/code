CCustomMenu::CCustomMenu(){
	m_ItemCount = 0;
	m_Index = 0;
	m_MenuList = NULL;
	m_BkColor = RGB(204,119,186);
	m_SelTopColor = RGB(193,210,238);
    m_RandColor = FALSE;
}

CCustomMenu::~CCustomMenu(){
	if (m_ItemCount > 0)
	{
		delete []m_MenuList;
	}
}

void CCustomMenu::GetAllItemCount(HMENU hMenu, int &ItemCount,BOOL FirstFind){
	CMenu* pMenu = CMenu::FromHandle(hMenu);
	if (pMenu)
	{
		if (FirstFind)
		{
			ItemCount = 0;
		}
		int count = pMenu->GetMenuItemCount();
		ItemCount +=count;
		CMenu* pSubMenu = NULL;
		for (int i=0;i<count;i++)
		{
			pSubMenu = pMenu->GetSubMenu(i);
			if (pSubMenu != NULL)
			{
				GetAllItemCount(pSubMenu->m_hMenu,ItemCount,FALSE);
			}
		}
	}
}

BOOL CCustomMenu::AttachMenu(HMENU hMenu){
	Attch(hMenu);
	GetAllItemCount(hMenu,m_ItemCount);
	if (m_ItemCount > 0)
	{
		m_MenuList = new CMenuItem[m_ItemCount];
	}
	return TRUE;
}

BOOL CCustomMenu::SetMenuItemInfo(CMenu *pMenu, BOOL Toped){
	if (pMenu != NULL)
	{
		int MenuCount = pMenu->GetMenuItemCount();
		for (int i=0;i<MenuCount;i++)
		{
			pMenu->GetMenuString(i,m_MenuList[m_Index].m_MenuText,MF_BYPOSOTION);
			UINT MenuID = pMenu->GetMenuItemID(i);
			if ((MenuID==-1||MenuID==65535)&&Toped == TRUE)
			{
				MenuID = -2;
			}
			m_MenuList[m_Index].m_MenuType = MenuID;
			pMenu->ModifyMenu(i,MF_OWNERDRAW|MF_BYPOSITION|MF_STRING,m_MenuList[m_Index].m_MenuType,(LPSTR)&(m_MenuList[m_Index]));
			m_Index += 1;
			CMenu* pSubMenu = pMenu->GetSubMenu(i);
			if (pSubMenu)
			{
				SetMenuItemInfo(pSubMenu,FALSE);
			}

		}
	}
	return TRUE;
}

int CCustomMenu::GetTopMenuWidth(){
	int Count = GetMenuItemCount();
	int width = 0;
	CRect rc;
	for (int i=0;i<Count;i++)
	{
		::GetMenuItemRect(AfxGetMainWnd()->m_hWnd,m_hMenu,i,rc);
		width += rc.Width();
	}
	return width;
}

HRGN CCustomMenu::GetClienMenuRgn(){
	MENUBARINFO MenuInfo;
	memset(&MenuInfo,0,sizeof(MENUBARINFO));
	MenuInfo.cbSize = sizeof(MENUBARINFO);
	::GetMenuBarInfo(AfxGetMainWnd()->m_hWnd,OBJID_MENU,0,&MenuInfo);
    CRect rc = MenuInfo.rcBar;
	int MenuCount = GetMenuItemCount();
	CRect *pRC = new CRect[MenuCount];
	HRGN *pRgn = new HRGN[MenuCount];
	CRect winRC;
	AfxGetMainWnd()->GetWindowRect(winRC);
	int x = winRC.left;
	int y = winRC.top;
	rc.left = rc.left - x;
	rc.right = rc.right - x;
	rc.top = rc.top - y;
	rc.bottom = rc.bottom - y;

	for (int i=0;i<MenuCount;i++)
	{
		GetMenuItemRect(AfxGetMainWnd()->m_hWnd,m_hMenu,i,&pRC[i]);
		pRC[i].left = pRC[i].left - x;
		pRC[i].right = pRC[i].right - x;
		pRC[i].top = pRC[i].top - y;
        pRC[i].bottom = pRC[i].bottom - y;
		pRgn[i] = CreateRectRgn(pRC[i].left,pRC[i].top,pRC[i].right,pRC[i].bottom);
	}
	HRGN MenuRgn = CreateRectRgn(rc.left,rc.top,rc.right,rc.bottom);
	HRGN retRgn = CreateRectRgn(0,0,0,0);
	HRGN MenuClientRgn = CreateRectRgn(0,0,0,0);
	for (int j=0;j<MenuCount;j++)
	{
		CombineRgn(MenuClientRgn,MenuClientRgn,pRgn[j],RGN_OR);
	}
	CombineRgn(retRgn,MenuRgn,MenuClientRgn,RGN_DIFF);
	for (j=0;j<MenuCount;j++)
	{
		DeleteObject(pRgn[j]);
	}
	DeleteObject(MenuRgn);
	DeleteObject(MenuClientRgn);
	delete []pRC;
	delete []pRgn;
	return retRgn;
}

void CCustomMenu::SetMenuItemText(CDC *pDC,LPSTR strMenuText,CRect Rect){
	Rect.DeflateRect(20,0);
	pDC->DrawText(strMenuText,Rect,DT_SINGLELINE|DT_VCENTER|DT_LEFT);
}

void CCustomMenu::DrawTopMenuBk(CDC *pDC,CRect Rect,BOOL State){

}