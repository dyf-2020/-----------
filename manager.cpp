#include"manager.h"


//显示职工个人信息
void Manager::showInfo() {
	cout << "职工编号：" << this->m_Id
		<< "\t职工姓名：" << this->m_Name
		<< "\t所在部门：" << getDeptName()
		<< "\t岗位职责：" << "完成老板交给的任务，并分配给普通员工" << endl;
}
//获取岗位信息
string Manager::getDeptName() {
	return string("经理");
}
//构造函数
Manager::Manager(int id, string name, int dId) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}