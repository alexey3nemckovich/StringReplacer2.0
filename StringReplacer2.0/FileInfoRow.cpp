#include "stdafx.h"
#include "FileInfoRow.h"
#include "ContextMenu.h"


BEGIN_MESSAGE_MAP(CStringReplacerFileTable::FileInfoRow, CWnd)
    ON_WM_SIZE()
    ON_WM_RBUTTONUP()
    ON_COMMAND_RANGE(MIN_ID, MAX_ID, CStringReplacerFileTable::FileInfoRow::OnRangeCmds)
END_MESSAGE_MAP()


BOOL CStringReplacerFileTable::FileInfoRow::Create(CStringReplacerFileTable* table, CRect &rect, CString filePath/* = L""*/, CString fileName/* = L""*/)
{
    if (!CStringReplacerFileTable::Row::Create(table, rect))
    {
        return false;
    }

    _onNewMatchCallback = [this]() 
    {
        this->OnNewMatch();
    };
    _onFileProcessedCallback = [this](vector<string> res) 
    {
        this->OnFileProcessed(res); 
    };
    function<void(string)> _onFileProcessedCallback;
#define DELETE_TEXT L"Click to delete record"
#define BS_STYLE WS_VISIBLE | WS_CHILD | BS_PUSHBUTTON | BS_MULTILINE
#define SS_STYLE WS_CHILD | WS_VISIBLE | WS_BORDER | SS_CENTERIMAGE | SS_CENTER
    if (filePath != L"")
    {
        _fileInfo = StringReplacerFileInfo(filePath, fileName);
    }
    map<string, pair<int, CString>> menuItemsMap = {
        { "add",{ IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this), L"Add row" } },
        { "delete",{ IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this), L"Delete row" } }
    };
    _contextMenu = ContextMenu::Ptr(new ContextMenu(this, menuItemsMap));
    m_staticFileName.Create(L"", SS_STYLE, CRect(), this, IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this));
    m_staticStatus.Create(L"", SS_STYLE, CRect(), this, IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this));
    m_staticCountMatches.Create(L"", SS_STYLE, CRect(), this, IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this));
    m_btnAction.Create(L"", BS_STYLE, CRect(), this, IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this));
    m_btnDelete.Create(DELETE_TEXT, BS_STYLE, CRect(), this, IDGenerator::GetInstance()->GenerateFreeIDForControlOf(this));
    UpdateRenderStatus();
    _inited = true;
    OnSize(NULL, rect.right - rect.left, rect.bottom - rect.top);

    return _inited;
}


CStringReplacerFileTable::FileInfoRow::~FileInfoRow()
{
    m_staticFileName.DestroyWindow();
    m_staticStatus.DestroyWindow();
    m_staticCountMatches.DestroyWindow();
    m_btnAction.DestroyWindow();
    m_btnDelete.DestroyWindow();
    if (_process.joinable())
    {
        TerminateThread(_process.native_handle(), 0);
        _process.join();
    }
}


void CStringReplacerFileTable::FileInfoRow::SetNumber(int number)
{
    _number = number;
    CRect rect;
    GetClientRect(&rect);
    OnSize(NULL, rect.right, rect.bottom);
}


void CStringReplacerFileTable::FileInfoRow::ChooseFile()
{
    CFileDialog fileDialog(true);
    int result = fileDialog.DoModal();
    if (result == IDOK)
    {
        _fileInfo.fullPath = fileDialog.GetPathName();
        _fileInfo.name = fileDialog.GetFileName();
        _fileInfo.status = FILE_PROCESSING_STATUS::FILE_CHOSEN;
        UpdateRenderStatus();
    }
}


void CStringReplacerFileTable::FileInfoRow::SetFileOnProcess()
{
    if (_process.joinable())
    {
        _process.join();
    }
    _process = thread(&StringReplacer::ProcessFile, CStringToString(_fileInfo.fullPath), _onNewMatchCallback, _onFileProcessedCallback);
    _fileInfo.status = FILE_PROCESSING_STATUS::ON_PROCESS;
    UpdateRenderStatus();
}


void CStringReplacerFileTable::FileInfoRow::CancelProcessing()
{
    TerminateThread(_process.native_handle(), 0);
    _fileInfo.countMacthes = 0;
    _fileInfo.status = FILE_PROCESSING_STATUS::FILE_CHOSEN;
    UpdateRenderStatus();
}


void CStringReplacerFileTable::FileInfoRow::SaveProcessResult()
{
    CFileDialog fileDialog(false);
    int result = fileDialog.DoModal();
    string pathName = CStringToString(fileDialog.GetPathName());
    if (result == IDOK)
    {
        StringReplacer::SaveStringsToFile(pathName, _fileInfo.processResult);
    }
}


void CStringReplacerFileTable::FileInfoRow::OnAction()
{
    switch (_fileInfo.status)
    {
    case FILE_PROCESSING_STATUS::FILE_NOT_CHOSEN:
        ChooseFile();
        break;
    case FILE_PROCESSING_STATUS::FILE_CHOSEN:
        SetFileOnProcess();
        break;
    case FILE_PROCESSING_STATUS::ON_PROCESS:
        CancelProcessing();
        break;
    case FILE_PROCESSING_STATUS::PROCESSED:
        SaveProcessResult();
        break;
    }
}


void CStringReplacerFileTable::FileInfoRow::OnNewMatch()
{
    CString str;
    str.Format(L"%d", ++_fileInfo.countMacthes);
    m_staticCountMatches.SetWindowText(str);
}


void CStringReplacerFileTable::FileInfoRow::OnDeleteRow()
{
    _onDelete = true;
    _table->SendMessage(DELETE_ROW_MSG, GetNumber(), NULL);
}


void CStringReplacerFileTable::FileInfoRow::OnFileProcessed(vector<string> res)
{
    _fileInfo.processResult = res;
    _fileInfo.status = FILE_PROCESSING_STATUS::PROCESSED;
    UpdateRenderStatus();
}


void CStringReplacerFileTable::FileInfoRow::UpdateRenderStatus()
{
    if (_renderingStatus != _fileInfo.status)
    {
        CString fileName = L"", statusText = L"", countMatchesText = L"", btnActionText = L"";
        m_btnDelete.EnableWindow(true);
        _contextMenu->EnableItem("delete", true);
        switch (_fileInfo.status)
        {
        case FILE_PROCESSING_STATUS::FILE_NOT_CHOSEN:
            statusText = FILE_NOT_CHOSEN_TEXT;
            fileName = "-";
            countMatchesText = "-";
            btnActionText = "Click to choose file";
            break;
        case FILE_PROCESSING_STATUS::FILE_CHOSEN:
            statusText = FILE_CHOSEN_TEXT;
            fileName = _fileInfo.name;
            countMatchesText = "-";
            btnActionText = "Click to process file";
            break;
        case FILE_PROCESSING_STATUS::ON_PROCESS:
            statusText = ON_PROCESS_TEXT;
            countMatchesText = "0";
            btnActionText = "Click to cancel";
            m_btnDelete.EnableWindow(false);
            _contextMenu->EnableItem("delete", false);
            break;
        case FILE_PROCESSING_STATUS::PROCESSED:
            statusText = PROCESSED_TEXT;
            btnActionText = "Click to save result to file";
            break;
        }
        m_staticStatus.SetWindowTextW(statusText);
        if (!fileName.IsEmpty()) m_staticFileName.SetWindowText(fileName);
        if (!countMatchesText.IsEmpty()) m_staticCountMatches.SetWindowTextW(countMatchesText);
        m_btnAction.SetWindowTextW(btnActionText);
    }
}


afx_msg void CStringReplacerFileTable::FileInfoRow::OnSize(UINT, int cx, int cy)
{
    if (_inited)
    {
        CRect cellRect;
        cellRect.left = cellRect.top = 0;
        cellRect.bottom = cellRect.top + _table->_cellHeight;
        cellRect.right = _table->_cellWidth;
        m_staticFileName.MoveWindow(cellRect, true);
        cellRect.left = cellRect.right;
        cellRect.right += _table->_cellWidth;
        m_staticStatus.MoveWindow(cellRect, true);
        cellRect.left = cellRect.right;
        cellRect.right += _table->_cellWidth;
        m_staticCountMatches.MoveWindow(cellRect, true);
        cellRect.left = cellRect.right;
        cellRect.right += _table->_cellWidth;
        m_btnAction.MoveWindow(cellRect, true);
        cellRect.left = cellRect.right;
        cellRect.right = _table->_width;
        m_btnDelete.MoveWindow(cellRect, true);
    }
}


afx_msg void CStringReplacerFileTable::FileInfoRow::OnRButtonUp(UINT, CPoint point)
{
    CRect rc;
    GetWindowRect(&rc);
    _contextMenu->SetClickPos(point);
    if (_table->_rows.size() == _table->_visibleRowsCount - 1)
    {
        _contextMenu->EnableItem("add", false);
    }
    else
    {
        _contextMenu->EnableItem("add", true);
    }
    _contextMenu->TrackPopupMenu(TPM_LEFTALIGN | TPM_LEFTBUTTON, rc.left + point.x, rc.top + point.y, this);
}


afx_msg void CStringReplacerFileTable::FileInfoRow::OnRangeCmds(UINT id)
{
    if ((*_contextMenu)["add"] == id)
    {
        _table->SendMessage(ADD_ROW_MSG, NULL, NULL);
    }
    if ((*_contextMenu)["delete"] == id)
    {
        _table->SendMessage(DELETE_ROW_MSG, GetNumber(), NULL);
    }
    if (!_onDelete)
    {
        if (m_btnAction.GetDlgCtrlID() == id)
        {
            OnAction();
        }
        if (m_btnDelete.GetDlgCtrlID() == id)
        {
            OnDeleteRow();
        }
    }
}
