#include "MainApp.h"



int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPreInstance, LPSTR args, int argv) {

	MSG msg;
	HWND hWnd;
	WNDCLASS wnc;
	
	wnc.cbClsExtra = NULL;
	wnc.cbWndExtra = NULL;
	wnc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wnc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wnc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	wnc.hInstance = hInstance;
	wnc.lpfnWndProc = &mainProc;
	wnc.lpszClassName = "alvWINDOW";
	wnc.lpszMenuName = NULL;
	wnc.style = CS_VREDRAW | CS_HREDRAW | CS_DBLCLKS;	//CS_DBLCLKS ��Ϊ���ô����ܹ���Ӧ˫���¼�

	//����������,�Լ����ô��������Ϣ

	if (!RegisterClass(&wnc)) {	//ע�ᴰ����,ʧ�����˳�
		MessageBox(0, "ERROR IN REGISTER CLASS", "ERROR", MB_ICONERROR);
		return -1;
	}

	hWnd = CreateWindow(wnc.lpszClassName, "Window", CW_USEDEFAULT,		
			CW_USEDEFAULT, CW_USEDEFAULT, 300, 300, NULL, NULL, hInstance, NULL);
	//��������

	if (hWnd == NULL) {			//ʧ�����˳�
		MessageBox(0, "ERROR IN CREATE WINDOW", "ERROR", MB_ICONERROR);
		return -1;
	}
	
	LONG wndExStyle = GetWindowLong(hWnd, GWL_EXSTYLE);	//��������� WS_EX_TOOLWINDOW ��ʽ,ʹ���ڲ�������������ʾ
	wndExStyle |= WS_EX_TOOLWINDOW;
	SetWindowLong(hWnd, GWL_EXSTYLE, wndExStyle);

	

	ShowWindow(hWnd, SW_SHOW);			//��ʾ����
	UpdateWindow(hWnd);					//���´���

	//SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOSIZE | SWP_NOMOVE);

	while (GetMessage(&msg, NULL, NULL, NULL)) {	//������Ϣѭ��
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return msg.wParam;
}

LRESULT CALLBACK mainProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
		
	case WM_CREATE:			//���ڴ�����Ϣ��Ӧ
		OnCreate(hWnd, msg, wParam, lParam);
		RegisterHotKey(hWnd, ID_KEY_SHOWxHIDE, MOD_ALT, 'X');
		break;

	case WM_LBUTTONDBLCLK:
		ShowWindow(hWnd, SW_HIDE);
		break;
	case WM_LBUTTONDOWN:	//������������Ϣ��Ӧ
		SendMessage(hWnd, WM_NCLBUTTONDOWN, HTCAPTION, lParam);				//��������������갴�µ���Ϣ,��ƭϵͳ
		break;
	case WM_MOVE:
		StayWindowSide(hWnd);
		break;
	case WM_RBUTTONUP:
		OnRButtonUp(hWnd, msg, wParam, lParam);
		
		break;
	case WM_COMMAND:
		OnBtnClick(hWnd, msg, wParam, lParam);
		break;
	case NM_MYTrayMSG:
		OnTrayMsg(hWnd, msg, wParam, lParam);
		break;
	case WM_HOTKEY:
		if (wParam == ID_KEY_SHOWxHIDE) {
			if (IsWindowVisible(hWnd))
				ShowWindow(hWnd, SW_HIDE);
			else
				ShowWindow(hWnd, SW_SHOW);
			break;
		}
		break;
	}

	return DefWindowProc(hWnd, msg, wParam, lParam);
}



