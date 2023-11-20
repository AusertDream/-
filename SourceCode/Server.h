#pragma once
#include "framework.h"
#include "InitWindows.h"
#include "SomeTools.h"
using namespace std;
typedef long long ll;

#define MAX_NUMBER  101

//��ŵ�ǰ�����û�
extern set<string> UserList;
//��ŵ�ǰ�����߳�
extern vector<thread> allThread;
//��ŵ�ǰ����socket����
extern vector<SOCKET> allSocket;
//���߳�ID��һӳ�䵽�û�������
extern map<thread::id, string> ID_UserName;

//������ļ�
// 
//��ʼ������
extern SOCKET InitServer();
//�����շ��ĺ���
extern void SendRecvProc(SOCKET);
 //���ͺ���
extern void OnSend(SOCKET, UserParam);
 //�����¼����
extern void OnLogIn(SOCKET, UserParam);
 //����ǳ�����
extern void OnLogOut(SOCKET, UserParam);

//����������
extern void StartServer();
