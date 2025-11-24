// EscapeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Escape.h"
#include "EscapeDlg.h"
#include "afxdialogex.h"
#include "CPictureDlg.h"
#include "CFailDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

protected:
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CEscapeDlg 대화 상자
CEscapeDlg::CEscapeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_ESCAPE_DIALOG, pParent), m_seconds(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CEscapeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CEscapeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_MOUSEMOVE()
	ON_WM_CTLCOLOR()
	ON_WM_LBUTTONDOWN()
	ON_BN_CLICKED(IDC_BUTTON_HIDE, &CEscapeDlg::OnBnClickedButtonHide)
	ON_BN_CLICKED(IDC_BUTTON_OUT, &CEscapeDlg::OnBnClickedButtonOut)
	ON_WM_TIMER()
END_MESSAGE_MAP()


// CEscapeDlg 메시지 처리기
BOOL CEscapeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 0초로 초기화
	m_seconds = 0;

	// 타이머 시작 (1초마다)
	SetTimer(1, 1000, nullptr);

	// 글꼴 설정
	m_fontTimer.CreatePointFont(200, _T("굴림"));
	GetDlgItem(IDC_STATIC_TIMER)->SetFont(&m_fontTimer);

	// 배경 이미지 로드
	if (FAILED(m_imgBg.Load(L"res/image/EscapeMainPage.bmp")))
	{
		AfxMessageBox(L"배경 이미지 로드 실패!");
	}

	// 다이얼로그 크기 설정
	int nWidth = 1026;
	int nHeight = 770;
	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	// 시스템 메뉴 "정보..." 추가
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);  // 큰 아이콘
	SetIcon(m_hIcon, FALSE); // 작은 아이콘

	// 마우스 좌표 표시용 static 제일 위로
	CWnd* pStatic = GetDlgItem(IDC_STATIC);
	if (pStatic)
	{
		pStatic->SetWindowPos(&wndTop, 0, 0, 0, 0,
			SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE);
	}

	return TRUE;
}

void CEscapeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

void CEscapeDlg::OnPaint()
{
	CPaintDC dc(this);
	if (!m_imgBg.IsNull())
	{
		CRect rect;
		GetClientRect(rect);
		m_imgBg.Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
	}

	if (IsIconic())
	{
		CPaintDC dc(this);
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

HCURSOR CEscapeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CEscapeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect bookList(0, 0, 448, 241);
	CRect laptop(60, 302, 339, 479);
	CRect light(443, 261, 557, 487);
	CRect safe(337, 655, 517, 746);
	CRect frame(825, 26, 1001, 248);

	if (bookList.PtInRect(point)) {
		MessageBox(L"책장");
	}
	else if (laptop.PtInRect(point)) {
		MessageBox(L"노트북");
	}
	else if (light.PtInRect(point)) {
		MessageBox(L"전등");
	}
	else if (safe.PtInRect(point)) {
		MessageBox(L"금고");
	}
	else if (frame.PtInRect(point)) {
		CPictureDlg picturedlg;
		picturedlg.DoModal();
		
	}

	CDialogEx::OnLButtonDown(nFlags, point);
}

void CEscapeDlg::OnBnClickedButtonHide()
{
	m_imgBg.Destroy();

	if (FAILED(m_imgBg.Load(L"res/image/EscapeMainPageHide.bmp")))
	{
		AfxMessageBox(L"이미지 로드 실패!");
		return;
	}

	Invalidate(TRUE);
	UpdateWindow();
}

void CEscapeDlg::OnBnClickedButtonOut()
{
	m_imgBg.Destroy();

	if (FAILED(m_imgBg.Load(L"res/image/EscapeMainPage.bmp")))
	{
		AfxMessageBox(L"이미지 로드 실패!");
		return;
	}

	Invalidate(TRUE);
	UpdateWindow();
}

void CEscapeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_seconds++;
		int minutes = m_seconds / 60;
		int seconds = m_seconds % 60;

		CString text;
		text.Format(L"%02d:%02d", minutes, seconds);

		SetDlgItemText(IDC_STATIC_TIMER, text);
	}

	CDialogEx::OnTimer(nIDEvent);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 추가 초기화 코드

	return TRUE; // 포커스를 컨트롤에 설정하지 않을 경우 TRUE 반환
}
