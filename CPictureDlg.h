#pragma once
#include "afxdialogex.h"


// CPictureDlg 대화 상자

class CPictureDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CPictureDlg)

public:
	CPictureDlg(CWnd* pParent = nullptr);   // 표준 생성자입니다.
	virtual ~CPictureDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PICTURE_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.
	virtual void PostNcDestroy();
	virtual void OnCancel();
	virtual void OnOK();
	DECLARE_MESSAGE_MAP()
public:
	CImage m_bmpPicture;
	CImage m_bmpPicture1;
	CImage m_bmpPicture2;
	CImage m_bmpPicture3;
	CImage* m_bmpPictureCurrent;
	int m_selectedPictureRadio=0;
	virtual BOOL OnInitDialog();
	afx_msg void OnClickedRadioFail1();
	afx_msg void OnClickedRadioFail2();
	afx_msg void OnClickedRadioSuccess();   
	
	afx_msg void OnClickedButtonSubmit();
	afx_msg void OnPaint();
};
//여기서 작업하셈