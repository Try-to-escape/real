#pragma once
#include "afxdialogex.h"


// CBookDlg 대화 상자

class CBookDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CBookDlg)

private:
	CImage m_imgWBook; // 윈도우 책 이미지
	CImage m_imgFBook; // 가짜 책 이미지


public:
	CBookDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CBookDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_BOOK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	int m_nBookType; // 0=FBook, 1=WBook
	virtual BOOL OnInitDialog();
private:
	CImage* m_pBookImage;
public:
	afx_msg void OnPaint();
};