
#include "basefunc.h"

BOOL ProcAddNewCloth(HWND hwnd)
{
	Pcvl p=AddCloth();
	Cloth clo;
	clo.soldnum=0;
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
	clo.cid=cheader.nextid;
	cheader.nextid++;
	cheader.clothcount++;
	memcpy(p,&clo,sizeof(Cloth));
	fseek(fcloth,0,SEEK_SET);
	fwrite(&cheader,sizeof(cheader),1,fcloth);
	fseek(fcloth,sizeof(cheader)+sizeof(Cloth)*(cheader.clothcount-1),SEEK_SET);
	fwrite(&clo,sizeof(Cloth),1,fcloth);
	return 1;
}

