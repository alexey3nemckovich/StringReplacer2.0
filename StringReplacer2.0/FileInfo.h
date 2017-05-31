#pragma once
#include <string>
using namespace std;


struct FileInfo
{
    CString name;
    CString fullPath;
    FileInfo() = default;
    FileInfo(const CString &path, const CString &name)
    {
        this->fullPath = path;
        this->name = name;
    }
};
