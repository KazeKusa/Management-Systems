#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;
#define MAX 1000 //最大人数





//显示菜单
void showMenu()
{   
	cout << "***********************" << endl;
	cout << "*****1、添加联系人*****" << endl;
	cout << "*****2、显示联系人*****" << endl;
	cout << "*****3、删除联系人*****" << endl;
	cout << "*****4、查找联系人*****" << endl;
	cout << "*****5、修改联系人*****" << endl;
	cout << "*****6、清空联系人*****" << endl;
	cout << "*****0、退出通讯录*****" << endl;
	cout << "***********************" << endl;
}



//联系人结构体
struct Person
{
	string m_Name; //姓名
	int m_Sex; //性别：1男 2女
	int m_Age; //年龄
	string m_Phone; //电话
	string m_Addr; //住址
};



//通讯录结构体
struct Addressbooks
{
	struct Person personArray[MAX]; //通讯录中保存的联系人数组
	int m_Size; //通讯录中人员个数
};



//1、添加联系人
void addPerson(Addressbooks* abs)
{
	//判断通讯录是否已满，如果满了就不再添加
	if (abs->m_Size == MAX)
	{
		cout << "通讯录已满，无法添加！" << endl;
		return;
	}
	else
	{
		//添加具体联系人
		// 
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		//性别
		int sex = 0;
		cout << "请输入性别：" << endl;
		cout << "1-男   2-女" << endl;
		while (true)
		{
			cin >> sex;
			//如果输入的是1或2可以退出循环，因为输入的是正确值
			//如果输入有误，重新输入
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}

		//年龄
		int age = 0;
		cout << "请输入年龄：" << endl;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//电话
		string phone;
		cout << "请输入电话：" << endl;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//家庭住址
		string address;
		cout << "请输入家庭住址：" << endl;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//更新通讯录人数
		abs->m_Size++;

		cout << "添加成功！" << endl;

		system("pause");//请按任意键继续
		system("cls");//清屏操作
	}
}



//2、显示联系人
void showPerson(Addressbooks* abs)
{
	//判断通讯录中人数是否为0，如果为0，提示记录为空
	if (abs->m_Size == 0)
	{
		cout << "当前记录为空！" << endl;
	}
	//如果不为0，显示记录的联系人信息
	else
	{
		for (int count = 0; count < abs->m_Size; count++)
		{
			cout << "通讯人" << count+1 << endl;
			cout << "姓名：" << abs->personArray[count].m_Name << "\t";
			cout << "性别：" << (abs->personArray[count].m_Sex == 1?"男":"女") << "\t"; //用三目运算符就可以避免if else语句的繁琐了
			cout << "年龄：" << abs->personArray[count].m_Age << "\t";
			cout << "电话：" << abs->personArray[count].m_Phone << "\t";
			cout << "家庭住址：" << abs->personArray[count].m_Addr << endl;
			cout << endl;
		}
	}
	system("pause");//按任意键继续
	system("cls");//清空屏幕
}



//检测联系人是否存在，如果存在，返回联系人所在数组中的具体位置，不存在返回-1
//参数1 通讯录   参数2 对比姓名
int is_Exist(Addressbooks *abs,string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		//找到用户输入的姓名了
		if (abs->personArray[i].m_Name == name)
		{
			return i;    //找到了，返回这个人在数组中的下标编号
		}
	}
	return -1;  //如果遍历结束都没有找到，返回-1
}



//3、删除指定联系人
void deletePerson(Addressbooks* abs)
{
	cout << "请输入您要删除的联系人：" << endl;
	string name;
	cin >> name;
	int ret = is_Exist(abs, name);
	//ret == -1 未查到
	//ret != -1 查到了
	if (ret != -1)
	{
		//查到此人，要进行删除操作
		for (int i = ret; i < abs->m_Size; i++)
		{
			//数据前移
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;//更新通讯录中的人员数
		cout << "删除成功！" << endl;
	}
	else
	{
		cout << "查无此人!" << endl;
	}
	system("pause");
	system("cls");//清屏
}



//4、查找指定联系人信息（是“显示联系人”功能的派生
void findPerson(Addressbooks* abs)
{
	cout << "请输入您要查找的联系人：" << endl;
	string name;
	cin >> name;
	//判断指定的联系人是否存在于通讯录中
	int ret = is_Exist(abs, name);
	if (ret != -1)//找到联系人
	{
		cout << "通讯人" << ret + 1 << endl;
		cout << "姓名：" << abs->personArray[ret].m_Name << "\t";
		cout << "性别：" << (abs->personArray[ret].m_Sex == 1 ? "男" : "女") << "\t"; //用三目运算符就可以避免if else语句的繁琐了
		cout << "年龄：" << abs->personArray[ret].m_Age << "\t";
		cout << "电话：" << abs->personArray[ret].m_Phone << "\t";
		cout << "家庭住址：" << abs->personArray[ret].m_Addr << endl;
		cout << endl;
	}
	else // 未找到联系人
	{
		cout << "查无此人！" << endl;
	}
	system("pause");
	system("cls");
}



//5、修改指定联系人信息（是添加联系人功能的派生）
void modifyPerson(Addressbooks* abs)
{
	cout << "请输入您要修改的联系人：" << endl;
	string name;
	cin >> name;
	int ret = is_Exist(abs, name);
	if (ret != -1) //找到指定的联系人
	{
		//姓名
		string name;
		cout << "请输入姓名：" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		//性别
		int sex = 0;
		cout << "请输入性别：" << endl;
		cout << "1-男   2-女" << endl;
		while (true)
		{
			cin >> sex;
			//如果输入的是1或2可以退出循环，因为输入的是正确值
			//如果输入有误，重新输入
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "输入有误，请重新输入" << endl;
		}

		//年龄
		int age = 0;
		cout << "请输入年龄：" << endl;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		//电话
		string phone;
		cout << "请输入电话：" << endl;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		//家庭住址
		string address;
		cout << "请输入家庭住址：" << endl;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
	}
	else //未找到联系人
	{
		cout << "查无此人！" << endl;
	}
	cout << "修改成功！" << endl;
	system("pause");
	system("cls");
}



//6、清空所有联系人
void cleanPerson(Addressbooks* abs)
{
	abs->m_Size = 0;
	cout << "通讯录已清空" << endl; //将当期记录联系人数量置为0，做逻辑清空操作
	system("pause");
	system("cls");
}





int main()
{
	//创建通讯录结构体变量
	Addressbooks abs;
	//初始化通讯录中当前人员个数
	abs.m_Size = 0;

	int select = 0;
	while (true)  //一直循环，直到select的输入值为0退出系统
	{
		//调用菜单
		showMenu();

		//选择功能
		cin >> select;
		switch (select)
		{
		case 1: //添加联系人
			addPerson(&abs);//利用地址传递，可以修饰实参
			break;
		case 2: //显示联系人
			showPerson(&abs);
			break;
		case 3: //删除联系人
			deletePerson(&abs);
			break;
		case 4: //查找联系人
			findPerson(&abs);
			break;
		case 5: //修改联系人
			modifyPerson(&abs);
			break;
		case 6: //清空联系人
			cleanPerson(&abs);
			break;
		case 0: //退出通讯录
			cout << "欢迎下次使用" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "输入错误，请重新输入" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}