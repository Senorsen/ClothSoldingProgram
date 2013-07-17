#include "basefunc.h"

void ProcStat(HWND hwnd)
{
	SendDlgItemMessage(hwnd,IDC_LV,LVM_DELETEALLITEMS,0,0);
	int year,mon;
	char tmp[50];
	SendDlgItemMessage(hwnd,IDC_EDITYR,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%d",&year);
	SendDlgItemMessage(hwnd,IDC_EDITMO,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%d",&mon);
	Psvl p=firstsld;
	int usrnum=uheader.usercount;
	int *usoldnum;
	float *usoldpri,*usprofit;
	usoldnum=(int*)malloc(usrnum*sizeof(int));
	usoldpri=(float*)malloc(usrnum*sizeof(float));
	usprofit=(float*)malloc(usrnum*sizeof(float));
	memset(usoldnum,0,usrnum*sizeof(int));
	memset(usoldpri,0,usrnum*sizeof(float));
	memset(usprofit,0,usrnum*sizeof(float));
	int totsoldnum=0;
	float totsoldpri=0,totsprofit=0;
	while(p)
	{
		if(p->year==year&&p->month==mon)
		{
			int localu=GetLocalUid(p->uid);
			if(p->oprtype==1)
			{
				totsoldnum++;
				totsoldpri+=p->soldprice;
				totsprofit+=p->soldprice-p->purchpr;
				if(localu==-1)
				{
					//用户不存在，已被删除
					continue; 
				}
				usoldnum[localu]++;
				usoldpri[localu]+=p->soldprice;
				usprofit[localu]+=p->soldprice-p->purchpr;
			}
			//换货无影响
			//退货则反过来
			if(p->oprtype==2)
			{
				totsoldnum--;
				totsoldpri-=p->soldprice;
				totsprofit-=p->soldprice-p->purchpr;
				if(localu==-1)
				{
					continue;
				}
				usoldnum[localu]--;
				usoldpri[localu]-=p->soldprice;
				usprofit[localu]-=p->soldprice-p->purchpr;
			}
		}
		p=p->next;
	}
	sprintf(tmp,"%d",totsoldnum);
	SendDlgItemMessage(hwnd,IDC_MONSLD,WM_SETTEXT,0,tmp);
	sprintf(tmp,"%g",totsoldpri);
	SendDlgItemMessage(hwnd,IDC_MONINC,WM_SETTEXT,0,tmp);
	sprintf(tmp,"%g",totsprofit);
	SendDlgItemMessage(hwnd,IDC_MONPROFIT,WM_SETTEXT,0,tmp);
	int i;
	for(i=0;i<uheader.usercount;i++)
	{
		sprintf(tmp,"%d",usrlist[i].uid);
		LVITEM vitem;
		vitem.mask=LVIF_TEXT;
		vitem.pszText=tmp;
		vitem.iItem=i;
		vitem.iSubItem=0;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTITEM,0,&vitem);
		vitem.pszText=usrlist[i].username;
		vitem.iItem=i;
		vitem.iSubItem=1;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,1,&vitem);
		sprintf(tmp,"%d",usoldnum[i]);
		vitem.pszText=tmp;
		vitem.iItem=i;
		vitem.iSubItem=2;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,2,&vitem);
		sprintf(tmp,"%g",usoldpri[i]);
		vitem.pszText=tmp;
		vitem.iItem=i;
		vitem.iSubItem=3;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,3,&vitem);
		sprintf(tmp,"%g",usprofit[i]);
		vitem.pszText=tmp;
		vitem.iItem=i;
		vitem.iSubItem=4;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,4,&vitem);
	}
	free(usoldnum);
	free(usoldpri);
	free(usprofit);
	//我还算有点良心吧…… 
}

