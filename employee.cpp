#include"employee.h"


//��ʾְ��������Ϣ
void Employee::showInfo() {
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t���ڲ��ţ�" << getDeptName()
		<< "\t��λְ��" << "��ɾ�����������" << endl;
}
//��ȡ��λ��Ϣ
string Employee::getDeptName() {
	return string("Ա��");
}
//���캯��
Employee::Employee(int id, string name, int dId) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}