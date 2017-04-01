#include "stdafx.h"
#include "HeaderRow.h"


BOOL CStringReplacerFileTable::HeaderRow::Create(CStringReplacerFileTable* table, CRect &rect, vector<CString> colsTexts)
{
    if (!CStringReplacerFileTable::Row::Create(table, rect))
    {
        return false;
    }

    m_staticCols = vector<CStatic>(_table->_colsCount);
    for (int i = 0; i < table->_colsCount; i++)
    {
        m_staticCols[i].Create(colsTexts[i], WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTERIMAGE | SS_CENTER, CRect(), this, IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this));
    }
    _inited = true;
    OnSize(NULL, rect.right - rect.left, rect.bottom - rect.top);

    return _inited;
}


CStringReplacerFileTable::HeaderRow::~HeaderRow()
{
    for (int i = 0; i < m_staticCols.size(); i++)
    {
        m_staticCols[i].DestroyWindow();
    }
}


void CStringReplacerFileTable::HeaderRow::SetNumber(int number)
{

}


afx_msg void CStringReplacerFileTable::HeaderRow::OnSize(UINT, int cx, int cy)
{
    if (_inited)
    {
        CRect rect;
        rect.left = rect.top = 0;
        rect.bottom = cy;
        rect.right = _table->_cellWidth;
        for (int i = 0; i < _table->_colsCount; i++)
        {
            m_staticCols[i].MoveWindow(&rect, true);
            rect.left = rect.right;
            if (i != _table->_colsCount - 2)
            {
                rect.right += _table->_cellWidth;
            }
            else
            {
                rect.right = cx;
            }
        }
    }
}
