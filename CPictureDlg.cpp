// CPictureDlg.cpp: 구현 파일
//

#include "pch.h"
#include "Escape.h"
#include "afxdialogex.h"
#include "CPictureDlg.h"
#include "CFailDlg.h"
#include "resource.h"

// CPictureDlg 대화 상자

IMPLEMENT_DYNAMIC(CPictureDlg, CDialogEx)

CPictureDlg::CPictureDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PICTURE_DIALOG, pParent)
{

}

CPictureDlg::~CPictureDlg()
{
}

void CPictureDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CPictureDlg, CDialogEx)
	ON_BN_CLICKED(IDC_RADIO_FAIL1, &CPictureDlg::OnClickedRadioFail1)
	ON_BN_CLICKED(IDC_RADIO_FAIL2, &CPictureDlg::OnClickedRadioFail2)
	ON_BN_CLICKED(IDC_RADIO_SUCCESS, &CPictureDlg::OnClickedRadioSuccess)
	ON_BN_CLICKED(IDC_BUTTON_SUBMIT, &CPictureDlg::OnClickedButtonSubmit)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CPictureDlg 메시지 처리기

BOOL CPictureDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  여기에 추가 초기화 작업을 추가합니다.
	m_selectedPictureRadio = 0;

	m_bmpPicture.Load(L"res/image/EscapePicture.bmp");
	m_bmpPicture1.Load(L"res/image/EscapePicture1.bmp");
	m_bmpPicture2.Load(L"res/image/EscapePicture2.bmp");
	m_bmpPicture3.Load(L"res/image/EscapePicture3.bmp");

	m_bmpPictureCurrent = &m_bmpPicture;

	int nWidth = 1026;
	int nHeight = 770;

	CRect rect(0, 0, nWidth, nHeight);
	AdjustWindowRect(&rect, GetStyle(), FALSE);

	SetWindowPos(NULL, 0, 0, rect.Width(), rect.Height(), SWP_NOMOVE | SWP_NOZORDER);
	Invalidate();
	return TRUE;  // return TRUE unless you set the focus to a control
	// 예외: OCX 속성 페이지는 FALSE를 반환해야 합니다.
}


void CPictureDlg::OnClickedRadioSuccess()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_selectedPictureRadio = 1;
}

void CPictureDlg::OnClickedRadioFail1()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_selectedPictureRadio = 2;
}

void CPictureDlg::OnClickedRadioFail2()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	m_selectedPictureRadio = 3;
}


void CPictureDlg::OnClickedButtonSubmit()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CFailDlg* pFailDlg = new CFailDlg;
	switch (m_selectedPictureRadio) {
	case 1:
		m_bmpPictureCurrent = &m_bmpPicture1;
		break;
	case 2:
		
		m_bmpPictureCurrent = &m_bmpPicture2;
		if (pFailDlg->Create(IDD_FAIL_DIALOG, this))
		{
			pFailDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			delete pFailDlg;
		}
		break;
	case 3:
		
		m_bmpPictureCurrent = &m_bmpPicture3;
		if (pFailDlg->Create(IDD_FAIL_DIALOG, this))
		{
			pFailDlg->ShowWindow(SW_SHOW);
		}
		else
		{
			delete pFailDlg;
		}

		break;
	}

	Invalidate();

	((CButton*)GetDlgItem(IDC_RADIO_SUCCESS))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_FAIL1))->SetCheck(BST_UNCHECKED);
	((CButton*)GetDlgItem(IDC_RADIO_FAIL2))->SetCheck(BST_UNCHECKED);

	// 선택값 초기화
	m_selectedPictureRadio = 0;
}

void CPictureDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
	// 그리기 메시지에 대해서는 CDialogEx::OnPaint()을(를) 호출하지 마십시오.
	if (m_bmpPictureCurrent && !m_bmpPictureCurrent->IsNull())
	{
		CRect rect;
		GetClientRect(rect);
		m_bmpPictureCurrent->Draw(dc, rect.left, rect.top, rect.Width(), rect.Height());
	}
}

void CPictureDlg::OnCancel()
{
	DestroyWindow();  
}

void CPictureDlg::OnOK()
{
	DestroyWindow();  
}

void CPictureDlg::PostNcDestroy()
{
	delete this;  
}
