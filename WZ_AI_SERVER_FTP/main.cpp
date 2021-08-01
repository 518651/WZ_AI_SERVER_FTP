#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <fstream>
#include <string>
//#include <Windows.h>
#include <future>
#include <ctime>
#include "ftplib.h"


using namespace std;
#pragma warning(disable :4996)



ifstream ifs;

//全局变量区
int tot = 0;
int tor = 0;
int ok1 = 1;
int ok2 = 1;


struct message
{
	int connect_error;
	int login_error;
	int upload_error;
	int Mkdir_error;
	int Chdir_error;
	int Get;  
}e1;



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
		//              printf("%c", chr[idx]);//字符输出
		sprintf(buf, "%c", chr[idx]);
		strResult.append(buf);
	}
	//cout << strResult.c_str() << endl;

	return strResult.c_str();
}

string file_P;


int WINAPI_MANY_PROCESS(string file_box, char file_path[50000], char server_file_path[5000]);



void setcolor(unsigned short color)
{
	HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(hcon, color);
}


int 控制模块(string file_P, string str_a[50000], string str_cba[5000]);

int dowsload_numer = 0;



typedef struct
{
	string file;
	string A;
	string B;
}TEMP;
TEMP temp;

mutex mu;//线程互斥对象
bool PoolFlag = true;//true =继续 false=停止  传完了 这个要清空  flase
int length = 0;
void threadPool(TEMP data)
{
	mu.lock(); //同步数据锁 
	std::this_thread::sleep_for(std::chrono::milliseconds(10));
	ftplib* ftp = new ftplib();
	e1.connect_error = ftp->Connect("120.26.51.161:21");
	//ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	char file_a[256];
	strcpy(file_a, data.file.c_str());
	//e1.Mkdir_error = ftp->Mkdir(file_a);
	e1.Chdir_error = ftp->Chdir(file_a);
	if (e1.Chdir_error==0)
	{	
		cout << "线程进入FTP下载文件夹失败" << endl;	
	}

	for (int i = 0; i < 1; i++)
	{

		for (int i = 0; i < 2; i++)
		{
			if (i < 2 - 1)
			{
				printf("\r上传中[%.2lf%%]:", i * 100.0 / (2 - 1));

			}
			else
			{
				printf("\r上传完成[%.2lf%%]:", i * 100.0 / (2 - 1));
			}
			int show_num = i * 20 / 2;
			for (int j = 1; j <= show_num; j++)
			{
				setcolor(11);
				std::cout << "█";
				setcolor(15);
				Sleep(1);
			}

		}
		std::cout << std::endl;
		char file_path[50000] = { 0 };
		char server_file_path[5000] = { 0 };
		memcpy(server_file_path, data.B.c_str(), data.B.size());
		memcpy(file_path, data.A.c_str(), data.A.size());
		//memcpy(file_path, process_number_a[i].c_str(), process_number_a[i].size());
		//memcpy(server_file_path, process_number_b[i].c_str(), process_number_b[i].size());
		e1.upload_error = ftp->Put(file_path, server_file_path, ftplib::image);
		cout << "当前FTP服务器文件夹编号:" << data.file << endl;
		for (int i = 0; i < 1; i++)
		{
			dowsload_numer = dowsload_numer + 1;
			setcolor(14);
			cout << "当前上传文件数:" << dowsload_numer << endl;
			setcolor(3);
			cout << "本地上传目录文件总数:" << tot << endl;
			setcolor(15);
		}
		cout << "上传的文件名称:" << (const char*)file_path << endl;
		cout << "上传至服务器目录下名称:" << data.file << "<--" << server_file_path << endl;
		cout << "远程FTP反馈状态:" << e1.upload_error << endl;
		//Sleep(1000);
		if (e1.upload_error)
		{
			setcolor(1);
			cout << "训练数据文件上传成功" << endl;
			setcolor(2);
			cout << "本地路径:" << file_path << endl;
			setcolor(15);
		}
		else
		{
			setcolor(4);
			cout << "文件上传失败!" << endl;
			setcolor(15);
		}
	}
	ftp->Quit();
	mu.unlock();//解除锁定  
}

int main()
{
	int menu = 1;
	while (menu!=0)
	{		
			setcolor(4);
			cout << ">>>>>>欢迎使用王者AI训练数据共享平台<<<<<<" << endl;
			setcolor(9);
			cout << "               菜单列表                                 " << endl;
			cout << "选择1:      训练文件上传                            " << endl;
			cout << "选择2:     训练模型文件下载                            " << endl;
			cout << "选择3:     启动全自动脚本                              " << endl;
			cout << "选择0:         退出程序                                " << endl;
			setcolor(4);
			cout << ">>>>>>欢迎使用王者AI训练数据共享平台<<<<<<" << endl;
			setcolor(15);
			cout << "请输入你要执行的功能编号:";
	cin >> menu;
		switch (menu)
		{
		case1:
		{
		ftplib* ftp = new ftplib();
		e1.connect_error = ftp->Connect("120.26.51.161:21");
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
		e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
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
		cout << ">>>>>>欢迎使用王者AI训练数据共享平台<<<<<<" << endl;
		cout << "正在检查配置文件........." << endl;
		setcolor(15);
		string name = "WZ_AI_config.txt";
		if (FILE* file = fopen(name.c_str(), "r")) {
			fclose(file);
			setcolor(9);
			cout << "配置文件检查存在!正在进行下一步" << endl;
			setcolor(15);
		}
		else {
			setcolor(5);
			cout << "配置文件不存在，当前无法完成上传等操作!" << endl;
			cout << "请先运行配套AI学习python文件,文件将自动创建配置文件" << endl;
			setcolor(15);
			Sleep(15);
			exit(0);
		}
		setcolor(14);
		cout << "正在为您在远程FTP服务器创建本次下载文件夹" << endl;
		setcolor(15);
		string file_P = password();
		char file_a[256];
		file_P = password();
		strcpy(file_a, file_P.c_str());
		e1.Mkdir_error = ftp->Mkdir(file_a);
		if (e1.Mkdir_error)
		{
			setcolor(2);
			cout << "远程FTP服务器创建文件夹                 [成功]" << endl;
			setcolor(15);
		}
		else
		{
			setcolor(4);
			cout << "远程FTP服务器创建文件夹                 [失败]" << endl;
			cout << "请稍等重新尝试!" << endl;
			setcolor(15);
			Sleep(15);
			//exit(0);
		}
		setcolor(14);
		cout << "正在为您导航进文件夹" << endl;
		setcolor(15);
		e1.Chdir_error = ftp->Chdir(file_a);
		if (e1.Chdir_error)
		{
			setcolor(2);
			cout << "进入下载文件夹                 [成功]" << endl;
			setcolor(15);
		}
		else
		{
			setcolor(4);
			cout << "进入下载文件夹                [失败]" << endl;
			cout << "请稍等重新尝试!" << endl;
			setcolor(15);
			Sleep(15);
			exit(0);
		}
		cout << "正在读取配置文件" << endl;
		Sleep(1);


		string str_abc;
		string str_cba[5000];
		//int tot=0;
		ifstream ifrs("WZ_AI_FILE_NUMBER.txt", ios::in);
		while (getline(ifrs, str_abc, '\n')) {
			for (int i = 0; i < 1; i++)
			{
				str_cba[tot++] = str_abc;//服务器文件参数
			}
		}
		ifrs.close();

		//int tor = 0;
		string str;
		string str_a[50000];
		ifstream ifs("WZ_AI_config.txt", ios::in);
		while (getline(ifs, str, '\n'))
		{
			for (int i = 0; i < 1; i++)
			{
				str_a[tor++] = str;//本地上传文件路径
			}
		}
		ifs.close();

		length = 0;
		while (PoolFlag)
		{
			std::thread threadID[10];
			for (int i = 0; i < 10; i++)//创建线程池
			{
				temp.file = file_P;
				temp.A = str_a[length];
				temp.B = str_cba[length];
				threadID[i] = std::thread(threadPool, temp);//后面参数

				if (length < tot)length++;
				else PoolFlag = false;//	PoolFlag = false;
			}
			for (auto& t : threadID)
				t.join();
		}
	
		setcolor(2);
		cout << "[消息]:所有训练图片以成功上传FTP服务器!" << endl;
		cout << "[消息]:现在正在上传";
		setcolor(13);
		cout << "操作文件";
		setcolor(2);
		cout << "........." << endl;
		cout << "请稍等....." << endl;
		cout << "Loading........" << endl;

		setcolor(15);

		char karl[256];
		char karl_name[256];
		string aaa_name = "_操作数据.json";
		string path_add_name = "_操作数据.json";
		string path_zero;
		string path_massage;
		ifstream ifrzs("AI_WZ_config.txt", ios::in);
		while (getline(ifrzs, path_zero, '\n'))
		{
			path_massage = path_zero + path_add_name;
		}
		ifrzs.close();
		strcpy(karl, path_massage.c_str());
		strcpy(karl_name, aaa_name.c_str());
		e1.upload_error = ftp->Put(karl, karl_name, ftplib::image);
			if (e1.upload_error)
			{
			setcolor(2);
			cout << "感谢等待!当前以完成对所有文件上传任务" << endl;
			setcolor(15);
			}
			 else
			 {
				setcolor(4);
				cout << "很抱歉，未能完成当前对操作文件上传任务，请重新上传数据" << endl;
				cout << "感谢您的理解！" << endl;
				setcolor(14);
				cout << "WARNING:请注意控制台是否多次上传操作文件，如果有就是上传成功了！" << endl;
				cout << "WARNING:请注意控制台是否多次上传操作文件，如果有就是上传成功了！" << endl;
				cout << "WARNING:请注意控制台是否多次上传操作文件，如果有就是上传成功了！" << endl;
				setcolor(15);
			 }


			return 0;
			system("pause");
			ftp->Quit();
		}
		break;
	case 2:
			{
				ftplib* ftp = new ftplib();
				e1.connect_error = ftp->Connect("120.26.51.161:21");
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
					e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
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
			}

		break;
	default:
		cout << "error!没有该选项,请重新选择!" << endl;
		break;
	}

}












	
}






//int WINAPI_MANY_PROCESS(string file_box, char file_path[50000], char server_file_path[5000]) {
//	ok1 = 0;
//	ftplib* ftp = new ftplib();
//	e1.connect_error = ftp->Connect("120.26.51.161:21");
//	//ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
//	e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
//	char file_a[256];
//	strcpy(file_a, file_box.c_str());
//	//e1.Mkdir_error = ftp->Mkdir(file_a);
//	e1.Chdir_error = ftp->Chdir(file_a);
//	if (e1.Chdir_error==0)
//	{
//		stop.lock();
//		cout << "线程进入FTP下载文件夹失败" << endl;
//		stop.unlock();
//	}
//
//	for (int i = 0; i < 1; i++)
//	{
//
//		for (int i = 0; i < 2; i++)
//		{
//			if (i < 2 - 1)
//			{
//				printf("\r上传中[%.2lf%%]:", i * 100.0 / (2 - 1));
//
//			}
//			else
//			{
//				printf("\r上传完成[%.2lf%%]:", i * 100.0 / (2 - 1));
//			}
//			int show_num = i * 20 / 2;
//			for (int j = 1; j <= show_num; j++)
//			{
//				setcolor(11);
//				std::cout << "█";
//				setcolor(15);
//				Sleep(1);
//			}
//
//		}
//		std::cout << std::endl;
//		//char file_path[50000] = { 0 };
//		//char server_file_path[5000] = { 0 };
//		//memcpy(server_file_path, server_b[i].c_str(), server_b[i].size());
//		//memcpy(file_path, local_a[i].c_str(), local_a[i].size());
//		//memcpy(file_path, process_number_a[i].c_str(), process_number_a[i].size());
//		//memcpy(server_file_path, process_number_b[i].c_str(), process_number_b[i].size());
//		e1.upload_error = ftp->Put(file_path, server_file_path, ftplib::image);
//		cout << "当前FTP服务器文件夹编号:" << file_P << endl;
//		for (int i = 0; i < 1; i++)
//		{
//			dowsload_numer = dowsload_numer + 1;
//			setcolor(14);
//			cout << "当前上传文件数:" << dowsload_numer << endl;
//			setcolor(3);
//			cout << "本地上传目录文件总数:" << tot << endl;
//			setcolor(15);
//		}
//		cout << "上传的文件名称:" << (const char*)file_path << endl;
//		cout << "上传至服务器目录下名称:" << file_P << "\\" << server_file_path << endl;
//		cout << "远程FTP反馈状态:" << e1.upload_error << endl;
//		//Sleep(1000);
//		if (e1.upload_error)
//		{
//			setcolor(1);
//			cout << "训练数据文件上传成功" << endl;
//			setcolor(2);
//			cout << "本地路径:" << file_path << endl;
//			setcolor(15);
//		}
//		else
//		{
//			setcolor(4);	
//			cout << "文件上传失败!" << endl;
//			setcolor(15);
//		}
//	}
//	ftp->Quit();
//	ok1 = 1;
//	return 0;
//}

//char file_path[5000];
//char server_file_path[5000];


//int 控制模块(string file_P,string str_a[50000], string str_cba[5000]) {
//
//	stop.lock();
//	for (int i = 0; i < tot;)
//	{
//		
//	label: 
//		
//		char file_path[50000] = { 0 };
//		char server_file_path[5000] = { 0 };
//		memcpy(server_file_path, str_cba[i].c_str(), str_cba[i].size());
//		memcpy(file_path, str_a[i].c_str(), str_a[i].size());
//
//		if (ok1)
//		{
//			thread t1(WINAPI_MANY_PROCESS, file_P, file_path, server_file_path);
//			
//			t1.join();
//			i++;
//			goto label;
//		}
//		if (ok2)
//		{
//			thread t2(WINAPI_MANY_PROCESS, file_P, file_path, server_file_path);
//			t2.join();
//			i++;
//			goto label;
//		}
//		
//	} 
//	
//		
//	}


/*
		//for (int i = 0; i < tor; i++)
		//{
		//
		//	for (int i = 0; i < 2; i++)
		//	{
		//		if (i < tot - 1)
		//		{
		//			printf("\r上传中[%.2lf%%]:", i * 100.0 / (2 - 1));
		//
		//
		//		}
		//		else
		//		{
		//			printf("\r上传完成[%.2lf%%]:", i * 100.0 / (2 - 1));
		//		}
		//		int show_num = i * 20 / 2;
		//		for (int j = 1; j <= show_num; j++)
		//		{
		//			setcolor(11);
		//			std::cout << "█";
		//			setcolor(15);
		//			Sleep(1);
		//		}

		//	}
		//	std::cout << std::endl;
		//	char file_path[5000] = { 0 };
		//	char server_file_path[5000] = { 0 };
		//	memcpy(server_file_path, str_cba[i].c_str(), str_cba[i].size());
		//	memcpy(file_path, str_a[i].c_str(), str_a[i].size());
		//	e1.upload_error = ftp->Put((const char*)file_path, server_file_path, ftplib::image);
		//	cout << "当前FTP服务器文件夹编号:" << file_P << endl;
		//	for (int i = 0; i < 1; i++)
		//	{
		//		dowsload_numer = dowsload_numer + 1;
		//		setcolor(14);
		//		cout << "当前上传文件数:" << dowsload_numer << endl;
		//		setcolor(3);
		//		cout << "本地上传目录文件总数:" << tot << endl;
		//		setcolor(15);
		//	}
		//	cout << "上传的文件名称:" << (const char*)file_path << endl;
		//	cout << "上传至服务器目录下名称:" <<file_P<<"\\" << server_file_path << endl;
		//	cout << "远程FTP反馈状态:" << e1.upload_error << endl;
		//	//Sleep(1000);
		//	if (e1.upload_error)
		//	{
		//		setcolor(1);
		//		cout << "训练数据文件上传成功" << endl;
		//		setcolor(2);
		//		cout << "本地路径:" << file_path << endl;
		//		setcolor(15);
		//	}
		//	else
		//	{
		//		setcolor(4);
		//		cout << "文件上传失败!" << endl;
		//		setcolor(15);
		//	}
		//}
		*/