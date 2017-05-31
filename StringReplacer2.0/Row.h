#pragma once
#include "afxwin.h"
#include <vector>
#include <memory>
#include "StringReplacerFileTable.h"
using namespace std;


class CStringReplacerFileTable::Row abstract
    : public CWnd
{
public:
    virtual BOOL Create(CStringReplacerFileTable*, const CRect &rect);
public:
    typedef unique_ptr<CStringReplacerFileTable::Row> Ptr;
    Row() = default;
    Row(const Row&) = delete;
    int GetNumber() const;
    virtual ~Row() = default;
    virtual void SetNumber(int number) = 0;
protected:
    afx_msg virtual void OnSize(UINT, int, int) = 0;
    DECLARE_MESSAGE_MAP()
protected:
    int _number;
    bool _inited = false;
    CStringReplacerFileTable *_table;
};
