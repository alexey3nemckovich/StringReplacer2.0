#include "stdafx.h"
#include "StringReplacerFileTable.h"
#include "StringReplacerFileTableControls.h"


BEGIN_MESSAGE_MAP(CStringReplacerFileTable, CWnd)
    ON_WM_SIZE()
    ON_WM_CREATE()
    ON_WM_RBUTTONUP()
    ON_MESSAGE(ADD_ROW_MSG, OnAddRow)
    ON_MESSAGE(DELETE_ROW_MSG, OnDeleteRow)
    ON_COMMAND_RANGE(MIN_ID, MAX_ID, OnRangeCmds)
    //ON_NOTIFY()
END_MESSAGE_MAP()


CStringReplacerFileTable::CStringReplacerFileTable() = default;


CStringReplacerFileTable::~CStringReplacerFileTable()
{
    CWnd::~CWnd();
}


BOOL CStringReplacerFileTable::Create(const RECT& rect, CWnd* pParentWnd, int cRows/* = 0*/)
{
    if (!CWnd::Create(
        NULL,
        NULL,
        AFX_WS_DEFAULT_VIEW | WS_VSCROLL | WS_VISIBLE | WS_CHILD,
        rect,
        pParentWnd,
        IDGenerator::GetInstance()->GenerateFreeIDForControlOf(pParentWnd)))
    {
        return false;
    }

    static vector<CString> headerColumns = { CString("File name"), CString("Status"), CString("Count matches"), CString("Action"), CString("Optional") };
    CRect headerRect;
    headerRect.top = headerRect.left = 0;
    headerRect.right = _width;
    headerRect.bottom = _cellHeight;
    _header = HeaderRow::Ptr(new HeaderRow());
    _header->Create(this, headerRect, headerColumns);
    map<string, pair<int, CString>> menuItemsMap = {
        {"add", {IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this), L"Add row"}}
    };
    _contextMenu = ContextMenu::Ptr(new ContextMenu(this, menuItemsMap));
    AddRow();

    return _inited = true;
}


void CStringReplacerFileTable::AddRow()
{
    CRect rect;
    rect.left = 0;
    rect.top = _cellHeight * (_rows.size()+1);
    rect.bottom = rect.top + _cellHeight;
    rect.right = _width;
    _rows.push_back(FileInfoRow::Ptr(new FileInfoRow()));
    _rows[_rows.size() - 1]->Create(this, rect);
}


void CStringReplacerFileTable::DeleteRow(int number)
{
    for (int i = number; i < _rows.size(); i++)
    {
        _rows[i]->SetNumber(i);
    }
    _rows.erase(_rows.begin() + number - 1);
    ForceRepaint();
}


void CStringReplacerFileTable::ForceRepaint()
{
    OnSize(NULL, _width, _height);
    CRect rcWin;
    GetWindowRect(rcWin);
    ScreenToClient(rcWin);
    HWND hWnd = GetSafeHwnd();
    ::SetWindowPos(hWnd, HWND_TOP, rcWin.left,
        rcWin.top, rcWin.right - rcWin.left,
        rcWin.bottom - rcWin.top, SWP_FRAMECHANGED);
}


afx_msg int CStringReplacerFileTable::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
    if (CWnd::OnCreate(lpCreateStruct) == -1)
        return -1;
    
    return 0;
}

    
afx_msg void CStringReplacerFileTable::OnSize(UINT type, int cx, int cy)
{
    _width = cx;
    _height = cy;
    _cellWidth = _width / _colsCount;
    _cellHeight = _height / _visibleRowsCount;
    CRect rect;
    rect.top = rect.left = 0;
    rect.right = _width;
    rect.bottom = _cellHeight;
    if (_inited)
    {
        _header->MoveWindow(rect);
        for (int i = 0; i < _rows.size(); i++)
        {
            rect.top = rect.bottom;
            rect.bottom += _cellHeight;
            _rows[i]->MoveWindow(rect);
        }
    }
}


afx_msg void CStringReplacerFileTable::OnRButtonUp(UINT, CPoint point)
{
    CRect rc;
    GetWindowRect(&rc);
    if (_rows.size() == _visibleRowsCount - 1)
    {
        _contextMenu->EnableItem("add", false);
    }
    else
    {
        _contextMenu->EnableItem("add", true);
    }
    _contextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rc.left + point.x, rc.top + point.y, this);
}


afx_msg void CStringReplacerFileTable::OnRangeCmds(UINT id)
{
    if ((*_contextMenu)["add"] == id)
    {
        AddRow();
    }
}


afx_msg LRESULT CStringReplacerFileTable::OnDeleteRow(WPARAM wParam, LPARAM)
{
    DeleteRow(wParam);
    return 0;
}


afx_msg LRESULT CStringReplacerFileTable::OnAddRow(WPARAM, LPARAM)
{
    AddRow();
    return 0;
}


afx_msg BOOL CStringReplacerFileTable::OnNotify(WPARAM, LPARAM, LRESULT*)
{
    Beep(500, 100);
    return TRUE;
}
