#pragma once
#include<iostream>
using namespace std;


//����ְ����
class Worker {
public:
	//��ʾְ��������Ϣ
	virtual void showInfo() = 0;
	//��ȡ��λ��Ϣ
	virtual string getDeptName() = 0;
	//ְ�����
	int m_Id;
	//ְ������
	string m_Name;
	//ְ�����ڲ��ű��
	int m_DeptId;
};