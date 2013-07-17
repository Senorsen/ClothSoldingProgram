#include "basefunc.h"

BOOL ProcEditCloth(HWND hwnd)
{
	Pcvl p=GetClothPointer(cureu_localindex);
	Cloth clo;
	clo.soldnum=p->soldnum;
	SendDlgItemMessage(hwnd,IDC_BARCODE,WM_GETTEXT,256,clo.barcode);
	SendDlgItemMessage(hwnd,IDC_TM,WM_GETTEXT,256,clo.trademark);
	SendDlgItemMessage(hwnd,IDC_CKIND,WM_GETTEXT,256,clo.ckind);
	SendDlgItemMessage(hwnd,IDC_PNUM,WM_GETTEXT,256,clo.partnum);
	char tmpstr[50];
	SendDlgItemMessage(hwnd,IDC_INVTR,WM_GETTEXT,256,tmpstr);
	sscanf(tmpstr,"%d",&clo.inventory);
	SendDlgItemMessage(hwnd,IDC_PURCHPR,WM_GETTEXT,256,tmpstr);
	sscanf(tmpstr,"%f",&clo.purchpr);
	SendDlgItemMessage(hwnd,IDC_PRSLDPR,WM_GETTEXT,256,tmpstr);
	sscanf(tmpstr,"%f",&clo.presoldprice);
	clo.cid=p->cid;
	if(SendDlgItemMessage(hwnd,IDC_CHK,BM_GETCHECK,0,0))
	{
		//选中了"进货" 
		clo.inventory+=p->inventory;
	}
	memcpy(p,&clo,sizeof(Cloth));
	fseek(fcloth,sizeof(cheader)+sizeof(Cloth)*cureu_localindex,SEEK_SET);
	fwrite(&clo,sizeof(Cloth),1,fcloth);
	return 1;
}


