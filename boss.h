#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//�����ϰ���
class Boss :public Worker {
public:
	//��ʾְ��������Ϣ
	virtual void showInfo();
	//��ȡ��λ��Ϣ
	virtual string getDeptName();
	//���캯��
	Boss(int id, string name, int dId);
};