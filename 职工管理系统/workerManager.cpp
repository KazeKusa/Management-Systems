#define _CRT_SECURE_NO_WARNINGS 1
#include"workerManager.h"



//构造函数
workerManager::workerManager()
{
	//文件不存在
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //读文件
	//文件不存在的情况
	if (!ifs.is_open())
	{
		//初始化属性
		//初始化记录人数
		this->m_EmpNum = 0;
		//初始化数组指针
		this->m_EmpArray = NULL;
		//初始化文件是否为空
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，并且没有记录
	char ch;
	ifs >> ch; //读取一个字符，如果读到的是EOF，表明文件已经读到尾部
	if (ifs.eof()) //eof()是读取文件
	{
		//文件为空
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//文件存在，并且记录数据
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	//开辟空间
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//将文件中的数据存到数组中,从而使程序一运行就能获取已经写好的数据，让显示职工的功能得以实现
	this->init_Emp();
}



//析构函数
workerManager::~workerManager()
{
	if (this->m_EmpArray != NULL)
	{
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			if (this->m_EmpArray[i] != NULL)
			{
				delete this->m_EmpArray[i];
			}
		}
		delete[] this->m_EmpArray;
		this->m_EmpArray = NULL;
	}
}
		



//展示菜单
void workerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  欢迎使用职工管理系统！  *********" << endl;
	cout << "*************  0.退出管理系统  *************" << endl;
	cout << "*************  1.增加职工信息  *************" << endl;
	cout << "*************  2.显示职工信息  *************" << endl;
	cout << "*************  3.删除离职职工  *************" << endl;
	cout << "*************  4.修改职工信息  *************" << endl;
	cout << "*************  5.查找职工信息  *************" << endl;
	cout << "*************  6.按照编号排序  *************" << endl;
	cout << "*************  7.清空所有文档  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}



//退出系统
void workerManager::ExitSystem()
{
	cout << "欢迎下次使用" << endl;
	system("pause");
	exit(0);
}



//添加职工
void workerManager::Add_Emp()
{
	cout << "请输入添加职工的数量：" << endl;
	int addNum = 0; //保存用户输入的数量
	cin >> addNum;
	if (addNum > 0)
	{
		//添加职工
		//计算添加的新的空间大小
		int newSize = this->m_EmpNum + addNum; //新空间大小 = 原来记录人数 + 新增人数
		//开辟新空间
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//批量添加新数据
		for (int i = 0; i < addNum; i++)
		{
			int id; //职工编号
			string name; //职工姓名
			int dSelect; //部门选择
			cout << "请输入第" << i + 1 << "个新职工的编号：" << endl;
			cin >> id;
			//判断职工编号是否已经存在
			if (this->IsExist(id) != -1)
			{
				cout << "该编号已经存在，请重新输入！" << endl;
				i--;
				continue;
			}
			cout << "请输入第" << i + 1 << "个新职工的姓名：" << endl;
			cin >> name;
			cout << "选择该职工的岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;
			cout << endl;

			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(id, name, 1);
				break;
			case 2:
				worker = new Manager(id, name, 2);
				break;
			case 3:
				worker = new Boss(id, name, 3);
				break;
			default:
				cout << "输入数据有误" << endl;
				break;
			}
			//将创建的职工保存到数组中
			newSpace[this->m_EmpNum + i] = worker;
		}

		//释放原有空间
		delete[] this->m_EmpArray;
		//更新新空间的指向
		this->m_EmpArray = newSpace;
		//更新新的职工人数
		this->m_EmpNum = newSize;
		//成功添加后保存到文件中
		this->save();
		//更新职工不为空的标志
		this->m_FileIsEmpty = false;
		//提示添加成功
		cout << "成功添加" << addNum << "名新职工！" << endl;
		//按任意键后清屏回到上级目录
		system("pause");
		system("cls");
	}
	else
	{
		cout << "输入数据有误" << endl;
	}
}



//显示职工
void workerManager::Show_Emp()
{
	//判断文件是否为空
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//利用多态调用接口
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}



//保存文件
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //用输出的方式打开文件
	//将每个人的数据写入到文件中
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//关闭文件
	ofs.close();
}



//统计文件中的人数
int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //以读文件方式打开文件
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//统计人数变量
		num++;
	}
	return num;
}



//初始化员工
void workerManager::init_Emp()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in);
	int id;
	string name;
	int dId;
	int index = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		Worker* worker = NULL;
		if (dId == 1) //普通职工
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //经理
		{
			worker = new Manager(id, name, dId);
		}
		else //老板
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//关闭文件
	ifs.close();
}



//判断职工是否存在
int workerManager::IsExist(int id)
{
	int index = -1;
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		if (this->m_EmpArray[i]->m_Id == id)
		{
			index = i;
			break;
		}
	}
	return index;
}



//删除职工
void workerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入您要删除的职工编号：" << endl;
		int id;
		cin >> id;
		int index = IsExist(id);
		if (index == -1)
		{
			cout << "删除失败，查无此人！" << endl;
			return;
		}
		else //说明职工存在并且要删除掉index位置上的职工
		{
			//数据前移
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			/*delete this->m_EmpArray[m_EmpNum];
			this->m_EmpArray[m_EmpNum] = NULL;*/
			this->m_EmpNum--; //更新数组中记录人员个数
			//同步数据更新到文件中
			this->save();
			cout << "删除成功！" << endl;
		}
	}
	system("pause");
	system("cls");
}



//修改职工
void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请输入您要修改的职工编号：" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret == -1)
		{
			cout << "查无此人！" << endl;
		}
		else
		{
			//查找到编号的职工
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "查找到：" << id << "号职工，请输入新职工号：" << endl;
			cin >> newId;
			cout << "请输入新姓名：" << endl;
			cin >> newName;
			cout << "请输入岗位：" << endl;
			cout << "1、普通职工" << endl;
			cout << "2、经理" << endl;
			cout << "3、总裁" << endl;
			cin >> dSelect;
			//创建一个空的worker指针
			Worker* worker = NULL;
			switch (dSelect)
			{
			case 1:
				worker = new Employee(newId, newName, 1);
				break;
			case 2:
				worker = new Manager(newId, newName, 2);
				break;
			case 3:
				worker = new Boss(newId, newName, 3);
				break;
			default:
				cout << "输入数据有误" << endl;
				break;
			}
			//将创建的职工保存到数组中
			this->m_EmpArray[ret] = worker;
			this->save();
			cout << "修改成功！" << endl;
		}
	}
	system("pause");
	system("cls");
}



//查找职工
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空！" << endl;
	}
	else
	{
		cout << "请选择您要查找的方式：" << endl;
		cout << "1、通过职工编号查找" << endl;
		cout << "2、通过职工姓名查找" << endl;
		int select = 0;
		cin >> select;
		switch(select)
		{
		case 1:
		{
			//按照编号查
			cout << "请输入职工编号：" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret == -1)
			{
				cout << "查无此人！" << endl;
			}
			else
			{
				cout << "查找成功！该职工信息如下：" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
		}
		break;
		case 2:
		{
			//按照姓名查
			cout << "请输入职工姓名：" << endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (name == this->m_EmpArray[i]->m_Name)
				{
					cout << "查找成功，职工编号为"
						<< this->m_EmpArray[i]->m_Id
						<< "的职工信息如下：" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "查无此人！" << endl;
			}
		}
		break;
		default:
			cout << "输入信息有误！" << endl;
			break;
		}
	}
	system("pause");
	system("cls");
}



//排序
void workerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "文件不存在或记录为空" << endl;
		//在这里由于下面没有写按任意键清屏的操作，所以要补上
		system("pause");
		system("cls");
	}
	else
	{
		cout << "请选择排序方式：" << endl;
		cout << "1、按职工编号进行升序排序" << endl;
		cout << "2、按职工编号进行降序排序" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minORmax = i; //声明最小值或最大值下标
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				//升序排序
				if (select == 1)
				{
					if (this->m_EmpArray[minORmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;
					}
				}
				//降序排序
				else if (select == 2)
				{
					if (this->m_EmpArray[minORmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;
					}
				}
			}
			//判断一开始认定的最小值或最大值是不是计算的最小值或最大值，如果不是交换数据
			if (i != minORmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minORmax];
				this->m_EmpArray[minORmax] = temp;
			}
		}
		cout << "排序成功！排序后结果为：" << endl;
		this->save(); //排序后的结果保存到文件中
		this->Show_Emp(); //展示所有的职工，该函数本身包含按任意键清屏的功能，因而不用再写
	}
}



//清空文件
void workerManager::Clean_File()
{
	cout << "确定将文件全部清空？" << endl;
	cout << "1、确定清空" << endl;
	cout << "2、退出" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		//清空文件
		ofstream ofs(FILENAME, ios::trunc); //删除文件后再重新创建
		ofs.close();
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				delete this->m_EmpArray[i];
				this->m_EmpArray[i] = NULL;
			}
			delete[] this->m_EmpArray;
			this->m_EmpArray = NULL;
			this->m_EmpNum = 0;
			this->m_FileIsEmpty = true;
		}
		cout << "清空成功！" << endl;
	}	
	system("pause");
	system("cls");
}