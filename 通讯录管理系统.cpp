#define _CRT_SECURE_NO_WARNINGS 1
#include<iostream>
#include<string>
using namespace std;
#define MAX 1000 //�������





//��ʾ�˵�
void showMenu()
{   
	cout << "***********************" << endl;
	cout << "*****1�������ϵ��*****" << endl;
	cout << "*****2����ʾ��ϵ��*****" << endl;
	cout << "*****3��ɾ����ϵ��*****" << endl;
	cout << "*****4��������ϵ��*****" << endl;
	cout << "*****5���޸���ϵ��*****" << endl;
	cout << "*****6�������ϵ��*****" << endl;
	cout << "*****0���˳�ͨѶ¼*****" << endl;
	cout << "***********************" << endl;
}



//��ϵ�˽ṹ��
struct Person
{
	string m_Name; //����
	int m_Sex; //�Ա�1�� 2Ů
	int m_Age; //����
	string m_Phone; //�绰
	string m_Addr; //סַ
};



//ͨѶ¼�ṹ��
struct Addressbooks
{
	struct Person personArray[MAX]; //ͨѶ¼�б������ϵ������
	int m_Size; //ͨѶ¼����Ա����
};



//1�������ϵ��
void addPerson(Addressbooks* abs)
{
	//�ж�ͨѶ¼�Ƿ�������������˾Ͳ������
	if (abs->m_Size == MAX)
	{
		cout << "ͨѶ¼�������޷���ӣ�" << endl;
		return;
	}
	else
	{
		//��Ӿ�����ϵ��
		// 
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[abs->m_Size].m_Name = name;

		//�Ա�
		int sex = 0;
		cout << "�������Ա�" << endl;
		cout << "1-��   2-Ů" << endl;
		while (true)
		{
			cin >> sex;
			//����������1��2�����˳�ѭ������Ϊ���������ȷֵ
			//�������������������
			if (sex == 1 || sex == 2)
			{
				abs->personArray[abs->m_Size].m_Sex = sex;
				break;
			}
			cout << "������������������" << endl;
		}

		//����
		int age = 0;
		cout << "���������䣺" << endl;
		cin >> age;
		abs->personArray[abs->m_Size].m_Age = age;

		//�绰
		string phone;
		cout << "������绰��" << endl;
		cin >> phone;
		abs->personArray[abs->m_Size].m_Phone = phone;

		//��ͥסַ
		string address;
		cout << "�������ͥסַ��" << endl;
		cin >> address;
		abs->personArray[abs->m_Size].m_Addr = address;

		//����ͨѶ¼����
		abs->m_Size++;

		cout << "��ӳɹ���" << endl;

		system("pause");//�밴���������
		system("cls");//��������
	}
}



//2����ʾ��ϵ��
void showPerson(Addressbooks* abs)
{
	//�ж�ͨѶ¼�������Ƿ�Ϊ0�����Ϊ0����ʾ��¼Ϊ��
	if (abs->m_Size == 0)
	{
		cout << "��ǰ��¼Ϊ�գ�" << endl;
	}
	//�����Ϊ0����ʾ��¼����ϵ����Ϣ
	else
	{
		for (int count = 0; count < abs->m_Size; count++)
		{
			cout << "ͨѶ��" << count+1 << endl;
			cout << "������" << abs->personArray[count].m_Name << "\t";
			cout << "�Ա�" << (abs->personArray[count].m_Sex == 1?"��":"Ů") << "\t"; //����Ŀ������Ϳ��Ա���if else���ķ�����
			cout << "���䣺" << abs->personArray[count].m_Age << "\t";
			cout << "�绰��" << abs->personArray[count].m_Phone << "\t";
			cout << "��ͥסַ��" << abs->personArray[count].m_Addr << endl;
			cout << endl;
		}
	}
	system("pause");//�����������
	system("cls");//�����Ļ
}



//�����ϵ���Ƿ���ڣ�������ڣ�������ϵ�����������еľ���λ�ã������ڷ���-1
//����1 ͨѶ¼   ����2 �Ա�����
int is_Exist(Addressbooks *abs,string name)
{
	for (int i = 0; i < abs->m_Size; i++)
	{
		//�ҵ��û������������
		if (abs->personArray[i].m_Name == name)
		{
			return i;    //�ҵ��ˣ�����������������е��±���
		}
	}
	return -1;  //�������������û���ҵ�������-1
}



//3��ɾ��ָ����ϵ��
void deletePerson(Addressbooks* abs)
{
	cout << "��������Ҫɾ������ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	int ret = is_Exist(abs, name);
	//ret == -1 δ�鵽
	//ret != -1 �鵽��
	if (ret != -1)
	{
		//�鵽���ˣ�Ҫ����ɾ������
		for (int i = ret; i < abs->m_Size; i++)
		{
			//����ǰ��
			abs->personArray[i] = abs->personArray[i + 1];
		}
		abs->m_Size--;//����ͨѶ¼�е���Ա��
		cout << "ɾ���ɹ���" << endl;
	}
	else
	{
		cout << "���޴���!" << endl;
	}
	system("pause");
	system("cls");//����
}



//4������ָ����ϵ����Ϣ���ǡ���ʾ��ϵ�ˡ����ܵ�����
void findPerson(Addressbooks* abs)
{
	cout << "��������Ҫ���ҵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	//�ж�ָ������ϵ���Ƿ������ͨѶ¼��
	int ret = is_Exist(abs, name);
	if (ret != -1)//�ҵ���ϵ��
	{
		cout << "ͨѶ��" << ret + 1 << endl;
		cout << "������" << abs->personArray[ret].m_Name << "\t";
		cout << "�Ա�" << (abs->personArray[ret].m_Sex == 1 ? "��" : "Ů") << "\t"; //����Ŀ������Ϳ��Ա���if else���ķ�����
		cout << "���䣺" << abs->personArray[ret].m_Age << "\t";
		cout << "�绰��" << abs->personArray[ret].m_Phone << "\t";
		cout << "��ͥסַ��" << abs->personArray[ret].m_Addr << endl;
		cout << endl;
	}
	else // δ�ҵ���ϵ��
	{
		cout << "���޴��ˣ�" << endl;
	}
	system("pause");
	system("cls");
}



//5���޸�ָ����ϵ����Ϣ���������ϵ�˹��ܵ�������
void modifyPerson(Addressbooks* abs)
{
	cout << "��������Ҫ�޸ĵ���ϵ�ˣ�" << endl;
	string name;
	cin >> name;
	int ret = is_Exist(abs, name);
	if (ret != -1) //�ҵ�ָ������ϵ��
	{
		//����
		string name;
		cout << "������������" << endl;
		cin >> name;
		abs->personArray[ret].m_Name = name;

		//�Ա�
		int sex = 0;
		cout << "�������Ա�" << endl;
		cout << "1-��   2-Ů" << endl;
		while (true)
		{
			cin >> sex;
			//����������1��2�����˳�ѭ������Ϊ���������ȷֵ
			//�������������������
			if (sex == 1 || sex == 2)
			{
				abs->personArray[ret].m_Sex = sex;
				break;
			}
			cout << "������������������" << endl;
		}

		//����
		int age = 0;
		cout << "���������䣺" << endl;
		cin >> age;
		abs->personArray[ret].m_Age = age;

		//�绰
		string phone;
		cout << "������绰��" << endl;
		cin >> phone;
		abs->personArray[ret].m_Phone = phone;

		//��ͥסַ
		string address;
		cout << "�������ͥסַ��" << endl;
		cin >> address;
		abs->personArray[ret].m_Addr = address;
	}
	else //δ�ҵ���ϵ��
	{
		cout << "���޴��ˣ�" << endl;
	}
	cout << "�޸ĳɹ���" << endl;
	system("pause");
	system("cls");
}



//6�����������ϵ��
void cleanPerson(Addressbooks* abs)
{
	abs->m_Size = 0;
	cout << "ͨѶ¼�����" << endl; //�����ڼ�¼��ϵ��������Ϊ0�����߼���ղ���
	system("pause");
	system("cls");
}





int main()
{
	//����ͨѶ¼�ṹ�����
	Addressbooks abs;
	//��ʼ��ͨѶ¼�е�ǰ��Ա����
	abs.m_Size = 0;

	int select = 0;
	while (true)  //һֱѭ����ֱ��select������ֵΪ0�˳�ϵͳ
	{
		//���ò˵�
		showMenu();

		//ѡ����
		cin >> select;
		switch (select)
		{
		case 1: //�����ϵ��
			addPerson(&abs);//���õ�ַ���ݣ���������ʵ��
			break;
		case 2: //��ʾ��ϵ��
			showPerson(&abs);
			break;
		case 3: //ɾ����ϵ��
			deletePerson(&abs);
			break;
		case 4: //������ϵ��
			findPerson(&abs);
			break;
		case 5: //�޸���ϵ��
			modifyPerson(&abs);
			break;
		case 6: //�����ϵ��
			cleanPerson(&abs);
			break;
		case 0: //�˳�ͨѶ¼
			cout << "��ӭ�´�ʹ��" << endl;
			system("pause");
			return 0;
			break;
		default:
			cout << "�����������������" << endl;
			break;
		}
	}
	system("pause");
	return 0;
}