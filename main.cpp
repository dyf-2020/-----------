#include <iostream>
using namespace std;
#include "workermanager.h"
#include"employee.h"
#include"worker.h"
#include"boss.h"
#include"manager.h"


int main()
{
    WorkerManager wm;
    int choice = 0;
    while (true)
    {
        wm.Show_Menu();
        cout << "请输入您的选择：" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0: //退出管理系统
            wm.ExitSystem();
            break;
        case 1: //增加职工信息
            wm.Add_Emp();
            break;
        case 2: //显示职工信息
            wm.show_Emp();
            break;
        case 3: //删除离职职工
            wm.del_Emp();
            break;
        case 4: //修改职工信息
            wm.mod_Emp();
            break;
        case 5: //查找职工信息
            wm.find_Emp();
            break;
        case 6: //按照编号排序
            wm.sort_Emp();
            break;
        case 7: //清空所有文档
            wm.delete_File();
            break;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}