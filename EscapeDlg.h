
// EscapeDlg.h: 헤더 파일
//

#pragma once
#include "CBookListDlg.h"
#include "CLightDlg.h"
#include "CLockerDlg.h"
#include "CPictureDlg.h"

// CEscapeDlg 대화 상자
class CEscapeDlg : public CDialogEx
{
// 생성입니다.
public:
	CEscapeDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ESCAPE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.       

// 구현입니다.
protected:
	HICON m_hIcon;

	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg LRESULT OnLockerSuccess(WPARAM wParam, LPARAM lParam);

	DECLARE_MESSAGE_MAP()

	CImage m_imgBg;
public:


	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnBnClickedButtonHide();
	afx_msg void OnBnClickedButtonOut();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedButtonEnd();
	int m_seconds;
	CFont m_fontTimer;

	//120초 후 최초 띄우기용
	int m_prevSecond;
	//숨기버튼 클릭 여부
	bool m_bHideRequested;
	//숨은 시각
	int m_nHideSecond;
	//숨은 후 타이머 시작
	bool m_bHideTimer;
	//숨은 이미지 표지 타이머 시작
	bool m_bIsHiddenImage;
	//숨은 이미지 표지 시작 시간
	int  m_nHiddenImageTimer;  
	// 현재 엔딩 이미지 인덱스
	int  m_nCurrentEndingIndex; 
	CImage m_imgHint;
	CImage m_imgEnding[6];
	CImage* m_pCurrentImage;
	CButton m_btnHide;
	CButton m_btnOut;
	CStatic m_btnTimer;
	CButton m_btnEnd;
	CImage m_imgProfessorComing;

	//다이얼로그 변수 관리
	CBookListDlg* m_pBookListDlg;
	CLightDlg* m_pLightDlg;
	CLockerDlg* m_pLockerDlg;
	CPictureDlg* m_pPictureDlg;
	void CloseAllDialogs();
	CImage m_imgHide;
	CImage m_imgOut;
};
