#pragma once
#include "afxdialogex.h"
#include "CBookDlg.h"

// CBookListDlg 대화 상자

class CBookListDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookListDlg)

public:
	CBookListDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBookListDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOKLIST };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
private:
	CImage m_imgBg;
public:
	afx_msg void OnClickedButtonFbook();
	afx_msg void OnClickedButtonWbook();
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	CMFCButton m_btnFBook;
	CMFCButton m_btnWBook;
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
};