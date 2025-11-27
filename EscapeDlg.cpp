// EscapeDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "Escape.h"
#include "EscapeDlg.h"
#include "afxdialogex.h"
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
	DDX_Control(pDX, IDC_BUTTON_HIDE, m_btnHide);
	DDX_Control(pDX, IDC_BUTTON_OUT, m_btnOut);
	DDX_Control(pDX, IDC_STATIC_TIMER, m_btnTimer);
	DDX_Control(pDX, IDC_BUTTON_END, m_btnEnd);
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
	ON_BN_CLICKED(IDC_BUTTON_END, &CEscapeDlg::OnBnClickedButtonEnd)
	ON_MESSAGE(WM_USER + 1, &CEscapeDlg::OnLockerSuccess)
END_MESSAGE_MAP()



// CEscapeDlg 메시지 처리기
BOOL CEscapeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 값 초기화
	m_seconds = 0;
	m_bHideRequested = FALSE;
	m_bHideTimer = FALSE;
	m_nHideSecond = 0;
	m_bIsHiddenImage = FALSE;
	m_nHiddenImageTimer = 0;
	m_pBookListDlg = nullptr;
	m_pLightDlg = nullptr;
	m_pLockerDlg = nullptr;
	m_pPictureDlg = nullptr;

	//컨트롤 설정
	m_btnEnd.ShowWindow(SW_HIDE);
	m_btnHide.SetWindowPos(NULL, 65, 647, 100, 40, SWP_NOZORDER);
	m_btnOut.SetWindowPos(NULL, 180, 647, 100, 40, SWP_NOZORDER);
	m_btnEnd.SetWindowPos(NULL,826, 654, 100, 40, SWP_NOZORDER);
	m_btnTimer.SetWindowPos(NULL, 826, 654, 100, 40, SWP_NOZORDER);

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
	m_pCurrentImage = &m_imgBg;


	//가람파트 이미지 불러오기
	m_imgHint.Load(L"res/image/EscapeMainPageHint.bmp");
	m_imgEnding[0].Load(L"res/image/EscapeEnding1.bmp");
	m_imgEnding[1].Load(L"res/image/EscapeEnding2.bmp");
	m_imgEnding[2].Load(L"res/image/EscapeEnding3.bmp");
	m_imgEnding[3].Load(L"res/image/EscapeEnding4.bmp");
	m_imgEnding[4].Load(L"res/image/EscapeEnding5.bmp");
	m_imgEnding[5].Load(L"res/image/EscapeEnding6.bmp");
	m_imgProfessorComing.Load(L"res/image/EscapeMainPageAttack.bmp");

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
	if (m_pCurrentImage && !m_pCurrentImage->IsNull())
	{
		m_pCurrentImage->Draw(dc, 0, 0);
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

//영역 클릭시 대화상자 
void CEscapeDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	CRect bookList(0, 0, 448, 241);
	CRect laptop(60, 302, 339, 479);
	CRect light(443, 261, 557, 487);
	CRect safe(337, 655, 517, 746);
	CRect frame(825, 26, 1001, 248);

	if (bookList.PtInRect(point)) {
		if (m_pBookListDlg == nullptr || !::IsWindow(m_pBookListDlg->m_hWnd))
		{
			m_pBookListDlg = new CBookListDlg;
			if (m_pBookListDlg->Create(IDD_DIALOG_BOOKLIST, this))
				m_pBookListDlg->ShowWindow(SW_SHOW);
			else {
				delete m_pBookListDlg;
				m_pBookListDlg = nullptr;
			}
		}
		else {
			m_pBookListDlg->SetForegroundWindow();
		}
	}
	else if (laptop.PtInRect(point)) {
		MessageBox(L"노트북이 잠겨있다...");
	}
	else if (light.PtInRect(point)) {
		if (m_pLightDlg == nullptr || !::IsWindow(m_pLightDlg->m_hWnd))
		{
			m_pLightDlg = new CLightDlg;
			if (m_pLightDlg->Create(IDD_DIALOG_LIGHT, this))
				m_pLightDlg->ShowWindow(SW_SHOW);
			else {
				delete m_pLightDlg;
				m_pLightDlg = nullptr;
			}
		}
		else {
			m_pLightDlg->SetForegroundWindow();
		}
	}
	else if (safe.PtInRect(point)) {
		if (m_pLockerDlg == nullptr || !::IsWindow(m_pLockerDlg->m_hWnd))
		{
			m_pLockerDlg = new CLockerDlg;
			if (m_pLockerDlg->Create(IDD_DIALOG_LOCKER, this))
				m_pLockerDlg->ShowWindow(SW_SHOW);
			else {
				delete m_pLockerDlg;
				m_pLockerDlg = nullptr;
			}
		}
		else {
			m_pLockerDlg->SetForegroundWindow();
		}
	}

	////엔딩
	//if (lockerDlg.m_bSuccess)
	//{
	//	AfxMessageBox(_T("시험지를 획득했다! 이제 시험은 100점이다!"), MB_OK | MB_ICONINFORMATION);
	//	//버튼들 숨기기
	//	m_btnHide.ShowWindow(SW_HIDE);
	//	m_btnOut.ShowWindow(SW_HIDE);
	//	m_btnTimer.ShowWindow(SW_HIDE);
	//	//엔딩 이미지 시작
	//	m_nCurrentEndingIndex = 0;
	//	m_pCurrentImage = &m_imgEnding[m_nCurrentEndingIndex];
	//	Invalidate();

	//	SetTimer(2, 5000, nullptr);
	//}
	else if (frame.PtInRect(point)) {
		if (m_pPictureDlg == nullptr || !::IsWindow(m_pPictureDlg->m_hWnd))
		{
			m_pPictureDlg = new CPictureDlg;
			if (m_pPictureDlg->Create(IDD_PICTURE_DIALOG, this))
				m_pPictureDlg->ShowWindow(SW_SHOW);
			else {
				delete m_pPictureDlg;
				m_pPictureDlg = nullptr;
			}
		}
		else {
			m_pPictureDlg->SetForegroundWindow();
		}
	}
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

	if (m_bHideTimer) {
		m_bHideRequested = TRUE;
	}
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

	//교수님이 나가지 않았는데 나가기 버튼을 누른 경우
	if (m_bHideTimer || m_bIsHiddenImage ) {
		m_bHideTimer = FALSE;
		m_bIsHiddenImage = FALSE;
		AfxMessageBox(_T("교수님께 들켜버렸다!"), MB_OK | MB_ICONERROR);
		CFailDlg* pFailDlg = new CFailDlg;
		if (pFailDlg->Create(IDD_FAIL_DIALOG, this))
		{
			pFailDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			delete pFailDlg;
		}
	}
}

void CEscapeDlg::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_seconds++;
		int minutes = m_seconds / 60;
		int seconds = m_seconds % 60;

		//1. 5분이 지난 경우 -> 자동 실패 엔딩
		if (m_seconds > 300) {
			AfxMessageBox(_T("교수님이 커피를 사고 돌아오셨다..."), MB_OK | MB_ICONWARNING);
			CFailDlg* pFailDlg = new CFailDlg;
			if (pFailDlg->Create(IDD_FAIL_DIALOG, this))
			{
				pFailDlg->ShowWindow(SW_SHOW);
			}
			else
			{
				delete pFailDlg;
			}
		}

		//2. 교수님이 지갑을 가지러 다시 오신 경우
		if (m_prevSecond <= 120 && m_seconds > 120) {
			m_prevSecond = m_seconds;
			CloseAllDialogs();
			m_pCurrentImage = &m_imgProfessorComing;
			Invalidate();
			AfxMessageBox(_T("교수님이 5초안에 방으로 들어오실거같다"), MB_OK | MB_ICONWARNING);
			//대화상자 확인 버튼 누른 시점으로부터 5초 계산
			m_bHideTimer = TRUE;
			m_nHideSecond = m_seconds;
		}

		//3. 교수님이 오신 후 5초가 지남
		if (m_bHideTimer && (m_seconds - m_nHideSecond >= 5))
		{
			
			m_bHideTimer = FALSE;
			//1) 5초안에 숨기 버튼을 누름-> 힌트 이미지
			if (m_bHideRequested)
			{
				m_bHideRequested = FALSE;
				m_bIsHiddenImage = TRUE;
				m_nHiddenImageTimer = m_seconds;
				m_pCurrentImage = &m_imgHint;
				Invalidate();

			}
			//2) 5초안에 숨기 버튼을 안누름 -> 실패 엔딩
			else {
				AfxMessageBox(_T("교수님께 들켜버렸다!"), MB_OK | MB_ICONERROR);
				CFailDlg* pFailDlg = new CFailDlg;
				if (pFailDlg->Create(IDD_FAIL_DIALOG, this))
				{
					pFailDlg->ShowWindow(SW_SHOW);
				}
				else
				{
					delete pFailDlg;
				}
			}
		}

		//4. 숨은 상태로 5초가 지나면 원래 이미지로 복원
		if (m_bIsHiddenImage && (m_seconds - m_nHiddenImageTimer >= 5))
		{
			m_bIsHiddenImage = FALSE;
			m_pCurrentImage = &m_imgBg;
			Invalidate(TRUE);
			AfxMessageBox(_T("교수님이 다시 나가셨다...계속 방을 둘러보자"), MB_OK | MB_ICONINFORMATION);
		}

		CString text;
		text.Format(L"%02d:%02d", minutes, seconds);

		SetDlgItemText(IDC_STATIC_TIMER, text);
	}
	else if (nIDEvent == 2)
	{
		KillTimer(1);
		
		m_nCurrentEndingIndex++;

		//이미지 변화
		if (m_nCurrentEndingIndex < 6)
		{
			m_pCurrentImage = &m_imgEnding[m_nCurrentEndingIndex];
			Invalidate(TRUE);
		}
		//이미지 출력 끝
		else
		{	
			KillTimer(2);
			m_btnEnd.ShowWindow(SW_SHOW);
				
		}
	}


	CDialogEx::OnTimer(nIDEvent);
}


BOOL CAboutDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO: 추가 초기화 코드

	return TRUE; // 포커스를 컨트롤에 설정하지 않을 경우 TRUE 반환
}

//엔딩 후 종료 버튼
void CEscapeDlg::OnBnClickedButtonEnd()
{
	::PostQuitMessage(0);
}

//성공 호출 함수
LRESULT CEscapeDlg::OnLockerSuccess(WPARAM wParam, LPARAM lParam)
{
	// 엔딩 시작
	AfxMessageBox(_T("시험지를 획득했다! 이제 시험은 100점이다!"));
	m_btnHide.ShowWindow(SW_HIDE);
	m_btnOut.ShowWindow(SW_HIDE);
	m_btnTimer.ShowWindow(SW_HIDE);
	m_nCurrentEndingIndex = 0;
	m_pCurrentImage = &m_imgEnding[m_nCurrentEndingIndex];
	Invalidate();
	SetTimer(2, 5000, nullptr);
	return 0;
}

//자식 다이얼로그 닫기




void CEscapeDlg::CloseAllDialogs()
{
	if (m_pBookListDlg && ::IsWindow(m_pBookListDlg->m_hWnd))
	{
		m_pBookListDlg->DestroyWindow();
		m_pBookListDlg = nullptr;
	}

	if (m_pLightDlg && ::IsWindow(m_pLightDlg->m_hWnd))
	{
		m_pLightDlg->DestroyWindow();
		m_pLightDlg = nullptr;
	}

	if (m_pLockerDlg && ::IsWindow(m_pLockerDlg->m_hWnd))
	{
		m_pLockerDlg->DestroyWindow();
		m_pLockerDlg = nullptr;
	}

	if (m_pPictureDlg && ::IsWindow(m_pPictureDlg->m_hWnd))
	{
		m_pPictureDlg->DestroyWindow();
		m_pPictureDlg = nullptr;
	}
}
