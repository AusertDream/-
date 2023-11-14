#include<iostream>
#include<random>
using namespace std;
typedef long long ll;

template<typename T> //ʹ�ú���ģ���MyRandom����
T MyRandom(T min, T max) { //����C++�ṩ��������������������������
    random_device seed;//Ӳ���������������
    ranlux48 engine(seed());//���������������������
    uniform_int_distribution<> distrib(min, max);//�����������Χ��������ֲ���ʽΪ���ȷֲ�
    T res = distrib(engine);//�����
    return res;
}


/*
��string����ת��Ϊwchar_t*����

1.�Ƚ�stringת��Ϊwstring
2.Ȼ��wstringת��Ϊwchar_t*

string s;
wstring ss(s.begin(),s.end());
wchar_t* res=ss.c_str();
*/