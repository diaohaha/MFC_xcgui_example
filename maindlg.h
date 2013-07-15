// MFC360DemoDlg.h : header file
//

#if !defined(AFX_MFC360DEMODLG_H__1DB703A4_D701_4AAB_9D51_526610D6F084__INCLUDED_)
#define AFX_MFC360DEMODLG_H__1DB703A4_D701_4AAB_9D51_526610D6F084__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000


//对话框中子页面的类定义
class CXPage_login : public CXEventMsg//登陆页面
{
public:
  HELE  m_hEle;
	HELE hEdit1;
    HELE hEdit2;
	Data data;
	BOOL  denglu(HELE hEle,HELE hEventEle);
	void  Create();
	void  AdjustLayout();
};


class CXPage_renshi : public CXEventMsg//查询页面
{
public:
	Data  data;
	HELE  m_hEle;
	HELE  m_hList;
	HELE  hEdit_chaxun;
	HELE  hEdit_1_1,hEdit_1_2,hEdit_1_3,hEdit_1_4,hEdit_1_5,hEdit_1_6,hEdit_1_7,hEdit_1_8,hEdit_1_9,hEdit_1_10,hEdit_1_11,hEdit_1_12,hEdit_1_13,hEdit_1_14,hEdit_1_15,hEdit_1_16,hEdit_1_17,hEdit_1_18,hEdit_1_19,hEdit_1_20,hEdit_1_21,hEdit_1_22,hEdit_1_23,hEdit_1_24,hEdit_1_25,hEdit_1_26,hEdit_1_27,hEdit_1_28,hEdit_1_29,hEdit_1_30,hEdit_1_31;
	HELE  edit_view;
	HELE  hComboBox;
	BOOL  chaxun(HELE hELe,HELE hEventEle);
	BOOL  edit(HELE hEle,HELE hEventEle);
	BOOL  del(HELE hEle,HELE hEventEle);
	BOOL  baocun(HELE hEle,HELE hEventEle);
	BOOL  quxiao(HELE hEle,HELE hEventEle);
	BOOL  showall(HELE hEle,HELE hEventEle);
	BOOL  scbb(HELE hEle,HELE hEventEle);
	void  Create();
	void  AdjustLayout();
};


class CXPage_anquan : public CXEventMsg //数据安全页面
{
public:
	Data data;
	CString FilePathName;
	HELE  m_hEle;
	HELE hEdit_xmm;
    HELE hEdit_yhm;
	HELE hEdit_mm;
	HELE hEdit_bf;
	HELE hEdit_wj;
	HELE hRichEdit;
	BOOL  beifen(HELE hEle,HELE hEventEle);

	BOOL  geng(HELE hEle,HELE hEventEle);
	BOOL  chuang(HELE hEle,HELE hEventEle);
	BOOL  xuanze(HELE hEle,HELE hEventEle);
	BOOL  huanyuan(HELE hEle,HELE hEventEle);
	void  Create();
	void  AdjustLayout();
};


class CXPage_setting : public CXEventMsg //设置页面
{
public:
	HELE  m_hEle;
    BOOL  xiaogongju(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex);
	BOOL  setting(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex);
	void  Create();
	void  AdjustLayout();
};

class CXPage_add : public CXEventMsg 
{
public:
	HELE  m_hEle;
	Data data;
	HELE  hEdit_1_1,hEdit_1_2,hEdit_1_3,hEdit_1_4,hEdit_1_5,hEdit_1_6,hEdit_1_7,hEdit_1_8,hEdit_1_9,hEdit_1_10,hEdit_1_11,hEdit_1_12,hEdit_1_13,hEdit_1_14,hEdit_1_15,hEdit_1_16,hEdit_1_17,hEdit_1_18,hEdit_1_19,hEdit_1_20,hEdit_1_21,hEdit_1_22,hEdit_1_23,hEdit_1_24,hEdit_1_25,hEdit_1_26,hEdit_1_27,hEdit_1_28,hEdit_1_29,hEdit_1_30,hEdit_1_31;
	HELE  hEdit_2_1,hEdit_2_2,hEdit_2_3,hEdit_2_4,hEdit_2_5;
	HELE  hEdit_3_1,hEdit_3_2;
	HELE  hEdit_4_1,hEdit_4_2;
	HELE  hEdit_5_1,hEdit_5_2;

	BOOL  add_dadj(HELE hEle,HELE hEventEle);
	BOOL  add_xhgx(HELE hEle,HELE hEventEle);
	BOOL  add_zcbm(HELE hEle,HELE hEventEle);
	BOOL  add_bmbm(HELE hEle,HELE hEventEle);
	BOOL  add_whcdbm(HELE hEle,HELE hEventEle);
	void  Create();
	void  AdjustLayout();
};

class CXPage_cmd : public CXEventMsg 
{
public:
	HELE  m_hEle;
	
	void  Create();
	void  AdjustLayout();
};







//皮肤更改对话框
class CSkinDlg : public CXEventMsg 
{
public:
	HWINDOW  m_hWindow;
	HELE     m_hListView;	
	void Create();
	BOOL OnEventListViewSelect(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex);
	BOOL OnWndKillFocus(HWINDOW hWindow);
};

class CTongjiDlg : public CXEventMsg 
{
public:
	Data data;
	HWINDOW  m_hWindow;
	HELE     m_hListView;
	HELE m_hList;
	void Create();

	BOOL tongji1(HELE hEle,HELE hEventEle);
	BOOL tongji2(HELE hEle,HELE hEventEle);
	BOOL tongji3(HELE hEle,HELE hEventEle);
	BOOL tongji4(HELE hEle,HELE hEventEle);
	BOOL OnWndKillFocus(HWINDOW hWindow);
};
class CTongxunluDlg : public CXEventMsg 
{
public:
	HWINDOW  m_hWindow;
	HELE     m_hListView;	
	void Create();
	BOOL OnWndKillFocus(HWINDOW hWindow);
};
class CUserDlg : public CXEventMsg 
{
public:
	Data  data;
	HWINDOW  m_hWindow;
	HELE     m_hListView;
	HELE     m_hList;
	void Create();
	BOOL del(HELE hEle,HELE hEventEle);
	BOOL OnWndKillFocus(HWINDOW hWindow);
};
class CBaobiaoDlg : public CXEventMsg 
{
public:
	HWINDOW  m_hWindow;
	void Create();
};
class CYgsrtyDlg : public CXEventMsg 
{
public:
	Data  data;
	HWINDOW  m_hWindow;
	void Create();
};

class CWhbmsetDlg : public CXEventMsg 
{
public:
	HELE  edit_id,edit_name;
	Data data;
	HWINDOW  m_hWindow;
	HELE m_hList;
	void Create();
	BOOL change(HELE hEle,HELE hEventEle);
};
class CBmbmsetDlg : public CXEventMsg 
{
public:
	HELE  edit_id,edit_name;
	Data data;
	HWINDOW  m_hWindow;
	HELE m_hList;
	void Create();
	BOOL change(HELE hEle,HELE hEventEle);
};
class CZcbmsetDlg : public CXEventMsg 
{
public:
	HELE  edit_id,edit_name;
	Data data;
	HWINDOW  m_hWindow;
	HELE m_hList;
	void Create();
	BOOL change(HELE hEle,HELE hEventEle);
};

class CMFC360DemoDlg : public CDialog
{
public:
	HWINDOW m_hWindow; //窗口句柄
	
	HIMAGE  m_hThemeBackground; //主题背景图片
	HIMAGE  m_hThemeBorder; //主题背景图片
	int     m_SkinIndex;   //当前皮肤 默认为0
	
	HIMAGE  m_hImage_check_leave;
	HIMAGE  m_hImage_check_stay;
	HIMAGE  m_hImage_check_down;
	
	HELE    m_hBottomText;
	int     m_bottomText_width;
	
	HELE    hRadio4;

	HELE    m_hBtnClose;
	HELE    m_hBtnMax;
	HELE    m_hBtnMin;
	HELE    m_hBtnMenu;
	HELE    m_hBtnSkin;
	
	CXPage_login   m_page_login;
	CXPage_renshi   m_page_find;
	CXPage_anquan   m_page_aq;
	CXPage_setting   m_page_set;
	CXPage_add   m_page_add;
	CXPage_cmd   m_page_cmd;
	
	BOOL Create(); //创建窗口和按钮
	
	void CreateToolButtonAndPage();
	HELE CreateToolButton(int x,int y,HIMAGE hIcon,wchar_t *pName);
	
	void AdjustLayout(); 
	BOOL OnEventBtnClick_Close(HELE hEle,HELE hEleEvent);
	BOOL OnEventBtnClick_ChangeSkin(HELE hEle,HELE hEleEvent);
	CMFC360DemoDlg(CWnd* pParent = NULL);


	//{{AFX_DATA(CMFC360DemoDlg)
	enum { IDD = IDD_MFC360DEMO_DIALOG };
		// NOTE: the ClassWizard will add data members here
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CMFC360DemoDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support
	//}}AFX_VIRTUAL

protected:
	HICON m_hIcon;

	// Generated message map functions
	//{{AFX_MSG(CMFC360DemoDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnSize(UINT nType, int cx, int cy);
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ will insert additional declarations immediately before the previous line.

#endif // !defined(AFX_MFC360DEMODLG_H__1DB703A4_D701_4AAB_9D51_526610D6F084__INCLUDED_)
