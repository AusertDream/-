#pragma once

#include "framework.h"
#include "SourceCode.h"
using namespace std;


extern HANDLE hStdOutput; //���DOS����̨��������DEBUG
#define WM_SUCCESSLOGIN WM_USER+1011  //�ɹ���¼����Ϣ
//���еĴ��ھ��
extern HWND hMainWindow, hSubMainWindow, hLoginInput, hLoginButton, hTextInput, hUserList, hSendButton, hToolBar, hTextShowWindow;
extern HWND hTextAlias, hStartServer;

//ע�ᴴ�����еĴ���


HWND CreateMainWindow(HINSTANCE hIns); //����������
HWND CreateSubMainWindow(HINSTANCE hIns); //������������
HWND CreateLoginInput(HINSTANCE hIns); //�����û��������
HWND CreateLoginButton(HINSTANCE hIns); //������¼��ť
HWND CreateTextInput(HINSTANCE hIns); //���������
HWND CreateUserList(HINSTANCE hIns); //�����û��б�
HWND CreateSendButton(HINSTANCE hIns); //�������Ͱ�ť
HWND CreateToolBar(HINSTANCE hIns); //����������
HWND CreateTextShowWindow(HINSTANCE hIns); //���������¼��ʾ��
HWND CreateTextAlias(HINSTANCE hIns);//�����ǳ���ʾ����
HWND CreateStartServer(HINSTANCE hIns);//���������������İ�ť
LRESULT CALLBACK MyWndProc(HWND hWnd, UINT msgID, WPARAM wParam, LPARAM LParam);//���ڴ�������������Ϣ��
void func();
void OnCommand(WPARAM wParam); //����˵�������Ĳ���



