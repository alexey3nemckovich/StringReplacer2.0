#pragma once
#include "afxwin.h"
#include <vector>
#include <memory>
#include "Row.h"
#include <functional>
#include <thread>
#include <mutex>
#include "StringReplacer.h"
#include <fstream>
using namespace std;


class CStringReplacerFileTable::FileInfoRow
    :public Row
{
public:
    virtual BOOL Create(CStringReplacerFileTable*, const CRect &rect, const CString &filePath = L"", const CString &fileName = L"");
public:
    //control interface
    typedef unique_ptr<FileInfoRow> Ptr;
    FileInfoRow() = default;
    virtual ~FileInfoRow() override;
    virtual void SetNumber(int number) override;
protected:
    afx_msg virtual void OnSize(UINT, int, int) override;
    afx_msg void OnRButtonUp(UINT, CPoint);
    afx_msg virtual void OnRangeCmds(UINT);
    DECLARE_MESSAGE_MAP()
    //actions
private:
    void ChooseFile();
    void SetFileOnProcess();
    void CancelProcessing();
    void SaveProcessResult();
    //ui interface
private:
    void OnAction();
    void OnNewMatch();
    void OnDeleteRow();
    void OnFileProcessed(const vector<string>&);
    void UpdateRenderStatus();
private:
    ContextMenuPtr _contextMenu;
    StringReplacerFileInfo _fileInfo;
    CStatic m_staticFileName, m_staticStatus, m_staticCountMatches;
    CButton m_btnAction, m_btnDelete;
private:
    thread _process;
    bool _onDelete = false;
    StringReplacer::OnNewMatchCallback _onNewMatchCallback;
    StringReplacer::OnFileProcessedCallback _onFileProcessedCallback;
    FILE_PROCESSING_STATUS _renderingStatus = FILE_PROCESSING_STATUS::UNDEFINED;
};
