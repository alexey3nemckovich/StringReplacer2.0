#include "stdafx.h"
#include "StringReplacer2.0.h"
#include "ChildView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


CChildView::CChildView()
{

}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, CWnd)
    ON_WM_CREATE()
	ON_WM_PAINT()
    ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!CWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(NULL, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), NULL);

	return TRUE;
}


afx_msg int CChildView::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;

    CRect rect;
    GetClientRect(&rect);
    GetParent()->GetClientRect(&rect);
    if (!m_wndTable.Create(rect, this))
    {
        TRACE0("Failed to create table window\n");
        return -1;
    }
    
    return 0;
}


void CChildView::OnPaint()
{
	CPaintDC dc(this);
}


afx_msg void CChildView::OnSize(UINT type, int cx, int cy)
{
    CRect rect;
    rect.top = rect.left = 0;
    rect.right = cx;
    rect.bottom = cy;
    m_wndTable.MoveWindow(rect);
}