#include "basefunc.h"

BOOL ProcAddUser(HWND hwnd)
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
	if(is_first_use)
	{
		InitUserFile();
	}
	int i;
	for(i=0;i<uheader.usercount;i++)
	{
		if(strcmp(usrlist[i].username,usr)==0)
		{
			MessageBox(hwnd,"用户名与已有用户重名。","错误",MB_OK|MB_ICONSTOP);
			return 0;
		}
	}
	User user;
	//memset(&user,0,sizeof(User));
	user.isadmin=SendDlgItemMessage(hwnd,IDC_ALLPRIV,BM_GETCHECK,0,0)?1:0;
	user.uid=uheader.usercount+1;
	SendDlgItemMessage(hwnd,IDC_USR,WM_GETTEXT,256,user.username);
	strcpy(user.password,pwd);
	
	//重新构建用户列表 
	User *oldptr=usrlist;
	usrlist=(User*)calloc(sizeof(User)*(uheader.usercount+1),1);
	if(!is_first_use)
	{
		memcpy(usrlist,oldptr,sizeof(User)*uheader.usercount);
		free(oldptr);
	}
	memcpy(&usrlist[uheader.usercount],&user,sizeof(User));
	
	uheader.usercount++;
	user.uid=uheader.nextid;
	uheader.nextid++;
	//添加用户头、 用户信息
	fseek(fuser,SEEK_SET,0);
	fwrite(&uheader,1,sizeof(uheader),fuser);
	fseek(fuser,SEEK_SET,sizeof(uheader));
	fwrite(usrlist,1,sizeof(User)*uheader.usercount,fuser);
	if(is_first_use)
	{
		MessageBox(hwnd,"用户添加成功，现在您需要重新登录本程序","提示",MB_OK|MB_ICONINFORMATION);
	}
	else
	{
		RefreshUserCntDlg(lstboxwnd);
	}
	return 1;
}


