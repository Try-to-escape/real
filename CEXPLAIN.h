#pragma once
#include "afxdialogex.h"


// CEXPLAIN 대화 상자

class CExplainDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CExplainDlg)

public:
	CExplainDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CExplainDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXPLAIN };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CImage m_imgBg;
	afx_msg void OnPaint();
};
