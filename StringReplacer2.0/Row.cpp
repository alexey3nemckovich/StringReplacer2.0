#include "stdafx.h"
#include "Row.h"


BEGIN_MESSAGE_MAP(CStringReplacerFileTable::Row, CWnd)
    ON_WM_SIZE()
END_MESSAGE_MAP()


BOOL CStringReplacerFileTable::Row::Create(CStringReplacerFileTable *table, const CRect &rect)
{
    if (!CWnd::Create(
        NULL,
        NULL,
        AFX_WS_DEFAULT_VIEW | WS_VISIBLE | WS_CHILD,
        rect,
        table,
        IDGenerator::GetInstance()->GenerateFreeIDForControlOf(table)))
    {
        return false;
    }

    _table = table;
    _number = table->_rows.size();
    return true;
}


int CStringReplacerFileTable::Row::GetNumber() const
{
    return _number;
}


void CStringReplacerFileTable::Row::SetNumber(int number)
{
    _number = number;
}
