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
		cout << "连接FTP服务器         [成功]" << endl;
		setcolor(15);
	}
	else
	{
		setcolor(4);
		cout << "连接FTP服务器失败    [失败]" << endl;
		setcolor(15);
	}
	//ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	e1.login_error=ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	if (e1.login_error)
	{
		setcolor(2);
		cout << "登录FTP服务器          [成功]" << endl;
		setcolor(15);
	}
	else
	{
		setcolor(4);
		cout << "FTP服务器登录账号或者密码被管理员修改，请留意管理员动态" << endl;
		setcolor(15);
	}
	setcolor(6);
	cout << "请稍等......." << endl;
	cout << "正在检查配置文件......."<<endl;
	setcolor(15);

	//Sleep(1);
	//读取文件
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
				cout << "训练数据文件上传成功" << endl;
				setcolor(2);
				cout << "本地路径:" << str << endl;
				setcolor(15);
			}
			else
			{
				setcolor(4);
				cout << "文件上传失败!" << endl;
				setcolor(15);
			}

		}
	ifs.close();

	ftp->Quit();
}
