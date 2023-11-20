#pragma once
#include "framework.h"
using namespace std;
typedef long long ll;



#define NORMAL_MSG  1
#define LOGIN_REQUEST  2
#define LOGOUT_REQUEST 3
#define LOGIN_RESULT 4

template<typename T> //ʹ�ú���ģ���MyRandom����
T MyRandom(T min, T max);

typedef struct UserMessage {
    string UserName;
    vector<string> Msg;
    CTime timeInfo;
};


//�����û�ʹ��socket���͵����ݰ��ĸ�ʽ
typedef struct UserParam
{
    int Type;
    string Sender;
    string Receiver;
    UserMessage Msg;
    bool res;
};


// ���л����������ṹ�����ݸ��Ƶ��ַ������� ����ʹ��socket��������
extern void serialize(const UserParam& data, char* buffer);

// �����л����������ַ�����ת��Ϊ�ṹ������ ������ܵ�������
extern void deserialize(const char* buffer, UserParam& data);

/*
��string����ת��Ϊwchar_t*����

1.�Ƚ�stringת��Ϊwstring
2.Ȼ��wstringת��Ϊwchar_t*

string s;
wstring ss(s.begin(),s.end());
wchar_t* res=ss.c_str();
*/