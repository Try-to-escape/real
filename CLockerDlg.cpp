// CLockerDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CLockerDlg.h"


// CLockerDlg 대화 상자

IMPLEMENT_DYNAMIC(CLockerDlg, CDialogEx)

CLockerDlg::CLockerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOCKER, pParent)
{

}

CLockerDlg::~CLockerDlg()
{
}

void CLockerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LOCKER0, m_btnLocker0);
	DDX_Control(pDX, IDC_BUTTON_LOCKER1, m_btnLocker1);
	DDX_Control(pDX, IDC_BUTTON_LOCKER2, m_btnLocker2);
	DDX_Control(pDX, IDC_BUTTON_LOCKER3, m_btnLocker3);
	DDX_Control(pDX, IDC_BUTTON_LOCKER4, m_btnLocker4);
	DDX_Control(pDX, IDC_BUTTON_LOCKER5, m_btnLocker5);
	DDX_Control(pDX, IDC_BUTTON_LOCKER6, m_btnLocker6);
	DDX_Control(pDX, IDC_BUTTON_LOCKER7, m_btnLocker7);
	DDX_Control(pDX, IDC_BUTTON_LOCKER8, m_btnLocker8);
	DDX_Control(pDX, IDC_BUTTON_LOCKER9, m_btnLocker9);
	DDX_Control(pDX, IDC_EDIT_LOCKER_INPUT, m_editLockerInput);
	DDX_Control(pDX, IDC_BUTTON_TAKE_TESTPAPER, m_btnTakeTestpaper);
	DDX_Control(pDX, IDC_BUTTON_TAKE_GOLD, m_btnTakeGold);
}


BEGIN_MESSAGE_MAP(CLockerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_LOCKER0, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER1, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER2, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER3, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER4, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER5, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER6, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER7, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER8, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_LOCKER9, &CLockerDlg::OnLockerButton)
	ON_BN_CLICKED(IDC_BUTTON_TAKE_TESTPAPER, &CLockerDlg::OnBnClickedButtonTakeTestpaper)
	ON_BN_CLICKED(IDC_BUTTON_TAKE_GOLD, &CLockerDlg::OnBnClickedButtonTakeGold)
END_MESSAGE_MAP()



// CLockerDlg 메시지 처리기

BOOL CLockerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	//1. 이미지들 불러오기
	m_imgLocker.Load(L"res/image/locker.bmp");	//기본 금고 닫힘
	m_imgLockerOpen.Load(L"res/image/lockerOpen.bmp"); //금고 열림
	m_imgTestPaper.Load(L"res/image/EscapeEnding1.bmp"); //시험지

	//2. 초기 화면 설정(닫힌 금고)
	m_pCurrentImage = &m_imgLocker;
	m_btnTakeTestpaper.ShowWindow(SW_HIDE);
	m_btnTakeGold.ShowWindow(SW_HIDE);

	//3. 값 초기화
	m_strPassword = "7512";
	m_bSuccess = false;

	//4. 윈도우 크기 설정
	int nWidth = 1514;
	int nHeight = 801;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);
	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	Invalidate();

	return TRUE;
}

void CLockerDlg::OnPaint()
{
	CPaintDC dc(this); 

	//이미지 출력
	if (m_pCurrentImage == nullptr) {
		AfxMessageBox(L"m_pCurrentImage is null!");
	}
	else if (m_pCurrentImage->IsNull()) {
		AfxMessageBox(L"Image is loaded but empty!");
	}
	else {
		m_pCurrentImage->Draw(dc, 0, 0);
	}
}

void CLockerDlg::OnLockerButton()
{
	UINT nID = GetCurrentMessage()->wParam; 
	OnBnClickedButtonLocker(nID);          
}

void CLockerDlg::OnBnClickedButtonLocker(UINT nID)
{

	// 버튼 컨트롤 가져오기
	CButton* pBtn = (CButton*)GetDlgItem(nID);
	if (!pBtn) return;

	// 버튼 텍스트 읽기
	CString strBtnText;
	pBtn->GetWindowText(strBtnText);

	// Edit Box 값에 버튼 클릭값 추가
	CString strInput;
	m_editLockerInput.GetWindowText(strInput);
	strInput += strBtnText;
	m_editLockerInput.SetWindowText(strInput);

	// 4자리 입력 시 동작
	if (strInput.GetLength() == 4)
	{
		//1. 비밀번호 일치시->성공화면
		if (strInput == m_strPassword) {

			// 1) 컨트롤들 제거
			m_editLockerInput.ShowWindow(SW_HIDE);
			m_btnLocker0.ShowWindow(SW_HIDE);
			m_btnLocker1.ShowWindow(SW_HIDE);
			m_btnLocker2.ShowWindow(SW_HIDE);
			m_btnLocker3.ShowWindow(SW_HIDE);
			m_btnLocker4.ShowWindow(SW_HIDE);
			m_btnLocker5.ShowWindow(SW_HIDE);
			m_btnLocker6.ShowWindow(SW_HIDE);
			m_btnLocker7.ShowWindow(SW_HIDE);
			m_btnLocker8.ShowWindow(SW_HIDE);
			m_btnLocker9.ShowWindow(SW_HIDE);
			// 2) 열린 금고 화면
			m_pCurrentImage = &m_imgLockerOpen;
			Invalidate();
			m_btnTakeTestpaper.ShowWindow(SW_SHOW);
			m_btnTakeGold.ShowWindow(SW_SHOW);
		}
		//2. 비밀번호 불일치시->실패화면(경고 메세지, 창 닫기)
		else {
			AfxMessageBox(_T("암호 불일치, 교수님께 메세지를 보냈습니다"), MB_OK | MB_ICONWARNING);
			CFailDlg failDlg;
			failDlg.DoModal();
			EndDialog(IDOK);
		}

		m_editLockerInput.SetWindowText(_T(""));
		strInput.Empty();
		UpdateData(FALSE);

	}
}

void CLockerDlg::OnBnClickedButtonTakeTestpaper()
{
	//엔딩 출력 변수 활성화
	AfxMessageBox(_T("시험지를 획득했다!"), MB_OK | MB_ICONINFORMATION);
	m_bSuccess = true;
	EndDialog(IDOK);
}

void CLockerDlg::OnBnClickedButtonTakeGold()
{
	AfxMessageBox(_T("금괴가 사라지면 교수님이 눈치챌거야..."), MB_OK | MB_ICONWARNING);
	m_btnTakeGold.ShowWindow(SW_HIDE);
}
