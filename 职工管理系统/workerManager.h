#pragma once //��ֹͷ�ļ��ظ�����
#include<iostream> //�������������ͷ�ļ�
#include<string>
#include<fstream>
#define FILENAME "empFile.txt"
using namespace std; //ʹ�ñ�׼�����ռ�
#include"worker.h"
#include"employee.h"
#include"manager.h"
#include"boss.h"


//��������
class workerManager
{
public:
	//���캯��
	workerManager();
	//��������
	~workerManager();
	//չʾ�˵�
	void Show_Menu();
	//�˳�ϵͳ
	void ExitSystem();
	//���ְ��
	void Add_Emp();
	//��ʾְ��
	void Show_Emp();
	//�����ļ�
	void save();
	//ͳ���ļ��е�����
	int get_EmpNum();
	//��ʼ��Ա��
	void init_Emp();
	//�ж�ְ���Ƿ����
	int IsExist(int id);
	//ɾ��ְ��
	void Del_Emp();
	//�޸�ְ��
	void Mod_Emp();
	//����ְ��
	void Find_Emp();
	//����
	void Sort_Emp();
	//����ļ�
	void Clean_File();

	//��¼ְ������
	int m_EmpNum;
	//ְ�������ָ��
	Worker** m_EmpArray;
	//�ж��ļ��Ƿ�Ϊ�յı�־
	bool m_FileIsEmpty;
};
