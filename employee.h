#pragma once
#include<iostream>
using namespace std;
#include"worker.h"


//普通员工类
class Employee :public Worker {
public:
	//显示职工个人信息
	virtual void showInfo();
	//获取岗位信息
	virtual string getDeptName();
	//构造函数
	Employee(int id,string name,int dId);
};