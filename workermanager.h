#pragma once
#include<iostream>
using namespace std;
#include"worker.h"

#include<fstream>
#define FILENAME "empFile.txt"



class WorkerManager {
public:
    WorkerManager();
    ~WorkerManager();
    void Show_Menu();
    void ExitSystem();
    //���ְ��
    void Add_Emp();
    //�����ļ�
    void save();
    //��¼ְ������
    int m_EmpNum;
    //ְ������ָ��
    Worker** m_EmpArray;
    //�ļ��Ƿ�Ϊ�յı�־
    bool m_FileIsEmpty;
    //ͳ���ļ��г�Ա����
    int get_EmpNum();
    //��ʼ��Ա��
    void init_Emp();
    //��ʾְ����Ϣ
    void show_Emp();
    //ɾ����ְԱ��
    void del_Emp();
    //���ұ�Ŷ�ӦԱ��
    int is_Exist(int id);
    //�޸�ְ����Ϣ
    void mod_Emp();
    //����ְ����Ϣ
    void find_Emp();
    //����ְ���������
    void sort_Emp();
    //����ļ�
    void delete_File();
};