#include "stdafx.h"


string CStringToString(CString cstr)
{
    CT2CA pszConvertedAnsiString(cstr);
    string str(pszConvertedAnsiString);
    return str;
}
