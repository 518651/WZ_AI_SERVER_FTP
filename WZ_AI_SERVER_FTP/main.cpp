#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include "ftplib.h"

#pragma warning(disable :4996)

using namespace std;
ifstream ifs;

string password()
{
	int n = 32;

	char chr[] = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
			'A', 'B', 'C', 'D', 'E', 'F' };

	srand(time(NULL));
	string strResult;
	char buf[10] = { 0 };

	for (int i = 0; i < n; i++)
	{
		int idx = rand() % 16;
		//              printf("%c", chr[idx]);//�ַ����
		sprintf(buf, "%c", chr[idx]);
		strResult.append(buf);
	}
	//cout << strResult.c_str() << endl;

	return strResult.c_str();
}



struct message
{
	int connect_error;
	int login_error;
	int upload_error;
	int Mkdir_error;
	int Chdir_error;
}e1;


void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}



//char server_file_path[5000] = {0};
int download_number_add=1;
int dowsload_numer = 0;


void main()
{
	ftplib* ftp = new ftplib();
	e1.connect_error=ftp->Connect("120.26.51.161:21");
	if (e1.connect_error)
	{
		setcolor(2);
		cout << "����FTP������         [�ɹ�]" << endl;
		setcolor(15);
	}
	else
	{
		setcolor(4);
		cout << "����FTP������ʧ��    [ʧ��]" << endl;
		setcolor(15);
	}
	//ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	e1.login_error=ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	if (e1.login_error)
	{
		setcolor(2);
		cout << "��¼FTP������          [�ɹ�]" << endl;
		setcolor(15);
	}
	else
	{
		setcolor(4);
		cout << "FTP��������¼�˺Ż������뱻����Ա�޸ģ����������Ա��̬" << endl;
		setcolor(15);
	}
	setcolor(6);
	cout << ">>>>>>��ӭʹ������AIѵ�����ݹ���ƽ̨<<<<<<" << endl;
	cout << "���ڼ�������ļ�........."<<endl;
	setcolor(15);
	string name = "WZ_AI_config.txt";
	if (FILE* file = fopen(name.c_str(), "r")) {
		fclose(file);
		setcolor(9);
		cout << "�����ļ�������!���ڽ�����һ��" << endl;
		setcolor(15);
	}
	else {
		setcolor(5);
		cout << "�����ļ������ڣ���ǰ�޷�����ϴ��Ȳ���!" << endl;
		cout << "������������AIѧϰpython�ļ�,�ļ����Զ����������ļ�" << endl;
		setcolor(15);
		Sleep(15);
		exit(0);
	}
	setcolor(14);
	cout << "����Ϊ����Զ��FTP�������������������ļ���" << endl;
	setcolor(15);
	string file_P = password();
	char file_a[256];
	strcpy(file_a, file_P.c_str());
	e1.Mkdir_error = ftp->Mkdir(file_a);
	if (e1.Mkdir_error)
	{
		setcolor(2);
		cout << "Զ��FTP�����������ļ���                 [�ɹ�]" << endl;
		setcolor(15);
	}
	else
	{
		setcolor(4);
		cout << "Զ��FTP�����������ļ���                 [ʧ��]" << endl;
		cout << "���Ե����³���!" << endl;
		setcolor(15);
		Sleep(15);
		//exit(0);
	}
	setcolor(14);
	cout << "����Ϊ���������ļ���" << endl;
	setcolor(15);
	e1.Chdir_error = ftp->Chdir(file_a);
	if (e1.Chdir_error)
	{
		setcolor(2);
		cout << "���������ļ���                 [�ɹ�]" << endl;
		setcolor(15);
	}
	else
	{
		setcolor(4);
		cout << "���������ļ���                [ʧ��]" << endl;
		cout << "���Ե����³���!" << endl;
		setcolor(15);
		Sleep(15);
		//exit(0);
	}
	cout << "���ڶ�ȡ�����ļ�" << endl;
	Sleep(1);

	
	
	string str_abc;
	string str_cba[5000];
	int tot=0;
	ifstream ifrs("WZ_AI_FILE_NUMBER.txt", ios::in);
	while (getline(ifrs, str_abc,'\n')) {
		for (int i=0;i<1;i++)
		{
			str_cba[tot++] = str_abc;
		}
	}	
	ifrs.close();
	

	//memcpy(server_file_path, str_cba[i].c_str(), str_cba[i].size());
	//e1.upload_error = ftp->Put(file_path, server_file_path, ftplib::image);

		
		int tor = 0;
		string str;
		string str_a[5000];
		//char file_path[5000] = {0};
		ifstream ifs("WZ_AI_config.txt", ios::in);
		while (getline(ifs, str,'\n'))
		{
			for (int i = 0; i < 1; i++)
			{
				str_a[tor++] = str;
			}
		}
		ifs.close();

		
		
		for (int i = 0; i < tor; i++)
		{
			
			for (int i = 0; i < tot; i++)
			{
				if (i < tot - 1)
				{
					printf("\r�ϴ���[%.2lf%%]:", i * 100.0 / (tot - 1));
					
					
				}
				else
				{
					printf("\r�ϴ����[%.2lf%%]:", i * 100.0 / (tot - 1));
				}
				int show_num = i * 20 / tot;
				for (int j = 1; j <= show_num; j++)
				{
					setcolor(11);
					std::cout << "��";
					setcolor(15);
					Sleep(1);
				}

			}
			std::cout << std::endl;
			char file_path[5000] = { 0 };
			char server_file_path[5000] = { 0 };
			memcpy(server_file_path, str_cba[i].c_str(), str_cba[i].size());
			memcpy(file_path, str_a[i].c_str(), str_a[i].size());
			e1.upload_error = ftp->Put((const char*)file_path, server_file_path, ftplib::image);			
			cout << "��ǰFTP�������ļ��б��:" << file_P << endl;
			for (int i = 0; i < 1; i++)
			{
				dowsload_numer = dowsload_numer + 1;
				setcolor(14);
				cout << "��ǰ�ϴ��ļ���:" << dowsload_numer << endl;
				setcolor(3);
				cout << "�����ϴ�Ŀ¼�ļ�����:" << tot << endl;
				setcolor(15);
			}
			cout << "�ϴ����ļ�����:" << (const char*)file_path << endl;
			cout << "�ϴ���������Ŀ¼������:" <<file_P<<"\\" << server_file_path << endl;
			cout << "Զ��FTP����״̬:" << e1.upload_error << endl;
			//Sleep(1000);
			if (e1.upload_error)
			{
				setcolor(1);
				cout << "ѵ�������ļ��ϴ��ɹ�" << endl;
				setcolor(2);
				cout << "����·��:" << file_path << endl;
				setcolor(15);
			}
			else
			{
				setcolor(4);
				cout << "�ļ��ϴ�ʧ��!" << endl;
				setcolor(15);
			}
		}
		setcolor(2);
		cout << "[��Ϣ]:����ѵ��ͼƬ�Գɹ��ϴ�FTP������!" << endl;
		cout << "[��Ϣ]:���������ϴ������ļ�........." << endl;
		cout << "���Ե�....." << endl;
		cout << "Loading........" << endl;

		setcolor(15);
		
		char karl[256];
		char karl_name[256];
		string aaa_name = "_��������.json";
		string path_add_name = "_��������.json";
		string path_zero;
		string path_massage;
		ifstream ifrzs("AI_WZ_config.txt", ios::in);
		while (getline(ifrzs, path_zero, '\n'))
		{
			path_massage=path_zero + path_add_name;
		}
		ifrs.close();
		strcpy(karl, path_massage.c_str());
		strcpy(karl_name, aaa_name.c_str());
		e1.upload_error = ftp->Put(karl, karl_name, ftplib::image);
		if (e1.upload_error)
		{	
			setcolor(2);
			cout<<"��л�ȴ�!��ǰ����ɶ������ļ��ϴ�����"<<endl;
			setcolor(15);
		}
		else
		{
			setcolor(4);
			cout << "�ܱ�Ǹ��δ����ɵ�ǰ�Բ����ļ��ϴ������������ϴ�����" << endl;
			cout<<"��л������⣡" << endl;
			setcolor(14);
			cout << "WARNING:��ע�����̨�Ƿ����ϴ������ļ�������о����ϴ��ɹ��ˣ�" << endl;
			cout << "WARNING:��ע�����̨�Ƿ����ϴ������ļ�������о����ϴ��ɹ��ˣ�" << endl;
			cout << "WARNING:��ע�����̨�Ƿ����ϴ������ļ�������о����ϴ��ɹ��ˣ�" << endl;
			setcolor(15);
		}
			

	
	system("pause");
	ftp->Quit();
}



