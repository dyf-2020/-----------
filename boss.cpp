#include"boss.h"


//��ʾְ��������Ϣ
void Boss::showInfo() {
	cout << "ְ����ţ�" << this->m_Id
		<< "\tְ��������" << this->m_Name
		<< "\t���ڲ��ţ�" << getDeptName()
		<< "\t��λְ��" << "����˾��������" << endl;
}
//��ȡ��λ��Ϣ
string Boss::getDeptName() {
	return string("�ϰ�");
}
//���캯��
Boss::Boss(int id, string name, int dId) {
	this->m_Id = id;
	this->m_Name = name;
	this->m_DeptId = dId;
}