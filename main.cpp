#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string>
#include "ftplib.h"

#pragma warning(disable :4996)

using namespace std;
ifstream ifs;


//namespace connect{}

struct message
{
	int connect_error;
	int login_error;
	int upload_error;
	
}e1;







void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}




int main()
{
	/*ftplib* ftp = new ftplib();
	int ret = ftp->Connect("127.0.0.1:21");
	ret = ftp->Login("xiaoming", "123456");
	ret = ftp->Get("text.txt", "text.txt", ftplib::image);
	ftp->Quit();
	return 0;*/
	ftplib* ftp = new ftplib();
	e1.connect_error=ftp->Connect("47.97.98.152:21");
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
	cout << "���Ե�......." << endl;
	cout << "���ڼ�������ļ�......."<<endl;
	setcolor(15);

	//Sleep(1);
	//��ȡ�ļ�
	char server_file_path[256];
	ifstream ifrs("WZ_AI_FILE_NUMBER.txt", ios::in);
	string str_abc;
	while (getline(ifrs, str_abc)) {
		strcpy((char*)server_file_path, str_abc.c_str());
		cout << server_file_path << endl;
	}
	ifrs.close();
		ifstream ifs("WZ_AI_config.txt", ios::in);
		string str;
		char file_path[256];
		//strcpy((char*)file_path, str.c_str());
		while (getline(ifs, str))
		{
			strcpy((char*)file_path, str.c_str());
			e1.upload_error = ftp->Put(file_path, server_file_path, ftplib::ascii);
			if (e1.upload_error)
			{
				setcolor(1);
				cout << "ѵ�������ļ��ϴ��ɹ�" << endl;
				setcolor(2);
				cout << "����·��:" << str << endl;
				setcolor(15);
			}
			else
			{
				setcolor(4);
				cout << "�ļ��ϴ�ʧ��!" << endl;
				setcolor(15);
			}

		}
	ifs.close();

	ftp->Quit();
}
