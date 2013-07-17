
#include <stdio.h>
#include <windows.h>
#include <io.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>
#include <commctrl.h>
#include <time.h>
#include "resource.h"
#pragma pack(1)
#define BOOL int

//����ȫ�ֱ��
BOOL iscuradmin; 	//��ǰ�û��Ƿ�Ϊ����Ա
int curuid;
char curuser[255];
int curindex;
FILE *fuser,*fcloth,*fsold;
int is_first_use;
int cureu_localindex;
HWND lstboxwnd;
int thisoprtype;

typedef struct
{
	int uid;
	char username[255];
	char password[255];		//ʱ����ȣ���ʱ����hash�ˣ����Ĵ洢 
	BOOL isadmin;
}User;

struct Uheader
{
	char prefix[5];		//�̶�ֵUSER\0
	int usercount;
	int nextid;
}uheader;

typedef struct
{
	int cid;
	char ckind[50];
	char trademark[50];
	char barcode[50];
	char partnum[50];
	int inventory;	//ʵ�ʴ洢 
	int soldnum;	//���� 
	float purchpr;
	float presoldprice;
}Cloth;

typedef struct clonode
{
	int cid;
	char ckind[50];
	char trademark[50];
	char barcode[50];
	char partnum[50];
	int inventory;	//ʵ�ʴ洢 
	int soldnum;	//���� 
	float purchpr;
	float presoldprice;
	struct clonode *next;
}ClothVl,*Pcvl;

struct Cheader
{
	char prefix[5];		//�̶�ֵCLOT\0
	int clothcount;
	int nextid;
}cheader;

typedef struct
{
	int sid;
	int uid;
	int cid;
	int oprtype;	//1:���ۣ�2:�˻���3:���� 
	char reason[256];	//�˻���ԭ�� 
	float purchpr;
	int percent;
	float soldprice;
	int year,month,day,hour,minute,second;
}Sold;

typedef struct sldnode
{
	int sid;
	int uid;
	int cid;
	int oprtype;	//1:���ۣ�2:�˻���3:���� 
	char reason[256];	//�˻���ԭ�� 
	float purchpr;
	int percent;
	float soldprice;
	int year,month,day,hour,minute,second;
	struct sldnode *next;
}SoldVl,*Psvl;

struct Sheader
{
	char prefix[5];		//�̶�ֵSOLD\0
	int soldcount;
	int nextid;
}sheader;

User *usrlist;
Cloth *clothlist;
Sold *soldlist;
Pcvl firstclo;
Psvl firstsld;

//***************************
//WinMain & MainProc
int wnd;
int CreateMainWindow(char *title);
void MainProcCreate(HWND hwnd);
BOOL CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void RefreshClothInfo();
void AddClothLst(HWND hwnd,Pcvl p,int i);
BOOL CALLBACK AddNewClothProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void AddNewClothDlg(HWND hwnd);
BOOL CALLBACK EditClothProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void EditClothDlg(HWND hwnd,int curecl);
BOOL CALLBACK SoldClothDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void SoldClothPrompt(int localid,int type);
void StatDlg();
BOOL CALLBACK StatDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
void LogDlg();
BOOL CALLBACK LogDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
//***************************
BOOL CALLBACK AddUserDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK UserLoginDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK EditUserDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);
BOOL CALLBACK UserControlDlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam);

BOOL Initialize();
BOOL CreateNewUser(HWND hwnd,BOOL isfirstuse);
BOOL UserLoginDlg(HWND hwnd);
BOOL EditUserDlg(HWND hwnd,int i);
BOOL UserControlDlg(HWND hwnd);
void RefreshUserCntDlg(HWND hwnd);
Pcvl GetClothPointer(int n);
void DeleteCloth(int n);
Pcvl AddCloth();
Psvl GetSoldPointer(int n);
Psvl AddSold();

void InitUserFile();
void InitClothFile();
void InitSoldFile();
void LoadUserFile();

//AddUserDlgProc
BOOL ProcAddUser(HWND hwnd);

//UserLoginDlgProc
BOOL ProcUserLogin(HWND hwnd);

//EditUserDlgProc
BOOL ProcEditUser(HWND hwnd);

BOOL ProcAddNewCloth(HWND hwnd);

BOOL ProcSoldCloth(HWND hwnd);
BOOL ProcDiSoldCloth(HWND hwnd);
BOOL ProcExSoldCloth(HWND hwnd);

void ProcStat(HWND hwnd);

void ProcLog(HWND hwnd);
BOOL GetReason(HWND hwnd,int n,char *s);

