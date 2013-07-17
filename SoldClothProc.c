#include "basefunc.h"

BOOL ProcSoldCloth(HWND hwnd)	//�۳� 
{
	char tmp[100];
	int per;
	float sldpr;
	Pcvl p=GetClothPointer(cureu_localindex);
	SendDlgItemMessage(hwnd,IDC_SLDPR,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%f",&sldpr);
	per=(int)(sldpr*100.0f/p->presoldprice);
	Sold sld;
	sld.cid=p->cid;
	sld.uid=curuid;
	sld.sid=sheader.nextid;
	sheader.nextid++;
	sheader.soldcount++;
	sld.oprtype=1;	//�۳� 
	sld.percent=per;
	sld.soldprice=sldpr;
	sld.purchpr=p->purchpr;
	sld.reason[0]=0;	//������ԭ�� 
	time_t now;
	struct tm *timeinfo;
	time(&now);
	timeinfo=localtime(&now);
	sld.year=timeinfo->tm_year+1900;
	sld.month=timeinfo->tm_mon+1;
	sld.day=timeinfo->tm_mday;
	sld.hour=timeinfo->tm_hour;
	sld.minute=timeinfo->tm_min;
	sld.second=timeinfo->tm_sec;
	Psvl ps=AddSold();
	memcpy(ps,&sld,sizeof(Sold));
	p->soldnum++;		//�۳��� 
	p->inventory--;		//�����
	//����cloth
	fseek(fcloth,sizeof(cheader)+sizeof(Cloth)*cureu_localindex,SEEK_SET);
	fwrite(p,sizeof(Cloth),1,fcloth);
	//���sold
	fseek(fsold,0,SEEK_SET);
	fwrite(&sheader,sizeof(sheader),1,fsold);
	fseek(fsold,sizeof(sheader)+sizeof(Sold)*(sheader.soldcount-1),SEEK_SET);
	fwrite(ps,sizeof(Sold),1,fsold);
	return 1; 
}

BOOL ProcDiSoldCloth(HWND hwnd)	//�˻� 
{
	char tmp[100];
	int per;
	float sldpr;
	Pcvl p=GetClothPointer(cureu_localindex);
	SendDlgItemMessage(hwnd,IDC_SLDPR,WM_GETTEXT,256,tmp);
	sscanf(tmp,"%f",&sldpr);
	per=(int)(sldpr*100.0f/p->presoldprice);
	Sold sld;
	sld.cid=p->cid;
	sld.uid=curuid;
	sld.sid=sheader.nextid;
	sheader.nextid++;
	sheader.soldcount++;
	sld.oprtype=2;	//�˻� 
	sld.percent=per;
	sld.soldprice=sldpr;
	sld.purchpr=p->purchpr;
	SendDlgItemMessage(hwnd,IDC_REASON,WM_GETTEXT,256,sld.reason);
	time_t now;
	struct tm *timeinfo;
	time(&now);
	timeinfo=localtime(&now);
	sld.year=timeinfo->tm_year+1900;
	sld.month=timeinfo->tm_mon+1;
	sld.day=timeinfo->tm_mday;
	sld.hour=timeinfo->tm_hour;
	sld.minute=timeinfo->tm_min;
	sld.second=timeinfo->tm_sec;
	Psvl ps=AddSold();
	memcpy(ps,&sld,sizeof(Sold));
	p->soldnum--;		//�۳��� 
	p->inventory++;		//�����
	//����cloth
	fseek(fcloth,sizeof(cheader)+sizeof(Cloth)*cureu_localindex,SEEK_SET);
	fwrite(p,sizeof(Cloth),1,fcloth);
	//���sold
	fseek(fsold,0,SEEK_SET);
	fwrite(&sheader,sizeof(sheader),1,fsold);
	fseek(fsold,sizeof(sheader)+sizeof(Sold)*(sheader.soldcount-1),SEEK_SET);
	fwrite(ps,sizeof(Sold),1,fsold);
	return 1; 
}

BOOL ProcExSoldCloth(HWND hwnd)	//���� 
{
	Pcvl p=GetClothPointer(cureu_localindex);
	Sold sld;
	sld.cid=p->cid;
	sld.uid=curuid;
	sld.sid=sheader.nextid;
	sheader.nextid++;
	sheader.soldcount++;
	sld.oprtype=3;	//���� 
	sld.percent=0;
	sld.soldprice=0;
	sld.purchpr=p->purchpr;
	time_t now;
	struct tm *timeinfo;
	time(&now);
	timeinfo=localtime(&now);
	sld.year=timeinfo->tm_year+1900;
	sld.month=timeinfo->tm_mon+1;
	sld.day=timeinfo->tm_mday;
	sld.hour=timeinfo->tm_hour;
	sld.minute=timeinfo->tm_min;
	sld.second=timeinfo->tm_sec;
	SendDlgItemMessage(hwnd,IDC_REASON,WM_GETTEXT,256,sld.reason);
	Psvl ps=AddSold();
	memcpy(ps,&sld,sizeof(Sold));
	//���sold
	fseek(fsold,0,SEEK_SET);
	fwrite(&sheader,sizeof(sheader),1,fsold);
	fseek(fsold,sizeof(sheader)+sizeof(Sold)*(sheader.soldcount-1),SEEK_SET);
	fwrite(ps,sizeof(Sold),1,fsold);
	return 1; 
}

