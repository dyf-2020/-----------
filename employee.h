#pragma once
#include<iostream>
using namespace std;
#include"worker.h"


//��ͨԱ����
class Employee :public Worker {
public:
	//��ʾְ��������Ϣ
	virtual void showInfo();
	//��ȡ��λ��Ϣ
	virtual string getDeptName();
	//���캯��
	Employee(int id,string name,int dId);
};