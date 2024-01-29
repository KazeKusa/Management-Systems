#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
using namespace std;
#include"workerManager.h"
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"

int main()
{
	//实例化管理对象
	workerManager wm;
	int choice = 0; //用来储存用户的选项
	while (true)
	{
		//调用展示菜单的成员函数
		wm.Show_Menu();
		cout << "请输入您的选择：" << endl;;
		cin >> choice; //接受用户的选项
		switch (choice)
		{
		case 0: //退出系统
			wm.ExitSystem();
			break;
		case 1: //增加职工
			wm.Add_Emp();
			break;
		case 2: //显示职工
			wm.Show_Emp();
			break;
		case 3: //删除职工
			wm.Del_Emp();
			break;
		case 4: //修改职工
			wm.Mod_Emp();
			break;
		case 5: //查找职工
			wm.Find_Emp();
			break;
		case 6: //排序职工
			wm.Sort_Emp();
			break;
		case 7: //清空文档
			wm.Clean_File();
			break;
		default:
			system("cls"); //清屏
			break;
		}
	}
	system("pause");
	return 0;
}