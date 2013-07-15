// MFC360DemoDlg.cpp : implementation file
//
#include "stdafx.h"
#include "MFC360Demo.h"
#include "MFC360DemoDlg.h"

#include <string.h>
#include <iostream>
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

HFONTX hfontx1=XFont_Create2(L"幼圆",14,true,false,false,false);
HFONTX hfontx2=XFont_Create2(L"幼圆",16,true,false,false,false);
HFONTX hfontx3=XFont_Create2(L"幼圆",32,true,false,false,false);


CMFC360DemoDlg*  mainWnd = NULL;//
CString now_user;
char now_sql[1024];
int login_sign=0;


class CAboutDlg : public CDialog
{
public:
  CAboutDlg();

// Dialog Data
	//{{AFX_DATA(CAboutDlg)
	enum { IDD = IDD_ABOUTBOX };
	//}}AFX_DATA

	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CAboutDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	//}}AFX_VIRTUAL

// Implementation
protected:
	//{{AFX_MSG(CAboutDlg)
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
	//{{AFX_DATA_INIT(CAboutDlg)
	//}}AFX_DATA_INIT
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
	//{{AFX_MSG_MAP(CAboutDlg)
		// No message handlers
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


//原本的
CMFC360DemoDlg::CMFC360DemoDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMFC360DemoDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFC360DemoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMFC360DemoDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
END_MESSAGE_MAP()



void CALLBACK MyList_OnDrawItem(HELE hEle,list_drawItem_ *pDrawItem)
{
	RECT rect;
	XEle_GetClientRect (hEle, &rect);
	int nHeadHeigh = XList_GetHeaderHeight (hEle);
	
	pDrawItem->rect.left-=10;
	RECT rect1;
	rect1.left=pDrawItem->rect.left;
	rect1.right = pDrawItem->rect.right;
	int times = rect.bottom / 40;
	for( int i = XList_GetItemCount(hEle); i <= times; i++ )
	{
		
		if(i%2)
		{
			rect1.top = i * 40 ;
			rect1.bottom = i * 40+nHeadHeigh+40;
			XDraw_FillSolidRect_(pDrawItem->hDraw,&rect1,RGB(220,220,220));
			
		}
		else
		{
			rect1.top = i * 40 ;
			rect1.bottom = i * 40+ nHeadHeigh+40;
			XDraw_FillSolidRect_(pDrawItem->hDraw,&rect1,RGB(200,200,200));
		}
	}
	
	
    //绘制背景
    if(STATE_SELECT==pDrawItem->state)
    {
        XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(100,100,100));
    }
	else
    {
        if(0==pDrawItem->index%2)
            XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(200,200,200));
        else
            XDraw_FillSolidRect_(pDrawItem->hDraw,&pDrawItem->rect,RGB(220,220,220));
    }
	XDraw_DrawText_(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&pDrawItem->rect,DT_CENTER|DT_VCENTER | DT_SINGLELINE | DT_END_ELLIPSIS);
}

void CALLBACK MyListHeader_DrawItem(HELE hEle,listHeader_drawItem_ *pDrawItem)
{
	   RECT rect=pDrawItem->rect;
	   rect.left-=10;
	   
	   if(-1==pDrawItem->state)
	   {
		   return;
	   }
	   if(STATE_LEAVE==pDrawItem->state)
	   {
		   switch((pDrawItem->index)%2)
		   {
		   case 0:
			   rect.right--;
			   XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(72,118,255));
			   break;
		   case 1:
			   rect.right--;
			   XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(0,0,139));
			   break;
		   default:
			   break;
		   }
	   }
	   else if(STATE_STAY==pDrawItem->state)
	   {
		   XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(255,147,147));
	   }else if(STATE_DOWN==pDrawItem->state)
	   {
		   XDraw_FillSolidRect_(pDrawItem->hDraw,&rect,RGB(255,202,202));
	   }
	   
	   XDraw_SetTextColor_ (pDrawItem->hDraw, RGB(255,255,255));
	   XDraw_DrawText_(pDrawItem->hDraw,pDrawItem->pText,wcslen(pDrawItem->pText),&rect,DT_VCENTER |DT_CENTER| DT_SINGLELINE | DT_END_ELLIPSIS);  
}
//对话框初始化函数，中使用界面库生成对话框
BOOL CMFC360DemoDlg::OnInitDialog()
{
	CDialog::OnInitDialog();
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		
	
	CRect rect;
	rect.left =0;
	rect.right = 850;
	rect.top =0;
	rect.bottom =600;
	MoveWindow(rect);//改变制定窗口的位置和大小
	mainWnd = this;//现有的窗口对象的指针（import）
	
	Create();//生成对话框的函数
	
	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CMFC360DemoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}


void CMFC360DemoDlg::OnPaint() 
{
	CRect rect;
	GetClientRect(&rect);
	
	if(m_hWindow)
	{
		XWnd_SetWindowSize(m_hWindow, rect.right,rect.bottom);
		AdjustLayout();
	}
	
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

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
		CDialog::OnPaint();
	}
}

HCURSOR CMFC360DemoDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}













//外成对话框消息响应函数
BOOL CALLBACK WinMouseLeftDown(HWINDOW hWindow,UINT flags,POINT *pPt)//函数用来响应事件，
{//左键点击，point为点击时点的位置
	CRect rect;//矩形,
	GetClientRect(mainWnd->m_hWnd,&rect);//获得矩形
	if(pPt->x<(rect.right-200)&&pPt->y<=25)//标题栏按钮长度与高度
	{
		::PostMessage(mainWnd->m_hWnd, WM_NCLBUTTONDOWN,HTCAPTION,MAKELPARAM(pPt->x,pPt->y)); 
	}	//maybe shi yong lai move确实是用来移动的
	return FALSE;
}


BOOL CALLBACK MyFunClassCloseEventMsg(eventOrMsg_ *pEvent,xcgui_fun_type funType)//关闭按钮(当前处理元素句柄，触发事件的元素句柄）
{
	CMFC360DemoDlg* pThis = (CMFC360DemoDlg*)pEvent->pClass_fun;//dui hua kuang zhiz zhen de bian hua
	
	switch(funType)
	{
	case XE_BNCLICK://按钮点击事件
		pThis->EndDialog(1);
		break;
	}
	return FALSE;
}

BOOL CALLBACK MyFunClassMaxEventMsg(eventOrMsg_ *pEvent,xcgui_fun_type funType)
{
	CMFC360DemoDlg* pThis = (CMFC360DemoDlg*)pEvent->pClass_fun;
	
	if(IsZoomed(pThis->m_hWnd))
	{
		pThis->ShowWindow(SW_RESTORE);
		pThis->CenterWindow();
	}
	else
	{
		pThis->ShowWindow(SW_MAXIMIZE);
	}
	return FALSE;
}

BOOL CALLBACK MyFunClassMinEventMsg(eventOrMsg_ *pEvent,xcgui_fun_type funType)
{
	CMFC360DemoDlg* pThis = (CMFC360DemoDlg*)pEvent->pClass_fun;
	pThis->ShowWindow(SW_SHOWMINIMIZED);
	return FALSE;
}

BOOL CALLBACK MyFunClassChangeEventMsg(eventOrMsg_ *pEvent,xcgui_fun_type funType)
{
	CMFC360DemoDlg* pThis = (CMFC360DemoDlg*)pEvent->pClass_fun;
	
	if(pEvent->hEle!=pEvent->hEventEle) return FALSE;
	
	CSkinDlg  *pSkinDlg=new CSkinDlg;
	pSkinDlg->Create();
	
	return FALSE;
}


BOOL CMFC360DemoDlg::Create() //创建窗口和按钮
{
	m_SkinIndex=0;//初始化皮肤为0
	m_hWindow=XWnd_CreateWindowEx(NULL,NULL,NULL,WS_CHILD|WS_VISIBLE,0,0,800,800,m_hWnd,XC_SY_ROUND); //创建窗口
	if(m_hWindow)
	{
		XWnd_SetBorderSize(m_hWindow,0,0,0,0);//设置边界
		XWnd_EnableDragWindow(m_hWindow,FALSE);//拖拽窗口
		XWnd_SetRoundSize(m_hWindow,-10);//

		//标题栏
		m_hBottomText=XStatic_Create(0,6,234,20,L"   HIT 人事管理系统 1.0",m_hWindow);
		XStatic_AdjustSize(m_hBottomText);
		XEle_SetTextColor(m_hBottomText,RGB(255,255,255));
		XEle_SetBkTransparent(m_hBottomText,TRUE);
		XEle_EnableMouseThrough(m_hBottomText,TRUE);//zhe shi shen me
		RECT rect;
		XEle_GetClientRect(m_hBottomText,&rect);
		m_bottomText_width=rect.right-rect.left;//
        //背景设置
		m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame1.jpg");//导入图片
		m_hThemeBorder=XImage_LoadFileAdaptive(L"360image\\skin\\framemod_sim.png",12,48,122,166);

		XImage_SetDrawType(m_hThemeBackground,XC_IMAGE_TILE);//设置方式为平铺

		XWnd_SetImageNC(m_hWindow,m_hThemeBackground);
		XWnd_SetImage(m_hWindow,m_hThemeBorder);
        //设置下方的状态栏
		m_hBottomText=XStatic_Create(20,575,100,18,L"项目地址:https://github.com/diaohaha/",m_hWindow);
		XStatic_AdjustSize(m_hBottomText);
		XEle_SetTextColor(m_hBottomText,RGB(255,255,255));
		XEle_SetBkTransparent(m_hBottomText,TRUE);
		XEle_EnableMouseThrough(m_hBottomText,TRUE);//zhe shi shen me
		XEle_GetClientRect(m_hBottomText,&rect);
		m_bottomText_width=rect.right-rect.left;//

		//47*22 这里为关闭的按钮，虽然可以点击了，而且三种状态也有，但功能还没有
		m_hBtnClose=XBtn_Create(10,0,47,22,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnClose,TRUE);
		XEle_EnableFocus(m_hBtnClose,FALSE);
		XBtn_SetImageLeave(m_hBtnClose,XImage_LoadFileRect(L"360image\\sys_button_close.png",0,0,47,22));
		XBtn_SetImageStay(m_hBtnClose,XImage_LoadFileRect(L"360image\\sys_button_close.png",47,0,47,22));
		XBtn_SetImageDown(m_hBtnClose,XImage_LoadFileRect(L"360image\\sys_button_close.png",94,0,47,22));

		//44*22
		m_hBtnMax=XBtn_Create(10,0,33,22,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnMax,TRUE);
		XEle_EnableFocus(m_hBtnMax,FALSE);
		XBtn_SetImageLeave(m_hBtnMax,XImage_LoadFileRect(L"360image\\sys_button_max.png",0,0,33,22));
		XBtn_SetImageStay(m_hBtnMax,XImage_LoadFileRect(L"360image\\sys_button_max.png",33,0,33,22));
		XBtn_SetImageDown(m_hBtnMax,XImage_LoadFileRect(L"360image\\sys_button_max.png",66,0,33,22));

		m_hBtnMin=XBtn_Create(10,0,33,22,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnMin,TRUE);
		XEle_EnableFocus(m_hBtnMin,FALSE);
		XBtn_SetImageLeave(m_hBtnMin,XImage_LoadFileRect(L"360image\\sys_button_min.png",0,0,33,22));
		XBtn_SetImageStay(m_hBtnMin,XImage_LoadFileRect(L"360image\\sys_button_min.png",33,0,33,22));
		XBtn_SetImageDown(m_hBtnMin,XImage_LoadFileRect(L"360image\\sys_button_min.png",66,0,33,22));

		m_hBtnMenu=XBtn_Create(10,0,33,22,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnMenu,TRUE);
		XEle_EnableFocus(m_hBtnMenu,FALSE);
		XBtn_SetImageLeave(m_hBtnMenu,XImage_LoadFileRect(L"360image\\title_bar_menu.png",0,0,33,22));
		XBtn_SetImageStay(m_hBtnMenu,XImage_LoadFileRect(L"360image\\title_bar_menu.png",33,0,33,22));
		XBtn_SetImageDown(m_hBtnMenu,XImage_LoadFileRect(L"360image\\title_bar_menu.png",66,0,33,22));

		m_hBtnSkin=XBtn_Create(10,0,22,18,NULL,m_hWindow);
		XEle_SetBkTransparent(m_hBtnSkin,TRUE);
		XEle_EnableFocus(m_hBtnSkin,FALSE);
		XBtn_SetImageLeave(m_hBtnSkin,XImage_LoadFileRect(L"360image\\SkinButtom.png",0,0,22,18));
		XBtn_SetImageStay(m_hBtnSkin,XImage_LoadFileRect(L"360image\\SkinButtom.png",22,0,22,18));
		XBtn_SetImageDown(m_hBtnSkin,XImage_LoadFileRect(L"360image\\SkinButtom.png",44,0,22,18));

		CreateToolButtonAndPage();//创建页面切换按钮及子页面

		//注册事件
		XEle_RegisterEventEx(m_hBtnClose,XE_BNCLICK,MyFunClassCloseEventMsg,this);
		XEle_RegisterEventEx(m_hBtnSkin,XE_BNCLICK,MyFunClassChangeEventMsg,this);
		XEle_RegisterEventEx(m_hBtnMax,XE_BNCLICK,MyFunClassMaxEventMsg,this);
		XEle_RegisterEventEx(m_hBtnMin,XE_BNCLICK,MyFunClassMinEventMsg,this);

		AdjustLayout();
		XWnd_ShowWindow(m_hWindow,SW_SHOW); //显示窗口

		XWnd_RegisterMessage(m_hWindow, WM_LBUTTONDOWN, WinMouseLeftDown);
		return TRUE;
	}
	return FALSE;
}

void CMFC360DemoDlg::AdjustLayout()
{//每次都适应一下
	RECT rect;
	XWnd_GetClientRect(m_hWindow,&rect);

	RECT rc=rect;
	rc.left++;
	rc.right--;
	rc.top =110;
	rc.bottom-=26;

	XEle_SetRect(m_page_login.m_hEle,&rc);//设置页面的矩形,使之能铺满。
	XEle_SetRect(m_page_find.m_hEle,&rc);
	XEle_SetRect(m_page_aq.m_hEle,&rc);
	XEle_SetRect(m_page_set.m_hEle,&rc);
	XEle_SetRect(m_page_add.m_hEle,&rc);
	XEle_SetRect(m_page_cmd.m_hEle,&rc);

	rc.left=10;
	rc.right=rc.left+m_bottomText_width;
	rc.top=rect.bottom-23;
	rc.bottom=rc.top+18;
	XEle_SetRect(m_hBottomText,&rc);

	rc.top=0;
	rc.right=rect.right-5;
	rc.left=rc.right-47;
	rc.bottom=rc.top+22;
	XEle_SetRect(m_hBtnClose,&rc);

	rc.right=rc.left;
	rc.left=rc.right-33;
	XEle_SetRect(m_hBtnMax,&rc);

	rc.right=rc.left;
	rc.left=rc.right-33;
	XEle_SetRect(m_hBtnMin,&rc);

	rc.right=rc.left;
	rc.left=rc.right-33;
	XEle_SetRect(m_hBtnMenu,&rc);

	rc.right=rc.left-5;
	rc.left=rc.right-22;
	rc.bottom=18;
	XEle_SetRect(m_hBtnSkin,&rc);//对话框中的每一个对下都应写响应的适应方法
}

void CMFC360DemoDlg::CreateToolButtonAndPage()
{
	int left=3;
	int top=28;
	//这里设
	m_hImage_check_leave=XImage_LoadFile(L"360image\\toolBar\\toolbar_normal.png");
	m_hImage_check_stay=XImage_LoadFile(L"360image\\toolBar\\toolbar_hover.png");
	m_hImage_check_down=XImage_LoadFile(L"360image\\toolBar\\toolbar_pushed.png");

	HIMAGE hIcon=XImage_LoadFile(L"360image\\toolBar\\ico_main.png");
	HELE hRadio1=CreateToolButton(left,top,hIcon,L"首页"); left+=74;
	hIcon=XImage_LoadFile(L"360image\\toolBar\\ico_database.png");
	HELE hRadio2=CreateToolButton(left,top,hIcon,L"人事管理"); left+=74;
	hIcon=XImage_LoadFile(L"360image\\toolBar\\ico_anquan.png");
	HELE hRadio3=CreateToolButton(left,top,hIcon,L"数据安全"); left+=74;
	hIcon=XImage_LoadFile(L"360image\\toolBar\\ico_setting.png");
	HELE hRadio5=CreateToolButton(left,top,hIcon,L"其他功能"); left+=74;
	hIcon=XImage_LoadFile(L"360image\\toolBar\\ico_setting.png");
	hRadio4=CreateToolButton(left,top,hIcon,L"数据添加"); left+=74;
	hIcon=XImage_LoadFile(L"360image\\toolBar\\ico_setting.png");
	HELE hRadio7=CreateToolButton(left,top,hIcon,L"版本信息"); left+=74;

	XBtn_SetCheck(hRadio1,TRUE);//初始化设置在第一个按钮上

	m_page_login.Create();
	m_page_find.Create();
	m_page_aq.Create();
	m_page_set.Create();
	m_page_add.Create();
	m_page_cmd.Create();

	XRadio_SetBindEle(hRadio1,m_page_login.m_hEle);
	//点击页面的跳转
		
	XRadio_SetBindEle(hRadio2,m_page_find.m_hEle);
	XRadio_SetBindEle(hRadio3,m_page_aq.m_hEle);
	XRadio_SetBindEle(hRadio5,m_page_set.m_hEle);
	XRadio_SetBindEle(hRadio4,m_page_add.m_hEle);
	XRadio_SetBindEle(hRadio7,m_page_cmd.m_hEle);
	
}


HELE CMFC360DemoDlg::CreateToolButton(int x,int y,HIMAGE hIcon,wchar_t *pName)
{
	HELE hRadio=XRadio_Create(x,y,74,82,pName,m_hWindow);//添加按钮
	XRadio_EnableButtonStyle(hRadio,TRUE);
	XRadio_SetGroupID(hRadio,1);//可能是不让同时处于按下的状态

	XBtn_SetIcon(hRadio,hIcon);//设置按钮图标
	XBtn_SetIconAlign(hRadio,XC_ICON_ALIGN_TOP);//设置图标位置
	XEle_SetBkTransparent(hRadio,TRUE);//
	XEle_SetTextColor(hRadio,RGB(255,255,255));
	XBtn_SetOffset(hRadio,0,-3);
    //设置按钮的事件
	//处于三种状态下的情形，已经被封装，只需传入图片
	XRadio_SetImageLeave_UnCheck(hRadio,m_hImage_check_leave);
	XRadio_SetImageStay_UnCheck(hRadio,m_hImage_check_stay);
	XRadio_SetImageDown_UnCheck(hRadio,m_hImage_check_down);

	XRadio_SetImageLeave_Check(hRadio,m_hImage_check_down);
	XRadio_SetImageStay_Check(hRadio,m_hImage_check_down);
	XRadio_SetImageDown_Check(hRadio,m_hImage_check_down);

	XEle_EnableFocus(hRadio,FALSE);
	return hRadio;
}


















//////////////////////////////////////////////
void CXPage_login::Create()
{
	m_hEle=XPic_Create(2,110,300,465,mainWnd->m_hWindow);
	XPic_SetImage(m_hEle, XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(m_hEle,TRUE);
	//XEle_ShowEle(m_hEle,FALSE);
	
	//HELE hGif=XGif_Create(500,0,200,200,m_hEle);
	//XGif_SetImage(hGif,L"gif.gif");
	//HELE hDateTime=XDateTime_Create(400,300,200,20,m_hEle);

    //贴图
    //XDateTime_SetImage(hDateTime,XImage_LoadFile(L"360image\\page9\\bg.png",true));
	//HELE hMonth=XMonthCal_Create(500,200,192,150,m_hEle);
	//XEle_SetBorderColor(hMonth,RGB(255,255,0));//边框颜色

	HELE hStatic=XStatic_Create(50,145,72,20,L"管理员",m_hEle);
    XEle_SetBkTransparent(hStatic,true); //设置背景透明
	hStatic=XStatic_Create(50,185,72,20,L"密  码",m_hEle);
    XEle_SetBkTransparent(hStatic,true); //设置背景透明

	hEdit1=XEdit_Create(100,140,200,22,m_hEle);
	XEle_SetBkTransparent(hEdit1,TRUE);
	XEle_EnableBorder(hEdit1,true);
	hEdit2=XEdit_Create(100,180,200,22,m_hEle);
	XEle_SetBkTransparent(hEdit2,TRUE);
	XEle_EnableBorder(hEdit2,true);
    
	HELE hButton=XBtn_Create(220,250,80,30,L"登陆",m_hEle);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CXPage_login::denglu);
}	
BOOL  CXPage_login::denglu(HELE hEle,HELE hEventEle)
{
	wchar_t user[MAX_PATH]={0};
	XEdit_GetText(hEdit1,user,MAX_PATH);
	wchar_t passwd[MAX_PATH]={0};
	XEdit_GetText(hEdit2,passwd,MAX_PATH);

	CString cuser,cpasswd;
	wchar_t *true_user;
	wchar_t *true_passwd;

	mysql_query(&data.mysql,"select * from users");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int sign=0;
	while(row=mysql_fetch_row(data.result))
	{	
		cuser.Format("%s",row[0]);
		true_user=cuser.AllocSysString();
		if(!wcscmp(user,true_user))
		{
			cpasswd.Format("%s",row[1]);
			true_passwd=cpasswd.AllocSysString();
			if(!wcscmp(passwd,true_passwd))
			{
				sign=1;
				now_user=cuser;
				break;
			}
		}
	}
	
	if(sign)
	{
		MessageBox(NULL,"登陆成功!","提示",XMB_OK);
		login_sign=1;
		//XWnd_RedrawWnd(mainWnd->m_hWindow);
	}
	else
	{
		MessageBox(NULL,"用户名或密码错误!","提示",XMB_OK);
	}
	return false;
}


void CXPage_login::AdjustLayout()
{
	
}









/////////////////////////////////////////////////////////

void CXPage_renshi::Create()
{
	m_hEle=XPic_Create(2,110,300,465,mainWnd->m_hWindow);
	XPic_SetImage(m_hEle, XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(m_hEle,TRUE);
	XEle_ShowEle(m_hEle,FALSE);

	hComboBox=XComboBox_Create(10,20,100,28,m_hEle);
    XComboBox_EnableEdit(hComboBox,false); //禁止编辑内容
    XComboBox_SetListHeight(hComboBox,60); //设置下拉列表高度
    XComboBox_AddString(hComboBox,L"职工编号");
    XComboBox_AddString(hComboBox,L"姓名");
    XComboBox_AddString(hComboBox,L"性别");
    XComboBox_SetSelectItem(hComboBox,0);
	hEdit_chaxun=XEdit_Create(120,20,100,28,m_hEle);
	XEle_SetBkTransparent(hEdit_chaxun,TRUE);
	XEle_EnableBorder(hEdit_chaxun,true);

	HELE Button_chaxun=XBtn_Create(250,20,70,30,L"查询",m_hEle);
	XCGUI_RegEleEvent(Button_chaxun,XE_BNCLICK,&CXPage_renshi::chaxun);
	HELE Button_showall=XBtn_Create(350,20,70,30,L"显示全部",m_hEle);
	XCGUI_RegEleEvent(Button_showall,XE_BNCLICK,&CXPage_renshi::showall);
	//列表框
	m_hList=XList_Create(0,64,850,358,m_hEle);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);
	XList_AddColumn(m_hList,100,L"职工编码"); 
	XList_AddColumn(m_hList,80,L"姓名"); 
	XList_AddColumn(m_hList,60,L"性别"); 
	XList_AddColumn(m_hList,80,L"名族");
	XList_AddColumn(m_hList,80,L"出生年月");
	XList_AddColumn(m_hList,50,L"婚否");
	XList_AddColumn(m_hList,80,L"文化程度");
	XList_AddColumn(m_hList,80,L"健康状况");
	XList_AddColumn(m_hList,60,L"政治面貌");
	XList_AddColumn(m_hList,80,L"职称");
	XList_AddColumn(m_hList,80,L"籍贯");
	XList_AddColumn(m_hList,80,L"身份证号");
	XList_AddColumn(m_hList,80,L"毕业学校");
	XList_AddColumn(m_hList,80,L"特长");
	XList_AddColumn(m_hList,80,L"户口所在地");
	XList_AddColumn(m_hList,80,L"户口性质");
	XList_AddColumn(m_hList,80,L"现住址");
	XList_AddColumn(m_hList,80,L"职务");
	XList_AddColumn(m_hList,80,L"工种");
	XList_AddColumn(m_hList,80,L"技术培训");
	XList_AddColumn(m_hList,80,L"奖励处分");
	XList_AddColumn(m_hList,80,L"说明");
	XList_AddColumn(m_hList,80,L"填表人签名");
	XList_AddColumn(m_hList,80,L"填表日期");
	XList_AddColumn(m_hList,80,L"公司审查意见");
	XList_AddColumn(m_hList,80,L"审查日期");
	XList_AddColumn(m_hList,80,L"人员性质");
	XList_AddColumn(m_hList,80,L"入场时间");
	XList_AddColumn(m_hList,80,L"人员状态");
	XList_AddColumn(m_hList,80,L"备注");
	XList_AddColumn(m_hList,80,L"分属部门");


	mysql_query(&data.mysql,"select * from m_dadj");
	sprintf(now_sql,"select * from m_dadj");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(row=mysql_fetch_row(data.result))
	{
		CString zgbm,xm,xb,mz,csny,hyzk,whcd,jkzk,zzmm,zcbm,jg,sfzh,byxx,zytc,hkszd,hkxz,xzz,zw,gzm,jspx,jlcf,smwt,tbrqm,tbrq,gsyj,scrq,ryxz,rcsj,ryzt,bz,bmbm;
		zgbm.Format("%s",row[0]);//获得数据库结果
		xm.Format("%s",row[1]);
		xb.Format("%s",row[2]);
		mz.Format("%s",row[3]);
		csny.Format("%s",row[4]);
		hyzk.Format("%s",row[5]);
		whcd.Format("%s",row[6]);
		jkzk.Format("%s",row[7]);
		zzmm.Format("%s",row[8]);
		zcbm.Format("%s",row[9]);
		jg.Format("%s",row[10]);
		sfzh.Format("%s",row[11]);
		byxx.Format("%s",row[12]);
		zytc.Format("%s",row[13]);
		hkszd.Format("%s",row[14]);
		hkxz.Format("%s",row[15]);
		xzz.Format("%s",row[16]);
		zw.Format("%s",row[17]);
		gzm.Format("%s",row[18]);
		jspx.Format("%s",row[19]);
		jlcf.Format("%s",row[20]);
		smwt.Format("%s",row[21]);
		tbrqm.Format("%s",row[22]);
		tbrq.Format("%s",row[23]);
		gsyj.Format("%s",row[24]);
		scrq.Format("%s",row[25]);
		ryxz.Format("%s",row[26]);
		rcsj.Format("%s",row[27]);
		ryzt.Format("%s",row[28]);
		bz.Format("%s",row[29]);
		bmbm.Format("%s",row[30]);
		
		XList_AddItem(m_hList,zgbm.AllocSysString());
		XList_SetItemText(m_hList,i,1,xm.AllocSysString());
		XList_SetItemText(m_hList,i,2,xb.AllocSysString());
		XList_SetItemText(m_hList,i,3,mz.AllocSysString());
		XList_SetItemText(m_hList,i,4,csny.AllocSysString());
		XList_SetItemText(m_hList,i,5,hyzk.AllocSysString());
		XList_SetItemText(m_hList,i,6,whcd.AllocSysString());
		XList_SetItemText(m_hList,i,7,jkzk.AllocSysString());
		XList_SetItemText(m_hList,i,8,zzmm.AllocSysString());
		XList_SetItemText(m_hList,i,9,zcbm.AllocSysString());
		XList_SetItemText(m_hList,i,10,jg.AllocSysString());
		XList_SetItemText(m_hList,i,11,sfzh.AllocSysString());
		XList_SetItemText(m_hList,i,12,byxx.AllocSysString());
		XList_SetItemText(m_hList,i,13,zytc.AllocSysString());
		XList_SetItemText(m_hList,i,14,hkszd.AllocSysString());
		XList_SetItemText(m_hList,i,15,hkxz.AllocSysString());
		XList_SetItemText(m_hList,i,16,xzz.AllocSysString());
		XList_SetItemText(m_hList,i,17,zw.AllocSysString());
		XList_SetItemText(m_hList,i,18,gzm.AllocSysString());
		XList_SetItemText(m_hList,i,19,jspx.AllocSysString());
		XList_SetItemText(m_hList,i,20,jlcf.AllocSysString());
		XList_SetItemText(m_hList,i,21,smwt.AllocSysString());
		XList_SetItemText(m_hList,i,22,tbrqm.AllocSysString());
		XList_SetItemText(m_hList,i,23,tbrq.AllocSysString());
		XList_SetItemText(m_hList,i,24,gsyj.AllocSysString());
		XList_SetItemText(m_hList,i,25,scrq.AllocSysString());
		XList_SetItemText(m_hList,i,26,ryxz.AllocSysString());
		XList_SetItemText(m_hList,i,27,rcsj.AllocSysString());
		XList_SetItemText(m_hList,i,28,ryzt.AllocSysString());
		XList_SetItemText(m_hList,i,29,bz.AllocSysString());
		XList_SetItemText(m_hList,i,30,bmbm.AllocSysString());
		i++;	
	}
	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);
	mysql_free_result(data.result);

	HELE m_hBottom=XPic_Create(0,420,800,50,m_hEle);
	XEle_SetBkTransparent(m_hBottom,TRUE);
	HELE hButton1=XBtn_Create(420,6,100,28,L"生成报表",m_hBottom);
	XCGUI_RegEleEvent(hButton1,XE_BNCLICK,&CXPage_renshi::scbb);
	HELE hButton=XBtn_Create(550,6,100,28,L"编辑",m_hBottom);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CXPage_renshi::edit);
	HELE hButton2=XBtn_Create(680,6,100,28,L"删除",m_hBottom);
	XCGUI_RegEleEvent(hButton2,XE_BNCLICK,&CXPage_renshi::del);
}

void CXPage_renshi::AdjustLayout()
{

}
BOOL CXPage_renshi::showall(HELE hELe,HELE hEventEle)
{
	XList_DeleteAllItems(m_hList);
	CString zgbm,xm,xb,mz,csny,hyzk,whcd,jkzk,zzmm,zcbm,jg,sfzh,byxx,zytc,hkszd,hkxz,xzz,zw,gzm,jspx,jlcf,smwt,tbrqm,tbrq,gsyj,scrq,ryxz,rcsj,ryzt,bz,bmbm;
	mysql_query(&data.mysql,"select * from m_dadj");
	sprintf(now_sql,"select * from m_dadj");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(row=mysql_fetch_row(data.result))
	{
		zgbm.Format("%s",row[0]);//获得数据库结果
		xm.Format("%s",row[1]);
		xb.Format("%s",row[2]);
		mz.Format("%s",row[3]);
		csny.Format("%s",row[4]);
		hyzk.Format("%s",row[5]);
		whcd.Format("%s",row[6]);
		jkzk.Format("%s",row[7]);
		zzmm.Format("%s",row[8]);
		zcbm.Format("%s",row[9]);
		jg.Format("%s",row[10]);
		sfzh.Format("%s",row[11]);
		byxx.Format("%s",row[12]);
		zytc.Format("%s",row[13]);
		hkszd.Format("%s",row[14]);
		hkxz.Format("%s",row[15]);
		xzz.Format("%s",row[16]);
		zw.Format("%s",row[17]);
		gzm.Format("%s",row[18]);
		jspx.Format("%s",row[19]);
		jlcf.Format("%s",row[20]);
		smwt.Format("%s",row[21]);
		tbrqm.Format("%s",row[22]);
		tbrq.Format("%s",row[23]);
		gsyj.Format("%s",row[24]);
		scrq.Format("%s",row[25]);
		ryxz.Format("%s",row[26]);
		rcsj.Format("%s",row[27]);
		ryzt.Format("%s",row[28]);
		bz.Format("%s",row[29]);
		bmbm.Format("%s",row[30]);
		
		XList_AddItem(m_hList,zgbm.AllocSysString());
		XList_SetItemText(m_hList,i,1,xm.AllocSysString());
		XList_SetItemText(m_hList,i,2,xb.AllocSysString());
		XList_SetItemText(m_hList,i,3,mz.AllocSysString());
		XList_SetItemText(m_hList,i,4,csny.AllocSysString());
		XList_SetItemText(m_hList,i,5,hyzk.AllocSysString());
		XList_SetItemText(m_hList,i,6,whcd.AllocSysString());
		XList_SetItemText(m_hList,i,7,jkzk.AllocSysString());
		XList_SetItemText(m_hList,i,8,zzmm.AllocSysString());
		XList_SetItemText(m_hList,i,9,zcbm.AllocSysString());
		XList_SetItemText(m_hList,i,10,jg.AllocSysString());
		XList_SetItemText(m_hList,i,11,sfzh.AllocSysString());
		XList_SetItemText(m_hList,i,12,byxx.AllocSysString());
		XList_SetItemText(m_hList,i,13,zytc.AllocSysString());
		XList_SetItemText(m_hList,i,14,hkszd.AllocSysString());
		XList_SetItemText(m_hList,i,15,hkxz.AllocSysString());
		XList_SetItemText(m_hList,i,16,xzz.AllocSysString());
		XList_SetItemText(m_hList,i,17,zw.AllocSysString());
		XList_SetItemText(m_hList,i,18,gzm.AllocSysString());
		XList_SetItemText(m_hList,i,19,jspx.AllocSysString());
		XList_SetItemText(m_hList,i,20,jlcf.AllocSysString());
		XList_SetItemText(m_hList,i,21,smwt.AllocSysString());
		XList_SetItemText(m_hList,i,22,tbrqm.AllocSysString());
		XList_SetItemText(m_hList,i,23,tbrq.AllocSysString());
		XList_SetItemText(m_hList,i,24,gsyj.AllocSysString());
		XList_SetItemText(m_hList,i,25,scrq.AllocSysString());
		XList_SetItemText(m_hList,i,26,ryxz.AllocSysString());
		XList_SetItemText(m_hList,i,27,rcsj.AllocSysString());
		XList_SetItemText(m_hList,i,28,ryzt.AllocSysString());
		XList_SetItemText(m_hList,i,29,bz.AllocSysString());
		XList_SetItemText(m_hList,i,30,bmbm.AllocSysString());
		i++;	
	}
	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);
	mysql_free_result(data.result);
	XWnd_RedrawWnd(mainWnd->m_hWindow);
	return 0;
}
BOOL CXPage_renshi::chaxun(HELE hELe,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	int lie=XComboBox_GetSelectItem	(hComboBox);
	XList_DeleteAllItems(m_hList);
	wchar_t zgbm[MAX_PATH]={0};
	XEdit_GetText(hEdit_chaxun,zgbm,MAX_PATH);
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP,NULL,zgbm,-1,NULL,0,NULL,FALSE);
	char *szgbm;
	szgbm = new char[dwNum];
	WideCharToMultiByte (CP_OEMCP,NULL,zgbm,-1,szgbm,dwNum,NULL,FALSE);
	char sqlBuf[1024];
	char *bfh="%";
	switch(lie)
	{
		case 0:{
				sprintf(sqlBuf,"select * from m_dadj where zgbm=%s",szgbm);
				sprintf(now_sql,"select * from m_dadj where zgbm=%s",szgbm);
				break;
		   }
		case 1:{
				sprintf(sqlBuf,"select * from m_dadj where xm like '%s%s'",szgbm,bfh);
				sprintf(now_sql,"select * from m_dadj where xm like '%s%s'",szgbm,bfh);
				break;
		   }
		case 2:{
				sprintf(sqlBuf,"select * from m_dadj where xb='%s'",szgbm);
				sprintf(now_sql,"select * from m_dadj where xb='%s'",szgbm);
				break;
		   }
	}
	if(mysql_query(&data.mysql,sqlBuf))
	{
		MessageBox(NULL,"查询失败!","提示",XMB_OK);
		return 0;
	}
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	delete []szgbm;
	
	while(row=mysql_fetch_row(data.result))
	{
		CString zgbm,xm,xb,mz,csny,hyzk,whcd,jkzk,zzmm,zcbm,jg,sfzh,byxx,zytc,hkszd,hkxz,xzz,zw,gzm,jspx,jlcf,smwt,tbrqm,tbrq,gsyj,scrq,ryxz,rcsj,ryzt,bz,bmbm;
		zgbm.Format("%s",row[0]);//获得数据库结果
		xm.Format("%s",row[1]);
		xb.Format("%s",row[2]);
		mz.Format("%s",row[3]);
		csny.Format("%s",row[4]);
		hyzk.Format("%s",row[5]);
		whcd.Format("%s",row[6]);
		jkzk.Format("%s",row[7]);
		zzmm.Format("%s",row[8]);
		zcbm.Format("%s",row[9]);
		jg.Format("%s",row[10]);
		sfzh.Format("%s",row[11]);
		byxx.Format("%s",row[12]);
		zytc.Format("%s",row[13]);
		hkszd.Format("%s",row[14]);
		hkxz.Format("%s",row[15]);
		xzz.Format("%s",row[16]);
		zw.Format("%s",row[17]);
		gzm.Format("%s",row[18]);
		jspx.Format("%s",row[19]);
		jlcf.Format("%s",row[20]);
		smwt.Format("%s",row[21]);
		tbrqm.Format("%s",row[22]);
		tbrq.Format("%s",row[23]);
		gsyj.Format("%s",row[24]);
		scrq.Format("%s",row[25]);
		ryxz.Format("%s",row[26]);
		rcsj.Format("%s",row[27]);
		ryzt.Format("%s",row[28]);
		bz.Format("%s",row[29]);
		bmbm.Format("%s",row[30]);
		
		XList_AddItem(m_hList,zgbm.AllocSysString());
		XList_SetItemText(m_hList,i,1,xm.AllocSysString());
		XList_SetItemText(m_hList,i,2,xb.AllocSysString());
		XList_SetItemText(m_hList,i,3,mz.AllocSysString());
		XList_SetItemText(m_hList,i,4,csny.AllocSysString());
		XList_SetItemText(m_hList,i,5,hyzk.AllocSysString());
		XList_SetItemText(m_hList,i,6,whcd.AllocSysString());
		XList_SetItemText(m_hList,i,7,jkzk.AllocSysString());
		XList_SetItemText(m_hList,i,8,zzmm.AllocSysString());
		XList_SetItemText(m_hList,i,9,zcbm.AllocSysString());
		XList_SetItemText(m_hList,i,10,jg.AllocSysString());
		XList_SetItemText(m_hList,i,11,sfzh.AllocSysString());
		XList_SetItemText(m_hList,i,12,byxx.AllocSysString());
		XList_SetItemText(m_hList,i,13,zytc.AllocSysString());
		XList_SetItemText(m_hList,i,14,hkszd.AllocSysString());
		XList_SetItemText(m_hList,i,15,hkxz.AllocSysString());
		XList_SetItemText(m_hList,i,16,xzz.AllocSysString());
		XList_SetItemText(m_hList,i,17,zw.AllocSysString());
		XList_SetItemText(m_hList,i,18,gzm.AllocSysString());
		XList_SetItemText(m_hList,i,19,jspx.AllocSysString());
		XList_SetItemText(m_hList,i,20,jlcf.AllocSysString());
		XList_SetItemText(m_hList,i,21,smwt.AllocSysString());
		XList_SetItemText(m_hList,i,22,tbrqm.AllocSysString());
		XList_SetItemText(m_hList,i,23,tbrq.AllocSysString());
		XList_SetItemText(m_hList,i,24,gsyj.AllocSysString());
		XList_SetItemText(m_hList,i,25,scrq.AllocSysString());
		XList_SetItemText(m_hList,i,26,ryxz.AllocSysString());
		XList_SetItemText(m_hList,i,27,rcsj.AllocSysString());
		XList_SetItemText(m_hList,i,28,ryzt.AllocSysString());
		XList_SetItemText(m_hList,i,29,bz.AllocSysString());
		XList_SetItemText(m_hList,i,30,bmbm.AllocSysString());
		i++;	
	}
	XWnd_RedrawWnd(mainWnd->m_hWindow);
	mysql_free_result(data.result);
	return 1;
}
BOOL CXPage_renshi::del(HELE hELe,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	int sign=XList_GetSelectCount(m_hList);
	if(sign<=0)
	{
		MessageBox(NULL,"请先选中一项!","提示",XMB_OK);
		return false;
	}
	int j=XList_GetSelectItem	(m_hList);
	j++;
	CString zgbm;
	mysql_query(&data.mysql,now_sql);//用来保存当前的查询语句
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(i<j)
	{
		row=mysql_fetch_row(data.result);
		i++;
	}
	mysql_free_result(data.result);
	int m=1;
	char sql[1024];
	sprintf(sql,"delete from m_dadj where zgbm='%s'",row[0]);
	m=mysql_query(&data.mysql,sql);
	if(m==0)
	{
		XList_DeleteItem(m_hList,sign+1);
		XEle_RedrawEle(m_hList);
	}
	else
	{
		MessageBox(NULL,"删除错误,请检查输入!","提示",XMB_OK);
	}
	return 0;
}
BOOL CXPage_renshi::scbb(HELE hEle,HELE hEbentELe)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	int sign=XList_GetSelectCount(m_hList);
	if(sign<=0)
	{
		MessageBox(NULL,"请先选中一项!","提示",XMB_OK);
		return false;
	}
	int j=XList_GetSelectItem	(m_hList);
	j++;
	CString zgbm,xm,xb,mz,csny,hyzk,whcd,jkzk,zzmm,zcbm,jg,sfzh,byxx,zytc,hkszd,hkxz,xzz,zw,gzm,jspx,jlcf,smwt,tbrqm,tbrq,gsyj,scrq,ryxz,rcsj,ryzt,bz,bmbm;
	mysql_query(&data.mysql,now_sql);//用来保存当前的查询语句
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(i<j)
	{
		row=mysql_fetch_row(data.result);
		i++;
	}
	zgbm.Format("%s",row[0]);//获得数据库结果
	xm.Format("%s",row[1]);
	xb.Format("%s",row[2]);
	mz.Format("%s",row[3]);
	csny.Format("%s",row[4]);
	hyzk.Format("%s",row[5]);
	whcd.Format("%s",row[6]);
	jkzk.Format("%s",row[7]);
	zzmm.Format("%s",row[8]);
	zcbm.Format("%s",row[9]);
	jg.Format("%s",row[10]);
	sfzh.Format("%s",row[11]);
	byxx.Format("%s",row[12]);
	zytc.Format("%s",row[13]);
	hkszd.Format("%s",row[14]);
	hkxz.Format("%s",row[15]);
	xzz.Format("%s",row[16]);
	zw.Format("%s",row[17]);
	gzm.Format("%s",row[18]);
	jspx.Format("%s",row[19]);
	jlcf.Format("%s",row[20]);
	smwt.Format("%s",row[21]);
	tbrqm.Format("%s",row[22]);
	tbrq.Format("%s",row[23]);
	gsyj.Format("%s",row[24]);
	scrq.Format("%s",row[25]);
	ryxz.Format("%s",row[26]);
	rcsj.Format("%s",row[27]);
	ryzt.Format("%s",row[28]);
	bz.Format("%s",row[29]);
	bmbm.Format("%s",row[30]);
	mysql_free_result(data.result);

	CBaobiaoDlg  *pDlg=new CBaobiaoDlg;
	pDlg->Create();

	return true;
}
void CBaobiaoDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(0,0,300,400,L"报表生成");
	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);

	RECT rect;
    XWnd_GetClientRect(m_hWindow,&rect);
	HXCGUI hWeb=NULL;
	hWeb=XWeb_Create(m_hWindow,2,2,rect.right-4,rect.bottom-2); //浏览器控件
    XWeb_OpenURL(hWeb,L"C:\\a\\a.html");

	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}


BOOL CXPage_renshi::edit(HELE hELe,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	int sign=XList_GetSelectCount(m_hList);
	if(sign<=0)
	{
		MessageBox(NULL,"请先选中一项!","提示",XMB_OK);
		return false;
	}
	int j=XList_GetSelectItem	(m_hList);
	j++;
	CString zgbm,xm,xb,mz,csny,hyzk,whcd,jkzk,zzmm,zcbm,jg,sfzh,byxx,zytc,hkszd,hkxz,xzz,zw,gzm,jspx,jlcf,smwt,tbrqm,tbrq,gsyj,scrq,ryxz,rcsj,ryzt,bz,bmbm;
	mysql_query(&data.mysql,now_sql);//用来保存当前的查询语句
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(i<j)
	{
		row=mysql_fetch_row(data.result);
		i++;
	}
	zgbm.Format("%s",row[0]);//获得数据库结果
	xm.Format("%s",row[1]);
	xb.Format("%s",row[2]);
	mz.Format("%s",row[3]);
	csny.Format("%s",row[4]);
	hyzk.Format("%s",row[5]);
	whcd.Format("%s",row[6]);
	jkzk.Format("%s",row[7]);
	zzmm.Format("%s",row[8]);
	zcbm.Format("%s",row[9]);
	jg.Format("%s",row[10]);
	sfzh.Format("%s",row[11]);
	byxx.Format("%s",row[12]);
	zytc.Format("%s",row[13]);
	hkszd.Format("%s",row[14]);
	hkxz.Format("%s",row[15]);
	xzz.Format("%s",row[16]);
	zw.Format("%s",row[17]);
	gzm.Format("%s",row[18]);
	jspx.Format("%s",row[19]);
	jlcf.Format("%s",row[20]);
	smwt.Format("%s",row[21]);
	tbrqm.Format("%s",row[22]);
	tbrq.Format("%s",row[23]);
	gsyj.Format("%s",row[24]);
	scrq.Format("%s",row[25]);
	ryxz.Format("%s",row[26]);
	rcsj.Format("%s",row[27]);
	ryzt.Format("%s",row[28]);
	bz.Format("%s",row[29]);
	bmbm.Format("%s",row[30]);
	mysql_free_result(data.result);
	
	edit_view=XSView_Create(10,90,830,300,m_hEle);
    XSView_SetSize(edit_view,600,800); //设置滚动视图内容大小1000代表的是高

	HELE hStatic11=XStatic_Create(20,10,144,40,L"职工编号",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,10,144,40,L"姓名",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,50,144,40,L"性别",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,50,144,40,L"民族",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,90,144,40,L"出生年月",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,90,144,40,L"婚否",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,130,144,40,L"文化程度编码",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,130,144,40,L"健康状况",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,170,144,40,L"政治面貌",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,170,144,40,L"职称编码",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,210,144,40,L"籍贯",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,250,144,40,L"身份证号",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,250,144,40,L"毕业学校",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,290,144,40,L"专业及特长",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,330,144,40,L"户口所在地",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,370,144,40,L"户口性质",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,370,144,40,L"现住址",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,410,144,40,L"职务",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,410,144,40,L"工种名",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,450,144,40,L"何时技术培训",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,450,144,40,L"何时奖励处分",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,490,144,40,L"需要说明问题",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,530,144,40,L"填表人签名",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,530,144,40,L"填表日期",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,570,144,40,L"公司审核意见",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,610,144,40,L"审核日期",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,610,144,40,L"人员性质",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,650,144,40,L"入场时间",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,650,144,40,L"人员状态",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,690,144,40,L"备注",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,730,144,40,L"部门编码",edit_view);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hEdit_1_1=XEdit_Create(160,10,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_1,TRUE);
	XEle_EnableBorder(hEdit_1_1,true);
	hEdit_1_2=XEdit_Create(540,10,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_2,TRUE);
	XEle_EnableBorder(hEdit_1_2,true);
	hEdit_1_3=XEdit_Create(160,50,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_3,TRUE);
	XEle_EnableBorder(hEdit_1_3,true);
	hEdit_1_4=XEdit_Create(540,50,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_4,TRUE);
	XEle_EnableBorder(hEdit_1_4,true);
	hEdit_1_5=XEdit_Create(160,90,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_5,TRUE);
	XEle_EnableBorder(hEdit_1_5,true);
	hEdit_1_6=XEdit_Create(540,90,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_6,TRUE);
	XEle_EnableBorder(hEdit_1_6,true);
	hEdit_1_7=XEdit_Create(160,130,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_7,TRUE);
	XEle_EnableBorder(hEdit_1_7,true);
	hEdit_1_8=XEdit_Create(540,130,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_8,TRUE);
	XEle_EnableBorder(hEdit_1_8,true);
	hEdit_1_9=XEdit_Create(160,170,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_9,TRUE);
	XEle_EnableBorder(hEdit_1_9,true);
	hEdit_1_10=XEdit_Create(540,170,200,22,edit_view);//-------200-------------------------
	XEle_SetBkTransparent(hEdit_1_10,TRUE);
	XEle_EnableBorder(hEdit_1_10,true);
	hEdit_1_11=XEdit_Create(160,210,577,22,edit_view);//----577----------------------------
	XEle_SetBkTransparent(hEdit_1_11,TRUE);
	XEle_EnableBorder(hEdit_1_11,true);
	hEdit_1_12=XEdit_Create(160,250,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_12,TRUE);
	XEle_EnableBorder(hEdit_1_12,true);
	hEdit_1_13=XEdit_Create(540,250,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_13,TRUE);
	XEle_EnableBorder(hEdit_1_13,true);
	hEdit_1_14=XEdit_Create(160,290,577,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_14,TRUE);
	XEle_EnableBorder(hEdit_1_14,true);
	hEdit_1_15=XEdit_Create(160,330,577,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_15,TRUE);
	XEle_EnableBorder(hEdit_1_15,true);
	hEdit_1_16=XEdit_Create(160,370,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_16,TRUE);
	XEle_EnableBorder(hEdit_1_16,true);
	hEdit_1_17=XEdit_Create(540,370,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_17,TRUE);
	XEle_EnableBorder(hEdit_1_17,true);
	hEdit_1_18=XEdit_Create(160,410,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_18,TRUE);
	XEle_EnableBorder(hEdit_1_18,true);
	hEdit_1_19=XEdit_Create(540,410,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_19,TRUE);
	XEle_EnableBorder(hEdit_1_19,true);
	hEdit_1_20=XEdit_Create(160,450,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_20,TRUE);
	XEle_EnableBorder(hEdit_1_20,true);
	hEdit_1_21=XEdit_Create(540,450,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_21,TRUE);
	XEle_EnableBorder(hEdit_1_21,true);
	hEdit_1_22=XEdit_Create(160,490,577,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_22,TRUE);
	XEle_EnableBorder(hEdit_1_22,true);
	hEdit_1_23=XEdit_Create(160,530,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_23,TRUE);
	XEle_EnableBorder(hEdit_1_23,true);
	hEdit_1_24=XEdit_Create(540,530,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_24,TRUE);
	XEle_EnableBorder(hEdit_1_24,true);
	hEdit_1_25=XEdit_Create(160,570,577,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_25,TRUE);
	XEle_EnableBorder(hEdit_1_25,true);
	hEdit_1_26=XEdit_Create(160,610,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_26,TRUE);
	XEle_EnableBorder(hEdit_1_26,true);
	hEdit_1_27=XEdit_Create(540,610,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_27,TRUE);
	XEle_EnableBorder(hEdit_1_27,true);
	hEdit_1_28=XEdit_Create(160,650,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_28,TRUE);
	XEle_EnableBorder(hEdit_1_28,true);
	hEdit_1_29=XEdit_Create(540,650,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_29,TRUE);
	XEle_EnableBorder(hEdit_1_29,true);
	hEdit_1_30=XEdit_Create(160,690,577,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_30,TRUE);
	XEle_EnableBorder(hEdit_1_30,true);
	hEdit_1_31=XEdit_Create(160,730,200,22,edit_view);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_31,TRUE);
	XEle_EnableBorder(hEdit_1_31,true);

	XEdit_SetText (hEdit_1_1,zgbm.AllocSysString());
	XEdit_SetText (hEdit_1_2,xm.AllocSysString());
	XEdit_SetText (hEdit_1_3,xb.AllocSysString());
	XEdit_SetText (hEdit_1_4,mz.AllocSysString());
	XEdit_SetText (hEdit_1_5,csny.AllocSysString());
	XEdit_SetText (hEdit_1_6,hyzk.AllocSysString());
	XEdit_SetText (hEdit_1_7,whcd.AllocSysString());
	XEdit_SetText (hEdit_1_8,jkzk.AllocSysString());
	XEdit_SetText (hEdit_1_9,zzmm.AllocSysString());
	XEdit_SetText (hEdit_1_10,zcbm.AllocSysString());
	XEdit_SetText (hEdit_1_11,jg.AllocSysString());
	XEdit_SetText (hEdit_1_12,sfzh.AllocSysString());
	XEdit_SetText (hEdit_1_13,byxx.AllocSysString());
	XEdit_SetText (hEdit_1_14,zytc.AllocSysString());
	XEdit_SetText (hEdit_1_15,hkszd.AllocSysString());
	XEdit_SetText (hEdit_1_16,hkxz.AllocSysString());
	XEdit_SetText (hEdit_1_17,xzz.AllocSysString());
	XEdit_SetText (hEdit_1_18,zw.AllocSysString());
	XEdit_SetText (hEdit_1_19,gzm.AllocSysString());
	XEdit_SetText (hEdit_1_20,jspx.AllocSysString());
	XEdit_SetText (hEdit_1_21,jlcf.AllocSysString());
	XEdit_SetText (hEdit_1_22,smwt.AllocSysString());
	XEdit_SetText (hEdit_1_23,tbrqm.AllocSysString());
	XEdit_SetText (hEdit_1_24,tbrq.AllocSysString());
	XEdit_SetText (hEdit_1_25,gsyj.AllocSysString());
	XEdit_SetText (hEdit_1_26,scrq.AllocSysString());
	XEdit_SetText (hEdit_1_27,ryxz.AllocSysString());
	XEdit_SetText (hEdit_1_28,rcsj.AllocSysString());
	XEdit_SetText (hEdit_1_29,ryzt.AllocSysString());
	XEdit_SetText (hEdit_1_30,bz.AllocSysString());
	XEdit_SetText (hEdit_1_31,bmbm.AllocSysString());

	XEle_ShowEle(edit_view,TRUE);
	XWnd_RedrawWnd(mainWnd->m_hWindow);

	HELE hButton_baocun=XBtn_Create(540,770,80,30,L"保存",edit_view);
	XCGUI_RegEleEvent(hButton_baocun,XE_BNCLICK,&CXPage_renshi::baocun);//事件注册
	HELE hButton_quxiao=XBtn_Create(640,770,80,30,L"取消",edit_view);
	XCGUI_RegEleEvent(hButton_quxiao,XE_BNCLICK,&CXPage_renshi::quxiao);//事件注册
	return 0;
}
BOOL  CXPage_renshi::baocun(HELE hEle,HELE hEventEle)
{
	int sign=XList_GetSelectCount(m_hList);
	if(sign<=0)
	{
		MessageBox(NULL,"请先选中一项!","提示",XMB_OK);
		return false;
	}
	int j=XList_GetSelectItem	(m_hList);
	j++;
	CString zgbm;
	mysql_query(&data.mysql,now_sql);//用来保存当前的查询语句
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(i<j)
	{
		row=mysql_fetch_row(data.result);
		i++;
	}
	mysql_free_result(data.result);
	int m=1;
	char sql[1024];
	sprintf(sql,"delete from m_dadj where zgbm='%s'",row[0]);
	m=mysql_query(&data.mysql,sql);
	wchar_t data_1_1[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_1,data_1_1,MAX_PATH);
	wchar_t data_1_2[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_2,data_1_2,MAX_PATH);
	wchar_t data_1_3[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_3,data_1_3,MAX_PATH);
	wchar_t data_1_4[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_4,data_1_4,MAX_PATH);
	wchar_t data_1_5[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_5,data_1_5,MAX_PATH);
	wchar_t data_1_6[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_6,data_1_6,MAX_PATH);
	wchar_t data_1_7[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_7,data_1_7,MAX_PATH);
	wchar_t data_1_8[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_8,data_1_8,MAX_PATH);
	wchar_t data_1_9[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_9,data_1_9,MAX_PATH);
	wchar_t data_1_10[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_10,data_1_10,MAX_PATH);
	wchar_t data_1_11[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_11,data_1_11,MAX_PATH);
	wchar_t data_1_12[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_12,data_1_12,MAX_PATH);
	wchar_t data_1_13[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_13,data_1_13,MAX_PATH);
	wchar_t data_1_14[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_14,data_1_14,MAX_PATH);
	wchar_t data_1_15[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_15,data_1_15,MAX_PATH);
	wchar_t data_1_16[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_16,data_1_16,MAX_PATH);
	wchar_t data_1_17[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_17,data_1_17,MAX_PATH);
	wchar_t data_1_18[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_18,data_1_18,MAX_PATH);
	wchar_t data_1_19[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_19,data_1_19,MAX_PATH);
	wchar_t data_1_20[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_20,data_1_20,MAX_PATH);
	wchar_t data_1_21[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_21,data_1_21,MAX_PATH);
	wchar_t data_1_22[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_22,data_1_22,MAX_PATH);
	wchar_t data_1_23[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_23,data_1_23,MAX_PATH);
	wchar_t data_1_24[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_24,data_1_24,MAX_PATH);
	wchar_t data_1_25[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_25,data_1_25,MAX_PATH);
	wchar_t data_1_26[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_26,data_1_26,MAX_PATH);
	wchar_t data_1_27[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_27,data_1_27,MAX_PATH);
	wchar_t data_1_28[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_28,data_1_28,MAX_PATH);
	wchar_t data_1_29[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_29,data_1_29,MAX_PATH);
	wchar_t data_1_30[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_30,data_1_30,MAX_PATH);
	wchar_t data_1_31[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_31,data_1_31,MAX_PATH);


	
	CString cdata_1_1,cdata_1_2,cdata_1_3,cdata_1_4,cdata_1_5,cdata_1_6,cdata_1_7,cdata_1_8,cdata_1_9,cdata_1_10,cdata_1_11,cdata_1_12,cdata_1_13,cdata_1_14,cdata_1_15,cdata_1_16,cdata_1_17,cdata_1_18,cdata_1_19,cdata_1_20,cdata_1_21,cdata_1_22,cdata_1_23,cdata_1_24,cdata_1_25,cdata_1_26,cdata_1_27,cdata_1_28,cdata_1_29,cdata_1_30,cdata_1_31;//定义Cstring，用来将wchar_t类型转换为cstring然后在转换为string
	WideCharToMultiByte(CP_ACP,0,data_1_1,256,cdata_1_1.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_2,256,cdata_1_2.GetBuffer(500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_3,256,cdata_1_3.GetBuffer(1000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_4,256,cdata_1_4.GetBuffer(1500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_5,256,cdata_1_5.GetBuffer(2000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_6,256,cdata_1_6.GetBuffer(2500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_7,256,cdata_1_7.GetBuffer(3000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_8,256,cdata_1_8.GetBuffer(3500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_9,256,cdata_1_9.GetBuffer(4000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_10,256,cdata_1_10.GetBuffer(4500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_11,256,cdata_1_11.GetBuffer(5000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_12,256,cdata_1_12.GetBuffer(5500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_13,256,cdata_1_13.GetBuffer(6000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_14,256,cdata_1_14.GetBuffer(6500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_15,256,cdata_1_15.GetBuffer(7000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_16,256,cdata_1_16.GetBuffer(7500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_17,256,cdata_1_17.GetBuffer(8000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_18,256,cdata_1_18.GetBuffer(8500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_19,256,cdata_1_19.GetBuffer(9000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_20,256,cdata_1_20.GetBuffer(9500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_21,256,cdata_1_21.GetBuffer(10000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_22,256,cdata_1_22.GetBuffer(10500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_23,256,cdata_1_23.GetBuffer(11000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_24,256,cdata_1_24.GetBuffer(11500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_25,256,cdata_1_25.GetBuffer(12000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_26,256,cdata_1_26.GetBuffer(12500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_27,256,cdata_1_27.GetBuffer(13000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_28,256,cdata_1_28.GetBuffer(13500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_29,256,cdata_1_29.GetBuffer(14000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_30,256,cdata_1_30.GetBuffer(14500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_31,256,cdata_1_31.GetBuffer(15000),256,NULL,NULL);

	int idata_1_7;
	sscanf((LPCTSTR)cdata_1_7,"%d",&idata_1_7);//jiang cstring chuan wei int
	int idata_1_10;
	sscanf((LPCTSTR)cdata_1_10,"%d",&idata_1_10);//jiang cstring chuan wei int
	int idata_1_18;
	sscanf((LPCTSTR)cdata_1_18,"%d",&idata_1_18);//jiang cstring chuan wei int
	CString sql1;
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	sql1.Format("insert into m_dadj values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",cdata_1_1,cdata_1_2,cdata_1_3,cdata_1_4,cdata_1_5,cdata_1_6,idata_1_7,cdata_1_8,cdata_1_9,idata_1_10,cdata_1_11,cdata_1_12,cdata_1_13,cdata_1_14,cdata_1_15,cdata_1_16,cdata_1_17,idata_1_18,cdata_1_19,cdata_1_20,cdata_1_21,cdata_1_22,cdata_1_23,cdata_1_24,cdata_1_25,cdata_1_26,cdata_1_27,cdata_1_28,cdata_1_29,cdata_1_30,cdata_1_31);
	int n=mysql_query(&data.mysql,(char*)(LPCTSTR)sql1);

	cdata_1_1.ReleaseBuffer(0);
	cdata_1_2.ReleaseBuffer(500);
	cdata_1_3.ReleaseBuffer(1000);
	cdata_1_4.ReleaseBuffer(1500);
	cdata_1_5.ReleaseBuffer(2000);
	cdata_1_6.ReleaseBuffer(2500);
	cdata_1_7.ReleaseBuffer(3000);
	cdata_1_8.ReleaseBuffer(3500);
	cdata_1_9.ReleaseBuffer(4000);
	cdata_1_10.ReleaseBuffer(4500);
	cdata_1_11.ReleaseBuffer(5000);
	cdata_1_12.ReleaseBuffer(5500);
	cdata_1_13.ReleaseBuffer(6000);
	cdata_1_14.ReleaseBuffer(6500);
	cdata_1_15.ReleaseBuffer(7000);
	cdata_1_16.ReleaseBuffer(7500);
	cdata_1_17.ReleaseBuffer(8000);
	cdata_1_18.ReleaseBuffer(8500);
	cdata_1_19.ReleaseBuffer(9000);
	cdata_1_20.ReleaseBuffer(9500);
	cdata_1_21.ReleaseBuffer(10000);
	cdata_1_22.ReleaseBuffer(10500);
	cdata_1_23.ReleaseBuffer(11000);
	cdata_1_24.ReleaseBuffer(11500);
	cdata_1_25.ReleaseBuffer(12000);
	cdata_1_26.ReleaseBuffer(12500);
	cdata_1_27.ReleaseBuffer(13000);
	cdata_1_28.ReleaseBuffer(13500);
	cdata_1_29.ReleaseBuffer(14000);
	cdata_1_30.ReleaseBuffer(14500);
	cdata_1_31.ReleaseBuffer(15000);


	if(m==0&&n==0)
	{
		MessageBox(NULL,"更改成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"更改错误,请检查输入!","提示",XMB_OK);
	}


	XEle_ShowEle(edit_view,FALSE);
	XWnd_RedrawWnd(mainWnd->m_hWindow);
	return 0;
}
BOOL  CXPage_renshi::quxiao(HELE hEle,HELE hEventEle)
{
	XEle_ShowEle(edit_view,FALSE);
	XWnd_RedrawWnd(mainWnd->m_hWindow);
	return 0;
}








void CXPage_anquan::Create()
{
	m_hEle=XPic_Create(2,110,300,465,mainWnd->m_hWindow);
	XPic_SetImage(m_hEle, XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(m_hEle,TRUE);
	XEle_ShowEle(m_hEle,FALSE);

	HELE hStatic1=XStatic_Create(20,10,144,40,L"账户管理",m_hEle);
    XEle_SetBkTransparent(hStatic1,true);
	XEle_SetFont(hStatic1,hfontx2);
	XEle_SetTextColor(hStatic1,777);//设置字体颜色

	HELE hStatic11=XStatic_Create(88,10,144,40,L"  密码更改",m_hEle);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx2);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色

	HELE hStatic14=XStatic_Create(220,10,144,40,L"新密码",m_hEle);
    XEle_SetBkTransparent(hStatic14,true);
	XEle_SetFont(hStatic14,hfontx2);
	XEle_SetTextColor(hStatic14,777);//设置字体颜色

	hEdit_xmm=XEdit_Create(320,10,200,22,m_hEle);
	XEle_SetBkTransparent(hEdit_xmm,TRUE);
	XEle_EnableBorder(hEdit_xmm,true);

	HELE hButton_geng=XBtn_Create(540,10,80,30,L"更改",m_hEle);
	XCGUI_RegEleEvent(hButton_geng,XE_BNCLICK,&CXPage_anquan::geng);
	

	HELE hStatic15=XStatic_Create(88,55,144,40,L"  创建用户",m_hEle);
    XEle_SetBkTransparent(hStatic15,true);
	XEle_SetFont(hStatic15,hfontx2);
	XEle_SetTextColor(hStatic15,777);//设置字体颜色

	HELE hStatic16=XStatic_Create(220,55,144,40,L"用户名",m_hEle);
    XEle_SetBkTransparent(hStatic16,true);
	XEle_SetFont(hStatic16,hfontx2);
	XEle_SetTextColor(hStatic16,777);//设置字体颜色

	hEdit_yhm=XEdit_Create(320,55,200,22,m_hEle);
	XEle_SetBkTransparent(hEdit_yhm,TRUE);
	XEle_EnableBorder(hEdit_yhm,true);

	HELE hStatic17=XStatic_Create(220,85,144,40,L"密码",m_hEle);
    XEle_SetBkTransparent(hStatic17,true);
	XEle_SetFont(hStatic17,hfontx2);
	XEle_SetTextColor(hStatic17,777);//设置字体颜色

	hEdit_mm=XEdit_Create(320,85,200,22,m_hEle);
	XEle_SetBkTransparent(hEdit_mm,TRUE);
	XEle_EnableBorder(hEdit_mm,true);

	HELE hButton_chuang=XBtn_Create(540,55,80,30,L"创建",m_hEle);
	XCGUI_RegEleEvent(hButton_chuang,XE_BNCLICK,&CXPage_anquan::chuang);//事件注册

	//分割线
	HELE hButton=XBtn_Create(2,120,500,1,NULL,m_hEle);
	XEle_SetBkTransparent(hButton,TRUE);
	XEle_EnableFocus(hButton,FALSE);
	XBtn_SetImageLeave(hButton,XImage_LoadFile(L"360image\\fengjie.png"));

	HELE hStatic2=XStatic_Create(20,125,144,40,L"数据备份",m_hEle);
    XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,777);//设置字体颜色
	hStatic2=XStatic_Create(100,165,144,40,L"备份信息",m_hEle);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,777);//设置字体颜色
	hEdit_bf=XEdit_Create(180,165,440,22,m_hEle);
	XEle_SetBkTransparent(hEdit_bf,TRUE);
	XEle_EnableBorder(hEdit_bf,false);
	HELE hButton_beifen=XBtn_Create(540,125,80,30,L"备份当前",m_hEle);
	XCGUI_RegEleEvent(hButton_beifen,XE_BNCLICK,&CXPage_anquan::beifen);


	//分割线
	HELE hButton2=XBtn_Create(2,205,500,1,NULL,m_hEle);
	XEle_SetBkTransparent(hButton,TRUE);
	XEle_EnableFocus(hButton,FALSE);
	XBtn_SetImageLeave(hButton,XImage_LoadFile(L"360image\\fengjie.png"));

	HELE hStatic3=XStatic_Create(20,210,144,40,L"数据还原",m_hEle);
    XEle_SetBkTransparent(hStatic3,true);
	XEle_SetFont(hStatic3,hfontx2);
	XEle_SetTextColor(hStatic3,777);//设置字体颜色

	hEdit_wj=XEdit_Create(100,210,420,22,m_hEle);
	XEle_SetBkTransparent(hEdit_wj,TRUE);
	XEle_EnableBorder(hEdit_wj,true);
	HELE hButton_wenjian=XBtn_Create(540,210,80,30,L"选择文件",m_hEle);
	XCGUI_RegEleEvent(hButton_wenjian,XE_BNCLICK,&CXPage_anquan::xuanze);

	HELE hButton_huanyuan=XBtn_Create(540,250,80,30,L"还原",m_hEle);
	XCGUI_RegEleEvent(hButton_huanyuan,XE_BNCLICK,&CXPage_anquan::huanyuan);
	hRichEdit=XRichEdit_Create(100,250,420,180,m_hEle); //创建RichEdit
    HELE hView=XSView_GetView(hRichEdit);
    XEle_SetBkColor(hView,RGB(0,0,9));

	
}
BOOL  CXPage_anquan::xuanze(HELE hEle,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框
    if(dlg.DoModal()==IDOK)
	{
		FilePathName=dlg.GetPathName();
		XEdit_SetText(hEdit_wj,FilePathName.AllocSysString());
		XEle_RedrawEle(hEdit_wj);
	}
	return 0;

}
BOOL  CXPage_anquan::beifen(HELE hEle,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}	
	char strPath[MAX_PATH]; 
	GetModuleFileName(NULL, strPath, MAX_PATH);
	(strrchr(strPath, '\\'))[1] = 0;
	SYSTEMTIME time;
    GetSystemTime(&time);
	int a=mysql_query(&data.mysql,"LOCK TABLES users READ");
	char sqlBuf[1024];
	//sprintf(sqlBuf,"SELECT * INTO OUTFILE 'C:/a/user_%d_%d_%d_%d.sql' FIELDS TERMINATED BY ',' FROM users",time.wYear,time.wMonth,time.wDay,time.wSecond);
	sprintf(sqlBuf,"MySQLdump -u root -pgd1992 >C:/a/test_%d_%d_%d_%d_%d_%d.sql",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
	system(sqlBuf);
	int c=mysql_query(&data.mysql,"UNLOCK TABLES");

	if(a==0&&c==0)
	{
		CString temp;
		temp.Format("已成功备份至C:/a/test_%d_%d_%d_%d_%d_%d.sql",time.wYear,time.wMonth,time.wDay,time.wHour,time.wMinute,time.wSecond);
		XEdit_SetText(hEdit_bf,temp.AllocSysString());
		XWnd_RedrawWnd(mainWnd->m_hWindow);
	}
	else
	{
		MessageBox(NULL,"备份失败","提示",XMB_OK);
	}

	return 0;
}
BOOL  CXPage_anquan::huanyuan(HELE hEle,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	char *pa = "";
	char *pb = (char*)((LPCTSTR)FilePathName);
	if(!strcmp(pa,pb))
	{
		MessageBox(NULL,"选择文件错误","提示",XMB_OK);
		return 0;
	}
	mysql_query(&data.mysql,"LOCK TABLES users READ");
	mysql_query(&data.mysql,"LOCK TABLES m_dadj READ");
	mysql_query(&data.mysql,"LOCK TABLES bm_bm READ");
	mysql_query(&data.mysql,"LOCK TABLES bm_wh READ");
	mysql_query(&data.mysql,"LOCK TABLES bm_zc READ");
	char sqlBuf[1024];
	sprintf(sqlBuf,"mysqldump -hlocalhost -uroot -pgd1992 test<%s",pb);
	system(sqlBuf);
	int c=mysql_query(&data.mysql,"UNLOCK TABLES");

	if(c==0)
	{
		//CString huifu_time;
		XRichEdit_InsertTextEx(hRichEdit,L"成功恢复！\n",-1,-1,0,true,1000);
		XEle_RedrawEle(hRichEdit);
		//XRichEdit_InsertTextEx(hRichEdit,,-1,-1,0,true,123);
		//XEle_RedrawEle(hRichEdit);
	}
	else
	{
		MessageBox(NULL,"恢复失败","提示",XMB_OK);
	}
	return 0;
}
BOOL  CXPage_anquan::chuang(HELE hEle,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	wchar_t user[MAX_PATH]={0};
	XEdit_GetText(hEdit_yhm,user,MAX_PATH);
	wchar_t passwd[MAX_PATH]={0};
	XEdit_GetText(hEdit_mm,passwd,MAX_PATH);

	CString cuser,cpasswd;
	CString sql;
	int i=1;
	WideCharToMultiByte(CP_ACP,0,user,256,cuser.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,passwd,256,cpasswd.GetBuffer(1024),256,NULL,NULL);
	
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	sql.Format("insert into users values(\'%s\',\'%s\')",cuser,cpasswd);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cuser.ReleaseBuffer(0);
	cpasswd.ReleaseBuffer(1024);
	if(i==0)
	{
		MessageBox(NULL,"添加成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"添加错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}
BOOL  CXPage_anquan::geng(HELE hEle,HELE hEventEle)
{
	if(login_sign==0)
	{
		MessageBox(NULL,"登陆后可使用","提示",XMB_OK);
		return 0;
	}
	wchar_t npasswd[MAX_PATH]={0};
	XEdit_GetText(hEdit_xmm,npasswd,MAX_PATH);
	CString sql;
	CString cnpasswd;
	WideCharToMultiByte(CP_ACP,0,npasswd,256,cnpasswd.GetBuffer(0),256,NULL,NULL);
	sql.Format("UPDATE users SET passwd = '%s' where user = '%s'",cnpasswd,now_user);
	int i=1;
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);
	cnpasswd.ReleaseBuffer(0);
	if(i==0)
	{
		MessageBox(NULL,"更改成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"更改错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}

void CXPage_anquan::AdjustLayout()
{

}













///////////////////////////////////////////////////////////////////////
void CXPage_setting::Create()
{
	m_hEle=XPic_Create(2,110,300,465,mainWnd->m_hWindow);
	XPic_SetImage(m_hEle, XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(m_hEle,TRUE);
	XEle_ShowEle(m_hEle,FALSE);

	HELE hStatic1=XStatic_Create(10,30,144,40,L"其他工具",m_hEle);
    XEle_SetBkTransparent(hStatic1,true);
	XEle_SetFont(hStatic1,hfontx2);
	XEle_SetTextColor(hStatic1,0);//设置字体颜色

	HELE m_hListView=XListView_Create(2,60,844,120,m_hEle);
	XListView_SetIconSize(m_hListView,58,58);
	XListView_SetItemBorderSpacing(m_hListView,16,5,16,8);

	HXCGUI hImageLsit=XImageList_Create(58,58);
	XImageList_EnableFixedSize(hImageLsit,true);

	CString iconName;
	for (int i=1;i<8;i++)
	{
		iconName.Format("360image\\AppIcon\\%d.png",i);
		XImageList_AddImage(hImageLsit,XImage_LoadFile(iconName.AllocSysString()));
	}

	XListView_SetImageList(m_hListView,hImageLsit);
	XListView_AddItem(m_hListView,L"通讯录",0);
	XListView_AddItem(m_hListView,L"计算器",1);
	XListView_AddItem(m_hListView,L"记事本",2);
	XListView_AddItem(m_hListView,L"员工生日提醒",3);
	XListView_AddItem(m_hListView,L"综合统计",4);
	XListView_AddItem(m_hListView,L"数据库",5);
	XListView_AddItem(m_hListView,L"所有用户",6);

	HIMAGE hImageStay=XImage_LoadFile(L"360image\\page9\\listView_stay.png");
	HIMAGE hImageSelect=XImage_LoadFile(L"360image\\page9\\listView_select.png");
	for (i=0;i<8;i++)
	{
		XListView_SetItemImageStay(m_hListView,-1,i,hImageStay);
		XListView_SetItemImageSelect(m_hListView,-1,i,hImageSelect);
	}

	hStatic1=XStatic_Create(10,210,144,40,L"编码设置",m_hEle);
    XEle_SetBkTransparent(hStatic1,true);
	XEle_SetFont(hStatic1,hfontx2);
	XEle_SetTextColor(hStatic1,0);//设置字体颜色

	HELE m_hListView2=XListView_Create(2,240,844,120,m_hEle);
	XListView_SetIconSize(m_hListView2,58,58);
	XListView_SetItemBorderSpacing(m_hListView2,16,5,16,8);

	HXCGUI hImageLsit2=XImageList_Create(58,58);
	XImageList_EnableFixedSize(hImageLsit2,true);

	for (i=1;i<4;i++)
	{
		iconName.Format("360image\\AppIcon2\\%d.png",i);
		XImageList_AddImage(hImageLsit2,XImage_LoadFile(iconName.AllocSysString()));//
	}

	XListView_SetImageList(m_hListView2,hImageLsit2);
	XListView_AddItem(m_hListView2,L"部门编码",0);
	XListView_AddItem(m_hListView2,L"文化程度编码",1);
	XListView_AddItem(m_hListView2,L"职工编码",2);

	for (i=0;i<4;i++)
	{
		XListView_SetItemImageStay(m_hListView2,-1,i,hImageStay);
		XListView_SetItemImageSelect(m_hListView2,-1,i,hImageSelect);
	}

	XCGUI_RegEleEvent(m_hListView,XE_LISTVIEW_SELECT,&CXPage_setting::xiaogongju);
	XCGUI_RegEleEvent(m_hListView2,XE_LISTVIEW_SELECT,&CXPage_setting::setting);
}
BOOL  CXPage_setting::xiaogongju(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex)
{
	switch(itemIndex)
		{
		case 0: {CTongxunluDlg  *pTongxunluDlg=new CTongxunluDlg;
			pTongxunluDlg->Create();} break;
		case 1: ShellExecute(NULL,"open","calc.exe",NULL,NULL,SW_SHOWNORMAL); break;
		case 2: ShellExecute(NULL,"open","notepad.exe",NULL,NULL,SW_SHOWNORMAL); break;
		case 3: {CYgsrtyDlg  *pYgsrtyDlg=new CYgsrtyDlg;
			pYgsrtyDlg->Create();} break;
		case 4: {CTongjiDlg  *pTongjiDlg=new CTongjiDlg;
			pTongjiDlg->Create();} break;
		case 5: system("mysql -u root -p gd1992"); break;
		case 6: {CUserDlg  *pUserDlg=new CUserDlg;
			pUserDlg->Create();} break;
		}
	return 0;
}
BOOL  CXPage_setting::setting(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex)
{
	switch(itemIndex)
		{
		case 0: {CBmbmsetDlg  *pBmbmDlg=new CBmbmsetDlg;
			pBmbmDlg->Create();} break;
		case 1: {CWhbmsetDlg  *pWhbmDlg=new CWhbmsetDlg;
			pWhbmDlg->Create();} break;
		case 2: {CZcbmsetDlg  *pZcbmDlg=new CZcbmsetDlg;
			pZcbmDlg->Create();} break;
		}
	return 0;
}
void CXPage_setting::AdjustLayout()
{

}





void CXPage_add::Create()
{
	m_hEle=XPic_Create(2,110,300,465,mainWnd->m_hWindow);
	XPic_SetImage(m_hEle, XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(m_hEle,TRUE);
	XEle_ShowEle(m_hEle,FALSE);

	HELE hTabBar=XTabBar_Create(5,5,730,31,m_hEle);
	XEle_EnableBorder(hTabBar,FALSE);
	XEle_SetBkTransparent(hTabBar,TRUE);
	XTabBar_SetLabelSpacing(hTabBar,0);
	XTabBar_AddLabel(hTabBar,L"   档案登记   ");
	XTabBar_AddLabel(hTabBar,L"   社会关系   ");
	XTabBar_AddLabel(hTabBar,L"   职称编码   ");
	XTabBar_AddLabel(hTabBar,L"   部门编码   ");
	XTabBar_AddLabel(hTabBar,L" 文化程度编码 ");


	HIMAGE  hImageLeave = XImage_LoadFileAdaptive(L"360image\\page5\\tab_leave.png",9,103,10,25);
	HIMAGE  hImageStay = XImage_LoadFileAdaptive(L"360image\\page5\\tab_stay.png",9,103,10,25);
	HIMAGE  hImageCheck = XImage_LoadFileAdaptive(L"360image\\page5\\tab_check.png",9,102,8,21);

	for (int i=0;i<5;i++)
	{
		HELE hButton=XTabBar_GetLabel(hTabBar,i);
		XEle_EnableFocus(hButton,FALSE);
		XEle_SetBkTransparent(hButton,TRUE);
		XBtn_SetOffset(hButton,0,3);

		XBtn_SetImageLeave(hButton,hImageLeave);
		XBtn_SetImageStay(hButton,hImageStay);
		XBtn_SetImageDown(hButton,hImageCheck);
		XBtn_SetImageCheck(hButton,hImageCheck);
	}

	HELE view_dadj=XPic_Create(0,35,900,465,m_hEle);
	XPic_SetImage(view_dadj,XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(view_dadj,TRUE);
	XEle_ShowEle(m_hEle,FALSE);

	XTabBar_SetBindEle(hTabBar,0,view_dadj);
	HELE hScrollView1=XSView_Create(10,10,830,360,view_dadj);
    XSView_SetSize(hScrollView1,600,800); //设置滚动视图内容大小1000代表的是高

	HELE hStatic11=XStatic_Create(20,10,144,40,L"职工编号",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,10,144,40,L"姓名",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,50,144,40,L"性别",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,50,144,40,L"民族",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,90,144,40,L"出生年月",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,90,144,40,L"婚否",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,130,144,40,L"文化程度编码",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,130,144,40,L"健康状况",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,170,144,40,L"政治面貌",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,170,144,40,L"职称编码",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,210,144,40,L"籍贯",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,250,144,40,L"身份证号",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,250,144,40,L"毕业学校",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,290,144,40,L"专业及特长",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,330,144,40,L"户口所在地",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,370,144,40,L"户口性质",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,370,144,40,L"现住址",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,410,144,40,L"职务",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,410,144,40,L"工种名",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,450,144,40,L"何时技术培训",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,450,144,40,L"何时奖励处分",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,490,144,40,L"需要说明问题",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,530,144,40,L"填表人签名",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,530,144,40,L"填表日期",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,570,144,40,L"公司审核意见",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,610,144,40,L"审核日期",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,610,144,40,L"人员性质",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,650,144,40,L"入场时间",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(400,650,144,40,L"人员状态",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,690,144,40,L"备注",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	hStatic11=XStatic_Create(20,730,144,40,L"部门编码",hScrollView1);
    XEle_SetBkTransparent(hStatic11,true);
	XEle_SetFont(hStatic11,hfontx1);
	XEle_SetTextColor(hStatic11,777);//设置字体颜色
	HELE add_dadj=XBtn_Create(700,420,100,28,L"添加",m_hEle);
	XCGUI_RegEleEvent(add_dadj,XE_BNCLICK,&CXPage_add::add_dadj);//事件注册
	hEdit_1_1=XEdit_Create(160,10,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_1,TRUE);
	XEle_EnableBorder(hEdit_1_1,true);
	hEdit_1_2=XEdit_Create(540,10,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_2,TRUE);
	XEle_EnableBorder(hEdit_1_2,true);
	hEdit_1_3=XEdit_Create(160,50,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_3,TRUE);
	XEle_EnableBorder(hEdit_1_3,true);
	hEdit_1_4=XEdit_Create(540,50,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_4,TRUE);
	XEle_EnableBorder(hEdit_1_4,true);
	hEdit_1_5=XEdit_Create(160,90,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_5,TRUE);
	XEle_EnableBorder(hEdit_1_5,true);
	hEdit_1_6=XEdit_Create(540,90,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_6,TRUE);
	XEle_EnableBorder(hEdit_1_6,true);
	hEdit_1_7=XEdit_Create(160,130,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_7,TRUE);
	XEle_EnableBorder(hEdit_1_7,true);
	hEdit_1_8=XEdit_Create(540,130,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_8,TRUE);
	XEle_EnableBorder(hEdit_1_8,true);
	hEdit_1_9=XEdit_Create(160,170,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_9,TRUE);
	XEle_EnableBorder(hEdit_1_9,true);
	hEdit_1_10=XEdit_Create(540,170,200,22,hScrollView1);//-------200-------------------------
	XEle_SetBkTransparent(hEdit_1_10,TRUE);
	XEle_EnableBorder(hEdit_1_10,true);
	hEdit_1_11=XEdit_Create(160,210,577,22,hScrollView1);//----577----------------------------
	XEle_SetBkTransparent(hEdit_1_11,TRUE);
	XEle_EnableBorder(hEdit_1_11,true);
	hEdit_1_12=XEdit_Create(160,250,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_12,TRUE);
	XEle_EnableBorder(hEdit_1_12,true);
	hEdit_1_13=XEdit_Create(540,250,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_13,TRUE);
	XEle_EnableBorder(hEdit_1_13,true);
	hEdit_1_14=XEdit_Create(160,290,577,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_14,TRUE);
	XEle_EnableBorder(hEdit_1_14,true);
	hEdit_1_15=XEdit_Create(160,330,577,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_15,TRUE);
	XEle_EnableBorder(hEdit_1_15,true);
	hEdit_1_16=XEdit_Create(160,370,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_16,TRUE);
	XEle_EnableBorder(hEdit_1_16,true);
	hEdit_1_17=XEdit_Create(540,370,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_17,TRUE);
	XEle_EnableBorder(hEdit_1_17,true);
	hEdit_1_18=XEdit_Create(160,410,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_18,TRUE);
	XEle_EnableBorder(hEdit_1_18,true);
	hEdit_1_19=XEdit_Create(540,410,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_19,TRUE);
	XEle_EnableBorder(hEdit_1_19,true);
	hEdit_1_20=XEdit_Create(160,450,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_20,TRUE);
	XEle_EnableBorder(hEdit_1_20,true);
	hEdit_1_21=XEdit_Create(540,450,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_21,TRUE);
	XEle_EnableBorder(hEdit_1_21,true);
	hEdit_1_22=XEdit_Create(160,490,577,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_22,TRUE);
	XEle_EnableBorder(hEdit_1_22,true);
	hEdit_1_23=XEdit_Create(160,530,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_23,TRUE);
	XEle_EnableBorder(hEdit_1_23,true);
	hEdit_1_24=XEdit_Create(540,530,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_24,TRUE);
	XEle_EnableBorder(hEdit_1_24,true);
	hEdit_1_25=XEdit_Create(160,570,577,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_25,TRUE);
	XEle_EnableBorder(hEdit_1_25,true);
	hEdit_1_26=XEdit_Create(160,610,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_26,TRUE);
	XEle_EnableBorder(hEdit_1_26,true);
	hEdit_1_27=XEdit_Create(540,610,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_27,TRUE);
	XEle_EnableBorder(hEdit_1_27,true);
	hEdit_1_28=XEdit_Create(160,650,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_28,TRUE);
	XEle_EnableBorder(hEdit_1_28,true);
	hEdit_1_29=XEdit_Create(540,650,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_29,TRUE);
	XEle_EnableBorder(hEdit_1_29,true);
	hEdit_1_30=XEdit_Create(160,690,577,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_30,TRUE);
	XEle_EnableBorder(hEdit_1_30,true);
	hEdit_1_31=XEdit_Create(160,730,200,22,hScrollView1);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_31,TRUE);
	XEle_EnableBorder(hEdit_1_31,true);

	HELE view_xhgx=XPic_Create(0,35,900,465,m_hEle);
	XPic_SetImage(view_xhgx,XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(view_xhgx,TRUE);
	XEle_ShowEle(m_hEle,FALSE);
	XTabBar_SetBindEle(hTabBar,1,view_xhgx);
	HELE hStatic12=XStatic_Create(20,10,144,40,L"职工编号",view_xhgx);
    XEle_SetBkTransparent(hStatic12,true);
	XEle_SetFont(hStatic12,hfontx1);
	XEle_SetTextColor(hStatic12,777);//设置字体颜色
	hStatic12=XStatic_Create(400,10,144,40,L"与本人关系",view_xhgx);
    XEle_SetBkTransparent(hStatic12,true);
	XEle_SetFont(hStatic12,hfontx1);
	XEle_SetTextColor(hStatic12,777);//设置字体颜色
	hStatic12=XStatic_Create(20,50,144,40,L"姓名",view_xhgx);
    XEle_SetBkTransparent(hStatic12,true);
	XEle_SetFont(hStatic12,hfontx1);
	XEle_SetTextColor(hStatic12,777);//设置字体颜色
	hStatic12=XStatic_Create(400,50,144,40,L"工作",view_xhgx);
    XEle_SetBkTransparent(hStatic12,true);
	XEle_SetFont(hStatic12,hfontx1);
	XEle_SetTextColor(hStatic12,777);//设置字体颜色
	hStatic12=XStatic_Create(20,90,144,40,L"主键",view_xhgx);
    XEle_SetBkTransparent(hStatic12,true);
	XEle_SetFont(hStatic12,hfontx1);
	XEle_SetTextColor(hStatic12,777);//设置字体颜色
	HELE add_xhgx=XBtn_Create(700,385,100,28,L"添加",view_xhgx);
	XCGUI_RegEleEvent(add_xhgx,XE_BNCLICK,&CXPage_add::add_xhgx);//事件注册
	hEdit_2_1=XEdit_Create(160,10,200,22,view_xhgx);//--------------------------------
	XEle_SetBkTransparent(hEdit_1_1,TRUE);
	XEle_EnableBorder(hEdit_2_1,true);
	hEdit_2_2=XEdit_Create(540,10,200,22,view_xhgx);//--------------------------------
	XEle_SetBkTransparent(hEdit_2_2,TRUE);
	XEle_EnableBorder(hEdit_2_2,true);
	hEdit_2_3=XEdit_Create(160,50,200,22,view_xhgx);//--------------------------------
	XEle_SetBkTransparent(hEdit_2_3,TRUE);
	XEle_EnableBorder(hEdit_2_3,true);
	hEdit_2_4=XEdit_Create(540,50,200,22,view_xhgx);//--------------------------------
	XEle_SetBkTransparent(hEdit_2_4,TRUE);
	XEle_EnableBorder(hEdit_2_4,true);
	hEdit_2_5=XEdit_Create(160,90,200,22,view_xhgx);//--------------------------------
	XEle_SetBkTransparent(hEdit_2_5,TRUE);
	XEle_EnableBorder(hEdit_2_5,true);


	HELE view_zcbm=XPic_Create(0,35,900,465,m_hEle);
	XPic_SetImage(view_zcbm,XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(view_zcbm,TRUE);
	XEle_ShowEle(m_hEle,FALSE);
	XTabBar_SetBindEle(hTabBar,2,view_zcbm);
	HELE hStatic13=XStatic_Create(20,10,144,40,L"职称编号",view_zcbm);
    XEle_SetBkTransparent(hStatic13,true);
	XEle_SetFont(hStatic13,hfontx1);
	XEle_SetTextColor(hStatic13,777);//设置字体颜色
	hStatic13=XStatic_Create(400,10,144,40,L"职称名称",view_zcbm);
    XEle_SetBkTransparent(hStatic13,true);
	XEle_SetFont(hStatic13,hfontx1);
	XEle_SetTextColor(hStatic13,777);//设置字体颜色
	HELE add_zcbm=XBtn_Create(700,385,100,28,L"添加",view_zcbm);
	XCGUI_RegEleEvent(add_zcbm,XE_BNCLICK,&CXPage_add::add_zcbm);
	hEdit_3_1=XEdit_Create(160,10,200,22,view_zcbm);//--------------------------------
	XEle_SetBkTransparent(hEdit_3_1,TRUE);
	XEle_EnableBorder(hEdit_3_1,true);
	hEdit_3_2=XEdit_Create(540,10,200,22,view_zcbm);//--------------------------------
	XEle_SetBkTransparent(hEdit_3_2,TRUE);
	XEle_EnableBorder(hEdit_3_2,true);

	HELE view_bmbm=XPic_Create(0,35,900,465,m_hEle);
	XPic_SetImage(view_bmbm,XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(view_bmbm,TRUE);
	XEle_ShowEle(m_hEle,FALSE);
	XTabBar_SetBindEle(hTabBar,3,view_bmbm);
	HELE hStatic14=XStatic_Create(20,10,144,40,L"部门编码",view_bmbm);
    XEle_SetBkTransparent(hStatic14,true);
	XEle_SetFont(hStatic14,hfontx1);
	XEle_SetTextColor(hStatic14,777);//设置字体颜色
	hStatic14=XStatic_Create(400,10,144,40,L"部门名",view_bmbm);
    XEle_SetBkTransparent(hStatic14,true);
	XEle_SetFont(hStatic14,hfontx1);
	XEle_SetTextColor(hStatic14,777);//设置字体颜色
	HELE add_bmbm=XBtn_Create(700,385,100,28,L"添加",view_bmbm);
	XCGUI_RegEleEvent(add_bmbm,XE_BNCLICK,&CXPage_add::add_bmbm);
	hEdit_4_1=XEdit_Create(160,10,200,22,view_bmbm);//--------------------------------
	XEle_SetBkTransparent(hEdit_4_1,TRUE);
	XEle_EnableBorder(hEdit_4_1,true);
	hEdit_4_2=XEdit_Create(540,10,200,22,view_bmbm);//--------------------------------
	XEle_SetBkTransparent(hEdit_4_2,TRUE);
	XEle_EnableBorder(hEdit_4_2,true);

	HELE view_whcdbm=XPic_Create(0,35,900,465,m_hEle);
	XPic_SetImage(view_whcdbm,XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(view_whcdbm,TRUE);
	XEle_ShowEle(m_hEle,FALSE);
	XTabBar_SetBindEle(hTabBar,4,view_whcdbm);
	HELE hStatic15=XStatic_Create(20,10,144,40,L"文化程度编码",view_whcdbm);
    XEle_SetBkTransparent(hStatic15,true);
	XEle_SetFont(hStatic15,hfontx1);
	XEle_SetTextColor(hStatic15,777);//设置字体颜色
	hStatic15=XStatic_Create(400,10,144,40,L"文化程度名称",view_whcdbm);
    XEle_SetBkTransparent(hStatic15,true);
	XEle_SetFont(hStatic15,hfontx1);
	XEle_SetTextColor(hStatic15,777);//设置字体颜色
	HELE add_whcdbm=XBtn_Create(700,385,100,28,L"添加",view_whcdbm);
	XCGUI_RegEleEvent(add_whcdbm,XE_BNCLICK,&CXPage_add::add_whcdbm);
	hEdit_5_1=XEdit_Create(160,10,200,22,view_whcdbm);//--------------------------------
	XEle_SetBkTransparent(hEdit_5_1,TRUE);
	XEle_EnableBorder(hEdit_5_1,true);
	hEdit_5_2=XEdit_Create(540,10,200,22,view_whcdbm);//--------------------------------
	XEle_SetBkTransparent(hEdit_5_2,TRUE);
	XEle_EnableBorder(hEdit_5_2,true);
}


void CXPage_add::AdjustLayout()
{

}

BOOL  CXPage_add::add_dadj(HELE hEle,HELE hEventEle)
{
	wchar_t data_1_1[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_1,data_1_1,MAX_PATH);
	wchar_t data_1_2[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_2,data_1_2,MAX_PATH);
	wchar_t data_1_3[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_3,data_1_3,MAX_PATH);
	wchar_t data_1_4[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_4,data_1_4,MAX_PATH);
	wchar_t data_1_5[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_5,data_1_5,MAX_PATH);
	wchar_t data_1_6[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_6,data_1_6,MAX_PATH);
	wchar_t data_1_7[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_7,data_1_7,MAX_PATH);
	wchar_t data_1_8[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_8,data_1_8,MAX_PATH);
	wchar_t data_1_9[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_9,data_1_9,MAX_PATH);
	wchar_t data_1_10[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_10,data_1_10,MAX_PATH);
	wchar_t data_1_11[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_11,data_1_11,MAX_PATH);
	wchar_t data_1_12[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_12,data_1_12,MAX_PATH);
	wchar_t data_1_13[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_13,data_1_13,MAX_PATH);
	wchar_t data_1_14[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_14,data_1_14,MAX_PATH);
	wchar_t data_1_15[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_15,data_1_15,MAX_PATH);
	wchar_t data_1_16[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_16,data_1_16,MAX_PATH);
	wchar_t data_1_17[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_17,data_1_17,MAX_PATH);
	wchar_t data_1_18[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_18,data_1_18,MAX_PATH);
	wchar_t data_1_19[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_19,data_1_19,MAX_PATH);
	wchar_t data_1_20[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_20,data_1_20,MAX_PATH);
	wchar_t data_1_21[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_21,data_1_21,MAX_PATH);
	wchar_t data_1_22[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_22,data_1_22,MAX_PATH);
	wchar_t data_1_23[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_23,data_1_23,MAX_PATH);
	wchar_t data_1_24[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_24,data_1_24,MAX_PATH);
	wchar_t data_1_25[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_25,data_1_25,MAX_PATH);
	wchar_t data_1_26[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_26,data_1_26,MAX_PATH);
	wchar_t data_1_27[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_27,data_1_27,MAX_PATH);
	wchar_t data_1_28[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_28,data_1_28,MAX_PATH);
	wchar_t data_1_29[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_29,data_1_29,MAX_PATH);
	wchar_t data_1_30[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_30,data_1_30,MAX_PATH);
	wchar_t data_1_31[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_1_31,data_1_31,MAX_PATH);


	
	CString cdata_1_1,cdata_1_2,cdata_1_3,cdata_1_4,cdata_1_5,cdata_1_6,cdata_1_7,cdata_1_8,cdata_1_9,cdata_1_10,cdata_1_11,cdata_1_12,cdata_1_13,cdata_1_14,cdata_1_15,cdata_1_16,cdata_1_17,cdata_1_18,cdata_1_19,cdata_1_20,cdata_1_21,cdata_1_22,cdata_1_23,cdata_1_24,cdata_1_25,cdata_1_26,cdata_1_27,cdata_1_28,cdata_1_29,cdata_1_30,cdata_1_31;//定义Cstring，用来将wchar_t类型转换为cstring然后在转换为string
	CString sql;
	int i=1;
	WideCharToMultiByte(CP_ACP,0,data_1_1,256,cdata_1_1.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_2,256,cdata_1_2.GetBuffer(500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_3,256,cdata_1_3.GetBuffer(1000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_4,256,cdata_1_4.GetBuffer(1500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_5,256,cdata_1_5.GetBuffer(2000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_6,256,cdata_1_6.GetBuffer(2500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_7,256,cdata_1_7.GetBuffer(3000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_8,256,cdata_1_8.GetBuffer(3500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_9,256,cdata_1_9.GetBuffer(4000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_10,256,cdata_1_10.GetBuffer(4500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_11,256,cdata_1_11.GetBuffer(5000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_12,256,cdata_1_12.GetBuffer(5500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_13,256,cdata_1_13.GetBuffer(6000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_14,256,cdata_1_14.GetBuffer(6500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_15,256,cdata_1_15.GetBuffer(7000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_16,256,cdata_1_16.GetBuffer(7500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_17,256,cdata_1_17.GetBuffer(8000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_18,256,cdata_1_18.GetBuffer(8500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_19,256,cdata_1_19.GetBuffer(9000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_20,256,cdata_1_20.GetBuffer(9500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_21,256,cdata_1_21.GetBuffer(10000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_22,256,cdata_1_22.GetBuffer(10500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_23,256,cdata_1_23.GetBuffer(11000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_24,256,cdata_1_24.GetBuffer(11500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_25,256,cdata_1_25.GetBuffer(12000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_26,256,cdata_1_26.GetBuffer(12500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_27,256,cdata_1_27.GetBuffer(13000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_28,256,cdata_1_28.GetBuffer(13500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_29,256,cdata_1_29.GetBuffer(14000),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_30,256,cdata_1_30.GetBuffer(14500),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_1_31,256,cdata_1_31.GetBuffer(15000),256,NULL,NULL);

	int idata_1_8;
	sscanf((LPCTSTR)cdata_1_8,"%d",&idata_1_8);//jiang cstring chuan wei int
	int idata_1_11;
	sscanf((LPCTSTR)cdata_1_11,"%d",&idata_1_11);//jiang cstring chuan wei int
	int idata_1_19;
	sscanf((LPCTSTR)cdata_1_19,"%d",&idata_1_19);//jiang cstring chuan wei int
	
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	sql.Format("insert into m_dadj values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%d\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",cdata_1_1,cdata_1_2,cdata_1_3,cdata_1_4,cdata_1_5,cdata_1_6,cdata_1_7,idata_1_8,cdata_1_9,cdata_1_10,idata_1_11,cdata_1_12,cdata_1_13,cdata_1_14,cdata_1_15,cdata_1_16,cdata_1_17,cdata_1_18,idata_1_19,cdata_1_20,cdata_1_21,cdata_1_22,cdata_1_23,cdata_1_24,cdata_1_25,cdata_1_26,cdata_1_27,cdata_1_28,cdata_1_29,cdata_1_30,cdata_1_31);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cdata_1_1.ReleaseBuffer(0);
	cdata_1_2.ReleaseBuffer(500);
	cdata_1_3.ReleaseBuffer(1000);
	cdata_1_4.ReleaseBuffer(1500);
	cdata_1_5.ReleaseBuffer(2000);
	cdata_1_6.ReleaseBuffer(2500);
	cdata_1_7.ReleaseBuffer(3000);
	cdata_1_8.ReleaseBuffer(3500);
	cdata_1_9.ReleaseBuffer(4000);
	cdata_1_10.ReleaseBuffer(4500);
	cdata_1_11.ReleaseBuffer(5000);
	cdata_1_12.ReleaseBuffer(5500);
	cdata_1_13.ReleaseBuffer(6000);
	cdata_1_14.ReleaseBuffer(6500);
	cdata_1_15.ReleaseBuffer(7000);
	cdata_1_16.ReleaseBuffer(7500);
	cdata_1_17.ReleaseBuffer(8000);
	cdata_1_18.ReleaseBuffer(8500);
	cdata_1_19.ReleaseBuffer(9000);
	cdata_1_20.ReleaseBuffer(9500);
	cdata_1_21.ReleaseBuffer(10000);
	cdata_1_22.ReleaseBuffer(10500);
	cdata_1_23.ReleaseBuffer(11000);
	cdata_1_24.ReleaseBuffer(11500);
	cdata_1_25.ReleaseBuffer(12000);
	cdata_1_26.ReleaseBuffer(12500);
	cdata_1_27.ReleaseBuffer(13000);
	cdata_1_28.ReleaseBuffer(13500);
	cdata_1_29.ReleaseBuffer(14000);
	cdata_1_30.ReleaseBuffer(14500);
	cdata_1_31.ReleaseBuffer(15000);

	if(i==0)
	{
		MessageBox(NULL,"添加成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"添加错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}
BOOL  CXPage_add::add_xhgx(HELE hEle,HELE hEventEle)
{
	wchar_t data_2_1[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_2_1,data_2_1,MAX_PATH);
	wchar_t data_2_2[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_2_2,data_2_2,MAX_PATH);
	wchar_t data_2_3[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_2_3,data_2_3,MAX_PATH);
	wchar_t data_2_4[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_2_4,data_2_4,MAX_PATH);
	wchar_t data_2_5[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_2_5,data_2_5,MAX_PATH);
	CString cdata_2_1,cdata_2_2,cdata_2_3,cdata_2_4,cdata_2_5;
	CString sql;
	int i=1;
	WideCharToMultiByte(CP_ACP,0,data_2_1,256,cdata_2_1.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_2_2,256,cdata_2_2.GetBuffer(512),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_2_3,256,cdata_2_3.GetBuffer(1024),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_2_4,256,cdata_2_4.GetBuffer(2048),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_2_5,256,cdata_2_5.GetBuffer(3096),256,NULL,NULL);
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	sql.Format("insert into cygx values(\'%s\',\'%s\',\'%s\',\'%s\',\'%s\')",cdata_2_1,cdata_2_2,cdata_2_3,cdata_2_4,cdata_2_5);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cdata_2_1.ReleaseBuffer(0);
	cdata_2_2.ReleaseBuffer(512);
	cdata_2_3.ReleaseBuffer(1024);
	cdata_2_4.ReleaseBuffer(2048);
	cdata_2_5.ReleaseBuffer(3096);

	if(i==0)
	{
		MessageBox(NULL,"添加成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"添加错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}
BOOL  CXPage_add::add_zcbm(HELE hEle,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	wchar_t data_3_1[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_3_1,data_3_1,MAX_PATH);
	wchar_t data_3_2[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_3_2,data_3_2,MAX_PATH);
	CString cdata_3_1,cdata_3_2;
	
	CString sql;
	int i=1;
	WideCharToMultiByte(CP_ACP,0,data_3_1,236,cdata_3_1.GetBuffer(0),236,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_3_2,236,cdata_3_2.GetBuffer(1023),236,NULL,NULL);
	
	int idata_3_1;
	sscanf((LPCTSTR)cdata_3_1,"%d",&idata_3_1);//jiang cstring chuan wei int 

	sql.Format("insert into bm_zc values(\'%d\',\'%s\')",idata_3_1,cdata_3_2);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cdata_3_1.ReleaseBuffer(0);
	cdata_3_2.ReleaseBuffer(1023);
	if(i==0)
	{
		MessageBox(NULL,"添加成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"添加错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}
BOOL  CXPage_add::add_bmbm(HELE hEle,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	wchar_t data_4_1[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_4_1,data_4_1,MAX_PATH);
	wchar_t data_4_2[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_4_2,data_4_2,MAX_PATH);
	CString cdata_4_1,cdata_4_2;
	
	CString sql;
	int i=1;
	WideCharToMultiByte(CP_ACP,0,data_4_1,246,cdata_4_1.GetBuffer(0),246,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_4_2,246,cdata_4_2.GetBuffer(1024),246,NULL,NULL);
	
	int idata_4_1;
	sscanf((LPCTSTR)cdata_4_1,"%d",&idata_4_1);//jiang cstring chuan wei int 

	sql.Format("insert into bm_bm values(\'%d\',\'%s\')",idata_4_1,cdata_4_2);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cdata_4_1.ReleaseBuffer(0);
	cdata_4_2.ReleaseBuffer(1024);
	if(i==0)
	{
		MessageBox(NULL,"添加成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"添加错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}
BOOL  CXPage_add::add_whcdbm(HELE hEle,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	wchar_t data_5_1[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_5_1,data_5_1,MAX_PATH);
	wchar_t data_5_2[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(hEdit_5_2,data_5_2,MAX_PATH);
	CString cdata_5_1,cdata_5_2;
	
	CString sql;
	int i=1;
	WideCharToMultiByte(CP_ACP,0,data_5_1,256,cdata_5_1.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,data_5_2,256,cdata_5_2.GetBuffer(500),256,NULL,NULL);
	
	int idata_5_1;
	sscanf((LPCTSTR)cdata_5_1,"%d",&idata_5_1);//jiang cstring chuan wei int 

	sql.Format("insert into bm_wh values(\'%d\',\'%s\')",idata_5_1,cdata_5_2);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cdata_5_1.ReleaseBuffer(0);
	cdata_5_2.ReleaseBuffer(500);
	if(i==0)
	{
		MessageBox(NULL,"添加成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"添加错误,请检查输入!","提示",XMB_OK);
	}
	return true;
}












void CXPage_cmd::Create()
{
	m_hEle=XPic_Create(2,110,300,465,mainWnd->m_hWindow);
	XPic_SetImage(m_hEle, XImage_LoadFileAdaptive(L"360image\\page9\\bg.png",10,340,10,150));
	XEle_SetBkTransparent(m_hEle,TRUE);
	XEle_ShowEle(m_hEle,FALSE);

	HELE hGif=XGif_Create(0,1,900,30,m_hEle);
	XGif_SetImage(hGif,L"11.gif");
	
	
	HELE hStatic=XStatic_Create(240,260,300,40,L"数据库版本:  mysql server 5.5",m_hEle);
	XEle_SetBkTransparent(hStatic,true);
	XEle_SetFont(hStatic,hfontx2);
	XEle_SetTextColor(hStatic,0);
	hStatic=XStatic_Create(240,230,90,40,L"MFC界面库:",m_hEle);
	XEle_SetBkTransparent(hStatic,true);
	XEle_SetFont(hStatic,hfontx2);
	XEle_SetTextColor(hStatic,0);
	hStatic=XStatic_Create(310,170,190,50,L"谢谢使用",m_hEle);
	XEle_SetBkTransparent(hStatic,true);
	XEle_SetFont(hStatic,hfontx3);
	XEle_SetTextColor(hStatic,0);
	HELE hLink=XTextLink_Create(340,230,200,20,L"http://www.xcgui.com/",m_hEle);
	XEle_SetBkTransparent(hLink,TRUE);
	XEle_SetFont(hLink,hfontx2);
}

void CXPage_cmd::AdjustLayout()
{

}













/////////////////////////////////////////////////////////////////////////
void CSkinDlg::Create()
{
	int width=380;
	int height=320;

	RECT rect;
	XEle_GetRect(mainWnd->m_hBtnSkin,&rect);

	POINT pt;
	pt.x=rect.right-width;
	pt.y=rect.bottom;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);
	ClientToScreen(hMainWnd,&pt);

	m_hWindow=XWnd_CreateWindow(pt.x,pt.y,width,height,L"Skin",hMainWnd,XC_SY_ROUND);
	XWnd_SetRoundSize(m_hWindow,9);

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));

	m_hListView=XListView_Create(20,45,350,205,m_hWindow);
	XListView_SetIconSize(m_hListView,97,62);
	XListView_SetItemBorderSpacing(m_hListView,3,3,3,3);
	XListView_SetViewLeftAlign(m_hListView,0);
	XListView_SetViewTopAlign(m_hListView,0);
	XEle_SetTextColor(m_hListView,RGB(255,255,255));
	XEle_EnableBorder(m_hListView,FALSE);
	XEle_SetBkTransparent(m_hListView,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hListView),TRUE);

	HXCGUI hImageList=XImageList_Create(97,62);
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin1.jpg"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin2.jpg"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin3.jpg"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin4.jpg"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin5.jpg"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin6.jpg"));
	XImageList_AddImage(hImageList,XImage_LoadFile(L"360image\\skin\\skin7.jpg"));

	XListView_SetImageList(m_hListView,hImageList);
	XListView_AddItem(m_hListView,L"默认皮肤",0);
	XListView_AddItem(m_hListView,L"优雅爵士",1);
	XListView_AddItem(m_hListView,L"神秘星空",2);
	XListView_AddItem(m_hListView,L"粉色之恋",3);
	XListView_AddItem(m_hListView,L"奋斗的小鸟",4);
	XListView_AddItem(m_hListView,L"青青世界",5);
	XListView_AddItem(m_hListView,L"古典木纹",6);
	
	HIMAGE  hImageStay=XImage_LoadFile(L"360image\\skinDlg\\listView_stay.png");
	HIMAGE  hImageSelect=XImage_LoadFile(L"360image\\skinDlg\\listView_select.png");
	for (int i=0;i<7;i++)
	{
		XListView_SetItemImageStay(m_hListView,-1,i,hImageStay);
		XListView_SetItemImageSelect(m_hListView,-1,i,hImageSelect);
	}
	XListView_SetSelectItem(m_hListView,-1,mainWnd->m_SkinIndex,TRUE);

	HELE hScrollBar=XSView_GetVScrollBar(m_hListView);
	XEle_SetBkTransparent(hScrollBar,TRUE);
	XSBar_EnableScrollButton2(hScrollBar,FALSE);
	XSBar_SetImageLeaveSlider(hScrollBar,XImage_LoadFileAdaptive(L"360image\\skinDlg\\ScrollBar_leave.png",1,14,10,40));
	XSBar_SetImageStaySlider(hScrollBar,XImage_LoadFileAdaptive(L"360image\\skinDlg\\ScrollBar_stay.png",1,14,10,40));
	XSBar_SetImageDownSlider(hScrollBar,XImage_LoadFileAdaptive(L"360image\\skinDlg\\ScrollBar_stay.png",1,14,10,40));

	XCGUI_RegEleEvent(m_hListView,XE_LISTVIEW_SELECT,&CSkinDlg::OnEventListViewSelect);
	XCGUI_RegWndMessage(m_hWindow,WM_KILLFOCUS,&CSkinDlg::OnWndKillFocus);
	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}

BOOL CSkinDlg::OnEventListViewSelect(HELE hEle,HELE hEventEle,int groupIndex,int itemIndex)
{
	if(itemIndex<0) return FALSE;

	if(mainWnd->m_SkinIndex!=itemIndex) //切换皮肤
	{
		mainWnd->m_SkinIndex=itemIndex;
		switch(itemIndex)
		{
		case 0: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame1.jpg"); break;
		case 1: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame2.jpg"); break;
		case 2: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame3.jpg"); break;
		case 3: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame4.jpg"); break;
		case 4: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame5.jpg"); break;
		case 5: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame6.jpg"); break;
		case 6: mainWnd->m_hThemeBackground=XImage_LoadFile(L"360image\\skin\\frame7.jpg"); break;
		}
		
		XImage_SetDrawType(mainWnd->m_hThemeBackground,XC_IMAGE_TILE);

		XWnd_SetImageNC(mainWnd->m_hWindow,mainWnd->m_hThemeBackground);
		XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);

		XWnd_RedrawWnd(mainWnd->m_hWindow);
		XWnd_RedrawWnd(m_hWindow);
	}
	return FALSE;
}

BOOL CSkinDlg::OnWndKillFocus(HWINDOW hWindow)
{
	HWND hWnd=XWnd_GetHWnd(m_hWindow);
	::DestroyWindow(hWnd);
	delete this;
	return TRUE;
}


void CMFC360DemoDlg::OnSize(UINT nType, int cx, int cy) 
{
	CDialog::OnSize(nType, cx, cy);
	
	// TODO: Add your message handler code here
	if(m_hWindow)
	{
		XWnd_SetWindowSize (m_hWindow, cx, cy);
		AdjustLayout();
	}
}




void CTongjiDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"文化编码设置");
	XWnd_SetRoundSize(m_hWindow,9);


	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	HELE hPicTitle=XPic_Create(120,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(100,5,100,20,L"统计",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	m_hList=XList_Create(0,80,580,358,m_hWindow);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);

	HELE hButton=XBtn_Create(10,40,80,30,L"按性别",m_hWindow);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CTongjiDlg::tongji1);
	hButton=XBtn_Create(100,40,80,30,L"按部门",m_hWindow);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CTongjiDlg::tongji2);
	hButton=XBtn_Create(190,40,80,30,L"按职称",m_hWindow);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CTongjiDlg::tongji3);
	hButton=XBtn_Create(280,40,80,30,L"按文化程度",m_hWindow);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CTongjiDlg::tongji4);

	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);
	
	
	
	//XList_AddItem(m_hList,zgbm.AllocSysString());
	//XList_SetItemText(m_hList,i,1,xm.AllocSysString());

	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}

BOOL CTongjiDlg::tongji1(HELE hEle,HELE hEventEle)
{
	int man=0,women=0;
	int sign=1;
	sign=mysql_query(&data.mysql,"select xb from m_dadj where xb='男'");
	if(sign)
	{
		MessageBox(NULL,"统计失败","提示",XMB_OK);
		return 0;
	}
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	while(row=mysql_fetch_row(data.result))
	{	
		man++;
	}
	mysql_free_result(data.result);

	sign=mysql_query(&data.mysql,"select xb from m_dadj where xb='女'");
	if(sign)
	{
		MessageBox(NULL,"统计失败","提示",XMB_OK);
		return 0;
	}
	data.result=mysql_store_result(&data.mysql);
	while(row=mysql_fetch_row(data.result))
	{	
		women++;
	}
	mysql_free_result(data.result);

	XList_DeleteAllColumns(m_hList);
	XList_AddColumn(m_hList,100,L"性别"); 
	XList_AddColumn(m_hList,450,L"人数");

	CString cnum;
	cnum.Format("%d",man);
	XList_AddItem(m_hList,L"男");
	XList_SetItemText(m_hList,0,1,cnum.AllocSysString());
	XList_AddItem(m_hList,L"女");
	cnum.Format("%d",women);
	XList_SetItemText(m_hList,1,1,cnum.AllocSysString());
	XEle_RedrawEle(m_hList);
	return true;
}
BOOL CTongjiDlg::tongji2(HELE hEle,HELE hEventEle)
{
	int sign=1;
	sign=mysql_query(&data.mysql,"select bmbm from m_dadj");
	if(sign)
	{
		MessageBox(NULL,"统计失败","提示",XMB_OK);
		return 0;
	}
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int bm[50]={0};
	char temp[10];
	while(row=mysql_fetch_row(data.result))
	{	
		for(int i=0;i<50;i++)
		{		
			itoa(i,temp,10);//将int转换为char数组
			if(!strcmp(row[0],temp))
				bm[i]++;
		}
	}
	mysql_free_result(data.result);
	XList_DeleteAllColumns(m_hList);
	XList_AddColumn(m_hList,100,L"职称"); 
	XList_AddColumn(m_hList,450,L"人数");
	CString cbm;
	CString cnum;
	char sqlBuf[1024];
	int j=0;
	for (int i=0;i<50;i++)
	{
		if(bm[i]!=0)
		{
			sprintf(sqlBuf,"select bmm from bm_bm where bmbm=%d",i);
			mysql_query(&data.mysql,sqlBuf);
			data.result=mysql_store_result(&data.mysql);
			row=mysql_fetch_row(data.result);
			cbm.Format("%s",row[0]);
			cnum.Format("%d",bm[i]);
			XList_AddItem(m_hList,cbm.AllocSysString());
			XList_SetItemText(m_hList,j,1,cnum.AllocSysString());
			mysql_free_result(data.result);
			j++;
		}
	}
	XEle_RedrawEle(m_hList);
	return true;
}
BOOL CTongjiDlg::tongji3(HELE hEle,HELE hEventEle)
{
	int sign=1;
	sign=mysql_query(&data.mysql,"select zcbm from m_dadj");
	if(sign)
	{
		MessageBox(NULL,"统计失败","提示",XMB_OK);
		return 0;
	}
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int zc[50]={0};
	char temp[10];
	while(row=mysql_fetch_row(data.result))
	{	
		for(int i=0;i<50;i++)
		{		
			itoa(i,temp,10);//将int转换为char数组
			if(!strcmp(row[0],temp))
				zc[i]++;
		}
	}
	mysql_free_result(data.result);
	XList_DeleteAllColumns(m_hList);
	XList_AddColumn(m_hList,100,L"职称"); 
	XList_AddColumn(m_hList,450,L"人数");
	CString czc;
	CString cnum;
	char sqlBuf[1024];
	int j=0;
	for (int i=0;i<50;i++)
	{
		if(zc[i]!=0)
		{
			sprintf(sqlBuf,"select zcmc from bm_zc where zcbm=%d",i);
			mysql_query(&data.mysql,sqlBuf);
			data.result=mysql_store_result(&data.mysql);
			row=mysql_fetch_row(data.result);
			czc.Format("%s",row[0]);
			cnum.Format("%d",zc[i]);
			XList_AddItem(m_hList,czc.AllocSysString());
			XList_SetItemText(m_hList,j,1,cnum.AllocSysString());
			mysql_free_result(data.result);
			j++;
		}
	}
	XEle_RedrawEle(m_hList);
	return true;
}
BOOL CTongjiDlg::tongji4(HELE hEle,HELE hEventEle)
{
	int sign=1;
	sign=mysql_query(&data.mysql,"select whcd from m_dadj");
	if(sign)
	{
		MessageBox(NULL,"统计失败","提示",XMB_OK);
		return 0;
	}
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int whcd[50]={0};
	char temp[10];
	while(row=mysql_fetch_row(data.result))
	{	
		for(int i=0;i<50;i++)
		{		
			itoa(i,temp,10);//将int转换为char数组
			if(!strcmp(row[0],temp))
				whcd[i]++;
		}
	}
	mysql_free_result(data.result);
	XList_DeleteAllColumns(m_hList);
	XList_AddColumn(m_hList,100,L"文化程度"); 
	XList_AddColumn(m_hList,450,L"人数");
	CString cwhcd;
	CString cnum;
	char sqlBuf[1024];
	int j=0;
	for (int i=0;i<50;i++)
	{
		if(whcd[i]!=0)
		{
			sprintf(sqlBuf,"select whcd from bm_wh where whbm=%d",i);
			mysql_query(&data.mysql,sqlBuf);
			data.result=mysql_store_result(&data.mysql);
			row=mysql_fetch_row(data.result);
			cwhcd.Format("%s",row[0]);
			cnum.Format("%d",whcd[i]);
			XList_AddItem(m_hList,cwhcd.AllocSysString());
			XList_SetItemText(m_hList,j,1,cnum.AllocSysString());
			mysql_free_result(data.result);
			j++;
		}
	}
	XEle_RedrawEle(m_hList);
	return true;
}









void CTongxunluDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"通讯录",hMainWnd,XC_SY_ROUND);
	XWnd_SetRoundSize(m_hWindow,9);

	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(10,5,100,20,L"通讯录",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	HELE m_hList=XList_Create(0,40,580,358,m_hWindow);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);

	XList_AddColumn(m_hList,100,L"姓名"); 
	XList_AddColumn(m_hList,250,L"固定电话");
	XList_AddColumn(m_hList,250,L"移动电话");
	CString name;
	for (int i=0;i<50;i++)
	{
		name.Format("高达");
		XList_AddItem(m_hList,name.AllocSysString());
		XList_SetItemText(m_hList,i,1,L"6213040");
		XList_SetItemText(m_hList,i,2,L"18363120101");
	}

	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	XCGUI_RegWndMessage(m_hWindow,WM_KILLFOCUS,&CTongxunluDlg::OnWndKillFocus);
	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}
BOOL CTongxunluDlg::OnWndKillFocus(HWINDOW hWindow)
{
	HWND hWnd=XWnd_GetHWnd(m_hWindow);
	::DestroyWindow(hWnd);
	delete this;
	return TRUE;
}


void CUserDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);
	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"文化编码设置");
	XWnd_SetRoundSize(m_hWindow,9);


	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(10,5,100,20,L"用户管理",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	HELE hButton=XBtn_Create(410,350,100,30,L"删除",m_hWindow);
	XCGUI_RegEleEvent(hButton,XE_BNCLICK,&CUserDlg::del);

	m_hList=XList_Create(0,40,580,308,m_hWindow);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);

	XList_AddColumn(m_hList,200,L"用户名"); 
	XList_AddColumn(m_hList,450,L"密码");
	mysql_query(&data.mysql,"select * from users");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	CString user,passwd;
	while(row=mysql_fetch_row(data.result))
	{
		user.Format("%s",row[0]);
		passwd.Format("%s",row[1]);
		XList_AddItem(m_hList,user.AllocSysString());
		XList_SetItemText(m_hList,i,1,passwd.AllocSysString());
		i++;	
	}

	mysql_free_result(data.result);

	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}
BOOL CUserDlg::del(HELE hEle,HELE hEventEle)
{
	int sign=XList_GetSelectCount(m_hList);
	if(sign<=0)
	{
		MessageBox(NULL,"请先选中一项!","提示",XMB_OK);
		return false;
	}
	int j=XList_GetSelectItem(m_hList);
	j++;
	CString zgbm;
	mysql_query(&data.mysql,"select * from users");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	while(i<j)
	{
		row=mysql_fetch_row(data.result);
		i++;
	}
	mysql_free_result(data.result);
	int m=1;
	char sql[1024];
	sprintf(sql,"delete from users where user='%s'",row[0]);
	m=mysql_query(&data.mysql,sql);
	if(m==0)
	{
		XList_DeleteItem(m_hList,sign+1);
		XEle_RedrawEle(m_hList);
	}
	else
	{
		MessageBox(NULL,"删除错误,请检查输入!","提示",XMB_OK);
	}
	return 0;
}


void CYgsrtyDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"");
	XWnd_SetRoundSize(m_hWindow,9);

	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(10,5,100,20,L"员工生日提醒",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	HELE hRichEdit=XRichEdit_Create(10,40,530,330,m_hWindow); //创建RichEdit
    HELE hView=XSView_GetView(hRichEdit);
    XEle_SetBkColor(hView,RGB(152,245,255));
	
	int sign=0;
	int r=-1;
	int birth_now;
	mysql_query(&data.mysql,"select xm,csny from m_dadj");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	SYSTEMTIME time;
	GetSystemTime(&time);
	CString strbirth,name,birth;
	CString year,month,day;
	int y,m,d;
	while(row=mysql_fetch_row(data.result))
	{	
		birth_now=100;
		strbirth.Format("%s",row[1]);
		year=strbirth.Left(4);
		strbirth=strbirth.Right(strbirth.GetLength()-strbirth.Find("-")-1);
		month=strbirth.Left (strbirth.Find ("-"));
		day=strbirth.Right(strbirth.GetLength()-strbirth.Find("-")-1);
		y=atoi(year);
		m=atoi(month);
		d=atoi(day);
		if(m>=time.wMonth)
		{
			if(m==time.wMonth)
				if(d>time.wDay)
					birth_now=d-time.wDay;
			else
				birth_now=30*(m-time.wMonth)+d;
		}
		if(birth_now<21)
		{
			sign=1;
			XRichEdit_InsertTextEx(hRichEdit,L"员工",r,-1,0,true,123);
			name.Format("%s",row[0]);
			XRichEdit_InsertTextEx(hRichEdit,name.AllocSysString(),r,-1,0,true,123);
			birth.Format("%d月%d",m,d);
			XRichEdit_InsertTextEx(hRichEdit,birth.AllocSysString(),r,-1,0,true,123);
			XRichEdit_InsertTextEx(hRichEdit,L"过生日",r,-1,0,true,123);
			XRichEdit_InsertText(hRichEdit,L"\n",r,-1);
		}
	}
	if(sign==0)
	{
		XRichEdit_InsertTextEx(hRichEdit,L"近期没有人过生日",-1,-1,0,true,123);
	}

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}











void CWhbmsetDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"文化编码设置");
	XWnd_SetRoundSize(m_hWindow,9);

	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(10,5,100,20,L"文化程度编码设置",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	HELE hStatic1=XStatic_Create(10,48,144,40,L"当前编码",m_hWindow);
	XEle_SetBkTransparent(hStatic1,true);
	XEle_SetFont(hStatic1,hfontx2);
	XEle_SetTextColor(hStatic1,0);

	XGBox_Create(10,270,560,138,L"更改",m_hWindow);
	HELE hStatic2=XStatic_Create(120,310,100,40,L"编码",m_hWindow);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,0);
	hStatic2=XStatic_Create(120,350,100,40,L"文化程度名",m_hWindow);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,0);
	edit_id=XEdit_Create(190,310,200,25,m_hWindow);
	edit_name=XEdit_Create(190,350,200,25,m_hWindow);
	HELE hButton_change=XBtn_Create(410,350,100,30,L"更改",m_hWindow);
	XCGUI_RegEleEvent(hButton_change,XE_BNCLICK,&CWhbmsetDlg::change);

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	m_hList=XList_Create(0,80,580,178,m_hWindow);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);
	XList_AddColumn(m_hList,100,L"编号"); 
	XList_AddColumn(m_hList,450,L"文化程度名称");

	mysql_query(&data.mysql,"select * from bm_wh");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	CString id,name;
	while(row=mysql_fetch_row(data.result))
	{
		id.Format("%s",row[0]);
		name.Format("%s",row[1]);
		XList_AddItem(m_hList,id.AllocSysString());
		XList_SetItemText(m_hList,i,1,name.AllocSysString());
		i++;	
	}

	mysql_free_result(data.result);

	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);
	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}
BOOL CWhbmsetDlg::change(HELE hEle,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	wchar_t id[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(edit_id,id,MAX_PATH);
	wchar_t name[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(edit_name,name,MAX_PATH);
	CString cid,cname;
	
	CString sql;
	int i=1,j=1;
	WideCharToMultiByte(CP_ACP,0,id,256,cid.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,name,256,cname.GetBuffer(500),256,NULL,NULL);
	
	int iid;
	sscanf((LPCTSTR)cid,"%d",&iid);//将cstring转换为int 
	sql.Format("delete from bm_wh where whbm =\'%d\'",iid);
	j=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);
	sql.Format("insert into bm_wh values(\'%d\',\'%s\')",iid,cname);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cid.ReleaseBuffer(0);
	cname.ReleaseBuffer(500);
	if(i==0&&j==0)
	{
		MessageBox(NULL,"更改成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"更改错误!","提示",XMB_OK);
	}
	return true;
}










void CBmbmsetDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"职称编码设置");
	XWnd_SetRoundSize(m_hWindow,9);
	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);

	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(10,5,100,20,L"部门编码设置",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	HELE hStatic1=XStatic_Create(10,48,144,40,L"当前编码",m_hWindow);
	XEle_SetBkTransparent(hStatic1,true);
	XEle_SetFont(hStatic1,hfontx2);
	XEle_SetTextColor(hStatic1,0);

	XGBox_Create(10,270,560,138,L"更改",m_hWindow);
	HELE hStatic2=XStatic_Create(120,310,100,40,L"编码",m_hWindow);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,0);
	hStatic2=XStatic_Create(120,350,100,40,L"部门名",m_hWindow);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,0);
	edit_id=XEdit_Create(190,310,200,25,m_hWindow);
	edit_name=XEdit_Create(190,350,200,25,m_hWindow);
	HELE hButton_change=XBtn_Create(410,350,100,30,L"更改",m_hWindow);
	XCGUI_RegEleEvent(hButton_change,XE_BNCLICK,&CBmbmsetDlg::change);

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder);

	m_hList=XList_Create(0,80,580,178,m_hWindow);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);
	XList_AddColumn(m_hList,100,L"编号"); 
	XList_AddColumn(m_hList,450,L"部门名称");

	mysql_query(&data.mysql,"select * from bm_bm");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	CString id,name;
	while(row=mysql_fetch_row(data.result))
	{
		id.Format("%s",row[0]);
		name.Format("%s",row[1]);
		XList_AddItem(m_hList,id.AllocSysString());
		XList_SetItemText(m_hList,i,1,name.AllocSysString());
		i++;	
	}
	mysql_free_result(data.result);

	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);

	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}
BOOL CBmbmsetDlg::change(HELE hEle,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	wchar_t id[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(edit_id,id,MAX_PATH);
	wchar_t name[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(edit_name,name,MAX_PATH);
	CString cid,cname;
	
	CString sql;
	int i=1,j=1;
	WideCharToMultiByte(CP_ACP,0,id,256,cid.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,name,256,cname.GetBuffer(500),256,NULL,NULL);
	
	int iid;
	sscanf((LPCTSTR)cid,"%d",&iid);//将cstring转换为int 
	sql.Format("delete from bm_bm where bmbm =\'%d\'",iid);
	j=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);
	sql.Format("insert into bm_bm values(\'%d\',\'%s\')",iid,cname);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cid.ReleaseBuffer(0);
	cname.ReleaseBuffer(500);
	if(i==0&&j==0)
	{
		MessageBox(NULL,"更改成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"更改错误!","提示",XMB_OK);
	}
	return TRUE;
}



void CZcbmsetDlg::Create()
{
	int width=580;
	int height=420;

	HWND hMainWnd=XWnd_GetHWnd(mainWnd->m_hWindow);

	m_hWindow=XWnd_CreateWindow(400,200,width,height,L"职称编码设置");
	XWnd_SetRoundSize(m_hWindow,9);
	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);

	HELE hPicTitle=XPic_Create(10,10,360,25,m_hWindow);
	XEle_SetBkTransparent(hPicTitle,TRUE);
	XPic_SetImage(hPicTitle,XImage_LoadFile(L"360image\\skinDlg\\titleBG.png"));
	
	HELE hStaticTitle=XStatic_Create(10,5,100,20,L"职称编码设置",hPicTitle);
	XEle_SetBkTransparent(hStaticTitle,TRUE);
	XEle_SetTextColor(hStaticTitle,RGB(255,255,255));

	HELE hStatic1=XStatic_Create(10,48,144,40,L"当前编码",m_hWindow);
	XEle_SetBkTransparent(hStatic1,true);
	XEle_SetFont(hStatic1,hfontx2);
	XEle_SetTextColor(hStatic1,0);

	XGBox_Create(10,270,560,138,L"更改",m_hWindow);
	HELE hStatic2=XStatic_Create(120,310,100,40,L"编码",m_hWindow);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,0);
	hStatic2=XStatic_Create(120,350,100,40,L"职称名",m_hWindow);
	XEle_SetBkTransparent(hStatic2,true);
	XEle_SetFont(hStatic2,hfontx2);
	XEle_SetTextColor(hStatic2,0);
	edit_id=XEdit_Create(190,310,200,25,m_hWindow);
	edit_name=XEdit_Create(190,350,200,25,m_hWindow);
	HELE hButton_change=XBtn_Create(410,350,100,30,L"更改",m_hWindow);
	XCGUI_RegEleEvent(hButton_change,XE_BNCLICK,&CZcbmsetDlg::change);

	XWnd_SetImageNC(m_hWindow,mainWnd->m_hThemeBackground);
	XWnd_SetImage(m_hWindow,mainWnd->m_hThemeBorder); 
	
	m_hList=XList_Create(0,80,580,178,m_hWindow);
	XEle_EnableBorder(m_hList,FALSE);
	XList_EnableCheckBox(m_hList,FALSE);
	XEle_SetBkTransparent(m_hList,TRUE);
	XEle_SetBkTransparent(XSView_GetView(m_hList),TRUE);
	XList_AddColumn(m_hList,100,L"编号"); 
	XList_AddColumn(m_hList,450,L"职称名称");

	mysql_query(&data.mysql,"select * from bm_zc");
	data.result=mysql_store_result(&data.mysql);
	MYSQL_ROW row;
	int i=0;
	CString id,name;
	while(row=mysql_fetch_row(data.result))
	{
		id.Format("%s",row[0]);
		name.Format("%s",row[1]);
		XList_AddItem(m_hList,id.AllocSysString());
		XList_SetItemText(m_hList,i,1,name.AllocSysString());
		i++;	
	}

	mysql_free_result(data.result);

	XList_SetUserDrawItemHeader(m_hList,MyListHeader_DrawItem);
	XList_SetUserDrawItem(m_hList,MyList_OnDrawItem);

	XWnd_ShowWindow(m_hWindow,SW_SHOW);
}
BOOL CZcbmsetDlg::change(HELE hEle,HELE hEventEle)
{
	mysql_query(&data.mysql,"SET NAMES 'gb2321'");
	wchar_t id[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(edit_id,id,MAX_PATH);
	wchar_t name[MAX_PATH]={0};//编辑框中接受数据
	XEdit_GetText(edit_name,name,MAX_PATH);
	CString cid,cname;
	
	CString sql;
	int i=1,j=1;
	WideCharToMultiByte(CP_ACP,0,id,256,cid.GetBuffer(0),256,NULL,NULL);
	WideCharToMultiByte(CP_ACP,0,name,256,cname.GetBuffer(500),256,NULL,NULL);
	
	int iid;
	sscanf((LPCTSTR)cid,"%d",&iid);//将cstring转换为int 
	sql.Format("delete from bm_zc where zcbm =\'%d\'",iid);
	j=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);
	sql.Format("insert into bm_zc values(\'%d\',\'%s\')",iid,cname);
	i=mysql_query(&data.mysql,(char*)(LPCTSTR)sql);

	cid.ReleaseBuffer(0);
	cname.ReleaseBuffer(500);
	if(i==0&&j==0)
	{
		MessageBox(NULL,"更改成功","提示",XMB_OK);
	}
	else
	{
		MessageBox(NULL,"更改错误!","提示",XMB_OK);
	}
	return TRUE;
}



//让外城的窗口忽略此消息，使得能传递到内衬
BOOL CMFC360DemoDlg::PreTranslateMessage(MSG* pMsg) 
{
	// TODO: Add your specialized code here and/or call the base class
	if (pMsg->message == WM_CHAR)    //如果消息类型为WM_KEYDOWN并且用户按下的是回车
         return FALSE;
	return CDialog::PreTranslateMessage(pMsg);
}
