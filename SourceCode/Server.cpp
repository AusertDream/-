#include "framework.h"
#include "InitWindows.h"
using namespace std;
typedef long long ll;
//������ļ�






static void StartServer() {

	//1.ȷ��Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2||HIBYTE(wsaData.wVersion)!=2) {
		MessageBox(hMainWindow, "ͨ�Ű汾��2.2", "Error", MB_OK);
		//����汾��Ϣ
		WSACleanup();
		return;
	}
	//2.����socket
	//����������ģʽ��TCPЭ�顣AF_INET��ʾʹ�õĴ���Э��ΪTCP,UDP֮���Э�顣
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		char* ErrorMsg=" ";
		//�������ʧ�����������Ϣ
		sprintf(ErrorMsg, "����socketʧ�ܣ�%d\n", GetLastError());
		MessageBox(hMainWindow, ErrorMsg, "Error", MB_OK);
		return;
	}
	//3.ȷ����������Э���ַ��
	SOCKADDR_IN addr = { 0 };
	addr.sin_family = AF_INET; //ʹ�õ���ʲôЭ���봴��SOCKETʱ��д���뱣��һ��
	addr.sin_addr.S_un.S_addr = inet_addr("127.0.0.1"); //��������ip��ַ
	addr.sin_port = htons(10086); //�������ṩ����Ķ˿ں�

	//4. ��
	int r = bind(sSocket, (sockaddr*)&addr, sizeof addr);
	if (r == -1) {
		char* ErrorMsg = " ";
		//�����ʧ�����������Ϣ
		sprintf(ErrorMsg, "��ʧ�ܣ�%d\n", GetLastError());
		closesocket(sSocket); //�Ͽ�����
		WSACleanup(); //����Э��汾��Ϣ
		MessageBox(hMainWindow, ErrorMsg, "Error", MB_OK);
		return;
	}

	//5.����
	r = listen(sSocket, 10);
	if (r == -1) {
		char* ErrorMsg = " ";
		//�������ʧ�����������Ϣ
		sprintf(ErrorMsg, "����ʧ�ܣ�%d\n", GetLastError());
		closesocket(sSocket); //�Ͽ�����
		WSACleanup(); //����Э��汾��Ϣ
		MessageBox(hMainWindow, ErrorMsg, "Error", MB_OK);
		return;
	}

	//6.�ȴ��ͻ�������
	SOCKET cSocket = accept(sSocket, NULL, NULL);
	if (cSocket == SOCKET_ERROR) {
		char* ErrorMsg = " ";
		//����ȴ�ʧ��˵���������������������Ϣ
		sprintf(ErrorMsg, "������������%d\n", GetLastError());
		closesocket(sSocket); //�Ͽ�����
		WSACleanup(); //����Э��汾��Ϣ
		MessageBox(hMainWindow, ErrorMsg, "Error", MB_OK);
		return;
	}

	//7.ͨ��
	char buff[256] = { 0 };
	while (true) {
		r = recv(cSocket, buff, 255, NULL);
		if (r > 0) {
			buff[r] = 0;
			WriteConsole(hStdOutput, buff, strlen(buff), NULL, NULL);
		}
	}

	while (true) {

	}
}