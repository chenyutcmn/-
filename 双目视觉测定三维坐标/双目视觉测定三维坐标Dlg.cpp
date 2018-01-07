
// 双目视觉测定三维坐标Dlg.cpp : 实现文件
//

#include "stdafx.h"
#include "双目视觉测定三维坐标.h"
#include "双目视觉测定三维坐标Dlg.h"
#include "afxdialogex.h"
#include <iostream>
#include <fstream>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/calib3d/calib3d.hpp"


using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

VideoCapture cap1(2);
VideoCapture cap2(1);
Mat frame[2];
CString strText = _T("");


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

void MatToCImage(Mat &mat, CImage &cImage);
string DoubleToString(double d);

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
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


// C双目视觉测定三维坐标Dlg 对话框



C双目视觉测定三维坐标Dlg::C双目视觉测定三维坐标Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void C双目视觉测定三维坐标Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(C双目视觉测定三维坐标Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(btnInit, &C双目视觉测定三维坐标Dlg::OnBnClickedbtninit)
	ON_WM_TIMER()
	ON_BN_CLICKED(btnGet3D, &C双目视觉测定三维坐标Dlg::OnBnClickedbtnget3d)
	ON_BN_CLICKED(btnShowMats, &C双目视觉测定三维坐标Dlg::OnBnClickedbtnshowmats)
END_MESSAGE_MAP()


// C双目视觉测定三维坐标Dlg 消息处理程序

BOOL C双目视觉测定三维坐标Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	cap1.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap1.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	cap2.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	cap2.set(CV_CAP_PROP_FRAME_HEIGHT, 480);
	//模拟点击初始化按钮
	PostMessage(WM_COMMAND, MAKEWPARAM(btnInit, BN_CLICKED), NULL);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void C双目视觉测定三维坐标Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void C双目视觉测定三维坐标Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR C双目视觉测定三维坐标Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//初始化按钮
void C双目视觉测定三维坐标Dlg::OnBnClickedbtninit()
{
	// TODO: 在此添加控件通知处理程序代码
	Mat frame[2];
	CImage myImage[2];
	frame[0].setTo(0);
	frame[1].setTo(0);
	if (cap1.isOpened() && cap2.isOpened()) {
		cap1 >> frame[0];
		cap2 >> frame[1];
	}
	else {
		AfxMessageBox(_T("打开摄像头失败"));
	}
	MatToCImage(frame[0], myImage[0]);
	MatToCImage(frame[1], myImage[1]);
	CRect rect;
	CWnd *pWnd = GetDlgItem(picRight);
	CDC *pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	myImage[0].Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);
	myImage[0].Destroy();
	CRect rect1;
	CWnd *pWnd1 = GetDlgItem(picLeft);
	CDC *pDC1 = pWnd1->GetDC();
	pWnd1->GetClientRect(&rect1);
	pDC1->SetStretchBltMode(STRETCH_HALFTONE);
	myImage[1].Draw(pDC1->m_hDC, rect1);
	ReleaseDC(pDC1);
	myImage[1].Destroy();
	SetTimer(1, 10, NULL);
}

//Mat转Cimage用于在pic控件上显示
void MatToCImage(Mat &mat, CImage &cImage)
{
	//create new CImage  
	int width = mat.cols;
	int height = mat.rows;
	int channels = mat.channels();
	//cout << channels << endl;
	cImage.Destroy(); //clear  
	cImage.Create(width,
		height, //positive: left-bottom-up   or negative: left-top-down  
		8 * channels); //numbers of bits per pixel  

					   //copy values  
	uchar* ps;
	uchar* pimg = (uchar*)cImage.GetBits(); //A pointer to the bitmap buffer  

											//The pitch is the distance, in bytes. represent the beginning of   
											// one bitmap line and the beginning of the next bitmap line  
	int step = cImage.GetPitch();

	for (int i = 0; i < height; ++i)
	{
		ps = (mat.ptr<uchar>(i));
		for (int j = 0; j < width; ++j)
		{
			if (channels == 1) //gray  
			{
				*(pimg + i*step + j) = ps[j];
			}
			else if (channels == 3) //color  
			{
				for (int k = 0; k < 3; ++k)
				{
					*(pimg + i*step + j * 3 + k) = ps[j * 3 + k];
				}
			}
		}
	}
}
//显示摄像头图像的定时器
void C双目视觉测定三维坐标Dlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CImage myImage[2];
	frame[0].setTo(0);
	frame[1].setTo(0);
	if (cap1.isOpened() && cap2.isOpened()) {
		cap1 >> frame[0];
		cap2 >> frame[1];
	}
	else {
		AfxMessageBox(_T("打开摄像头失败"));
	}
	MatToCImage(frame[0], myImage[0]);
	MatToCImage(frame[1], myImage[1]);
	CRect rect;
	CWnd *pWnd = GetDlgItem(picRight);
	CDC *pDC = pWnd->GetDC();
	pWnd->GetClientRect(&rect);
	pDC->SetStretchBltMode(STRETCH_HALFTONE);
	myImage[0].Draw(pDC->m_hDC, rect);
	ReleaseDC(pDC);
	myImage[0].Destroy();
	CRect rect1;
	CWnd *pWnd1 = GetDlgItem(picLeft);
	CDC *pDC1 = pWnd1->GetDC();
	pWnd1->GetClientRect(&rect1);
	pDC1->SetStretchBltMode(STRETCH_HALFTONE);
	myImage[1].Draw(pDC1->m_hDC, rect1);
	ReleaseDC(pDC1);
	myImage[1].Destroy();
	CDialogEx::OnTimer(nIDEvent);
}


//求取目标点坐标
void C双目视觉测定三维坐标Dlg::OnBnClickedbtnget3d()
{
	// TODO: 在此添加控件通知处理程序代码
	strText = _T("");
	FileStorage fsRamp("rmap.yml", FileStorage::READ);
	Mat rmap[2][2];
	fsRamp["ramp00"] >> rmap[0][0];
	fsRamp["ramp01"] >> rmap[0][1];
	fsRamp["ramp10"] >> rmap[1][0];
	fsRamp["ramp11"] >> rmap[1][1];
	fsRamp.release();
	Mat frameR = frame[0];
	Mat frameL = frame[1];
	if (frameR.cols!=0 && frameL.cols != 0) {
		imshow("right", frame[0]);
		imshow("left", frame[1]);
		//打印信息
		strText += _T("获取图像成功\r\n");
		GetDlgItem(showSomething)->SetWindowText(strText);
	}
	else {
		AfxMessageBox(_T("未获取到图像！"));
		return;
	}
	Mat copyR = frameR.clone();
	Mat copyL = frameL.clone();
	Mat newR = frameR.clone();
	Mat newL = frameL.clone();
	remap(copyR, newR, rmap[0][0], rmap[0][1], INTER_LINEAR);
	remap(copyL, newL, rmap[1][0], rmap[1][1], INTER_LINEAR);
	//打印信息
	GetDlgItem(showSomething)->GetWindowText(strText);
	strText += _T("图像矫正完成\r\n");
	GetDlgItem(showSomething)->SetWindowText(strText);
	Mat newRGry, newLGry;
	cvtColor(newR, newRGry, CV_RGB2GRAY);
	cvtColor(newL, newLGry, CV_RGB2GRAY);
	//erode(newRGry, rGryErode, NULL);
	int thresh = 200;
	Mat dst, dst_norm;
	Mat dst_norm_scaled[2];
	dst = Mat::zeros(newRGry.size(), CV_32FC1);


	vector<Point2f> corners[2];
	vector<vector<Point2f>> corCircles1;
	vector<vector<Point2f>> corCircles2;
	vector<Point2f> pointCircle[2];
	int count;
	int test;
	//打印信息
	GetDlgItem(showSomething)->GetWindowText(strText);
	strText += _T("开始获取角点\r\n");
	GetDlgItem(showSomething)->SetWindowText(strText);
	//右图像获取目标点
	cornerHarris(newRGry, dst, 7, 5, 0.04, BORDER_DEFAULT);
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled[0]);
	test = 0;
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				circle(dst_norm_scaled[0], Point(i, j), 5, CV_RGB(255, 0, 0), 1, 8, 0);
				if (corners[0].size() != 0) {
					Point2f lastPoint = corners[0].back();
					test = (lastPoint.x - i)*(lastPoint.x - i) + (lastPoint.y - j)*(lastPoint.y - j);
				}
				if (test > 200 || corners[0].size() == 0) {
					Point2f corner(i, j);
					corners[0].push_back(corner);
					vector<Point2f> corCircle;
					int r = 10;
					for (int k = (0 - r); k < r + 1; k++) {
						Point2f point(i + k, j + r);
						corCircle.push_back(point);
					}
					for (int k = (r - 1); k >(0 - r - 1); k--) {
						Point2f point(i + r, j + k);
						corCircle.push_back(point);
					}
					for (int k = (r - 1); k > (0 - r - 1); k--) {
						Point2f point(i + k, j - r);
						corCircle.push_back(point);
					}
					for (int k = (0 - r + 1); k < r; k++) {
						Point2f point(i - r, j + k);
						corCircle.push_back(point);
					}
					corCircles1.push_back(corCircle);
				}
			}
		}
	}

	copyR = newRGry.clone();
	for (int i = 0; i < copyR.rows; i++) {
		for (int j = 0; j < copyR.cols; j++) {
			int test1 = (int)copyR.at<uchar>(i, j);
			if (test1 < 125) {
				copyR.at<uchar>(i, j) = 0;
			}
			else {
				copyR.at<uchar>(i, j) = 255;
			}
		}
	}


	for (int i = 0; i < corCircles1.size(); i++) {
		count = 0;
		for (int j = 0; j < corCircles1[i].size() - 1; j++) {
			int test1 = (int)copyR.at<uchar>(corCircles1[i][j].y, corCircles1[i][j].x);
			int test2 = (int)copyR.at<uchar>(corCircles1[i][j + 1].y, corCircles1[i][j + 1].x);
			if (abs(test1 - test2)>150) {
				count++;
			}
		}
		cout << "右图像第" << i << "角点超过200个数为：" << count << endl;
		if (count == 4) {
			Point2f point(corCircles1[i][0].x + 10, corCircles1[i][0].y - 10);
			pointCircle[0].push_back(point);
		}
		count = 0;
	}


	//左图像获取目标点
	cornerHarris(newLGry, dst, 7, 5, 0.04, BORDER_DEFAULT);
	normalize(dst, dst_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
	convertScaleAbs(dst_norm, dst_norm_scaled[1]);
	test = 0;
	for (int j = 0; j < dst_norm.rows; j++)
	{
		for (int i = 0; i < dst_norm.cols; i++)
		{
			if ((int)dst_norm.at<float>(j, i) > thresh)
			{
				circle(dst_norm_scaled[1], Point(i, j), 5, CV_RGB(255, 0, 0), 1, 8, 0);
				if (corners[1].size() != 0) {
					Point2f lastPoint = corners[1].back();
					test = (lastPoint.x - i)*(lastPoint.x - i) + (lastPoint.y - j)*(lastPoint.y - j);
				}
				if (test > 200 || corners[1].size() == 0) {
					Point2f corner(i, j);
					corners[1].push_back(corner);
					vector<Point2f> corCircle;
					int r = 10;
					for (int k = (0 - r); k < r + 1; k++) {
						Point2f point(i + k, j + r);
						corCircle.push_back(point);
					}
					for (int k = (r - 1); k >(0 - r - 1); k--) {
						Point2f point(i + r, j + k);
						corCircle.push_back(point);
					}
					for (int k = (r - 1); k > (0 - r - 1); k--) {
						Point2f point(i + k, j - r);
						corCircle.push_back(point);
					}
					for (int k = (0 - r + 1); k < r; k++) {
						Point2f point(i - r, j + k);
						corCircle.push_back(point);
					}
					//cout << corCircle;
					corCircles2.push_back(corCircle);
				}
			}
		}
	}

	copyL = newLGry.clone();
	for (int i = 0; i < copyL.rows; i++) {
		for (int j = 0; j < copyL.cols; j++) {
			int test1 = (int)copyL.at<uchar>(i, j);
			if (test1 < 125) {
				copyL.at<uchar>(i, j) = 0;
			}
			else {
				copyL.at<uchar>(i, j) = 255;
			}
		}
	}
	Mat element = getStructuringElement(0, Size(3, 3), Point(0, 0));
	erode(copyL, copyL, element);


	for (int i = 0; i < corCircles2.size(); i++) {
		count = 0;
		for (int j = 0; j < corCircles2[i].size() - 1; j++) {
			int test1 = (int)copyL.at<uchar>(corCircles2[i][j].y, corCircles2[i][j].x);
			int test2 = (int)copyL.at<uchar>(corCircles2[i][j + 1].y, corCircles2[i][j + 1].x);
			if (abs(test1 - test2)>150) {
				count++;
			}
		}
		cout << "左图像第" << i << "角点超过200个数为：" << count << endl;
		if (count == 4) {
			Point2f point(corCircles2[i][0].x + 10, corCircles2[i][0].y - 10);
			pointCircle[1].push_back(point);
		}
		count = 0;
	}
	if (pointCircle[0].size() != 1 && pointCircle[1].size() != 1) {
		AfxMessageBox(_T("提取目标角点失败！"));
		return;
	}
	else {
		//打印信息
		GetDlgItem(showSomething)->GetWindowText(strText);
		strText += _T("目标角点提取成功\r\n");
		GetDlgItem(showSomething)->SetWindowText(strText);
	}
	//打印信息
	GetDlgItem(showSomething)->GetWindowText(strText);
	strText += _T("开始计算目标点坐标\r\n");
	GetDlgItem(showSomething)->SetWindowText(strText);
	FileStorage fsMat("intrinsics.yml", FileStorage::READ);
	Mat p1, p2;
	fsMat["P1"] >> p1;
	fsMat["P2"] >> p2;
	fsMat.release();
	//cout << p1 << endl << p2 << endl;
	double w = 146.0 / 640.0;
	double h = 110.0 / 480.0;
	Mat pointRight = Mat(2, 1, 6);
	Mat pointLeft = Mat(2, 1, 6);
	pointRight.at<double>(0, 0) = (double)pointCircle[0][0].y * h;
	pointRight.at<double>(1, 0) = (double)pointCircle[0][0].x * w;
	pointLeft.at<double>(0, 0) = (double)pointCircle[1][0].y * h;
	pointLeft.at<double>(1, 0) = (double)pointCircle[1][0].x * w;

	Mat MA = Mat(4, 3, 6);
	Mat MB = Mat(4, 1, 6);
	//CvMat  *MA = cvCreateMat(4, 3, 6);
	//CvMat  *MB = cvCreateMat(4, 1, 6);
	//cout << p1.channels() << endl << pointLeft.channels() << endl << p1.type() << endl << pointLeft.type();
	//cout<<p2.at<double>(3, 1)*pointLeft.at<double>(1, 1) - p2.at<double>(1, 1);
	//初始化A
	double A11 = p2.at<double>(2, 0)*pointLeft.at<double>(0, 0) - p2.at<double>(0, 0);
	double A12 = p2.at<double>(2, 1)*pointLeft.at<double>(0, 0) - p2.at<double>(0, 1);
	double A13 = p2.at<double>(2, 2)*pointLeft.at<double>(0, 0) - p2.at<double>(0, 2);
	double A21 = p2.at<double>(2, 0)*pointLeft.at<double>(1, 0) - p2.at<double>(1, 0);
	double A22 = p2.at<double>(2, 1)*pointLeft.at<double>(1, 0) - p2.at<double>(1, 1);
	double A23 = p2.at<double>(2, 2)*pointLeft.at<double>(1, 0) - p2.at<double>(1, 2);
	double A31 = p1.at<double>(2, 0)*pointRight.at<double>(0, 0) - p1.at<double>(0, 0);
	double A32 = p1.at<double>(2, 1)*pointRight.at<double>(0, 0) - p1.at<double>(0, 1);
	double A33 = p1.at<double>(2, 2)*pointRight.at<double>(0, 0) - p1.at<double>(0, 2);
	double A41 = p1.at<double>(2, 0)*pointRight.at<double>(1, 0) - p1.at<double>(1, 0);
	double A42 = p1.at<double>(2, 1)*pointRight.at<double>(1, 0) - p1.at<double>(1, 1);
	double A43 = p1.at<double>(2, 2)*pointRight.at<double>(1, 0) - p1.at<double>(1, 2);
	double arrayA[12] = { A11, A12, A13, A21, A22, A23, A31, A32, A33, A41, A42, A43 };

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 3; j++) {
			MA.at<double>(i, j) = arrayA[i * 3 + j];
		}
	}
	//cvSetData(MA, arrayA, CV_AUTOSTEP);

	//初始化b
	double b11 = p2.at<double>(0, 3) - p2.at<double>(2, 3)*pointLeft.at<double>(0, 0);
	double b21 = p2.at<double>(1, 3) - p2.at<double>(2, 3)*pointLeft.at<double>(1, 0);
	double b31 = p1.at<double>(0, 3) - p1.at<double>(2, 3)*pointRight.at<double>(0, 0);
	double b41 = p1.at<double>(1, 3) - p1.at<double>(2, 3)*pointRight.at<double>(1, 0);
	double arrayb[4] = { b11,b21,b31,b41 };
	//cvSetData(MB, arrayb, CV_AUTOSTEP);
	for (int j = 0; j < 4; j++) {
		MB.at<double>(j, 0) = arrayb[j];
	}
	Mat MAT;
	MA.copyTo(MAT);
	MAT = MAT.t();
	Mat MATXA = MAT*MA;
	MATXA = MATXA.inv();
	Mat MATXAA = MATXA*MAT;
	Mat res = MATXAA*MB;
	ofstream fout("calibration_result.txt");
	fout << "一号相机内参数矩阵：" << endl;
	fout << res << endl;
	//打印信息
	GetDlgItem(showSomething)->GetWindowText(strText);
	strText += _T("坐标计算成功\r\n");
	GetDlgItem(showSomething)->SetWindowText(strText);
	string mat00 = DoubleToString(res.at<double>(0, 0));
	string mat10 = DoubleToString(res.at<double>(1, 0));
	string mat20 = DoubleToString(res.at<double>(2, 0));
	//打印信息
	GetDlgItem(showSomething)->GetWindowText(strText);
	strText += mat00.c_str();
	strText += _T("\r\n");
	strText += mat10.c_str();
	strText += _T("\r\n");
	strText += mat20.c_str();
	strText += _T("\r\n");
	GetDlgItem(showSomething)->SetWindowText(strText);
}


void C双目视觉测定三维坐标Dlg::OnBnClickedbtnshowmats()
{
	// TODO: 在此添加控件通知处理程序代码
	strText = _T("");
	GetDlgItem(showSomething)->SetWindowText(strText);
	CString strText = _T("右摄像头内参矩阵\r\n");
	FileStorage fsMat("intrinsics.yml", FileStorage::READ);
	if (!fsMat.isOpened())
	{
		CWnd::MessageBox(_T("打开文件失败!"), _T("error"), MB_OK);
	}
	Mat intrinsic_matrix[2], distortion_coeffs[2],R,T,P1,P2;
	fsMat["C0"] >> intrinsic_matrix[0];
	fsMat["D0"] >> distortion_coeffs[0];
	fsMat["C1"] >> intrinsic_matrix[1];
	fsMat["D1"] >> distortion_coeffs[1];
	fsMat["R"] >> R;
	fsMat["T"] >> T;
	fsMat["P1"] >> P1;
	fsMat["P2"] >> P2;
	fsMat.release();
	int nRows = intrinsic_matrix[0].rows;
	int nCols = intrinsic_matrix[0].cols;

	int i, j;
	double* p;
	for (i = 0; i < nRows; ++i)
	{
		p = intrinsic_matrix[0].ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t\r\t");
		}
		strText += _T("\r\n");
	}
	strText += _T("右摄像头畸变矩阵\r\n");
	nRows = distortion_coeffs[0].rows;
	nCols = distortion_coeffs[0].cols;

	for (i = 0; i < nRows; ++i)
	{
		p = distortion_coeffs[0].ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t\r\t");
		}
		strText += _T("\r\n");
	}
	
	nRows = intrinsic_matrix[1].rows;
	nCols = intrinsic_matrix[1].cols;
	strText += _T("左摄像头内参矩阵\r\n");

	for (i = 0; i < nRows; ++i)
	{
		p = intrinsic_matrix[1].ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t\r\t");
		}
		strText += _T("\r\n");
	}
	strText += _T("左摄像头畸变矩阵\r\n");
	nRows = distortion_coeffs[1].rows;
	nCols = distortion_coeffs[1].cols;

	for (i = 0; i < nRows; ++i)
	{
		p = distortion_coeffs[1].ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t");
		}
		strText += _T("\r\n");
	}
	//系统旋转矩阵
	
	nRows = R.rows;
	nCols = R.cols;
	strText += _T("系统旋转矩阵\r\n");

	for (i = 0; i < nRows; ++i)
	{
		p = R.ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t\r\t");
		}
		strText += _T("\r\n");
	}
	strText += _T("系统平移向量\r\n");
	nRows = T.rows;
	nCols = T.cols;

	for (i = 0; i < nRows; ++i)
	{
		p = T.ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t");
		}
		strText += _T("\r\n");
	}
	nRows = P1.rows;
	nCols = P1.cols;
	strText += _T("右摄像机投影矩阵\r\n");

	for (i = 0; i < nRows; ++i)
	{
		p = P1.ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t\r\t");
		}
		strText += _T("\r\n");
	}
	strText += _T("左摄像机投影矩阵\r\n");
	nRows = P2.rows;
	nCols = P2.cols;

	for (i = 0; i < nRows; ++i)
	{
		p = P2.ptr<double>(i);
		for (j = 0; j < nCols; j += 1)//
		{
			string ss = DoubleToString(p[j]);
			strText += ss.c_str();
			strText += _T("\r\t");
		}
		strText += _T("\r\n");
	}
	GetDlgItem(showSomething)->SetWindowText(strText);
}


string DoubleToString(double d)
{
	//Need #include <sstream>
	string str;
	stringstream ss;
	ss << d;
	ss >> str;
	return str;
}