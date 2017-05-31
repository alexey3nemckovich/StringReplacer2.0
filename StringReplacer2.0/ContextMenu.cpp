#include "stdafx.h"
#include "ContextMenu.h"


CStringReplacerFileTable::ContextMenu::ContextMenu(CWnd*, const map<string, pair<int, CString>> &menuItems)
{
    _menuItems = menuItems;
    CreatePopupMenu();
    for each(pair<string, pair<int, CString>> menuItem in _menuItems)
    {
        AppendMenu(MF_STRING, menuItem.second.first, menuItem.second.second);
    }
}


void CStringReplacerFileTable::ContextMenu::EnableItem(const string &name, bool enable/* = true*/)
{
    UINT val = enable ? MF_ENABLED : MF_DISABLED;
    EnableMenuItem(_menuItems[name].first, val);
}


int CStringReplacerFileTable::ContextMenu::operator[](const string &str)
{
    return _menuItems[str].first;
}
