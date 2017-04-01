#include "stdafx.h"
#include "ContextMenu.h"


CStringReplacerFileTable::ContextMenu::ContextMenu(CWnd*, map<string, pair<int, CString>> menuItems)
{
    _menuItems = menuItems;
    CreatePopupMenu();
    for each(pair<string, pair<int, CString>> menuItem in _menuItems)
    {
        AppendMenu(MF_STRING, menuItem.second.first, menuItem.second.second);
    }
}


void CStringReplacerFileTable::ContextMenu::SetClickPos(CPoint point)
{
    _point = point;
}


CPoint CStringReplacerFileTable::ContextMenu::GetLastClickPos()
{
    return _point;
}


void CStringReplacerFileTable::ContextMenu::EnableItem(string name, bool enable/* = true*/)
{
    UINT val = enable ? MF_ENABLED : MF_DISABLED;
    EnableMenuItem(_menuItems[name].first, val);
}


int CStringReplacerFileTable::ContextMenu::operator[](string str)
{
    return _menuItems[str].first;
}
