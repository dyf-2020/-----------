#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//���Ǿ�����
class Manager :public Worker {
public:
	//��ʾְ��������Ϣ
	virtual void showInfo();
	//��ȡ��λ��Ϣ
	virtual string getDeptName();
	//���캯��
	Manager(int id,string name,int dId);
};