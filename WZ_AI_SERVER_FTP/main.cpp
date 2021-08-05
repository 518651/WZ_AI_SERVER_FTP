#include <iostream>
#include <thread>
#include <chrono>
#include <stdio.h>
#include <fstream>
#include <string>
//#include <Windows.h>
#include <stdlib.h>
#include <WinSock2.h>
#include <future>
#include <ctime>
#include "ftplib.h"


using namespace std;
#pragma warning(disable :4996)
#pragma comment(lib,"ws2_32.lib")


ifstream ifs;
ftplib* ftp = new ftplib();
//全局变量区
int tot = 0;
int tor = 0;
int ok1 = 1;
int ok2 = 1;

//SOCKET全局变量区
int server_say = 0;
int client_say = 0;

const  int size_b = 1024; // 定义MB的计算常量

FtpCallbackXfer pointer;
char path[] = "模型_策略梯度_丙N3";      //FTP服务器下载文件
//char load_file[] = "..\\weights\\模型_策略梯度_丙N1";
char path_name[] = "模型_策略梯度_丙N3";
char load_file[] = "模型_策略梯度_丙N3";
char day[] = { NULL };





string 判断开关;

struct message
{
	int connect_error;	//连接
	int login_error;		//登录
	int upload_error;	//检测文件上传状态
	int Mkdir_error;	//创建FTP下载目录
	int Chdir_error;	//切换文件夹大小
	int Get_error;   //下载函数
	int RawOpen_error; 
	int Size; //确认全程文件大小
	int ModDate; //文最后访问日期
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



void threadPool(TEMP data)
{
	mu.lock(); //同步数据锁 
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//cout << "路径:" << data.A << endl;
	ftplib* ftp = new ftplib();
	e1.connect_error = ftp->Connect("120.26.51.161:21");
	ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
	char file_a[256];
	strcpy(file_a, data.file.c_str());
	e1.Mkdir_error = ftp->Mkdir(file_a);
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
	//	memcpy(file_path, process_number_a[i].c_str(), process_number_a[i].size());
	//	memcpy(server_file_path, process_number_b[i].c_str(), process_number_b[i].size());
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
			cout << "选择3:     AI环境文件下载                            " << endl;
			cout << "选择4:     启动全自动脚本                              " << endl;
			cout << "选择5:      训练文件上传+启动全自动脚本      " << endl;
			setcolor(2);
			cout << "选择6:      查询AI工程详细情况                    " << endl;
			setcolor(9);
			cout << "选择0:         退出程序                                " << endl;
			setcolor(4);
			cout << ">>>>>>欢迎使用王者AI训练数据共享平台<<<<<<" << endl;
			setcolor(15);
			cout << "请输入你要执行的功能编号:";
	cin >> menu;
		switch (menu)
		{
		case 1:
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
		if (ifrs.is_open())
		{
			while (getline(ifrs, str_abc))
			{
				if (ifrs.eof() || str_abc.size() == 0)break;
				str_cba[tot++] = str_abc;//上传文件路径
			}
		}

		ifrs.close();

			//int tor = 0;
			string str;
			string str_a[50000];
			ifstream ifs("WZ_AI_config.txt", ios::in);
			if (ifs.is_open())
			{
				while (getline(ifs, str))
				{
						if (ifs.eof() || str.size() == 0)break;
						str_a[tor++] = str;//本地上传文件路径
				}
			}
			ifs.close();
			int length = 0;
			while (length < tor)
			{
				std::thread threadID[10];
				int i;
				for (i = 0; i < 10; i++, length++)//创建线程池
				{
					if (length == tor)break;
					temp.file = file_P;
					temp.A = str_a[length];
					temp.B = str_cba[length];
					threadID[i] = std::thread(threadPool, temp);//后面参数
				}
				for (int x = 0; x < i; x++)
					threadID[x].join();
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
			
			ftp->Quit();
			system("pause");
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
				int value = 0;
				int* file_size = &value;
				//cout << &file_size << endl;
				e1.Size = ftp->Size(path,file_size, ftplib::image);
				if (e1.Size)
				{
					cout << "需要下载的模型文件大小为:" << (double)*file_size/size_b/size_b <<"MB" << endl;
				}
				else
				{
					cout << "查询下载文件大小失败,请稍后尝试!" << endl;
				}
				e1.ModDate = ftp->ModDate(path,day,50);
				if (e1.ModDate)
					cout << "训练模型最后更新日期:" << day << endl;
				else{
					cout << "无法获取模型最后更新日期!" << endl;
					break;
				}
				cout << "是否进续下载训练模型?(y/n)" << endl;
				cin >> 判断开关;
				if (判断开关 == "y")
				{
					cout << "开始下载模型文件" << endl;
				}
				else
				{
					cout << "正在退出!" << endl;
					break;
				}
				e1.Get_error = ftp->Get(load_file, path_name, ftplib::image);			
				if (e1.Get_error)
				{
					cout << "下载完成! 文件存放于同级目录！" << endl;
					cout << "文件名称:模型_策略梯度_丙N3" << endl;
				}
				else
				{
					cout << "下载失败!请稍后重试" << endl;
				}			
			}

		break;
		case 3:
		{
			cout << "请确认您要下载的环境选项:" << endl;
			cout << "1.Anaconda3-2021.05-Windows-x86_64.exe" << endl;
			cout << "2.PyCharm 2021.1.2 IDE(可以通过选项6获取激活秘钥)" << endl;
			cout << "CUDA 11.1" << endl;
			cout << "3.王者AI环境(pytorch对应版本的CUDA:11.1)" << endl;
			cout << "++++++++++++++++++++++++++++++++++" << endl;
		
		}
	break;

		case 4:
		{
			  
				 //进入对战
				cout << "进入对战" << endl;
				system("adb shell input tap 877 806");
			  //选择5V5
				cout << "选择5V5模式" << endl;
				system("adb shell input tap 423 596");
				//选择人机
				cout << "选择人机房" << endl;
				system("adb shell input tap 1168 549");
				//选择人机难度
				cout << "选择人机难度" << endl;
				system("adb shell input tap 1180 421");
				//开始确认
				cout << "开始确认" << endl;
				system("adb shell input tap 1770 843");
				//开始从列表中选择后羿
				cout << "开始从列表中选择后羿" << endl;
				Sleep(200);
				system("adb shell input swipe  148 755 154  86 2000");
				Sleep(1000);
				system("adb shell input swipe  148 755 154  86 2000");
				Sleep(1000);
				system("adb shell input swipe  148 755 154  86 2000");
				Sleep(1000);
				//选择后羿
				cout << "选择后羿" << endl;
				system("adb shell input tap 43 993");
				cout << "正在进行一次确认" << endl;
				system("adb shell input tap 1993 1041");
				cout << "进行二次确认" << endl;
				system("adb shell input tap 1993 1041");
				cout << "程序已完成自动开局!" << endl;
		}
		break;
		case 5:
		{
			setcolor(4);
			cout << "抱歉!因技术和开发团队等原因，此功能暂未开放!" << endl;
			setcolor(15);
		}
		break;
		case 6:
			{
				WSADATA chushihua;
				WSAStartup(MAKEWORD(2, 2), &chushihua);
				SOCKET socket=(PF_INET, SOCK_STREAM, IPPROTO_TCP);
				sockaddr_in socket_addr;
				memset(&socket_addr, 0, sizeof(socket_addr));
				socket_addr.sin_family = PF_INET; 
				socket_addr.sin_addr.s_addr = inet_addr("120.26.51.161");
				socket_addr.sin_port = htons(1200);
				if (connect(socket, (SOCKADDR*)&socket_addr, sizeof(SOCKADDR))==SOCKET_ERROR)
				{
					cout << "服务器连接失败!" << endl;
					//WSACleanup();
				}
				else
				{
					cout << "连接服务器成功!" << endl;
				}
				char szBuffer[MAXBYTE] = { 0 };
				bool server_socket_clock="关闭连接";
				bool server_off = "关闭连接";
				while (szBuffer != 0)
				{
					server_say = recv(socket, szBuffer, MAXBYTE, NULL);
					if (server_say < 0)
					{
						setcolor(4);
						cout << "接收AI数据中心终端数据失败!" << endl;
						cout << "请重新连接!" << endl;
						setcolor(15);
						break;
					}
					setcolor(2);
					cout << "来自AI训练数据中心的回复:" << szBuffer << endl;
					setcolor(14);
					cout << "您:";
					cin >> szBuffer;
					client_say = send(socket, szBuffer, strlen(szBuffer)+sizeof(char),NULL);
					if (client_say<0)
					{
						setcolor(4);
						cout << "发送信息至AI训练数据中心失败！" << endl;
						cout << "请重新连接!" << endl;
						setcolor(15);
						break;
					}
				}
				




				
				closesocket(socket);
				WSACleanup();
			}
			break;
	default:
		cout << "error!没有该选项,请重新选择!" << endl;
		break;
	}

}


 system("pause");
}



