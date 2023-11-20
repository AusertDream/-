
#include "framework.h"
#include "InitWindows.h"
#include "SomeTools.h"
#include "Server.h"
using namespace std;
typedef long long ll;
#define MAX_NUMBER  101


//��ŵ�ǰ�����û�
set<string> UserList;
//��ŵ�ǰ�����߳�
vector<thread> allThread;
//��ŵ�ǰ����socket����
vector<SOCKET> allSocket;
//���߳�ID��һӳ�䵽�û�������
map<thread::id, string> ID_UserName;




//������ļ�

SOCKET InitServer() {
	allThread.resize(MAX_NUMBER);
	allSocket.resize(MAX_NUMBER);
	//1.ȷ��Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		MessageBox(hMainWindow, "ͨ�Ű汾��2.2", "Error", MB_OK);
		//����汾��Ϣ
		WSACleanup();
	}
	//2.����socket
	//����������ģʽ��TCPЭ�顣AF_INET��ʾʹ�õĴ���Э��ΪTCP,UDP֮���Э�顣
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		char* ErrorMsg = " ";
		//�������ʧ�����������Ϣ
		sprintf(ErrorMsg, "����socketʧ�ܣ�%d\n", GetLastError());
		MessageBox(hMainWindow, ErrorMsg, "Error", MB_OK);
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
	}
	return sSocket;
}





void OnSend(SOCKET cSocket, UserParam receivedData) {
	//�������͵����ݣ�������д��Ϣ
	UserParam SendData;
	SendData.Type = NORMAL_MSG;
	SendData.Msg = receivedData.Msg;
	SendData.Sender = "Server";
	SendData.Receiver = "ALL";
	//���ṹ�����л�Ϊ�ַ����飬Ȼ��ʹ��send���ͳ�ȥ
	char buffer[sizeof(UserParam)];
	serialize(SendData, buffer);
	//���͸����пͻ���
	for (int i = 0; i < MAX_NUMBER; i++) {
		send(allSocket[i], buffer, sizeof buffer, NULL);
	}
}

void OnLogIn(SOCKET cSocket, UserParam receivedData) {
	if (UserList.find(receivedData.Sender) != UserList.end()) {
		UserParam res;
		res.Type = LOGIN_RESULT;
		res.Sender = "Server";
		res.Receiver = "";
		res.res = false;
		char buff[sizeof(res)];
		serialize(res, buff);
		send(cSocket, buff, sizeof buff, NULL);
		return;
	}
	else {
		UserList.insert(receivedData.Sender);
		ID_UserName[this_thread::get_id()] = receivedData.Sender;
		UserParam res;
		res.Type = LOGIN_RESULT;
		res.res = true;
		res.Sender = "Server";
		char buff[sizeof(res)];
		serialize(res, buff);
		send(cSocket, buff, sizeof buff, NULL);
		return;
	}
}

void OnLogOut(SOCKET cSocket, UserParam receivedData) {
	UserList.erase(receivedData.Sender);
	ID_UserName[this_thread::get_id()] = "";
}

void SendRecvProc(SOCKET cSocket) {
	
	int ret = 0;
	//7.ͨ��
	char recvBuff[sizeof(UserParam)];
	while (true) {
		//������Ϣ
		ret = recv(cSocket, recvBuff, sizeof(UserParam), NULL);
		// �����л����յ�������
		UserParam receivedData;
		deserialize(recvBuff, receivedData);
		//��������������������Ϣ����
		switch (receivedData.Type) {
		case NORMAL_MSG:
			OnSend(cSocket, receivedData);
			break;
		case LOGIN_REQUEST:
			OnLogIn(cSocket,receivedData);
			break;
		case LOGOUT_REQUEST:
			OnLogOut(cSocket, receivedData);
			break;
		}
	}
}

void StartServer() {
	//��ʼ��
	SOCKET sSocket = InitServer();
	UserList.insert("ALL");
	UserList.insert("Server");
	//�������̴߳����շ���Ϣ
	for (int i = 0; i < MAX_NUMBER; i++) {
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
		allSocket[i] = cSocket;
		allThread[i] = thread(SendRecvProc, cSocket);
		allThread[i].detach();
	}
	while (true) {

	}
}