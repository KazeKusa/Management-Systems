#define _CRT_SECURE_NO_WARNINGS 1
#include"workerManager.h"



//���캯��
workerManager::workerManager()
{
	//�ļ�������
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //���ļ�
	//�ļ������ڵ����
	if (!ifs.is_open())
	{
		//��ʼ������
		//��ʼ����¼����
		this->m_EmpNum = 0;
		//��ʼ������ָ��
		this->m_EmpArray = NULL;
		//��ʼ���ļ��Ƿ�Ϊ��
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ�����û�м�¼
	char ch;
	ifs >> ch; //��ȡһ���ַ��������������EOF�������ļ��Ѿ�����β��
	if (ifs.eof()) //eof()�Ƕ�ȡ�ļ�
	{
		//�ļ�Ϊ��
		this->m_EmpNum = 0;
		this->m_EmpArray = NULL;
		this->m_FileIsEmpty = true;
		ifs.close();
		return;
	}

	//�ļ����ڣ����Ҽ�¼����
	int num = this->get_EmpNum();
	this->m_EmpNum = num;
	//���ٿռ�
	this->m_EmpArray = new Worker * [this->m_EmpNum];
	//���ļ��е����ݴ浽������,�Ӷ�ʹ����һ���о��ܻ�ȡ�Ѿ�д�õ����ݣ�����ʾְ���Ĺ��ܵ���ʵ��
	this->init_Emp();
}



//��������
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
		



//չʾ�˵�
void workerManager::Show_Menu()
{
	cout << "********************************************" << endl;
	cout << "*********  ��ӭʹ��ְ������ϵͳ��  *********" << endl;
	cout << "*************  0.�˳�����ϵͳ  *************" << endl;
	cout << "*************  1.����ְ����Ϣ  *************" << endl;
	cout << "*************  2.��ʾְ����Ϣ  *************" << endl;
	cout << "*************  3.ɾ����ְְ��  *************" << endl;
	cout << "*************  4.�޸�ְ����Ϣ  *************" << endl;
	cout << "*************  5.����ְ����Ϣ  *************" << endl;
	cout << "*************  6.���ձ������  *************" << endl;
	cout << "*************  7.��������ĵ�  *************" << endl;
	cout << "********************************************" << endl;
	cout << endl;
}



//�˳�ϵͳ
void workerManager::ExitSystem()
{
	cout << "��ӭ�´�ʹ��" << endl;
	system("pause");
	exit(0);
}



//���ְ��
void workerManager::Add_Emp()
{
	cout << "���������ְ����������" << endl;
	int addNum = 0; //�����û����������
	cin >> addNum;
	if (addNum > 0)
	{
		//���ְ��
		//������ӵ��µĿռ��С
		int newSize = this->m_EmpNum + addNum; //�¿ռ��С = ԭ����¼���� + ��������
		//�����¿ռ�
		Worker** newSpace = new Worker * [newSize];
		if (this->m_EmpArray != NULL)
		{
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				newSpace[i] = this->m_EmpArray[i];
			}
		}

		//�������������
		for (int i = 0; i < addNum; i++)
		{
			int id; //ְ�����
			string name; //ְ������
			int dSelect; //����ѡ��
			cout << "�������" << i + 1 << "����ְ���ı�ţ�" << endl;
			cin >> id;
			//�ж�ְ������Ƿ��Ѿ�����
			if (this->IsExist(id) != -1)
			{
				cout << "�ñ���Ѿ����ڣ����������룡" << endl;
				i--;
				continue;
			}
			cout << "�������" << i + 1 << "����ְ����������" << endl;
			cin >> name;
			cout << "ѡ���ְ���ĸ�λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
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
				cout << "������������" << endl;
				break;
			}
			//��������ְ�����浽������
			newSpace[this->m_EmpNum + i] = worker;
		}

		//�ͷ�ԭ�пռ�
		delete[] this->m_EmpArray;
		//�����¿ռ��ָ��
		this->m_EmpArray = newSpace;
		//�����µ�ְ������
		this->m_EmpNum = newSize;
		//�ɹ���Ӻ󱣴浽�ļ���
		this->save();
		//����ְ����Ϊ�յı�־
		this->m_FileIsEmpty = false;
		//��ʾ��ӳɹ�
		cout << "�ɹ����" << addNum << "����ְ����" << endl;
		//��������������ص��ϼ�Ŀ¼
		system("pause");
		system("cls");
	}
	else
	{
		cout << "������������" << endl;
	}
}



//��ʾְ��
void workerManager::Show_Emp()
{
	//�ж��ļ��Ƿ�Ϊ��
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		for (int i = 0; i < m_EmpNum; i++)
		{
			//���ö�̬���ýӿ�
			this->m_EmpArray[i]->showInfo();
		}
	}
	system("pause");
	system("cls");
}



//�����ļ�
void workerManager::save()
{
	ofstream ofs;
	ofs.open(FILENAME, ios::out); //������ķ�ʽ���ļ�
	//��ÿ���˵�����д�뵽�ļ���
	for (int i = 0; i < this->m_EmpNum; i++)
	{
		ofs << this->m_EmpArray[i]->m_Id << " "
			<< this->m_EmpArray[i]->m_Name << " "
			<< this->m_EmpArray[i]->m_DeptId << endl;
	}
	//�ر��ļ�
	ofs.close();
}



//ͳ���ļ��е�����
int workerManager::get_EmpNum()
{
	ifstream ifs;
	ifs.open(FILENAME, ios::in); //�Զ��ļ���ʽ���ļ�
	int id;
	string name;
	int dId;
	int num = 0;
	while (ifs >> id && ifs >> name && ifs >> dId)
	{
		//ͳ����������
		num++;
	}
	return num;
}



//��ʼ��Ա��
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
		if (dId == 1) //��ְͨ��
		{
			worker = new Employee(id, name, dId);
		}
		else if (dId == 2) //����
		{
			worker = new Manager(id, name, dId);
		}
		else //�ϰ�
		{
			worker = new Boss(id, name, dId);
		}
		this->m_EmpArray[index] = worker;
		index++;
	}
	//�ر��ļ�
	ifs.close();
}



//�ж�ְ���Ƿ����
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



//ɾ��ְ��
void workerManager::Del_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫɾ����ְ����ţ�" << endl;
		int id;
		cin >> id;
		int index = IsExist(id);
		if (index == -1)
		{
			cout << "ɾ��ʧ�ܣ����޴��ˣ�" << endl;
			return;
		}
		else //˵��ְ�����ڲ���Ҫɾ����indexλ���ϵ�ְ��
		{
			//����ǰ��
			for (int i = index; i < this->m_EmpNum - 1; i++)
			{
				this->m_EmpArray[i] = this->m_EmpArray[i + 1];
			}
			/*delete this->m_EmpArray[m_EmpNum];
			this->m_EmpArray[m_EmpNum] = NULL;*/
			this->m_EmpNum--; //���������м�¼��Ա����
			//ͬ�����ݸ��µ��ļ���
			this->save();
			cout << "ɾ���ɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}



//�޸�ְ��
void workerManager::Mod_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��������Ҫ�޸ĵ�ְ����ţ�" << endl;
		int id;
		cin >> id;
		int ret = this->IsExist(id);
		if (ret == -1)
		{
			cout << "���޴��ˣ�" << endl;
		}
		else
		{
			//���ҵ���ŵ�ְ��
			delete this->m_EmpArray[ret];
			int newId = 0;
			string newName = "";
			int dSelect = 0;
			cout << "���ҵ���" << id << "��ְ������������ְ���ţ�" << endl;
			cin >> newId;
			cout << "��������������" << endl;
			cin >> newName;
			cout << "�������λ��" << endl;
			cout << "1����ְͨ��" << endl;
			cout << "2������" << endl;
			cout << "3���ܲ�" << endl;
			cin >> dSelect;
			//����һ���յ�workerָ��
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
				cout << "������������" << endl;
				break;
			}
			//��������ְ�����浽������
			this->m_EmpArray[ret] = worker;
			this->save();
			cout << "�޸ĳɹ���" << endl;
		}
	}
	system("pause");
	system("cls");
}



//����ְ��
void workerManager::Find_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ�գ�" << endl;
	}
	else
	{
		cout << "��ѡ����Ҫ���ҵķ�ʽ��" << endl;
		cout << "1��ͨ��ְ����Ų���" << endl;
		cout << "2��ͨ��ְ����������" << endl;
		int select = 0;
		cin >> select;
		switch(select)
		{
		case 1:
		{
			//���ձ�Ų�
			cout << "������ְ����ţ�" << endl;
			int id;
			cin >> id;
			int ret = this->IsExist(id);
			if (ret == -1)
			{
				cout << "���޴��ˣ�" << endl;
			}
			else
			{
				cout << "���ҳɹ�����ְ����Ϣ���£�" << endl;
				this->m_EmpArray[ret]->showInfo();
			}
		}
		break;
		case 2:
		{
			//����������
			cout << "������ְ��������" << endl;
			string name;
			cin >> name;
			bool flag = false;
			for (int i = 0; i < this->m_EmpNum; i++)
			{
				if (name == this->m_EmpArray[i]->m_Name)
				{
					cout << "���ҳɹ���ְ�����Ϊ"
						<< this->m_EmpArray[i]->m_Id
						<< "��ְ����Ϣ���£�" << endl;
					this->m_EmpArray[i]->showInfo();
					flag = true;
				}
			}
			if (!flag)
			{
				cout << "���޴��ˣ�" << endl;
			}
		}
		break;
		default:
			cout << "������Ϣ����" << endl;
			break;
		}
	}
	system("pause");
	system("cls");
}



//����
void workerManager::Sort_Emp()
{
	if (this->m_FileIsEmpty)
	{
		cout << "�ļ������ڻ��¼Ϊ��" << endl;
		//��������������û��д������������Ĳ���������Ҫ����
		system("pause");
		system("cls");
	}
	else
	{
		cout << "��ѡ������ʽ��" << endl;
		cout << "1����ְ����Ž�����������" << endl;
		cout << "2����ְ����Ž��н�������" << endl;
		int select = 0;
		cin >> select;
		for (int i = 0; i < this->m_EmpNum; i++)
		{
			int minORmax = i; //������Сֵ�����ֵ�±�
			for (int j = i + 1; j < m_EmpNum; j++)
			{
				//��������
				if (select == 1)
				{
					if (this->m_EmpArray[minORmax]->m_Id > this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;
					}
				}
				//��������
				else if (select == 2)
				{
					if (this->m_EmpArray[minORmax]->m_Id < this->m_EmpArray[j]->m_Id)
					{
						minORmax = j;
					}
				}
			}
			//�ж�һ��ʼ�϶�����Сֵ�����ֵ�ǲ��Ǽ������Сֵ�����ֵ��������ǽ�������
			if (i != minORmax)
			{
				Worker* temp = this->m_EmpArray[i];
				this->m_EmpArray[i] = this->m_EmpArray[minORmax];
				this->m_EmpArray[minORmax] = temp;
			}
		}
		cout << "����ɹ����������Ϊ��" << endl;
		this->save(); //�����Ľ�����浽�ļ���
		this->Show_Emp(); //չʾ���е�ְ�����ú����������������������Ĺ��ܣ����������д
	}
}



//����ļ�
void workerManager::Clean_File()
{
	cout << "ȷ�����ļ�ȫ����գ�" << endl;
	cout << "1��ȷ�����" << endl;
	cout << "2���˳�" << endl;
	int select;
	cin >> select;
	if (select == 1)
	{
		//����ļ�
		ofstream ofs(FILENAME, ios::trunc); //ɾ���ļ��������´���
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
		cout << "��ճɹ���" << endl;
	}	
	system("pause");
	system("cls");
}