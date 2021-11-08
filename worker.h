#pragma once
#include<iostream>
using namespace std;


//创建职工类
class Worker {
public:
	//显示职工个人信息
	virtual void showInfo() = 0;
	//获取岗位信息
	virtual string getDeptName() = 0;
	//职工编号
	int m_Id;
	//职工姓名
	string m_Name;
	//职工所在部门编号
	int m_DeptId;
};