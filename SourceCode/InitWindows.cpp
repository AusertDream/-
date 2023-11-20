#pragma once
#include "framework.h"
#include "InitWindows.h"
#include "SourceCode.h" //������Դ
using namespace std;

HANDLE hStdOutput = 0; //���DOS����̨��������DEBUG

//#define WM_MYMSG WM_USER+1011 �Զ�����Ϣ����

//���д��ڵľ��
HWND hMainWindow, hSubMainWindow, hLoginInput, hLoginButton, hTextInput, hUserList, hSendButton, hToolBar, hTextShowWindow;
HWND hTextAlias, hStartServer;

//����Ϊ�����ڵ�ʵ�ֹ��̣��Լ����ڴ������ľ��崦��

//����DOS��DEBUG����
void func() {
	char* text = "dfljaie";
	WriteConsole(hStdOutput, text, strlen(text), NULL, NULL);
}

//����˵�������Ĳ���
void OnCommand(WPARAM wParam) {
	//LOWORD��ȡ����Ĳ˵���ID
	switch (LOWORD(wParam)) {
	case ID_CN:
		//������й�����������ҵ�ʱ��
		//ģʽ�Ի��򣬳��������������
		DialogBox(NULL, (char*)IDD_DIALOG1, NULL, DefWindowProc); 
		//��ģʽ�Ի��򣬲��ᷢ��������������Ҫ��ʾ����Ҫʹ��showwindow������Ȼ��ʵ���ϻ�����������������
		//HWND hDialog = CreateDialog(NULL, (char*)IDD_DIALOG1, hMainWindow, DefWindowProc);
		//ShowWindow(hDialog, SW_SHOW);


		break;
	case ID_GLOBAL:
		//�����ȫ�������ҵ�ʱ��


		break;
	}
}

LRESULT CALLBACK SubMainWindowProc(
	HWND hWnd, //���ھ��
	UINT msgID, //��ϢID
	WPARAM wParam, //��Ϣ����1
	LPARAM LParam //��Ϣ����2
) {
	switch (msgID) {
	case WM_PAINT:
		//���ƻ�ӭ�ı�
		//���ƹ���
		PAINTSTRUCT ps;
		//��ʼ����
		HDC hdc = BeginPaint(hWnd, &ps);
		// ��������
		HFONT hFont = CreateFont(20, 0, 0, 0, FW_NORMAL, FALSE, FALSE, FALSE, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Arial");
		//���ö���
		SelectObject(hdc, hFont);
		// �������
		TextOut(hdc, 155, 20, "��ӭ��������������", strlen("��ӭ��������������"));
		// �������
		DeleteObject(hFont);
		//��������
		EndPaint(hWnd, &ps);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, LParam);
}

LRESULT CALLBACK StartServerButtonProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM LParam) {
	switch (msgID)
	{
	case WM_COMMAND:
		MessageBox(NULL, "Button is pressed", "y", MB_OK);
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, LParam);
}


LRESULT CALLBACK MainWindowProc(
	HWND hWnd, //���ھ��
	UINT msgID, //��ϢID
	WPARAM wParam, //��Ϣ����
	LPARAM LParam //��Ϣ����
)
{
	switch (msgID) {
	case WM_COMMAND: //����˵�������Ĳ���
		OnCommand(wParam);
		break;
	case WM_SUCCESSLOGIN:
		//���õ��ɹ���¼����Ϣ֮�󣬲Ž��˵����ϡ�
		//ʹ��setmenu�������Ҳ˵���
		SetMenu(hMainWindow, LoadMenu(NULL, (char*)IDRETRY));
		break;
	case WM_DESTROY: //���ر��ܴ��ڵ�ʱ�򣬽�����Ҳ������
		PostQuitMessage(0); //��msgid��WM_DESTROY��ֵ��ʱ���򽫽��̽�����
		break;
	case WM_SYSCOMMAND:
		//��������Ͻǵġ���ʱ�򣬵�����ʾ��ȷ�Ϲر���
		if (wParam == SC_CLOSE) {
			int mRet = MessageBox(hWnd, "���Ҫ�˳���QAQ", "����", MB_YESNO);
			if (mRet == IDYES) {
				//���ȷ�ϣ���ôʲô������������Ĭ�ϴ����������رմ���
			}
			else {
				//������ϣ���ô��ǰ������������ֹĬ�ϴ������رմ���
				return 0;
			}
		}
		break;
	}
	return DefWindowProc(hWnd, msgID, wParam, LParam);
}

HWND CreateMainWindow(HINSTANCE hIns)
{
	WNDCLASS MainWindow = { 0 }; //����һ�������� ���ֽ�MainWindow
	MainWindow.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	MainWindow.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	MainWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	MainWindow.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	MainWindow.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	MainWindow.hInstance = hIns; //��ǰ����ʵ�����
	MainWindow.lpfnWndProc = MainWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	MainWindow.lpszClassName = "MainWindow";//���ô���������֡�
	MainWindow.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	MainWindow.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&MainWindow);

	//���ڴ��д�������
	HWND hMainWindowRes = CreateWindowEx(
		0,//���ڵĶ���������
		"MainWindow",//�����Ĵ����������
		"Ausert�Ķ���������",//���ڵ����ϽǱ�������
		WS_OVERLAPPEDWINDOW,//���ô��ڵĻ������
		200,//���ڵĳ�ʼx����
		200,//���ڵĳ�ʼy����
		500,//���ڵĳ�ʼ���
		300,//���ڵĳ�ʼ�߶�
		NULL,//���ø����ڣ�û���ÿ�NULL
		NULL,//���ò˵���û�в˵�ΪNULL
		hIns,//��ǰ����ʵ�����
		NULL//ûɶ�õĲ���
	);
	//����������Ϊ���ɵ�����С��
	SetWindowLongPtr(hMainWindowRes, GWL_STYLE, WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX);
	return hMainWindowRes;
}

HWND CreateSubMainWindow(HINSTANCE hIns)
{
	WNDCLASS SubMainWindow = { 0 }; //����һ�������� ���ֽ�SubMainWindow
	SubMainWindow.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	SubMainWindow.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	SubMainWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	SubMainWindow.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	SubMainWindow.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	SubMainWindow.hInstance = hIns; //��ǰ����ʵ�����
	SubMainWindow.lpfnWndProc = SubMainWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	SubMainWindow.lpszClassName = "SubMainWindow";//���ô���������֡�
	SubMainWindow.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	SubMainWindow.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&SubMainWindow);


	HWND hSubMainWindowRes = CreateWindowEx(
		0,
		"SubMainWindow",
		NULL,
		WS_CHILD | WS_VISIBLE,
		0,
		0,
		500,
		300,
		hMainWindow,
		NULL,
		hIns,
		NULL
	);

	return hSubMainWindowRes;
}



HWND CreateLoginInput(HINSTANCE hIns)
{

	HWND hLoginInputRes = CreateWindowEx(
		0,
		"EDIT",
		NULL,
		WS_BORDER | WS_CHILD | WS_VISIBLE | ES_LEFT,
		140,
		100,
		260,
		25,
		hSubMainWindow,
		NULL,
		hIns,
		NULL
	);
	return hLoginInputRes;
}

HWND CreateLoginButton(HINSTANCE hIns)
{


	HWND hLoginButtonRes = CreateWindowEx(
		0, //ʹ�ø���չ���
		"BUTTON",
		NULL,
		WS_CHILD | WS_VISIBLE,
		130,
		170,
		200,
		25,
		hSubMainWindow,
		NULL,
		hIns,
		NULL
	);

	return hLoginButtonRes;
}

HWND CreateTextInput(HINSTANCE hIns)
{
	WNDCLASS TextInput = { 0 }; //����һ�������� ���ֽ�TextInput
	TextInput.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	TextInput.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	TextInput.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	TextInput.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	TextInput.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	TextInput.hInstance = hIns; //��ǰ����ʵ�����
	TextInput.lpfnWndProc = DefWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	TextInput.lpszClassName = "TextInput";//���ô���������֡�
	TextInput.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	TextInput.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&TextInput);

	HWND hTextInputRes = 0;


	return hTextInputRes;
}

HWND CreateUserList(HINSTANCE hIns)
{
	WNDCLASS UserList = { 0 }; //����һ�������� ���ֽ�UserList
	UserList.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	UserList.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	UserList.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	UserList.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	UserList.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	UserList.hInstance = hIns; //��ǰ����ʵ�����
	UserList.lpfnWndProc = DefWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	UserList.lpszClassName = "UserList";//���ô���������֡�
	UserList.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	UserList.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&UserList);

	HWND hUserListRes = 0;


	return hUserListRes;
}

HWND CreateSendButton(HINSTANCE hIns)
{
	WNDCLASS SendButton = { 0 }; //����һ�������� ���ֽ�SendButton
	SendButton.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	SendButton.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	SendButton.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	SendButton.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	SendButton.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	SendButton.hInstance = hIns; //��ǰ����ʵ�����
	SendButton.lpfnWndProc = DefWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	SendButton.lpszClassName = "SendButton";//���ô���������֡�
	SendButton.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	SendButton.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&SendButton);

	HWND hSendButtonRes = 0;


	return hSendButtonRes;
}

HWND CreateToolBar(HINSTANCE hIns)
{
	WNDCLASS ToolBar = { 0 }; //����һ�������� ���ֽ�ToolBar
	ToolBar.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	ToolBar.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	ToolBar.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	ToolBar.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	ToolBar.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	ToolBar.hInstance = hIns; //��ǰ����ʵ�����
	ToolBar.lpfnWndProc = DefWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	ToolBar.lpszClassName = "ToolBar";//���ô���������֡�
	ToolBar.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	ToolBar.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&ToolBar);

	HWND hToolBarRes = 0;


	return hToolBarRes;
}

HWND CreateTextShowWindow(HINSTANCE hIns)
{
	WNDCLASS TextShowWindow = { 0 }; //����һ�������� ���ֽ�TextShowWindow
	TextShowWindow.cbClsExtra = 0;// Ҫ���ݴ�����ṹ����Ķ����ֽ�����������Ҫ����Ļ�������
	TextShowWindow.cbWndExtra = 0; //�ڴ���ʵ��֮�����Ķ����ֽ�����������Ҫ����Ļ�������
	TextShowWindow.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);//���ô��ڵı���ɫ��COLOR_WINDOW+1Ϊ��ɫ��
	TextShowWindow.hCursor = NULL;//���ô��ڹ�꣬����ΪNULLΪĬ�Ϲ�ꡣ
	TextShowWindow.hIcon = NULL;//���ô���ͼ�꣬NULLΪĬ��ͼ�ꡣ
	TextShowWindow.hInstance = hIns; //��ǰ����ʵ�����
	TextShowWindow.lpfnWndProc = DefWindowProc; //���õ�ǰ���ڵĴ����������봦�����ĺ��������ɡ�
	TextShowWindow.lpszClassName = "TextShowWindow";//���ô���������֡�
	TextShowWindow.lpszMenuName = NULL; //���ô����Ƿ��в˵���NULLΪû�в˵���
	TextShowWindow.style = CS_HREDRAW | CS_VREDRAW; //���ô��ڷ��CS_HREDRAW��CS_VREDRAWΪ������ˮƽ���ߴ�ֱ��С�仯ʱ���ػ�����

	//ע�ᴰ�ڣ������ϵͳ��д�봰����Ϣ��
	RegisterClass(&TextShowWindow);


	HWND hTextShowWindowRes = 0;



	return hTextShowWindowRes;
}

HWND CreateTextAlias(HINSTANCE hIns)
{

	//���ڴ��д�������
	HWND hTextAliasRes = CreateWindowEx(
		0,//���ڵĶ���������
		"STATIC",//�����Ĵ����������
		"�ǳƣ�",//�ı�����
		WS_VISIBLE | WS_CHILD,//���ô��ڵĻ������
		90,
		105,
		45,
		20,
		hSubMainWindow,//���ø����ڣ�û���ÿ�NULL
		NULL,//���ò˵���û�в˵�ΪNULL
		hIns,//��ǰ����ʵ�����
		NULL//ûɶ�õĲ���
	);

	return hTextAliasRes;
}


HWND CreateStartServer(HINSTANCE hIns) {

	//���ڴ��д�������
	HWND hStartServerRes = CreateWindowEx(
		0,//���ڵĶ���������
		"BUTTON",//�����Ĵ����������
		"����������",//�ı�����
		WS_VISIBLE | WS_CHILD,//���ô��ڵĻ������
		370,
		20,
		100,
		20,
		hSubMainWindow,//���ø����ڣ�û���ÿ�NULL
		NULL,//���ò˵���û�в˵�ΪNULL
		hIns,//��ǰ����ʵ�����
		NULL//ûɶ�õĲ���
	);
	return hStartServerRes;
}
