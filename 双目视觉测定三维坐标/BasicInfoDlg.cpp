// BasicInfoDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "˫Ŀ�Ӿ��ⶨ��ά����Dlg.h"
#include "BasicInfoDlg.h"
#include "afxdialogex.h"
#include "Resource.h"


// BasicInfoDlg �Ի���

IMPLEMENT_DYNAMIC(BasicInfoDlg, CDialogEx)

BasicInfoDlg::BasicInfoDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_BASICINFODLG, pParent)
{

}

BasicInfoDlg::~BasicInfoDlg()
{
}

void BasicInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(BasicInfoDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &BasicInfoDlg::OnBnClickedOk)
	//ON_EN_CHANGE(IDC_EDIT1, &BasicInfoDlg::OnEnChangeEdit1)
END_MESSAGE_MAP()


// BasicInfoDlg ��Ϣ�������


void BasicInfoDlg::OnBnClickedOk()
{
	this->ShowWindow(SW_HIDE);
	C˫Ŀ�Ӿ��ⶨ��ά����Dlg dlg;
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
	::SendMessage(this->GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}


void BasicInfoDlg::OnEnChangeEdit1()
{
	// TODO:  ����ÿؼ��� RICHEDIT �ؼ���������
	// ���ʹ�֪ͨ��������д CDialogEx::OnInitDialog()
	// ���������� CRichEditCtrl().SetEventMask()��
	// ͬʱ�� ENM_CHANGE ��־�������㵽�����С�

	// TODO:  �ڴ���ӿؼ�֪ͨ����������
}
