#pragma once //防止头文件重复包含
#include<iostream> //包含输入输出流头文件
#include<string>
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std; //使用标准命名空间
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


//管理者类
class workerManager
{
public:
	//构造函数
	workerManager();
	//析构函数
	~workerManager();
	//展示菜单
	void Show_Menu();
	//退出系统
	void ExitSystem();
	//添加职工
	void Add_Emp();
	//显示职工
	void Show_Emp();
	//保存文件
	void save();
	//统计文件中的人数
	int get_EmpNum();
	//初始化员工
	void init_Emp();
	//判断职工是否存在
	int IsExist(int id);
	//删除职工
	void Del_Emp();
	//修改职工
	void Mod_Emp();
	//查找职工
	void Find_Emp();
	//排序
	void Sort_Emp();
	//清空文件
	void Clean_File();

	//记录职工人数
	int m_EmpNum;
	//职工数组的指针
	Worker** m_EmpArray;
	//判断文件是否为空的标志
	bool m_FileIsEmpty;
};
