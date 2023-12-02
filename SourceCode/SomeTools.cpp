#pragma once
#include "framework.h"
#include "SomeTools.h"
using namespace std;
typedef long long ll;



#define NORMAL_MSG  '1'
#define LOGIN_REQUEST  '2'
#define LOGOUT_REQUEST '3'
#define LOGIN_RESULT '4'

//template<typename T> //ʹ�ú���ģ���MyRandom����
//T MyRandom(T min, T max) { //����C++�ṩ��������������������������
//    random_device seed;//Ӳ���������������
//    ranlux48 engine(seed());//���������������������
//    uniform_int_distribution<> distrib(min, max);//�����������Χ��������ֲ���ʽΪ���ȷֲ�
//    T res = distrib(engine);//�����
//    return res;
//}





//���л��������ѷ���
// ���л����������ṹ�����ݸ��Ƶ��ַ������� ����ʹ��socket��������
void serialize(const UserParam& data, char* buffer) {
    memcpy(buffer, &data, sizeof(UserParam));
}

// �����л����������ַ�����ת��Ϊ�ṹ������ ������ܵ�������
void deserialize(const char* buffer, UserParam& data) {
    memcpy(&data, buffer, sizeof(UserParam));
}


//�������
void openTheBuff(wstring buffer, UserParam& data) {
	int cnt = 0;
	for (int l = 0; l < buffer.size(); l++) {
		int r = l + 1;
		while (r < buffer.size() && buffer[r] != L' ') {
			r++;
		}
		if (cnt == 0) {
			data.Type = (char)buffer[l];//���������ʹ���type
		}
		else if (cnt == 1) {
			data.Sender = buffer.substr(l, r - l);//�������ߴ���sender
		}
		else if (cnt == 2) {
			data.Receiver = buffer.substr(l, r - l);
		}
		else if (cnt == 3) {
			if (data.Type == LOGIN_RESULT) {
				if (buffer.substr(l, r - l) == L"true") {
					data.res = true;
				}
				else {
					data.res = false;
				}
			}
			else {
				data.Msg = buffer.substr(l, r - l);
			}
		}
		cnt++;
		l = r;
	}
}



// stringתwstring
wstring StringToWstring(const string& str)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.from_bytes(str);
}
// wstringתstring 
string WstringToString(const wstring& wstr)
{
	std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
	return converter.to_bytes(wstr);
}



/*
��string����ת��Ϊwchar_t*����

1.�Ƚ�stringת��Ϊwstring
2.Ȼ��wstringת��Ϊwchar_t*

string s;
wstring ss(s.begin(),s.end());
wchar_t* res=ss.c_str();
*/