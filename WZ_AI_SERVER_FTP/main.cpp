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
//ȫ�ֱ�����
int tot = 0;
int tor = 0;
int ok1 = 1;
int ok2 = 1;

//SOCKETȫ�ֱ�����
int server_say = 0;
int client_say = 0;

const  int size_b = 1024; // ����MB�ļ��㳣��

FtpCallbackXfer pointer;
char path[] = "ģ��_�����ݶ�_��N3";      //FTP�����������ļ�
//char load_file[] = "..\\weights\\ģ��_�����ݶ�_��N1";
char path_name[] = "ģ��_�����ݶ�_��N3";
char load_file[] = "ģ��_�����ݶ�_��N3";
char day[] = { NULL };





string �жϿ���;

struct message
{
	int connect_error;	//����
	int login_error;		//��¼
	int upload_error;	//����ļ��ϴ�״̬
	int Mkdir_error;	//����FTP����Ŀ¼
	int Chdir_error;	//�л��ļ��д�С
	int Get_error;   //���غ���
	int RawOpen_error; 
	int Size; //ȷ��ȫ���ļ���С
	int ModDate; //������������
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
		//              printf("%c", chr[idx]);//�ַ����
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


int ����ģ��(string file_P, string str_a[50000], string str_cba[5000]);

int dowsload_numer = 0;



typedef struct
{
	string file;
	string A;
	string B;
}TEMP;
TEMP temp;

mutex mu;//�̻߳������



void threadPool(TEMP data)
{
	mu.lock(); //ͬ�������� 
	std::this_thread::sleep_for(std::chrono::milliseconds(1));
	//cout << "·��:" << data.A << endl;
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
		cout << "�߳̽���FTP�����ļ���ʧ��" << endl;	
	}

	for (int i = 0; i < 1; i++)
	{

		for (int i = 0; i < 2; i++)
		{
			if (i < 2 - 1)
			{
				printf("\r�ϴ���[%.2lf%%]:", i * 100.0 / (2 - 1));

			}
			else
			{
				printf("\r�ϴ����[%.2lf%%]:", i * 100.0 / (2 - 1));
			}
			int show_num = i * 20 / 2;
			for (int j = 1; j <= show_num; j++)
			{
				setcolor(11);
				std::cout << "��";
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
		cout << "��ǰFTP�������ļ��б��:" << data.file << endl;
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
		cout << "�ϴ���������Ŀ¼������:" << data.file << "<--" << server_file_path << endl;
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
	ftp->Quit();
	mu.unlock();//�������  
}

int main()
{
	int menu = 1;
	while (menu!=0)
	{		
			setcolor(4);
			cout << ">>>>>>��ӭʹ������AIѵ�����ݹ���ƽ̨<<<<<<" << endl;
			setcolor(9);
			cout << "               �˵��б�                                 " << endl;
			cout << "ѡ��1:      ѵ���ļ��ϴ�                            " << endl;
			cout << "ѡ��2:     ѵ��ģ���ļ�����                            " << endl;
			cout << "ѡ��3:     AI�����ļ�����                            " << endl;
			cout << "ѡ��4:     ����ȫ�Զ��ű�                              " << endl;
			cout << "ѡ��5:      ѵ���ļ��ϴ�+����ȫ�Զ��ű�      " << endl;
			setcolor(2);
			cout << "ѡ��6:      ��ѯAI������ϸ���                    " << endl;
			setcolor(9);
			cout << "ѡ��0:         �˳�����                                " << endl;
			setcolor(4);
			cout << ">>>>>>��ӭʹ������AIѵ�����ݹ���ƽ̨<<<<<<" << endl;
			setcolor(15);
			cout << "��������Ҫִ�еĹ��ܱ��:";
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
		e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
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
		cout << "���ڼ�������ļ�........." << endl;
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
		file_P = password();
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
			exit(0);
		}
		cout << "���ڶ�ȡ�����ļ�" << endl;
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
				str_cba[tot++] = str_abc;//�ϴ��ļ�·��
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
						str_a[tor++] = str;//�����ϴ��ļ�·��
				}
			}
			ifs.close();
			int length = 0;
			while (length < tor)
			{
				std::thread threadID[10];
				int i;
				for (i = 0; i < 10; i++, length++)//�����̳߳�
				{
					if (length == tor)break;
					temp.file = file_P;
					temp.A = str_a[length];
					temp.B = str_cba[length];
					threadID[i] = std::thread(threadPool, temp);//�������
				}
				for (int x = 0; x < i; x++)
					threadID[x].join();
				}
			setcolor(2);
			cout << "[��Ϣ]:����ѵ��ͼƬ�Գɹ��ϴ�FTP������!" << endl;
			cout << "[��Ϣ]:���������ϴ�";
			setcolor(13);
			cout << "�����ļ�";
			setcolor(2);
			cout << "........." << endl;
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
				path_massage = path_zero + path_add_name;
			}
			ifrzs.close();
			strcpy(karl, path_massage.c_str());
			strcpy(karl_name, aaa_name.c_str());
			e1.upload_error = ftp->Put(karl, karl_name, ftplib::image);
			if (e1.upload_error)
			{
			setcolor(2);
			cout << "��л�ȴ�!��ǰ����ɶ������ļ��ϴ�����" << endl;
			setcolor(15);
			}
			 else
			 {
				setcolor(4);
				cout << "�ܱ�Ǹ��δ����ɵ�ǰ�Բ����ļ��ϴ������������ϴ�����" << endl;
				cout << "��л������⣡" << endl;
				setcolor(14);
				cout << "WARNING:��ע�����̨�Ƿ����ϴ������ļ�������о����ϴ��ɹ��ˣ�" << endl;
				cout << "WARNING:��ע�����̨�Ƿ����ϴ������ļ�������о����ϴ��ɹ��ˣ�" << endl;
				cout << "WARNING:��ע�����̨�Ƿ����ϴ������ļ�������о����ϴ��ɹ��ˣ�" << endl;
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
					cout << "����FTP������         [�ɹ�]" << endl;
					setcolor(15);
				}
				else
				{
					setcolor(4);
					cout << "����FTP������ʧ��    [ʧ��]" << endl;
					setcolor(15);
				}
					e1.login_error = ftp->Login("WZ_AI_USER", "b*qaK0BJSmeVPvi");
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
				int value = 0;
				int* file_size = &value;
				//cout << &file_size << endl;
				e1.Size = ftp->Size(path,file_size, ftplib::image);
				if (e1.Size)
				{
					cout << "��Ҫ���ص�ģ���ļ���СΪ:" << (double)*file_size/size_b/size_b <<"MB" << endl;
				}
				else
				{
					cout << "��ѯ�����ļ���Сʧ��,���Ժ���!" << endl;
				}
				e1.ModDate = ftp->ModDate(path,day,50);
				if (e1.ModDate)
					cout << "ѵ��ģ������������:" << day << endl;
				else{
					cout << "�޷���ȡģ������������!" << endl;
					break;
				}
				cout << "�Ƿ��������ѵ��ģ��?(y/n)" << endl;
				cin >> �жϿ���;
				if (�жϿ��� == "y")
				{
					cout << "��ʼ����ģ���ļ�" << endl;
				}
				else
				{
					cout << "�����˳�!" << endl;
					break;
				}
				e1.Get_error = ftp->Get(load_file, path_name, ftplib::image);			
				if (e1.Get_error)
				{
					cout << "�������! �ļ������ͬ��Ŀ¼��" << endl;
					cout << "�ļ�����:ģ��_�����ݶ�_��N3" << endl;
				}
				else
				{
					cout << "����ʧ��!���Ժ�����" << endl;
				}			
			}

		break;
		case 3:
		{
			cout << "��ȷ����Ҫ���صĻ���ѡ��:" << endl;
			cout << "1.Anaconda3-2021.05-Windows-x86_64.exe" << endl;
			cout << "2.PyCharm 2021.1.2 IDE(����ͨ��ѡ��6��ȡ������Կ)" << endl;
			cout << "CUDA 11.1" << endl;
			cout << "3.����AI����(pytorch��Ӧ�汾��CUDA:11.1)" << endl;
			cout << "++++++++++++++++++++++++++++++++++" << endl;
		
		}
	break;

		case 4:
		{
			  
				 //�����ս
				cout << "�����ս" << endl;
				system("adb shell input tap 877 806");
			  //ѡ��5V5
				cout << "ѡ��5V5ģʽ" << endl;
				system("adb shell input tap 423 596");
				//ѡ���˻�
				cout << "ѡ���˻���" << endl;
				system("adb shell input tap 1168 549");
				//ѡ���˻��Ѷ�
				cout << "ѡ���˻��Ѷ�" << endl;
				system("adb shell input tap 1180 421");
				//��ʼȷ��
				cout << "��ʼȷ��" << endl;
				system("adb shell input tap 1770 843");
				//��ʼ���б���ѡ�����
				cout << "��ʼ���б���ѡ�����" << endl;
				Sleep(200);
				system("adb shell input swipe  148 755 154  86 2000");
				Sleep(1000);
				system("adb shell input swipe  148 755 154  86 2000");
				Sleep(1000);
				system("adb shell input swipe  148 755 154  86 2000");
				Sleep(1000);
				//ѡ�����
				cout << "ѡ�����" << endl;
				system("adb shell input tap 43 993");
				cout << "���ڽ���һ��ȷ��" << endl;
				system("adb shell input tap 1993 1041");
				cout << "���ж���ȷ��" << endl;
				system("adb shell input tap 1993 1041");
				cout << "����������Զ�����!" << endl;
		}
		break;
		case 5:
		{
			setcolor(4);
			cout << "��Ǹ!�����Ϳ����Ŷӵ�ԭ�򣬴˹�����δ����!" << endl;
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
					cout << "����������ʧ��!" << endl;
					//WSACleanup();
				}
				else
				{
					cout << "���ӷ������ɹ�!" << endl;
				}
				char szBuffer[MAXBYTE] = { 0 };
				bool server_socket_clock="�ر�����";
				bool server_off = "�ر�����";
				while (szBuffer != 0)
				{
					server_say = recv(socket, szBuffer, MAXBYTE, NULL);
					if (server_say < 0)
					{
						setcolor(4);
						cout << "����AI���������ն�����ʧ��!" << endl;
						cout << "����������!" << endl;
						setcolor(15);
						break;
					}
					setcolor(2);
					cout << "����AIѵ���������ĵĻظ�:" << szBuffer << endl;
					setcolor(14);
					cout << "��:";
					cin >> szBuffer;
					client_say = send(socket, szBuffer, strlen(szBuffer)+sizeof(char),NULL);
					if (client_say<0)
					{
						setcolor(4);
						cout << "������Ϣ��AIѵ����������ʧ�ܣ�" << endl;
						cout << "����������!" << endl;
						setcolor(15);
						break;
					}
				}
				




				
				closesocket(socket);
				WSACleanup();
			}
			break;
	default:
		cout << "error!û�и�ѡ��,������ѡ��!" << endl;
		break;
	}

}


 system("pause");
}



