#pragma once


// BasicInfoDlg �Ի���

class BasicInfoDlg : public CDialogEx
{
	DECLARE_DYNAMIC(BasicInfoDlg)

public:
	BasicInfoDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~BasicInfoDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_BASICINFODLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEdit1();
};
