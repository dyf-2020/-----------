#include"workermanager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.�ļ�Ϊ��
	if (!ifs.is_open()) {
		cout << "�ļ���ʧ��" << endl;
		//��ʼ������
		this->m_FileIsEmpty = true;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		ifs.close();
		return;
	}
	//2.�ļ����ڣ�������Ϊ��
	char c;
	ifs >> c;
	if (ifs.eof()) {
		cout << "�ļ����ڣ�����Ϊ��" << endl;
		//��ʼ������
		this->m_FileIsEmpty = true;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		ifs.close();
		return;
	}
	//3.�ļ����ڣ����Ҽ�¼���� 
	int num = this->get_EmpNum();
	cout << "����ְ������Ϊ" << num << endl;
	this->m_EmpNum = num;
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ������ݴ洢��������
	this->init_Emp();
	//�ļ��Ƿ�Ϊ�յı�־
	this->m_FileIsEmpty = false;
}

WorkerManager::~WorkerManager() {
	if (this->m_EmpArray != nullptr) {
		for (int i = 0; i < this->m_EmpNum; i++) {
			delete this->m_EmpArray[i];
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = nullptr;
		this->m_EmpNum = 0;
	}

}

void WorkerManager::Show_Menu() {
	cout << "******��ӭʹ��ְ������ϵͳ*******" << endl;
	cout << "*******0.�˳�����ϵͳ************" << endl;
	cout << "*******1.����ְ����Ϣ************" << endl;
	cout << "*******2.��ʾְ����Ϣ************" << endl;
	cout << "*******3.ɾ����ְְ��************" << endl;
	cout << "*******4.�޸�ְ����Ϣ************" << endl;
	cout << "*******5.����ְ����Ϣ************" << endl;
	cout << "*******6.���ձ������************" << endl;
	cout << "*******7.��������ĵ�************" << endl;
	cout << "********************************" << endl;
}

void WorkerManager::ExitSystem() {
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}

//���ְ��
void WorkerManager::Add_Emp() {
	cout << "���������ְ��������" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		//���
		//�����¿ռ��С
		int newSize = this->m_EmpNum + addNum;  //�¿ռ�=��������+��������
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		//���ԭ���ռ䲻Ϊ�գ�ת������
		if (this->m_EmpArray != nullptr) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//���������
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dId;
			do {
				cout << "������ԭ�����в����ڵ�Ա����ţ�" << endl;
				cin >> id;
			} while (this->is_Exist(id) != -1);


			cout << "������Ա��������" << endl;
			cin >> name;
			cout << "������Ա�����ţ�" << endl;
			cout << "1.��ͨԱ��" << endl;
			cout << "2.����" << endl;
			cout << "3.�ϰ�" << endl;
			cin >> dId;
			Worker* worker = nullptr;
			switch (dId)
			{
			case 1:
				worker = new Employee(id, name, dId);
				break;
			case 2:
				worker = new Manager(id, name, dId);
				break;
			case 3:
				worker = new Boss(id, name, dId);
				break;
			default:
				break;
			}
			newSpace[i + this->m_EmpNum] = worker;
		}
		delete[]this->m_EmpArray;
		this->m_EmpArray = newSpace;
		//�µ�ְ������
		this->m_EmpNum = newSize;
		//�ļ���Ϊ�յı�־
		this->m_FileIsEmpty = false;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ��" << endl;
		//���浽�ļ���
		this->save();

	}
	else {
		cout << "������������" << endl;
	}
	//�������������ص��ϼ�Ŀ¼
	system("pause");
	system("cls");
}


//�����ļ�
void  WorkerManager::save() {
	ofstream ofs;
	ofs.open(FILENAME, ios::out);
	for (int i = 0; i < this->m_EmpNum; i++) {
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	ofs.close();
}

//ͳ���ļ��г�Ա����
int WorkerManager::get_EmpNum() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		num++;
	}
	return num;
}

//��ʼ��Ա��
void WorkerManager::init_Emp() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId) {
		Worker* worker = nullptr;
		if (dId == 1) {
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) {
			worker = new Manager(id, name, dId);
		}
		else {
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
}


//��ʾְ����Ϣ
void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty == true) {
		cout << "�ļ�Ϊ�ջ򲻴���" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//ɾ����ְԱ��
void WorkerManager::del_Emp() {
	if (this->m_FileIsEmpty == true) {
		cout << "�ļ�Ϊ�ջ򲻴��ڣ�ɾ��ʧ��" << endl;
		return;
	}
	cout << "������ְԱ����ţ�" << endl;
	int id;
	cin >> id;
	int index = this->is_Exist(id);
	if (index == -1) {
		cout << "ɾ��ʧ��δ�ҵ���ְ��" << endl;
	}
	else {  //ɾ��ְ������ǰ��
		for (int i = index; i < this->m_EmpNum - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "ɾ���ɹ�" << endl;
	}

}

//���ұ�Ŷ�ӦԱ��
int WorkerManager::is_Exist(int id) {
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++) {
		if (this->m_EmpArray[i]->m_Id == id) {
			index = i;
			break;
		}
	}
	return index;
}


//�޸�ְ����Ϣ
void WorkerManager::mod_Emp() {
	if (this->m_FileIsEmpty == true) {
		cout << "�ļ������ڻ�û������" << endl;
		return;
	}
	cout << "������Ҫ�޸�ְ���ı�ţ�" << endl;
	int id;
	cin >> id;
	int index = this->is_Exist(id);
	if (index == -1) {
		cout << "���޴���" << endl;
	}
	else {
		delete this->m_EmpArray[index];
		cout << "���ҵ�" << id << "��ŵ�ְ��" << endl;
		int newId;
		string newName;
		int newDId;
		cout << "������ְ���ı�ţ�" << endl;
		cin >> newId;
		cout << "������ְ�������֣�" << endl;
		cin >> newName;
		cout << "������ְ���Ĳ��ű�ţ�" << endl;
		cout << "1.��ְͨ��" << endl;
		cout << "2.����" << endl;
		cout << "3.�ϰ�" << endl;
		cin >> newDId;
		Worker* worker = nullptr;
		if (newDId == 1) {
			worker = new Employee(newId, newName, newDId);
		}
		else if (newDId == 2) {
			worker = new Manager(newId, newName, newDId);
		}
		else {
			worker = new Boss(newId, newName, newDId);
		}
		this->m_EmpArray[index] = worker;
		cout << "�޸ĳɹ�" << endl;
		this->save();
	}
	system("pause");
	system("cls");
	return;
}


//����ְ����Ϣ
void WorkerManager::find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ������ڻ���Ϊ��" << endl;
	}
	else {
		cout << "��������ҵķ�ʽ��" << endl;
		cout << "1.����Ų���" << endl;
		cout << "2.����������" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			//����Ų���
			int id;
			cout << "������ҵı��" << endl;
			cin >> id;
			int index = this->is_Exist(id);
			if (index == -1) {
				cout << "���޴���" << endl;
			}
			else {
				cout << "�鵽�ˣ����������Ϣ��" << endl;
				this->m_EmpArray[index]->showInfo();
			}
		}
		else if (select == 2) {
			//����������
			string name;
			cout << "������ҵ�����" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "���޴���" << endl;
			}
		}
		else {
			cout << "�������" << endl;
		}
		system("pause");
		system("cls");
	}
}

//����ְ���������
void WorkerManager::sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "�ļ�Ϊ�ջ��߲�����" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "ѡ������ʽ��" << endl;
		cout << "1.����" << endl;
		cout << "2.����" << endl;
		int select;
		cin >> select;
		if (select != 1 && select != 2) {
			cout << "��������ʽ����Ϊ1��2" << endl;
		}
		else {
			Worker* maxOrMin = this->m_EmpArray[0];
			for (int i = 0; i < this->m_EmpNum; i++) {
				for (int j = i; j < this->m_EmpNum; j++) {
					//��С����
					if (select == 1) {
						if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id) {
							maxOrMin = this->m_EmpArray[j];
							this->m_EmpArray[j] = this->m_EmpArray[i];
							this->m_EmpArray[i] = maxOrMin;
						}
					}
					//�Ӵ�С
					else {
						if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id) {
							maxOrMin = this->m_EmpArray[j];
							this->m_EmpArray[j] = this->m_EmpArray[i];
							this->m_EmpArray[i] = maxOrMin;
						}
					}
				}
			}
			cout << "����ɹ��������Ľ��Ϊ��" << endl;
			this->save();
			this->show_Emp();
		}
		return;
	}
}

//����ļ�
void WorkerManager::delete_File() {
	cout << "��ȷ��Ҫɾ���ļ��� Y/N" << endl;
	char c;
	cin >> c;
	if (c == 'Y') {
		ofstream ofs;
		ofs.open(FILENAME, ios::trunc);
		ofs.close();
		if (this->m_EmpArray != nullptr) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				delete this->m_EmpArray[i];
			}
			delete[]this->m_EmpArray;
			this->m_EmpArray = nullptr;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "ɾ���ļ��ɹ�" << endl;
	}
	system("pause");
	system("cls");
	return;
}