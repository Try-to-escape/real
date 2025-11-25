// CLightDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CLightDlg.h"


// CLightDlg 대화 상자

IMPLEMENT_DYNAMIC(CLightDlg, CDialogEx)

CLightDlg::CLightDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LIGHT, pParent)
{

}

CLightDlg::~CLightDlg()
{
}

void CLightDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_LIGHT, m_btnLight);
}


BEGIN_MESSAGE_MAP(CLightDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BUTTON_LIGHT, &CLightDlg::OnClickedButtonLight)
	ON_WM_DRAWITEM()
END_MESSAGE_MAP()


// CLightDlg 메시지 처리기

BOOL CLightDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	m_bLightOn = FALSE;

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_imgLightOff.Load(L"res/image/EscapeLightOff.bmp");
	m_imgLightOn.Load(L"res/image/EscapeLightOn.bmp");
	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	m_btnLight.EnableWindowsTheming(FALSE);
	m_btnLight.m_nFlatStyle = CMFCButton::BUTTONSTYLE_NOBORDERS;
	m_btnLight.m_bTransparent = TRUE;
	m_btnLight.m_bDrawFocus = FALSE;
	m_btnLight.SetMouseCursorHand();

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);

	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}

void CLightDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	CRect rect;
	GetClientRect(rect);

	if (m_bLightOn == TRUE)
	{
		if (!m_imgLightOn.IsNull())
		{
			m_imgLightOn.Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
		}
	}
	else
	{
		if (!m_imgLightOff.IsNull())
		{
			m_imgLightOff.Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
		}
	}
}

void CLightDlg::OnClickedButtonLight()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_bLightOn = !m_bLightOn;
	Invalidate();
}

void CLightDlg::OnDrawItem(int nIDCtl, LPDRAWITEMSTRUCT lpDrawItemStruct)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	if (nIDCtl == IDC_BUTTON_LIGHT)
	{
		return;
	}
	CDialogEx::OnDrawItem(nIDCtl, lpDrawItemStruct);
}

void CLightDlg::OnCancel()
{
	DestroyWindow();
}

void CLightDlg::OnOK()
{
	DestroyWindow();
}

void CLightDlg::PostNcDestroy()
{
	delete this;
}