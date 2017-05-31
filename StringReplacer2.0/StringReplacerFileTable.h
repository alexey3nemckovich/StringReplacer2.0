#pragma once
#include "afxwin.h"
#include <vector>
#include <memory>
#include <string>
#include "StringReplacerFileInfo.h"
using namespace std;


#define DELETE_ROW_MSG WM_USER + 100
#define ADD_ROW_MSG    WM_USER + 101
class CStringReplacerFileTable :
    public CWnd
{
public:
    class Row;
    class HeaderRow;
    class FileInfoRow;
    class ContextMenu;
    typedef unique_ptr<ContextMenu> ContextMenuPtr;
    typedef unique_ptr<HeaderRow> HeaderRowPtr;
    typedef unique_ptr<FileInfoRow> FileInfoRowPtr;
public:
    //Wnd interface
    BOOL Create(const RECT&, CWnd*, int cRows = 0);
public:
    //Table interface
    CStringReplacerFileTable();
    virtual ~CStringReplacerFileTable();
    void AddRow();
    void DeleteRow(int);
    //message mapping
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    virtual afx_msg void OnSize(UINT, int, int);
    afx_msg void OnRButtonUp(UINT, CPoint);
    afx_msg void OnRangeCmds(UINT);
    afx_msg LRESULT OnDeleteRow(WPARAM, LPARAM);
    afx_msg LRESULT OnAddRow(WPARAM, LPARAM);
    afx_msg BOOL OnNotify(WPARAM, LPARAM, LRESULT*);
    DECLARE_MESSAGE_MAP()
    //size properties
private:
    int _width;
    int _height;
    int _cellWidth;
    int _cellHeight;
    const int _colsCount = 5;
    const int _visibleRowsCount = 10;
    //logic properties
private:
    bool _inited = false;
    //table properties
private:
    ContextMenuPtr _contextMenu;
    HeaderRowPtr _header;
    vector<FileInfoRowPtr> _rows;
private:
    void ForceRepaint();
};
