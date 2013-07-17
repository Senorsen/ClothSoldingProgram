#include "basefunc.h"

void MainProcCreate(HWND hwnd)
{
	wnd=hwnd;
	HMENU hMenu, hSubMenu,hSubSMenu;
	if(iscuradmin)
	{
		hMenu=LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_MAINMENU));
	}
	else
	{
		hMenu=LoadMenu(GetModuleHandle(NULL),MAKEINTRESOURCE(IDR_STAFMENU));
	}
	SetMenu(hwnd,hMenu);
	SendMessage(hwnd,WM_SYSCOMMAND,SC_MAXIMIZE,0);
	//����LV 
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_FIRST+54,0,32);
	//fuck.....why......WTF?????????????????
	LVCOLUMN vcl;
	vcl.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM|LVS_SHOWSELALWAYS;
	vcl.pszText="ID";
	vcl.cx=50;
	vcl.iSubItem=0;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,0,&vcl);
	vcl.pszText="��װƷ��";
	vcl.cx=100;
	vcl.iSubItem=1;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,1,&vcl);
	vcl.pszText="����";
	vcl.cx=100;
	vcl.iSubItem=2;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,2,&vcl);
	vcl.pszText="������";
	vcl.cx=100;
	vcl.iSubItem=3;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,3,&vcl);
	vcl.pszText="���롢�ͺ�";
	vcl.cx=140;
	vcl.iSubItem=4;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,4,&vcl);
	vcl.pszText="�����";
	vcl.cx=90;
	vcl.iSubItem=5;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,5,&vcl);
	vcl.pszText="������";
	vcl.cx=90;
	vcl.iSubItem=6;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,6,&vcl);
	vcl.pszText="������";
	vcl.cx=90;
	vcl.iSubItem=7;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,8,&vcl);
	vcl.pszText="Ԥ�ۼ�";
	vcl.cx=90;
	vcl.iSubItem=8;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTCOLUMN,8,&vcl);
	RefreshClothInfo();
}

void AddClothLst(HWND hwnd,Pcvl p,int i)
{
	LVITEM vitem;
	vitem.mask=LVIF_TEXT;
	if(!p) return;
	vitem.pszText=(char*)malloc(256);
	sprintf(vitem.pszText,"%d",p->cid);
	vitem.iItem=i;
	vitem.iSubItem=0;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_INSERTITEM,0,&vitem);
	//��������
	vitem.iSubItem=1;
	vitem.pszText=p->trademark;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=2;
	vitem.pszText=p->ckind;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=3;
	vitem.pszText=p->barcode;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=4;
	vitem.pszText=p->partnum;
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=5;
	vitem.pszText=(char*)malloc(256);
	sprintf(vitem.pszText,"%d",p->inventory);
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=6;
	vitem.pszText=(char*)malloc(256);
	sprintf(vitem.pszText,"%d",p->soldnum);
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=7;
	vitem.pszText=(char*)malloc(256);
	sprintf(vitem.pszText,"%g",p->purchpr);
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	vitem.iSubItem=8;
	vitem.pszText=(char*)malloc(256);
	sprintf(vitem.pszText,"%g",p->presoldprice);
	SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_SETITEM,0,&vitem);
	AddClothLst(hwnd,p->next,i+1);
}

void RefreshClothInfo()
{
	//����û���Ϣ���б�
	HANDLE hListView=GetDlgItem(wnd,IDC_LSTUSR);
	SendDlgItemMessage(wnd,IDC_LSTCLT,LVM_DELETEALLITEMS,0,0);
	//������еĶ��� 
	Pcvl p=firstclo;
	AddClothLst(wnd,p,0);
}

void AddNewClothDlg(HWND hwnd)
{
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_ADDCLOTH),hwnd, AddNewClothProc);
	if(g_hDlg)
	{
		ShowWindow(g_hDlg,SW_SHOW);
	}
	else
	{
		return;
	}
}

BOOL DeleteClothDlg(int localid)
{
	if(cheader.clothcount==0) return;
	localid=localid==-1?0:localid;
	char prompt[1024];
	Pcvl p=GetClothPointer(localid);
	sprintf(prompt,"��ȷ��Ҫɾ��%d�ŷ�װ %s:%s %s(%s) ��",p->cid,p->barcode,p->trademark,p->ckind,p->partnum);
	int ret=MessageBox(wnd,prompt,"ɾ��ȷ��",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
	if(ret==IDYES)
	{
		DeleteCloth(localid);
		cheader.clothcount--;
		fseek(fcloth,0,SEEK_SET);
		fwrite(&cheader,sizeof(cheader),1,fcloth);
		p=GetClothPointer(localid);
		Cloth clo;
		while(p)
		{
			memcpy(&clo,p,sizeof(Cloth));
			fseek(fcloth,sizeof(cheader)+sizeof(Cloth)*localid,SEEK_SET);
			fwrite(&clo,sizeof(Cloth),1,fcloth);
			p=p->next;
		}
		return 1;
	}
	return 0;
}

void SoldClothPrompt(int localid,int type)
{
	if(cheader.clothcount==0) return;
	localid=localid==-1?0:localid;
	Pcvl p=GetClothPointer(localid);
	if(type==1&&p->inventory==0)
	{
		MessageBox(wnd,"������Ʒ��治�㣬�޷�����","��װ���۹���ϵͳ - ����",MB_OK|MB_ICONSTOP);
		return;
	}
	if(type==2&&p->soldnum==0)
	{
		MessageBox(wnd,"���󣺳�����Ϊ 0 ���޷��˻�","��װ���۹���ϵͳ - ����",MB_OK|MB_ICONSTOP);
		return;
	}
	if(type==3&&p->inventory==0)
	{
		MessageBox(wnd,"������Ʒ��治�㣬�޷�����","��װ���۹���ϵͳ - ����",MB_OK|MB_ICONSTOP);
		return;
	}
	if(type==3&&p->soldnum==0)
	{
		MessageBox(wnd,"���󣺳�����Ϊ 0 ���޷�����","��װ���۹���ϵͳ - ����",MB_OK|MB_ICONSTOP);
		return;
	}
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_SOLD),wnd, SoldClothDlgProc);
	if(g_hDlg)
	{
		ShowWindow(g_hDlg,SW_SHOW);
		cureu_localindex=localid;
		char tmp[1024];
		sprintf(tmp,"%d",p->cid);
		SendDlgItemMessage(g_hDlg,IDC_CID,WM_SETTEXT,0,tmp);
		SendDlgItemMessage(g_hDlg,IDC_BARCODE,WM_SETTEXT,0,p->barcode);
		SendDlgItemMessage(g_hDlg,IDC_TM,WM_SETTEXT,0,p->trademark);
		SendDlgItemMessage(g_hDlg,IDC_CKIND,WM_SETTEXT,0,p->ckind);
		SendDlgItemMessage(g_hDlg,IDC_PNUM,WM_SETTEXT,0,p->partnum);
		if(type!=3)		//�ǻ��� 
		{
			sprintf(tmp,"%g",p->presoldprice);
			SendDlgItemMessage(g_hDlg,IDC_PREPR,WM_SETTEXT,0,tmp);
			SendDlgItemMessage(g_hDlg,IDC_SLDPR,WM_SETTEXT,0,tmp);
			SendDlgItemMessage(g_hDlg,IDC_PERCENT,WM_SETTEXT,0,"100");
		}
		if(type==3)		//���� 
		{
			ShowWindow(GetDlgItem(g_hDlg,IDC_PREPR),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_SLDPR),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_PERCENT),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_BTNCALC),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_SOLDTIME),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICSLDT),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICSLDP),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_SOLDPER),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICPS),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICPER),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICSLDPR),SW_HIDE);
		}
		if(type==2)		//�˻�
		{
			//ShowWindow(GetDlgItem(g_hDlg,IDC_PREPR),SW_HIDE);
			//ShowWindow(GetDlgItem(g_hDlg,IDC_SLDPR),SW_HIDE);
			//ShowWindow(GetDlgItem(g_hDlg,IDC_PERCENT),SW_HIDE);
			//ShowWindow(GetDlgItem(g_hDlg,IDC_BTNCALC),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_SOLDTIME),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICSLDT),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_STATICSLDP),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_SOLDPER),SW_HIDE);
			//ShowWindow(GetDlgItem(g_hDlg,IDC_STATICPS),SW_HIDE);
			//ShowWindow(GetDlgItem(g_hDlg,IDC_STATICPER),SW_HIDE);
			//ShowWindow(GetDlgItem(g_hDlg,IDC_STATICSLDPR),SW_HIDE);
		} 
		sprintf(tmp,"%d",p->inventory);
		SendDlgItemMessage(g_hDlg,IDC_INVTR,WM_SETTEXT,0,tmp);
		SendDlgItemMessage(g_hDlg,IDC_SOLDPER,WM_SETTEXT,0,curuser);
		switch(type)
		{
		case 1:
			SendMessage(g_hDlg,WM_SETTEXT,0,"���۷�װȷ��");
			SendDlgItemMessage(g_hDlg,IDOK,WM_SETTEXT,0,"ȷ���۳�");
			ShowWindow(GetDlgItem(g_hDlg,IDC_STREASON),SW_HIDE);
			ShowWindow(GetDlgItem(g_hDlg,IDC_REASON),SW_HIDE);
			break;
		case 2:
			SendMessage(g_hDlg,WM_SETTEXT,0,"�˻�ȷ��");
			SendDlgItemMessage(g_hDlg,IDOK,WM_SETTEXT,0,"ȷ���˻�");
			break;
		case 3:
			SendMessage(g_hDlg,WM_SETTEXT,0,"����ȷ��");
			SendDlgItemMessage(g_hDlg,IDOK,WM_SETTEXT,0,"ȷ�ϻ���");
			break;
		}
		thisoprtype=type;
	}
	else
	{
		return;
	}
}

void StatDlg()
{
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_STAT),wnd, StatDlgProc);
	if(g_hDlg)
	{
		HWND hwnd=g_hDlg; 
		ShowWindow(g_hDlg,SW_SHOW);
		char tmp[50];
		int mon,year;
		time_t now;
		struct tm *timeinfo;
		time(&now);
		timeinfo=localtime(&now);
		year=timeinfo->tm_year+1900;
		mon=timeinfo->tm_mon+1;
		sprintf(tmp,"%d",year);
		SendDlgItemMessage(g_hDlg,IDC_EDITYR,WM_SETTEXT,0,tmp);
		sprintf(tmp,"%d",mon);
		SendDlgItemMessage(g_hDlg,IDC_EDITMO,WM_SETTEXT,0,tmp);
		//lv
		SendDlgItemMessage(hwnd,IDC_LV,LVM_FIRST+54,0,32);
		LVCOLUMN vcl;
		vcl.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM|LVS_SHOWSELALWAYS;
		vcl.pszText="ID";
		vcl.cx=60;
		vcl.iSubItem=0;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,0,&vcl);
		vcl.pszText="����";
		vcl.cx=100;
		vcl.iSubItem=1;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,1,&vcl);
		vcl.pszText="��������";
		vcl.cx=90;
		vcl.iSubItem=2;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,2,&vcl);
		vcl.pszText="���۶�";
		vcl.cx=90;
		vcl.iSubItem=3;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,3,&vcl);
		vcl.pszText="������";
		vcl.cx=90;
		vcl.iSubItem=4;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,4,&vcl);
		ProcStat(hwnd);
	}
	else
	{
		MessageBox(wnd,"���ش����޷�����[ͳ�Ʊ���]���壡������Դ�ļ��Ƿ�������\r\n���򼴽��˳���","���ش���",MB_OK|MB_ICONSTOP);
		exit(0);
	}
}

void LogDlg()
{
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_LOG),wnd, LogDlgProc);
	if(g_hDlg)
	{
		HWND hwnd=g_hDlg;
		ShowWindow(g_hDlg,SW_SHOW);
		char tmp[50];
		int mon,year;
		time_t now;
		struct tm *timeinfo;
		time(&now);
		timeinfo=localtime(&now);
		year=timeinfo->tm_year+1900;
		mon=timeinfo->tm_mon+1;
		sprintf(tmp,"%d",year);
		SendDlgItemMessage(g_hDlg,IDC_EDITYR,WM_SETTEXT,0,tmp);
		sprintf(tmp,"%d",mon);
		SendDlgItemMessage(g_hDlg,IDC_EDITMO,WM_SETTEXT,0,tmp);
		//lv
		SendDlgItemMessage(hwnd,IDC_LV,LVM_FIRST+54,0,32);
		LVCOLUMN vcl;
		vcl.mask=LVCF_TEXT|LVCF_WIDTH|LVCF_SUBITEM|LVS_SHOWSELALWAYS;
		vcl.pszText="ID";
		vcl.cx=40;
		vcl.iSubItem=0;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,0,&vcl);
		vcl.pszText="ʱ��";
		vcl.cx=120;
		vcl.iSubItem=1;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,1,&vcl);
		vcl.pszText="Ʒ��";
		vcl.cx=70;
		vcl.iSubItem=2;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,2,&vcl);
		vcl.pszText="������";
		vcl.cx=75;
		vcl.iSubItem=3;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,3,&vcl);
		vcl.pszText="����";
		vcl.cx=60;
		vcl.iSubItem=4;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,4,&vcl);
		vcl.pszText="������";
		vcl.cx=100;
		vcl.iSubItem=5;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,5,&vcl);
		vcl.pszText="������";
		vcl.cx=50;
		vcl.iSubItem=6;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,6,&vcl);
		vcl.pszText="Ԥ�ۼ�";
		vcl.cx=50;
		vcl.iSubItem=7;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,7,&vcl);
		vcl.pszText="�ۿ�";
		vcl.cx=40;
		vcl.iSubItem=8;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,8,&vcl);
		vcl.pszText="�۳���";
		vcl.cx=50;
		vcl.iSubItem=9;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,9,&vcl);
		vcl.pszText="ԭ��";
		vcl.cx=120;
		vcl.iSubItem=10;
		SendDlgItemMessage(hwnd,IDC_LV,LVM_INSERTCOLUMN,10,&vcl);
		ProcLog(hwnd);
	}
	else
	{
		MessageBox(wnd,"���ش����޷�����[���ۡ��˻�����¼]���壡������Դ�ļ��Ƿ�������\r\n���򼴽��˳���","���ش���",MB_OK|MB_ICONSTOP);
		exit(0);
	}
}

BOOL CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		MainProcCreate(hwnd);
		break;
	case WM_SIZE:
	{
		int height,width;
        height=HIWORD(lParam);        // retrieve width and height
        width=LOWORD(lParam); 
		//��ť:x�����-72��y:7& d=40
		//LV:6,6,-84,-30
		MoveWindow(GetDlgItem(hwnd,IDC_BTNSOLD),width-72*1.5,7*1.5,65*1.5,30*1.5,TRUE);
		MoveWindow(GetDlgItem(hwnd,IDC_BTNRET),width-72*1.5,47*1.5,65*1.5,30*1.5,TRUE);
		MoveWindow(GetDlgItem(hwnd,IDC_BTNCHANGE),width-72*1.5,87*1.5,65*1.5,30*1.5,TRUE);
		MoveWindow(GetDlgItem(hwnd,IDC_BTNADD),width-72*1.5,127*1.5,65*1.5,30*1.5,TRUE);
		MoveWindow(GetDlgItem(hwnd,IDC_BTNEDIT),width-72*1.5,167*1.5,65*1.5,30*1.5,TRUE);
		MoveWindow(GetDlgItem(hwnd,IDC_BTNDEL),width-72*1.5,207*1.5,65*1.5,30*1.5,TRUE);
		MoveWindow(GetDlgItem(hwnd,IDC_LSTCLT),6,6,width-84*1.5,height-15,TRUE);
        break;
    }
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
		case IDC_BTNSOLD:
			SoldClothPrompt(SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_GETNEXTITEM,0,LVNI_SELECTED),1);
			break;
		case IDC_BTNRET:
			SoldClothPrompt(SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_GETNEXTITEM,0,LVNI_SELECTED),2);
			break;
		case IDC_BTNCHANGE:
			SoldClothPrompt(SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_GETNEXTITEM,0,LVNI_SELECTED),3);
			break;
		case IDC_BTNADD:
			AddNewClothDlg(hwnd);
			break;
		case IDM_USRCNT:
			UserControlDlg(hwnd);
			break;
		case IDC_BTNEDIT:
			EditClothDlg(hwnd,SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_GETNEXTITEM,0,LVNI_SELECTED));
			break;
		case IDC_BTNDEL:
			if(DeleteClothDlg(SendDlgItemMessage(hwnd,IDC_LSTCLT,LVM_GETNEXTITEM,0,LVNI_SELECTED)))
			{
				RefreshClothInfo();
			}
			break;
		case IDM_STAT:
			StatDlg();
			break;
		case IDM_LOG:
			LogDlg();
			break;
		case IDM_EXIT:
			SendMessage(hwnd,WM_CLOSE,0,0);
			break;
		default:
			break;
		}
		break;
	case WM_CLOSE:
	{
		int ret=MessageBox(hwnd,"��ȷ��Ҫ�˳���ϵͳ��","ѯ��",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
		if(ret==IDYES)
		{
			EndDialog(hwnd,WM_CLOSE);
			exit(0);
		}
		break;
	}
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK StatDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			ProcStat(hwnd);
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

BOOL CALLBACK LogDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			ProcLog(hwnd);
			break;
		case IDC_BTNREASON:
			{
				int i=SendDlgItemMessage(hwnd,IDC_LV,LVM_GETNEXTITEM,0,LVNI_SELECTED);
				if(i==-1) i=0;
				char reason[1024];
				if(GetReason(hwnd,i,reason))
				{
					MessageBox(hwnd,reason,"ԭ������鿴",MB_OK|MB_ICONINFORMATION);
				}
				else
				{
					MessageBox(hwnd,"������ִ���","����",MB_OK|MB_ICONSTOP);
				}
			}
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

void EditClothDlg(HWND hwnd,int curecl)
{
	if(cheader.clothcount==0) return;
	curecl=curecl==-1?0:curecl;
	cureu_localindex=curecl;
	HWND g_hDlg=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(DLG_EDITCLOTH),hwnd, EditClothProc);
	if(g_hDlg)
	{
		ShowWindow(g_hDlg,SW_SHOW);
		Pcvl p=GetClothPointer(curecl);
		char tmp[1024];
		sprintf(tmp,"%d",p->cid);
		SendDlgItemMessage(g_hDlg,IDC_CID,WM_SETTEXT,0,tmp);
		SendDlgItemMessage(g_hDlg,IDC_BARCODE,WM_SETTEXT,0,p->barcode);
		SendDlgItemMessage(g_hDlg,IDC_TM,WM_SETTEXT,0,p->trademark);
		SendDlgItemMessage(g_hDlg,IDC_CKIND,WM_SETTEXT,0,p->ckind);
		SendDlgItemMessage(g_hDlg,IDC_PNUM,WM_SETTEXT,0,p->partnum);
		sprintf(tmp,"���۳� %d ��",p->soldnum);
		SendDlgItemMessage(g_hDlg,IDC_SOLDNUM,WM_SETTEXT,0,tmp);
		sprintf(tmp,"%g",p->purchpr);
		SendDlgItemMessage(g_hDlg,IDC_PURCHPR,WM_SETTEXT,0,tmp);
		sprintf(tmp,"%g",p->presoldprice);
		SendDlgItemMessage(g_hDlg,IDC_PRSLDPR,WM_SETTEXT,0,tmp);
		sprintf(tmp,"%d",p->inventory);
		SendDlgItemMessage(g_hDlg,IDC_INVTR,WM_SETTEXT,0,tmp);
	}
	else
	{
		return;
	}
}

BOOL CALLBACK AddNewClothProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			if(ProcAddNewCloth(hwnd))
			{
				RefreshClothInfo();
				EndDialog(hwnd,IDOK);
			}
			break;
		case IDCANCEL:
		{
			int ret=MessageBox(hwnd,"��ȷ��Ҫ�˳���ǰ�༭���κ����ݶ����ᱻ���档","ѯ��",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
			if(ret==IDYES)
			{
				EndDialog(hwnd,IDCANCEL);
			}
			break;
		}
		}
		break;
	case WM_CLOSE:
		SendMessage(hwnd,WM_COMMAND,MAKELONG(IDCANCEL,0),0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK EditClothProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDOK:
			if(ProcEditCloth(hwnd))
			{
				RefreshClothInfo();
				EndDialog(hwnd,IDOK);
			}
			break;
		case IDCANCEL:
		{
			int ret=MessageBox(hwnd,"��ȷ��Ҫ�˳���ǰ�༭���κ����ݶ����ᱻ���档","ѯ��",MB_ICONQUESTION|MB_YESNO|MB_DEFBUTTON2);
			if(ret==IDYES)
			{
				EndDialog(hwnd,IDCANCEL);
			}
			break;
		}
		}
		break;
	case WM_CLOSE:
		SendMessage(hwnd,WM_COMMAND,MAKELONG(IDCANCEL,0),0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

BOOL CALLBACK SoldClothDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
	case WM_INITDIALOG:
		break;
	case WM_COMMAND:
		switch(LOWORD(wParam))
		{
		case IDC_BTNCALC:
			{
				char tmp[50];
				int per;
				float sld;
				Pcvl p=GetClothPointer(cureu_localindex);
				SendDlgItemMessage(hwnd,IDC_PERCENT,WM_GETTEXT,256,tmp);
				sscanf(tmp,"%d",&per);
				sld=p->presoldprice*(float)per/100.0f;
				sprintf(tmp,"%g",sld);
				SendDlgItemMessage(hwnd,IDC_SLDPR,WM_SETTEXT,0,tmp);
			}
			break;
		case IDOK:
			switch(thisoprtype)
			{
			case 1:
				if(ProcSoldCloth(hwnd))
				{
					RefreshClothInfo();
					EndDialog(hwnd,IDOK);
				}
				break;
			case 2:
				if(ProcDiSoldCloth(hwnd))
				{
					RefreshClothInfo();
					EndDialog(hwnd,IDOK);
				}
				break;
			case 3:
				if(ProcExSoldCloth(hwnd))
				{
					RefreshClothInfo();
					EndDialog(hwnd,IDOK);
				}
				break;
			}
			break;
		case IDCANCEL:
		{
			EndDialog(hwnd,IDCANCEL);
			break;
		}
		}
		break;
	case WM_CLOSE:
		SendMessage(hwnd,WM_COMMAND,MAKELONG(IDCANCEL,0),0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

