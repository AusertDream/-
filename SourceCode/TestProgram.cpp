#pragma once
#include "framework.h"
#include "SomeTools.h"
#include "TestProgram.h"
using namespace std;
//���ڽ��ж��û��Ĳ����ļ�


//ִ�в��Բ���
void Test() {
	//1.ȷ��Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		MessageBox(NULL, "ͨ�Ű汾��2.2", "Error", MB_OK);
		//����汾��Ϣ
		WSACleanup();
		return;
	}
	//2.����socket
	//����������ģʽ��TCPЭ�顣AF_INET��ʾʹ�õĴ���Э��ΪTCP,UDP֮���Э�顣
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		char* ErrorMsg = " ";
		//�������ʧ�����������Ϣ
		sprintf(ErrorMsg, "����socketʧ�ܣ�%d\n", GetLastError());
		MessageBox(NULL, ErrorMsg, "Error", MB_OK);
		return;
	}
	//3.ȷ����������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //ʹ�õ���ʲôЭ���봴��SOCKETʱ��д���뱣��һ��
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //��������ip��ַ
	addr.sin_port = htons(10086); //�������ṩ����Ķ˿ں�

	//4. ���ӷ�����
	int r = connect(sSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1) {
		char* ErrorMsg = " ";
		//�������ʧ�����������Ϣ
		sprintf(ErrorMsg, "����ʧ�ܣ�%d\n", GetLastError());
		closesocket(sSocket); //�Ͽ�����
		WSACleanup(); //����Э��汾��Ϣ
		MessageBox(NULL, ErrorMsg, "Error", MB_OK);
		return;
	}

	//5.ͨ��
	string buff = "114514";
	while (true) {
		send(sSocket, buff.c_str(), buff.size(), NULL);
	}
}

static void StartTestProgram(int MaxUserNumber) {
	vector<thread> AllTestUsers(MaxUserNumber);
	for (int i = 0; i < MaxUserNumber; i++) {
		AllTestUsers[i] = thread(Test);
		AllTestUsers[i].detach();
	}
}
