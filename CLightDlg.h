#pragma once
#include "afxdialogex.h"


// CLightDlg 대화 상자

class CLightDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CLightDlg)

public:
	CLightDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CLightDlg();

	// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_LIGHT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
private:
	CImage m_imgLightOn;
	CImage m_imgLightOff;
	BOOL m_bLightOn;
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg void OnClickedButtonLight();
	afx_msg void OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct);
	CMFCButton m_btnLight;
};