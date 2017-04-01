#pragma once
#include "afxwin.h"
#include <vector>
#include <memory>
#include "Row.h"
using namespace std;


class CStringReplacerFileTable::HeaderRow
    :public Row
{
public:
    virtual BOOL Create(CStringReplacerFileTable*, CRect &rect, vector<CString> colsTexts);
public:
    typedef unique_ptr<HeaderRow> Ptr;
    HeaderRow() = default;
    virtual ~HeaderRow() override;
    virtual void SetNumber(int number) override;
public:
    afx_msg virtual void OnSize(UINT, int, int) override;
private:
    vector<CStatic> m_staticCols;
};
