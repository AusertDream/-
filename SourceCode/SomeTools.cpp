#pragma once
#include "framework.h"
#include "SomeTools.h"
using namespace std;
typedef long long ll;



#define NORMAL_MSG  1
#define LOGIN_REQUEST  2
#define LOGOUT_REQUEST 3
#define LOGIN_RESULT 4

template<typename T> //ʹ�ú���ģ���MyRandom����
T MyRandom(T min, T max) { //����C++�ṩ��������������������������
    random_device seed;//Ӳ���������������
    ranlux48 engine(seed());//���������������������
    uniform_int_distribution<> distrib(min, max);//�����������Χ��������ֲ���ʽΪ���ȷֲ�
    T res = distrib(engine);//�����
    return res;
}






// ���л����������ṹ�����ݸ��Ƶ��ַ������� ����ʹ��socket��������
void serialize(const UserParam& data, char* buffer) {
    memcpy(buffer, &data, sizeof(UserParam));
}

// �����л����������ַ�����ת��Ϊ�ṹ������ ������ܵ�������
void deserialize(const char* buffer, UserParam& data) {
    memcpy(&data, buffer, sizeof(UserParam));
}

/*
��string����ת��Ϊwchar_t*����

1.�Ƚ�stringת��Ϊwstring
2.Ȼ��wstringת��Ϊwchar_t*

string s;
wstring ss(s.begin(),s.end());
wchar_t* res=ss.c_str();
*/