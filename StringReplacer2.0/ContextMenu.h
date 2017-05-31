#pragma once
#include "afxwin.h"
#include "resource.h"
#include "StringReplacerFileTable.h"
#include <map>
using namespace std;


class CStringReplacerFileTable::ContextMenu
    : public CMenu
{
public:
    typedef unique_ptr<ContextMenu> Ptr;
    ContextMenu() = delete;
    ContextMenu(const ContextMenu&) = delete;
    ContextMenu(CWnd*, const map<string, pair<int, CString>>&);
    void EnableItem(const string&, bool = true);
    virtual ~ContextMenu() = default;
    //void SetClickPos(CPoint);
    //CPoint GetLastClickPos();
    int operator[](const string &str);
private:
    //CPoint _point;
    map<string, pair<int, CString>> _menuItems;
};
