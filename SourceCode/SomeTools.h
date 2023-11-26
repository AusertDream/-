#pragma once
#include "framework.h"
using namespace std;
typedef long long ll;



#define NORMAL_MSG  '1'
#define LOGIN_REQUEST  '2'
#define LOGOUT_REQUEST '3'
#define LOGIN_RESULT '4'

template<typename T> //ʹ�ú���ģ���MyRandom����
T MyRandom(T min, T max);

typedef struct UserMessage {
    wstring UserName;
    vector<wstring> Msg;
    CTime timeInfo;
};


//�����û�ʹ��socket���͵����ݰ��ĸ�ʽ
typedef struct UserParam
{
    char Type;
    wstring Sender;
    wstring Receiver;
    wstring Msg;
    bool res;
};


// ���л����������ṹ�����ݸ��Ƶ��ַ������� ����ʹ��socket��������
extern void serialize(const UserParam& data, char* buffer);

// �����л����������ַ�����ת��Ϊ�ṹ������ ������ܵ�������
extern void deserialize(const char* buffer, UserParam& data);


extern void openTheBuff(wstring buffer,UserParam& data);


// stringתwstring
extern wstring StringToWstring(const string& input);

// wstringתstring 
extern string WstringToString(const wstring& input);

/*
��string����ת��Ϊwchar_t*����

1.�Ƚ�stringת��Ϊwstring
2.Ȼ��wstringת��Ϊwchar_t*

string s;
wstring ss(s.begin(),s.end());
wchar_t* res=ss.c_str();
*/

//����Windows�еĺ�ת��wchar��char

/*
USES_CONVERSION;
char* test1 = W2A(L"���ǿ��ֽ�");//ת����Ĭ��
wchar_t* test12 = A2W("����խ�ֽ�");
*/