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
        cout << "����������ѡ��" << endl;
        cin >> choice;
        switch (choice)
        {
        case 0: //�˳�����ϵͳ
            wm.ExitSystem();
            break;
        case 1: //����ְ����Ϣ
            wm.Add_Emp();
            break;
        case 2: //��ʾְ����Ϣ
            wm.show_Emp();
            break;
        case 3: //ɾ����ְְ��
            wm.del_Emp();
            break;
        case 4: //�޸�ְ����Ϣ
            wm.mod_Emp();
            break;
        case 5: //����ְ����Ϣ
            wm.find_Emp();
            break;
        case 6: //���ձ������
            wm.sort_Emp();
            break;
        case 7: //��������ĵ�
            wm.delete_File();
            break;
        default:
            system("cls");
            break;
        }
    }
    return 0;
}