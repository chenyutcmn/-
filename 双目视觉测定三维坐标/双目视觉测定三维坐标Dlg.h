
// ˫Ŀ�Ӿ��ⶨ��ά����Dlg.h : ͷ�ļ�
//

#pragma once


// C˫Ŀ�Ӿ��ⶨ��ά����Dlg �Ի���
class C˫Ŀ�Ӿ��ⶨ��ά����Dlg : public CDialogEx
{
// ����
public:
	C˫Ŀ�Ӿ��ⶨ��ά����Dlg(CWnd* pParent = NULL);	// ��׼���캯��

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��


// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedbtninit();
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnBnClickedbtnget3d();
	afx_msg void OnBnClickedbtnshowmats();
};
