#include"workermanager.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


WorkerManager::WorkerManager() {
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	//1.文件为空
	if (!ifs.is_open()) {
		cout << "文件打开失败" << endl;
		//初始化属性
		this->m_FileIsEmpty = true;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		ifs.close();
		return;
	}
	//2.文件存在，但数据为空
	char c;
	ifs >> c;
	if (ifs.eof()) {
		cout << "文件存在，数据为空" << endl;
		//初始化属性
		this->m_FileIsEmpty = true;
		this->m_EmpNum = 0;
		this->m_EmpArray = nullptr;
		ifs.close();
		return;
	}
	//3.文件存在，并且记录数据 
	int num = this->get_EmpNum();
	cout << "现有职工人数为" << num << endl;
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中数据存储到数组中
	this->init_Emp();
	//文件是否为空的标志
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
	cout << "******欢迎使用职工管理系统*******" << endl;
	cout << "*******0.退出管理系统************" << endl;
	cout << "*******1.增加职工信息************" << endl;
	cout << "*******2.显示职工信息************" << endl;
	cout << "*******3.删除离职职工************" << endl;
	cout << "*******4.修改职工信息************" << endl;
	cout << "*******5.查找职工信息************" << endl;
	cout << "*******6.按照编号排序************" << endl;
	cout << "*******7.清空所有文档************" << endl;
	cout << "********************************" << endl;
}

void WorkerManager::ExitSystem() {
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}

//添加职工
void WorkerManager::Add_Emp() {
	cout << "请输入添加职工数量：" << endl;
	int addNum = 0;
	cin >> addNum;
	if (addNum > 0) {
		//添加
		//计算新空间大小
		int newSize = this->m_EmpNum + addNum;  //新空间=已有人数+新增人数
		//创建新空间
		Worker** newSpace = new Worker * [newSize];
		//如果原来空间不为空，转移数据
		if (this->m_EmpArray != nullptr) {
			for (int i = 0; i < this->m_EmpNum; i++) {
				newSpace[i] = this->m_EmpArray[i];
			}
		}
		//添加新数据
		for (int i = 0; i < addNum; i++) {
			int id;
			string name;
			int dId;
			do {
				cout << "请输入原数据中不存在的员工编号：" << endl;
				cin >> id;
			} while (this->is_Exist(id) != -1);


			cout << "请输入员工姓名：" << endl;
			cin >> name;
			cout << "请输入员工部门：" << endl;
			cout << "1.普通员工" << endl;
			cout << "2.经理" << endl;
			cout << "3.老板" << endl;
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
		//新的职工人数
		this->m_EmpNum = newSize;
		//文件不为空的标志
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工" << endl;
		//保存到文件中
		this->save();

	}
	else {
		cout << "输入数据有误" << endl;
	}
	//按任意键清屏后回到上级目录
	system("pause");
	system("cls");
}


//保存文件
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

//统计文件中成员函数
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

//初始化员工
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


//显示职工信息
void WorkerManager::show_Emp() {
	if (this->m_FileIsEmpty == true) {
		cout << "文件为空或不存在" << endl;
	}
	else {
		for (int i = 0; i < this->m_EmpNum; i++) {
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}

//删除离职员工
void WorkerManager::del_Emp() {
	if (this->m_FileIsEmpty == true) {
		cout << "文件为空或不存在，删除失败" << endl;
		return;
	}
	cout << "输入离职员工编号：" << endl;
	int id;
	cin >> id;
	int index = this->is_Exist(id);
	if (index == -1) {
		cout << "删除失败未找到该职工" << endl;
	}
	else {  //删除职工数组前移
		for (int i = index; i < this->m_EmpNum - 1; i++) {
			this->m_EmpArray[i] = this->m_EmpArray[i + 1];
		}
		this->m_EmpNum--;
		this->save();
		cout << "删除成功" << endl;
	}

}

//查找编号对应员工
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


//修改职工信息
void WorkerManager::mod_Emp() {
	if (this->m_FileIsEmpty == true) {
		cout << "文件不存在或没有数据" << endl;
		return;
	}
	cout << "请输入要修改职工的编号：" << endl;
	int id;
	cin >> id;
	int index = this->is_Exist(id);
	if (index == -1) {
		cout << "查无此人" << endl;
	}
	else {
		delete this->m_EmpArray[index];
		cout << "查找到" << id << "编号的职工" << endl;
		int newId;
		string newName;
		int newDId;
		cout << "输入新职工的编号：" << endl;
		cin >> newId;
		cout << "输入新职工的名字：" << endl;
		cin >> newName;
		cout << "输入新职工的部门编号：" << endl;
		cout << "1.普通职工" << endl;
		cout << "2.经理" << endl;
		cout << "3.老板" << endl;
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
		cout << "修改成功" << endl;
		this->save();
	}
	system("pause");
	system("cls");
	return;
}


//查找职工信息
void WorkerManager::find_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件不存在或者为空" << endl;
	}
	else {
		cout << "请输入查找的方式：" << endl;
		cout << "1.按编号查找" << endl;
		cout << "2.按姓名查找" << endl;
		int select;
		cin >> select;
		if (select == 1) {
			//按编号查找
			int id;
			cout << "输入查找的编号" << endl;
			cin >> id;
			int index = this->is_Exist(id);
			if (index == -1) {
				cout << "查无此人" << endl;
			}
			else {
				cout << "查到了，输出此人信息：" << endl;
				this->m_EmpArray[index]->showInfo();
			}
		}
		else if (select == 2) {
			//按姓名查找
			string name;
			cout << "输入查找的姓名" << endl;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++) {
				if (this->m_EmpArray[i]->m_Name == name) {
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (flag == false) {
				cout << "查无此人" << endl;
			}
		}
		else {
			cout << "输入错误" << endl;
		}
		system("pause");
		system("cls");
	}
}

//按照职工编号排序
void WorkerManager::sort_Emp() {
	if (this->m_FileIsEmpty) {
		cout << "文件为空或者不存在" << endl;
		system("pause");
		system("cls");
	}
	else {
		cout << "选择排序方式：" << endl;
		cout << "1.升序" << endl;
		cout << "2.降序" << endl;
		int select;
		cin >> select;
		if (select != 1 && select != 2) {
			cout << "输入排序方式必须为1或2" << endl;
		}
		else {
			Worker* maxOrMin = this->m_EmpArray[0];
			for (int i = 0; i < this->m_EmpNum; i++) {
				for (int j = i; j < this->m_EmpNum; j++) {
					//从小到大
					if (select == 1) {
						if (this->m_EmpArray[i]->m_Id > this->m_EmpArray[j]->m_Id) {
							maxOrMin = this->m_EmpArray[j];
							this->m_EmpArray[j] = this->m_EmpArray[i];
							this->m_EmpArray[i] = maxOrMin;
						}
					}
					//从大到小
					else {
						if (this->m_EmpArray[i]->m_Id < this->m_EmpArray[j]->m_Id) {
							maxOrMin = this->m_EmpArray[j];
							this->m_EmpArray[j] = this->m_EmpArray[i];
							this->m_EmpArray[i] = maxOrMin;
						}
					}
				}
			}
			cout << "排序成功，排序后的结果为：" << endl;
			this->save();
			this->show_Emp();
		}
		return;
	}
}

//清空文件
void WorkerManager::delete_File() {
	cout << "你确定要删除文件吗？ Y/N" << endl;
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
		cout << "删除文件成功" << endl;
	}
	system("pause");
	system("cls");
	return;
}