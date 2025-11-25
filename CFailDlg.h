#pragma once
#include "afxdialogex.h"


// CFailDlg 대화 상자

class CFailDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CFailDlg)

public:
	CFailDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CFailDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_FAIL_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	CImage m_bmpFailImage;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRetryButton();
	afx_msg void OnClickedExitButton();
	afx_msg void OnPaint();
};
