#include "basefunc.h"

BOOL ProcUserLogin(HWND hwnd)
{
	char user[256],password[256];
	SendDlgItemMessage(hwnd,IDC_USR,WM_GETTEXT,256,user);
	SendDlgItemMessage(hwnd,IDC_PWD,WM_GETTEXT,256,password);
	if(user[0]==0)
	{
		MessageBox(hwnd,"�������û���","����",MB_OK|MB_ICONSTOP);
		return 0;
	}
	if(password[0]==0)
	{
		MessageBox(hwnd,"���벻��Ϊ��","����",MB_OK|MB_ICONSTOP);
		return 0;
	}
	int i;
	for(i=0;i<uheader.usercount;i++)
	{
		if(strcmp(usrlist[i].username,user)==0)
		{
			if(strcmp(usrlist[i].password,password)==0)
			{
				iscuradmin=usrlist[i].isadmin;
				curuid=usrlist[i].uid;
				curindex=i;
				strcpy(curuser,usrlist[i].username);
				return 1;	//��¼�ɹ� 
			}
			else
			{
				MessageBox(hwnd,"�������","����",MB_OK|MB_ICONSTOP);
				return 0;
			}
		}
	}
	MessageBox(hwnd,"�û�������","����",MB_OK|MB_ICONSTOP);
	return 0;
}


