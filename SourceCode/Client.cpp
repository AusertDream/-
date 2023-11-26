#pragma once
#include "framework.h"
#include "InitWindows.h"
#include "Client.h"
using namespace std;
typedef long long ll;


//�ͻ����ļ�



extern void StartClient() {
	//1.ȷ��Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		MessageBox(hMainWindow, "ͨ�Ű汾��2.2", "Error", MB_OK);
		//����汾��Ϣ
		WSACleanup();
		return;
	}
	//2.����socket
	//����������ģʽ��TCPЭ�顣AF_INET��ʾʹ�õĴ���Э��ΪTCP,UDP֮���Э�顣
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		//�������ʧ�����������Ϣ

		MessageBox(hMainWindow, "����socketʧ��", "Error", MB_OK);
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
		//�������ʧ�����������Ϣ
		closesocket(sSocket); //�Ͽ�����
		WSACleanup(); //����Э��汾��Ϣ
		MessageBox(hMainWindow, "����ʧ��", "Error", MB_OK);
		return;
	}

	//5.ͨ��
	string buff = "114514";
	while(true) {
		send(sSocket, buff.c_str(), buff.size(), NULL);
	}
}