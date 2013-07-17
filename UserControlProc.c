#include "basefunc.h"

BOOL ProcUserDelete(HWND hwnd,int cursel)
{
	if(cursel==-1) cursel=0;
	char notify[256];
	int i=cursel;
	if(usrlist[i].uid==1)
	{
		MessageBox(hwnd,"警告：您不能删除此用户。","错误",MB_OK|MB_ICONSTOP);
		return 0;
	}
	sprintf(notify,"您确定要删除用户：%s (%s) 吗？",usrlist[i].username,usrlist[i].isadmin?"完全权限":"普通权限");
	int ret=MessageBox(hwnd,notify,"询问",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
	if(ret==IDYES)
	{
		//删除用户
		uheader.usercount--;
		int j;
		for(j=i;j<uheader.usercount;j++)
		{
			usrlist[j]=usrlist[j+1];
		}
		fseek(fuser,0,SEEK_SET);
		fwrite(&uheader,1,sizeof(uheader),fuser);
		fwrite(usrlist,1,sizeof(User)*uheader.usercount,fuser);
		RefreshUserCntDlg(lstboxwnd);
		return 1;
	}
	return 0;
}
