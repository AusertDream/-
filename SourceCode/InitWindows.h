#pragma once

#include "framework.h"
#include "SourceCode.h"
using namespace std;

extern HANDLE hStdOutput; //���DOS����̨��������DEBUG
#define WM_SUCCESSLOGIN WM_USER+1011  //�ɹ���¼����Ϣ
#define WM_UPDATETEXTSHOWWINDOW WM_USER+1012 //���������¼����Ϣ
#define BUTTONLOGIN   1 
#define BUTTONTEST   2 
#define BUTTONSENDMESSAGE 3
#define USERLIST 4
#define TOOLBAR 5
#define KAOMOJI 6
#define MAX_NUMBER  101
#define MAX_BUFFER_SIZE 1024
#define MAX_TEST_NUMBER 10
//���еĴ��ھ��
extern HWND hMainWindow, hSubMainWindow, hLoginInput, hLoginButton, hTextInput, hUserList, hSendButton, hToolBar, hTextShowWindow;
extern HWND hTextAlias, hStartServer;

//ע�ᴴ�����еĴ���






