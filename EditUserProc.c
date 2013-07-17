
#include "basefunc.h"

BOOL ProcEditUser(HWND hwnd)
{
	char pwd[256],pwd1[256],usr[256];
	SendDlgItemMessage(hwnd,IDC_PWD,WM_GETTEXT,256,pwd);
	SendDlgItemMessage(hwnd,IDC_PWD1,WM_GETTEXT,256,pwd1);
	if(strcmp(pwd,pwd1)!=0)
	{
		MessageBox(hwnd,"两次输入的密码不一致。请返回并重新输入密码。","错误",MB_OK|MB_ICONSTOP);
		return 0;
	}
	if(pwd[0]==0)
	{
		MessageBox(hwnd,"密码不能为空","错误",MB_OK|MB_ICONSTOP);
		return 0; 
	}
	SendDlgItemMessage(hwnd,IDC_USR,WM_GETTEXT,256,usr);
	if(usr[0]==0)
	{
		MessageBox(hwnd,"用户名不能为空","错误",MB_OK|MB_ICONSTOP);
		return 0;
	}
	int i=cureu_localindex;
	strcpy(usrlist[i].username,usr);
	strcpy(usrlist[i].password,pwd);
	usrlist[i].isadmin=SendDlgItemMessage(hwnd,IDC_ALLPRIV,BM_GETCHECK,0,0)?1:0;
	fseek(fuser,sizeof(uheader),SEEK_SET);
	fwrite(usrlist,1,sizeof(User)*uheader.usercount,fuser);
	RefreshUserCntDlg(lstboxwnd);
	strcpy(curuser,usrlist[curindex].username);
}
