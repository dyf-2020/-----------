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
    //添加职工
    void Add_Emp();
    //保存文件
    void save();
    //记录职工人数
    int m_EmpNum;
    //职工数组指针
    Worker** m_EmpArray;
    //文件是否为空的标志
    bool m_FileIsEmpty;
    //统计文件中成员函数
    int get_EmpNum();
    //初始化员工
    void init_Emp();
    //显示职工信息
    void show_Emp();
    //删除离职员工
    void del_Emp();
    //查找编号对应员工
    int is_Exist(int id);
    //修改职工信息
    void mod_Emp();
    //查找职工信息
    void find_Emp();
    //按照职工编号排序
    void sort_Emp();
    //清空文件
    void delete_File();
};