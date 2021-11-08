#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

//这是经理类
class Manager :public Worker {
public:
	//显示职工个人信息
	virtual void showInfo();
	//获取岗位信息
	virtual string getDeptName();
	//构造函数
	Manager(int id,string name,int dId);
};