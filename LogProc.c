#include "basefunc.h"

void ProcLog(HWND hwnd)
{
	SendDlgItemMessage(hwnd,IDC_LV,LVM_DELETEALLITEMS,0,0);
	int year,mon;
	char tmp[50];
	SendDlgItemMessage(hwnd,IDC_EDITYR,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%d",&year);
	SendDlgItemMessage(hwnd,IDC_EDITMO,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%d",&mon);
	Psvl p=firstsld;
	int totsoldnum=0;
	float totsoldpri=0,totsprofit=0;
	int n=0;
	while(p)
	{
		if(p->year==year&&p->month==mon)
		{
			int localu=GetLocalUid(p->uid);
			int i=localu;
			if(p->oprtype==1)
			{
				totsoldnum++;
				totsoldpri+=p->soldprice;
				totsprofit+=p->soldprice-p->purchpr;
				if(localu==-1)
				{
					//用户不存在，已被删除
					//continue; 
				}
				sprintf(tmp,"%d",p->sid);
				LVITEM vitem;
				vitem.mask=LVIF_TEXT;
				vitem.pszText=tmp;
				vitem.iItem=n;
				vitem.iSubItem=0;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTITEM,0,&vitem);
				sprintf(tmp,"%d-%d-%d %.2d:%.2d:%.2d",p->year,p->month,p->day,p->hour,p->minute,p->second);
				vitem.pszText=tmp;
				vitem.iSubItem=1;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=GetLocalCid(p->cid)==-1?"货物已删除":GetClothPointer(GetLocalCid(p->cid))->trademark;
				vitem.iSubItem=2;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=i==-1?"用户已删除":usrlist[i].username;
				vitem.iSubItem=3;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText="出售";
				vitem.iSubItem=4;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=GetLocalCid(p->cid)==-1?"货物已删除":GetClothPointer(GetLocalCid(p->cid))->barcode;
				vitem.iSubItem=5;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%g",p->purchpr);
				vitem.pszText=tmp;
				vitem.iSubItem=6;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				if(GetLocalCid(p->cid)==-1)
				{
					vitem.pszText="货物已删除";
				}
				else
				{
					sprintf(tmp,"%g",GetClothPointer(GetLocalCid(p->cid))->presoldprice);
				}
				vitem.pszText=tmp;
				vitem.iSubItem=7;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%d",p->percent);
				vitem.pszText=tmp;
				vitem.iSubItem=8;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%g",p->soldprice);
				vitem.pszText=tmp;
				vitem.iSubItem=9;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=p->reason;
				vitem.iSubItem=10;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
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
					//用户不存在，已被删除
					//continue; 
				}
				sprintf(tmp,"%d",p->sid);
				LVITEM vitem;
				vitem.mask=LVIF_TEXT;
				vitem.pszText=tmp;
				vitem.iItem=n;
				vitem.iSubItem=0;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTITEM,0,&vitem);
				sprintf(tmp,"%d-%d-%d %.2d:%.2d:%.2d",p->year,p->month,p->day,p->hour,p->minute,p->second);
				vitem.pszText=tmp;
				vitem.iSubItem=1;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=GetLocalCid(p->cid)==-1?"货物已删除":GetClothPointer(GetLocalCid(p->cid))->trademark;
				vitem.iSubItem=2;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=i==-1?"用户已删除":usrlist[i].username;
				vitem.iSubItem=3;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText="退货";
				vitem.iSubItem=4;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=GetLocalCid(p->cid)==-1?"货物已删除":GetClothPointer(GetLocalCid(p->cid))->barcode;
				vitem.iSubItem=5;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%g",p->purchpr);
				vitem.pszText=tmp;
				vitem.iSubItem=6;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				if(GetLocalCid(p->cid)==-1)
				{
					vitem.pszText="货物已删除";
				}
				else
				{
					sprintf(tmp,"%g",GetClothPointer(GetLocalCid(p->cid))->presoldprice);
				}
				vitem.pszText=tmp;
				vitem.iSubItem=7;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%d",p->percent);
				vitem.pszText=tmp;
				vitem.iSubItem=8;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%g",p->soldprice);
				vitem.pszText=tmp;
				vitem.iSubItem=9;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=p->reason;
				vitem.iSubItem=10;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
			}
			if(p->oprtype==3)
			{
				if(localu==-1)
				{
					//用户不存在，已被删除
					//continue; 
				}
				sprintf(tmp,"%d",p->sid);
				LVITEM vitem;
				vitem.mask=LVIF_TEXT;
				vitem.pszText=tmp;
				vitem.iItem=n;
				vitem.iSubItem=0;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTITEM,0,&vitem);
				sprintf(tmp,"%d-%d-%d %.2d:%.2d:%.2d",p->year,p->month,p->day,p->hour,p->minute,p->second);
				vitem.pszText=tmp;
				vitem.iSubItem=1;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=GetLocalCid(p->cid)==-1?"货物已删除":GetClothPointer(GetLocalCid(p->cid))->trademark;
				vitem.iSubItem=2;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=i==-1?"用户已删除":usrlist[i].username;
				vitem.iSubItem=3;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText="换货";
				vitem.iSubItem=4;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=GetLocalCid(p->cid)==-1?"货物已删除":GetClothPointer(GetLocalCid(p->cid))->barcode;
				vitem.iSubItem=5;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%g",p->purchpr);
				vitem.pszText=tmp;
				vitem.iSubItem=6;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				if(GetLocalCid(p->cid)==-1)
				{
					vitem.pszText="货物已删除";
				}
				else
				{
					sprintf(tmp,"%g",GetClothPointer(GetLocalCid(p->cid))->presoldprice);
				}
				vitem.pszText=tmp;
				vitem.iSubItem=7;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%d",p->percent);
				vitem.pszText=tmp;
				vitem.iSubItem=8;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				sprintf(tmp,"%g",p->soldprice);
				vitem.pszText=tmp;
				vitem.iSubItem=9;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
				vitem.pszText=p->reason;
				vitem.iSubItem=10;
				SendDlgItemMessage(hwnd,IDC_LV,LVM_SETITEM,0,&vitem);
			}
			n++;
		}
		p=p->next;
	}
	sprintf(tmp,"%d",totsoldnum);
	SendDlgItemMessage(hwnd,IDC_MONSLD,WM_SETTEXT,0,tmp);
	sprintf(tmp,"%g",totsoldpri);
	SendDlgItemMessage(hwnd,IDC_MONINC,WM_SETTEXT,0,tmp);
	sprintf(tmp,"%g",totsprofit);
	SendDlgItemMessage(hwnd,IDC_MONPROFIT,WM_SETTEXT,0,tmp);
}

BOOL GetReason(HWND hwnd,int n,char *s)
{
	int i=-1;
	int year,mon;
	char tmp[50];
	SendDlgItemMessage(hwnd,IDC_EDITYR,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%d",&year);
	SendDlgItemMessage(hwnd,IDC_EDITMO,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%d",&mon);
	Psvl p=firstsld;
	while(p&&i!=n)
	{
		if(p->year==year&&p->month==mon)
		{
			i++;
			if(i==n) break;
		}
		p=p->next;
	}
	if(i!=n)
	{
		return 0;
	}
	else
	{
		strcpy(s,p->reason);
		return 1;
	}
}

