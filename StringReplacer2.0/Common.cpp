#include "stdafx.h"


string CStringToString(const CString &cstr)
{
    CT2CA pszConvertedAnsiString(cstr);
    string str(pszConvertedAnsiString);
    return str;
}
