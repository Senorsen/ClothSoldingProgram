#include "basefunc.h"

BOOL ProcUserDelete(HWND hwnd,int cursel)
{
	if(cursel==-1) cursel=0;
	char notify[256];
	int i=cursel;
	if(usrlist[i].uid==1)
	{
		MessageBox(hwnd,"���棺������ɾ�����û���","����",MB_OK|MB_ICONSTOP);
		return 0;
	}
	sprintf(notify,"��ȷ��Ҫɾ���û���%s (%s) ��",usrlist[i].username,usrlist[i].isadmin?"��ȫȨ��":"��ͨȨ��");
	int ret=MessageBox(hwnd,notify,"ѯ��",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
	if(ret==IDYES)
	{
		//ɾ���û�
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
