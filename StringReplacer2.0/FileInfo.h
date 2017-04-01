#pragma once
#include <string>
using namespace std;


struct FileInfo
{
    CString name;
    CString fullPath;
    FileInfo() = default;
    FileInfo(CString path, CString name)
    {
        this->fullPath = path;
        this->name = name;
    }
};
