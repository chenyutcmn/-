
// 双目视觉测定三维坐标Dlg.h : 头文件
//

#pragma once


// C双目视觉测定三维坐标Dlg 对话框
class C双目视觉测定三维坐标Dlg : public CDialogEx
{
// 构造
public:
	C双目视觉测定三维坐标Dlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MY_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
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
