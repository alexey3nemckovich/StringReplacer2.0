#pragma once
#include <string>
#include "FileInfo.h"
#include "FileProcessingStatus.h"
using namespace std;


struct StringReplacerFileInfo
    :FileInfo
{
    FILE_PROCESSING_STATUS status;
    int countMacthes = 0;
    vector<string> processResult;
    StringReplacerFileInfo()
    {
        status = FILE_PROCESSING_STATUS::FILE_NOT_CHOSEN;
        countMacthes = 0;
    }
    StringReplacerFileInfo(CString path, CString name)
        : FileInfo(path, name)
    {
        status = FILE_PROCESSING_STATUS::FILE_CHOSEN;
        countMacthes = 0;
    }
};
