#include "basefunc.h"

HINSTANCE _hInstance;
HINSTANCE _hPrevInstance;
LPSTR _lpCmdLine;
int _nCmdShow;
int wnd;

int CreateMainWindow(char *title)
{
	HWND hwnd;
	HINSTANCE hInstance=_hInstance;
	HINSTANCE hPrevInstance=_hPrevInstance;
	LPSTR lpCmdLine=_lpCmdLine;
	int nCmdShow=_nCmdShow;
	hwnd=CreateDialogA(GetModuleHandle(NULL), MAKEINTRESOURCE(IDD_MAINWND),NULL, WndProc);
	if(hwnd!=NULL)
	{
		wnd=hwnd;
		SendMessage(hwnd,WM_SETTEXT,0,(LPARAM)(LPCTSTR)title);
		if(!iscuradmin)
		{
			ShowWindow(GetDlgItem(hwnd,IDC_BTNADD),SW_HIDE);
			ShowWindow(GetDlgItem(hwnd,IDC_BTNEDIT),SW_HIDE);
			ShowWindow(GetDlgItem(hwnd,IDC_BTNDEL),SW_HIDE);
		}
		ShowWindow(hwnd,SW_SHOW);
		return 0;
	}
	else
	{
		MessageBox(NULL,"严重错误：创建主窗口失败！","错误",MB_OK|MB_ICONSTOP);
		//手动阿狸笑哈哈。。。。。肯定是你RP问题啊！！ 
		exit(0);
	}
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	if(Initialize()) return 0;
	_hInstance=hInstance;
	_hPrevInstance=hPrevInstance;
	_lpCmdLine=lpCmdLine;
	_nCmdShow=nCmdShow; 
	MSG Msg;
	
	while(GetMessage(&Msg, NULL, 0, 0) > 0)
	{
		int iStyle=GetWindowLong(Msg.hwnd,GWL_STYLE);
		SetWindowLong(Msg.hwnd,GWL_STYLE,iStyle|WS_TABSTOP);
		if(Msg.message==WM_KEYDOWN&&Msg.wParam==VK_TAB)
		{
			HWND hWndCtrlNext=GetNextDlgTabItem(GetParent(GetFocus()),GetFocus(),(GetKeyState(VK_SHIFT)&0x8000)?TRUE:FALSE);//取得当前焦点控件的下一个控件的句柄
			if (hWndCtrlNext)
		    {
		    	SetFocus(hWndCtrlNext);//设置下一件控件得到输入焦点
		    }
			continue;
		}
		TranslateMessage(&Msg);
		DispatchMessage(&Msg);
	}
	return Msg.wParam;
}


