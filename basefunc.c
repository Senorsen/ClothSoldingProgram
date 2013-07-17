
#include "basefunc.h"

char CurrentPath[MAX_PATH],DatPath[MAX_PATH];
char UsrFile[MAX_PATH],CloFile[MAX_PATH],SldFile[MAX_PATH];
int is_first_use;
int cureu_localindex;

BOOL CreateNewUser(HWND hwnd,BOOL isfirstuse)	//如果是第一次创建，则必须为管理员 
{
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_ADDUSR),hwnd, AddUserDlgProc);
	if(g_hDlg!= NULL)
	{
		is_first_use=isfirstuse;
		ShowWindow(g_hDlg, SW_SHOW);
		if(isfirstuse)
		{
			SendDlgItemMessage(g_hDlg,IDC_ALLPRIV,BM_SETCHECK,1,0);	//设置所有权限选中
			//SendDlgItemMessage(g_hDlg,IDC_USR,WM_SETFOCUS,1,0);
			ShowWindow(GetDlgItem(g_hDlg,IDC_ALLPRIV),SW_HIDE);
		}
		return 0;
	}
	else
	{
		MessageBox(hwnd, "CreateDialog(NEWUSER) returned NUL", "Warning!",MB_OK|MB_ICONSTOP);
		return 1;
	}
}

BOOL UserLoginDlg(HWND hwnd)
{
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_USRLOGIN),hwnd, UserLoginDlgProc);
	if(g_hDlg!= NULL)
	{
		ShowWindow(g_hDlg, SW_SHOW);
		return 0;
	}
	else
	{
		MessageBox(hwnd, "CreateDialog(USERLOGIN) returned NUL", "Warning!",MB_OK|MB_ICONSTOP);
		return 1;
	}
}

BOOL EditUserDlg(HWND hwnd,int i)
{
	if(i==-1) i=0;
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL),MAKEINTRESOURCE(DLG_EDITUSR),hwnd,EditUserDlgProc);
	if(g_hDlg!=NULL)
	{
		char szuid[50];
		int uid=usrlist[i].uid;
		cureu_localindex=i;
		sprintf(szuid,"%d",uid);
		SendDlgItemMessage(g_hDlg,IDC_USRID,WM_SETTEXT,0,szuid);
		SendDlgItemMessage(g_hDlg,IDC_USR,WM_SETTEXT,0,usrlist[i].username);
		SendDlgItemMessage(g_hDlg,IDC_PWD,WM_SETTEXT,0,usrlist[i].password);
		SendDlgItemMessage(g_hDlg,IDC_PWD1,WM_SETTEXT,0,usrlist[i].password);
		if(usrlist[i].isadmin)
		{
			//设置完全权限标志 
			SendDlgItemMessage(g_hDlg,IDC_ALLPRIV,BM_SETCHECK,1,0);
		}
		else
		{
			SendDlgItemMessage(g_hDlg,IDC_ALLPRIV,BM_SETCHECK,0,0);
		}
		if(uid==1)
		{
			//一般来说，店主（第一个帐号）必须为管理员，所以隐藏选项，防止误取消勾选 
			ShowWindow(GetDlgItem(g_hDlg,IDC_ALLPRIV),SW_HIDE);
		} 
		ShowWindow(g_hDlg,SW_SHOW);
		return 0;
	}
	else
	{
		MessageBox(hwnd, "CreateDialog(EDITUSER) returned NUL", "Warning!",MB_OK|MB_ICONSTOP);
		return 1;
	}
}

void RefreshUserCntDlg(HWND hwnd)
{
	//添加用户信息到列表
	HANDLE hListView=GetDlgItem(hwnd,IDC_LSTUSR);
	SendDlgItemMessage(hwnd,IDC_LSTUSR,LVM_DELETEALLITEMS,0,0);
	LVITEM vitem;
	vitem.mask=LVIF_TEXT;
	int i;
	for(i=0;i<uheader.usercount;i++)
	{
		vitem.pszText=(char*)malloc(50);
		sprintf(vitem.pszText,"%d",usrlist[i].uid);
		vitem.iItem=i;
		vitem.iSubItem=0;
		SendDlgItemMessage(hwnd,IDC_LSTUSR,LVM_INSERTITEM,0,&vitem);
		//设置子项
		vitem.iSubItem=1;
		vitem.pszText=usrlist[i].username;
		SendDlgItemMessage(hwnd,IDC_LSTUSR,LVM_SETITEM,0,&vitem);
		vitem.iSubItem=2;
		vitem.pszText=usrlist[i].isadmin?"全部权限":"普通员工";
		SendDlgItemMessage(hwnd,IDC_LSTUSR,LVM_SETITEM,0,&vitem);
	}
}

BOOL UserControlDlg(HWND hwnd)
{
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_USRCNT),hwnd, UserControlDlgProc);
	if(g_hDlg!= NULL)
	{
		ShowWindow(g_hDlg,SW_SHOW);
		lstboxwnd=g_hDlg;
		SendDlgItemMessage(g_hDlg,IDC_LSTUSR,LVM_FIRST+54,0,32);
		//连云小森森在此表示蛋疼菊紧。 SHIT!
		LVCOLUMN vcl;
		vcl.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM|LVS_SHOWSELALWAYS;
		vcl.pszText="ID";
		vcl.cx=30;
		vcl.iSubItem=0;
		SendDlgItemMessage(g_hDlg,IDC_LSTUSR,LVM_INSERTCOLUMN,0,&vcl);
		vcl.pszText="用户名";
		vcl.cx=120;
		vcl.iSubItem=1;
		SendDlgItemMessage(g_hDlg,IDC_LSTUSR,LVM_INSERTCOLUMN,1,&vcl);
		vcl.pszText="权限";
		vcl.cx=60;
		vcl.iSubItem=2;
		SendDlgItemMessage(g_hDlg,IDC_LSTUSR,LVM_INSERTCOLUMN,2,&vcl);
		RefreshUserCntDlg(g_hDlg);
		return 0;
	}
	else
	{
		MessageBox(hwnd, "CreateDialog(USERCNT) returned NUL", "Warning!",MB_OK|MB_ICONSTOP);
		return 1;
	}
}

Pcvl GetClothPointer(int n)
{
	int i=0;
	Pcvl p=firstclo;
	while(p&&i<n)
	{
		p=p->next;
		i++;
	}
	return p;
}

void DeleteCloth(int n)
{
	if(n==0)
	{
		Pcvl newp=firstclo->next;
		free(firstclo);
		firstclo=newp;
	}
	else
	{
		Pcvl p=GetClothPointer(n-1);
		Pcvl newp=p->next->next;
		free(p->next);
		p->next=newp;
	}
}

Pcvl AddCloth()
{
	Pcvl p=(ClothVl*)calloc(1,sizeof(ClothVl));
	p->next=NULL;
	Pcvl t=firstclo;
	if(!firstclo)
	{
		firstclo=p;
		return p;
	}
	while(t->next)
	{
		t=t->next;
	}
	t->next=p;
	return p;
}

Psvl GetSoldPointer(int n)
{
	int i=0;
	Psvl p=firstsld;
	while(p&&i<n)
	{
		p=p->next;
		i++;
	}
	return p;
}

Psvl AddSold()
{
	Psvl p=(SoldVl*)calloc(1,sizeof(SoldVl));
	p->next=NULL;
	Psvl t=firstsld;
	if(!firstsld)
	{
		firstsld=p;
		return p;
	}
	while(t->next)
	{
		t=t->next;
	}
	t->next=p;
	return p;
}

BOOL Initialize()
{
	firstclo=NULL;
	firstsld=NULL;
	GetCurrentDirectory(MAX_PATH,CurrentPath);
	if(CurrentPath[strlen(CurrentPath)-1]!='\\')
    {
        strcat(CurrentPath,"\\");
    }
    sprintf(DatPath,"%sdata\\",CurrentPath);
    if(access(DatPath,0)==-1)
    {
    	mkdir(DatPath);
    }
    sprintf(UsrFile,"%susers.data",DatPath);
    sprintf(CloFile,"%scloth.data",DatPath);
    sprintf(SldFile,"%ssolds.data",DatPath);
    if(access(UsrFile,0)==-1)
    {
    	MessageBox(NULL,"用户数据不存在，此为您第一次使用本程序。将会为您建立新的数据。"
			,"服装销售管理系统 - 第一次使用提示",MB_OK|MB_ICONINFORMATION);
		if(CreateNewUser(NULL,1)) return 1;
		//然后再创建服装数据文件、事件记录文件
		InitClothFile();
		InitSoldFile();
    }
    else
    {
    	//该登录了……
		LoadUserFile();
		LoadClothFile();
		LoadSoldFile();
		UserLoginDlg(NULL);
    }
    return 0;
}

int GetLocalUid(int uid)
{
	int i;
	for(i=0;i<uheader.usercount;i++)
	{
		if(usrlist[i].uid==uid) return i;
	}
	return -1;	//用户不存在 
}

int GetLocalCid(int cid)
{
	int i=0;
	Pcvl p=firstclo;
	while(p)
	{
		if(p->cid==cid) return i;
		i++;
		p=p->next;
	}
	return -1;	//服装不存在 
}

int GetLocalSid(int sid)
{
	int i=0;
	Psvl p=firstsld;
	while(p)
	{
		if(p->sid==sid) return i;
		i++;
		p=p->next;
	}
	return -1;	//记录不存在 
}

void InitUserFile()	//初始化（第一次打开程序时的）建立各种数据文件 
{
	strcpy(uheader.prefix,"USER");
	uheader.usercount=0;
	uheader.nextid=1;
	fuser=NULL;
	fuser=fopen(UsrFile,"wb+");
	if(!fuser)
	{
		MessageBox(NULL,"严重错误：无法打开users.data文件。程序即将退出。"
			,"服装销售管理系统 - 错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	fwrite(&uheader,sizeof(uheader),1,fuser);
	//fclose(fuser);
}

void InitClothFile()
{
	strcpy(cheader.prefix,"CLOT");
	cheader.clothcount=0;
	cheader.nextid=1;
	fcloth=NULL;
	fcloth=fopen(CloFile,"wb+");
	if(!fcloth)
	{
		MessageBox(NULL,"严重错误：无法打开cloth.data文件。程序即将退出。"
			,"服装销售管理系统 - 错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	fwrite(&cheader,sizeof(cheader),1,fcloth);
}

void InitSoldFile()
{
	strcpy(sheader.prefix,"SOLD");
	sheader.soldcount=0;
	sheader.nextid=1;
	fsold=NULL;
	fsold=fopen(SldFile,"wb+");
	if(!fsold)
	{
		MessageBox(NULL,"严重错误：无法打开solds.data文件。程序即将退出。"
			,"服装销售管理系统 - 错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	fwrite(&sheader,sizeof(sheader),1,fsold);
}

void LoadUserFile()
{
	fuser=NULL;
	fuser=fopen(UsrFile,"rb+");
	if(!fuser)
	{
		MessageBox(NULL,"严重错误：无法打开users.data文件。程序即将退出。"
			,"服装销售管理系统 - 错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	fread(&uheader,sizeof(uheader),1,fuser);
	if(strcmp(uheader.prefix,"USER")!=0)
	{
		MessageBox(NULL,"严重错误：USER文件损坏，无法打开。","错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	usrlist=(User*)malloc(uheader.usercount*sizeof(User));
	int i;
	for(i=0;i<uheader.usercount;i++)
	{
		fseek(fuser,SEEK_SET,i*sizeof(User)+sizeof(uheader));
		fread(&usrlist[i],sizeof(User),1,fuser);
	}
}

void LoadClothFile()
{
	fcloth=NULL;
	fcloth=fopen(CloFile,"rb+");
	if(!fcloth)
	{
		MessageBox(NULL,"严重错误：无法打开cloth.data文件。程序即将退出。"
			,"服装销售管理系统 - 错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	fread(&cheader,sizeof(cheader),1,fcloth);
	if(strcmp(cheader.prefix,"CLOT")!=0)
	{
		MessageBox(NULL,"严重错误：CLOT文件损坏，无法打开。","错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	if(cheader.clothcount==0) return;
	clothlist=(Cloth*)malloc(cheader.clothcount*sizeof(Cloth));
	int i;
	for(i=0;i<cheader.clothcount;i++)
	{
		fseek(fcloth,SEEK_SET,i*sizeof(Cloth)+sizeof(cheader));
		fread(&clothlist[i],sizeof(Cloth),1,fcloth);
		Pcvl p=AddCloth();
		memcpy(p,&clothlist[i],sizeof(Cloth));	//从数组复制到链表中
	}
}

void LoadSoldFile()
{
	fsold=NULL;
	fsold=fopen(SldFile,"rb+");
	if(!fsold)
	{
		MessageBox(NULL,"严重错误：无法打开solds.data文件。程序即将退出。"
			,"服装销售管理系统 - 错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	fread(&sheader,sizeof(sheader),1,fsold);
	if(strcmp(sheader.prefix,"SOLD")!=0)
	{
		MessageBox(NULL,"严重错误：SOLD文件损坏，无法打开。","错误",MB_OK|MB_ICONSTOP);
		exit(0);
	}
	soldlist=(Sold*)malloc(sheader.soldcount*sizeof(Sold));
	int i;
	for(i=0;i<sheader.soldcount;i++)
	{
		fseek(fsold,SEEK_SET,i*sizeof(Sold)+sizeof(sheader));
		fread(&soldlist[i],sizeof(Sold),1,fsold);
		Psvl p=AddSold();
		memcpy(p,&soldlist[i],sizeof(Sold));	//从数组复制到链表中
		//fuck....数组什么的完全没用嘛！！！！！！！！！！
		//直接用链表不就好了？不过。。。保存时可能会有点点用。。。。。。。 
	}
}

/***********************************************************

				对话框窗体回调函数 
	
 ***********************************************************/
BOOL CALLBACK AddUserDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			//添加用户处理
			if(ProcAddUser(hwnd))
			{
				if(is_first_use)
				{
					is_first_use=0;
					UserLoginDlg(NULL);
				}
				EndDialog(hwnd,IDOK);
			}
			break;
		case IDCANCEL:
			if(is_first_use)
			{
				int ret=MessageBox(hwnd,"您确定要取消操作吗？任何数据都不会被保存。","询问",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
				if(ret==IDYES)
				{
					EndDialog(hwnd,IDCANCEL);
					exit(0);
				}
				else
				{
					break;
				}
			}
			EndDialog(hwnd,IDCANCEL);
			break;
		}
		break;
	case WM_CLOSE:
		SendMessage(hwnd,WM_COMMAND,IDCANCEL,0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK UserLoginDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_PAINT:
	{
        PAINTSTRUCT ps;
        BeginPaint(hwnd, &ps);
        EndPaint(hwnd, &ps);
		break;
	}
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			if(ProcUserLogin(hwnd))
			{
				//成功登录 
				//MessageBox(hwnd,"成功登录！","服装销售管理系统",MB_OK|MB_ICONINFORMATION);
				char *title=(char*)malloc(300);
				time_t now;
				struct tm *timeinfo;
    			time(&now);
    			timeinfo=localtime(&now);
				sprintf(title,"服装销售管理系统 - %s [%s]    %d 年 %d 月 %d 日",curuser,iscuradmin?"完全权限":"销售权限",timeinfo->tm_year+1900,timeinfo->tm_mon+1,timeinfo->tm_mday);
				CreateMainWindow(title);
				EndDialog(hwnd,IDOK);
			}
			break;
		case IDCANCEL:
			EndDialog(hwnd,IDCANCEL);
			exit(0);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd,WM_CLOSE);
		exit(0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EditUserDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			//编辑用户
			if(ProcEditUser(hwnd))
			{
				EndDialog(hwnd,IDOK);
			}
			break;
		case IDCANCEL:
			EndDialog(hwnd,IDCANCEL);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd,WM_CLOSE);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK UserControlDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_EDITUSR:
			//编辑用户
			EditUserDlg(hwnd,SendDlgItemMessage(hwnd,IDC_LSTUSR,LVM_GETNEXTITEM,0,LVNI_SELECTED));
			break;
		case IDC_ADDUSR:
			//新增用户
			CreateNewUser(hwnd,0);
			break;
		case IDC_DELUSR:
		 	//删除用户
			ProcUserDelete(hwnd,SendDlgItemMessage(hwnd,IDC_LSTUSR,LVM_GETNEXTITEM,0,LVNI_SELECTED));
			break;
		case IDCANCEL:
			EndDialog(hwnd,IDCANCEL);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd,WM_CLOSE);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

