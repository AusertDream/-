#pragma once
#include "framework.h"
#include "SomeTools.h"
#include "TestProgram.h"
using namespace std;
//���ڽ��ж��û��Ĳ����ļ�
#define MAX_BUFFER_SIZE 1024
mutex ProtectLogOutUserNumber;//���ڱ���LogOutUserNumber�Ļ�����
int LogOutUserNumber = 0;//�˳����û�����

//ִ�в��Բ���
void User() {
	//2.����socket
	//����������ģʽ��TCPЭ�顣AF_INET��ʾʹ�õĴ���Э��ΪTCP,UDP֮���Э�顣
	SOCKET sSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (SOCKET_ERROR == sSocket) {
		//�������ʧ��ֱ���˳�
		ProtectLogOutUserNumber.lock();
		LogOutUserNumber++;
		ProtectLogOutUserNumber.unlock();
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
		//�������ʧ��ֱ���˳�
		closesocket(sSocket); //�Ͽ�����
		ProtectLogOutUserNumber.lock();
		LogOutUserNumber++;
		ProtectLogOutUserNumber.unlock();
		return;
	}
	//��������û���
	string UserName;
	int UserNameLength = MyRandom(1, 10);
	UserName.resize(UserNameLength);
	for (int i = 0; i < UserNameLength; i++) {
		UserName[i] = MyRandom('a', 'z');
	}
	//���Ե�¼
	string LoginBuffer;
	LoginBuffer.push_back(LOGIN_REQUEST);
	LoginBuffer.push_back(' ');
	LoginBuffer.append(UserName);
	LoginBuffer.push_back(' ');
	LoginBuffer.append("Server");
	LoginBuffer.push_back(' ');
	LoginBuffer.append("loginrequest");
	LoginBuffer.push_back(' ');
	LoginBuffer.push_back('\0');
	//���͵�¼����
	send(sSocket,LoginBuffer.c_str(), LoginBuffer.size(), 0);
	//���յ�¼���
	char LoginResultBuffer[MAX_BUFFER_SIZE];
	recv(sSocket, LoginResultBuffer, MAX_BUFFER_SIZE, 0);
	USES_CONVERSION;
	wstring wLoginResultBuffer = A2W(LoginResultBuffer);
	UserParam LoginResult;
	//���
	openTheBuff(wLoginResultBuffer, LoginResult);
	if (LoginResult.res == false) {
		//��¼ʧ�ܣ�ֱ���˳�����
		closesocket(sSocket); //�Ͽ�����
		ProtectLogOutUserNumber.lock();
		LogOutUserNumber++;
		ProtectLogOutUserNumber.unlock();
		return;
	}
	else {
		//��¼�ɹ�����ʼ����
		//���Խ���������������ҷ�����Ϣ��ͬʱ��֧��˽�ŵĻ�Ӧ��
		while (true) {
			//ÿ�ο�ʼǰ����һ���ж����Ƿ�Ҫ�˳�������
			if (MyRandom(1, 100) <= 10) {
				break;
			}
			//���ѡ��һ����Ϣ�����ߣ����������ҵ�ѡ��԰뿪����
			string MsgReceiver;
			if (MyRandom(1, 100) <= 50) {
				MsgReceiver = "GLOBAL";
			}
			else {
				MsgReceiver = "CN";
			}
			//����һ����Ϣ��ĸ��Ȼ�������ĸ����������Ϣ
			vector<char> alphabet;
			for (int i = 0; i < 26; i++) {
				alphabet.push_back(char('a' + i));
			}
			for (int i = 0; i < 26; i++) {
				alphabet.push_back(char('A' + i));
			}
			for (int i = 0; i < 10; i++) {
				alphabet.push_back(char('0' + i));
			}
			string MsgContent;
			int MsgContentLen = MyRandom(1, 25);
			MsgContent.resize(MsgContentLen);
			for (int i = 0; i < MsgContentLen; i++) {
				int idx = MyRandom(0, (int)alphabet.size() - 1);
				MsgContent[i] = alphabet[idx];
			}
			string sendMsgBuffer;
			sendMsgBuffer.push_back(NORMAL_MSG);
			sendMsgBuffer.push_back(' ');
			sendMsgBuffer.append(UserName);
			sendMsgBuffer.push_back(' ');
			sendMsgBuffer.append(MsgReceiver);
			sendMsgBuffer.push_back(' ');
			sendMsgBuffer.append(MsgContent);
			sendMsgBuffer.push_back(' ');
			sendMsgBuffer.push_back('\0');
			send(sSocket, sendMsgBuffer.c_str(), sendMsgBuffer.size(), 0);
			//sleepһ�������ʱ��
			Sleep(MyRandom(800, 5000));
		}
		//���͵ǳ�����
		string LogoutBuffer;
		LogoutBuffer.push_back(LOGOUT_REQUEST);
		LogoutBuffer.push_back(' ');
		LogoutBuffer.append(UserName);
		LogoutBuffer.push_back(' ');
		LogoutBuffer.append("Server");
		LogoutBuffer.push_back(' ');
		LogoutBuffer.append("logoutrequest");
		LogoutBuffer.push_back(' ');
		LogoutBuffer.push_back('\0');
		send(sSocket, LogoutBuffer.c_str(), LogoutBuffer.size(), 0);
		closesocket(sSocket); //�Ͽ�����
		ProtectLogOutUserNumber.lock();
		LogOutUserNumber++;
		ProtectLogOutUserNumber.unlock();
	}
}

void StartTestProgram(int MaxUserNumber) {
	//1.ȷ��Э��汾
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (LOBYTE(wsaData.wVersion) != 2 || HIBYTE(wsaData.wVersion) != 2) {
		MessageBox(NULL, "ͨ�Ű汾��2.2", "Error", MB_OK);
		//����汾��Ϣ
		WSACleanup();
		return;
	}
	vector<thread> UserThreads(MaxUserNumber);
	for (int i = 0; i < MaxUserNumber; i++) {
		UserThreads[i] = thread(User);
		UserThreads[i].detach();
	}
	//�ȴ������û��˳�
	while (true) {
		ProtectLogOutUserNumber.lock();
		if (LogOutUserNumber == MaxUserNumber) {
			ProtectLogOutUserNumber.unlock();
			break;
		}
		else {
			ProtectLogOutUserNumber.unlock();
			Sleep(1000);
		}
	}
	WSACleanup();
	return;
}
