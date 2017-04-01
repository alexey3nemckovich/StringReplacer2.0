#pragma once
#include "StringReplacerFileTable.h"


class CChildView : public CWnd
{
// Construction
public:
	CChildView();

// Attributes
public:

public:
	virtual ~CChildView();

protected:
    virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
	// Generated message map functions
protected:
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnPaint();
    afx_msg void OnSize(UINT, int, int);
	DECLARE_MESSAGE_MAP()
private:
    CStringReplacerFileTable m_wndTable;
};