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

//ȫ�ֱ�����
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
		//              printf("%c", chr[idx]);//�ַ����
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
bool PoolFlag = true;//true =���� false=ֹͣ  ������ ���Ҫ���  flase
int length = 0;
void threadPool(TEMP data)
{
	mu.lock(); //ͬ�������� 
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
		//memcpy(file_path, process_number_a[i].c_str(), process_number_a[i].size());
		//memcpy(server_file_path, process_number_b[i].c_str(), process_number_b[i].size());
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
			cout << "ѡ��3:     ����ȫ�Զ��ű�                              " << endl;
			cout << "ѡ��0:         �˳�����                                " << endl;
			setcolor(4);
			cout << ">>>>>>��ӭʹ������AIѵ�����ݹ���ƽ̨<<<<<<" << endl;
			setcolor(15);
			cout << "��������Ҫִ�еĹ��ܱ��:";
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
		while (getline(ifrs, str_abc, '\n')) {
			for (int i = 0; i < 1; i++)
			{
				str_cba[tot++] = str_abc;//�������ļ�����
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
				str_a[tor++] = str;//�����ϴ��ļ�·��
			}
		}
		ifs.close();

		length = 0;
		while (PoolFlag)
		{
			std::thread threadID[10];
			for (int i = 0; i < 10; i++)//�����̳߳�
			{
				temp.file = file_P;
				temp.A = str_a[length];
				temp.B = str_cba[length];
				threadID[i] = std::thread(threadPool, temp);//�������

				if (length < tot)length++;
				else PoolFlag = false;//	PoolFlag = false;
			}
			for (auto& t : threadID)
				t.join();
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
			}

		break;
	default:
		cout << "error!û�и�ѡ��,������ѡ��!" << endl;
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
//		cout << "�߳̽���FTP�����ļ���ʧ��" << endl;
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
//				printf("\r�ϴ���[%.2lf%%]:", i * 100.0 / (2 - 1));
//
//			}
//			else
//			{
//				printf("\r�ϴ����[%.2lf%%]:", i * 100.0 / (2 - 1));
//			}
//			int show_num = i * 20 / 2;
//			for (int j = 1; j <= show_num; j++)
//			{
//				setcolor(11);
//				std::cout << "��";
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
//		cout << "��ǰFTP�������ļ��б��:" << file_P << endl;
//		for (int i = 0; i < 1; i++)
//		{
//			dowsload_numer = dowsload_numer + 1;
//			setcolor(14);
//			cout << "��ǰ�ϴ��ļ���:" << dowsload_numer << endl;
//			setcolor(3);
//			cout << "�����ϴ�Ŀ¼�ļ�����:" << tot << endl;
//			setcolor(15);
//		}
//		cout << "�ϴ����ļ�����:" << (const char*)file_path << endl;
//		cout << "�ϴ���������Ŀ¼������:" << file_P << "\\" << server_file_path << endl;
//		cout << "Զ��FTP����״̬:" << e1.upload_error << endl;
//		//Sleep(1000);
//		if (e1.upload_error)
//		{
//			setcolor(1);
//			cout << "ѵ�������ļ��ϴ��ɹ�" << endl;
//			setcolor(2);
//			cout << "����·��:" << file_path << endl;
//			setcolor(15);
//		}
//		else
//		{
//			setcolor(4);	
//			cout << "�ļ��ϴ�ʧ��!" << endl;
//			setcolor(15);
//		}
//	}
//	ftp->Quit();
//	ok1 = 1;
//	return 0;
//}

//char file_path[5000];
//char server_file_path[5000];


//int ����ģ��(string file_P,string str_a[50000], string str_cba[5000]) {
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
		//			printf("\r�ϴ���[%.2lf%%]:", i * 100.0 / (2 - 1));
		//
		//
		//		}
		//		else
		//		{
		//			printf("\r�ϴ����[%.2lf%%]:", i * 100.0 / (2 - 1));
		//		}
		//		int show_num = i * 20 / 2;
		//		for (int j = 1; j <= show_num; j++)
		//		{
		//			setcolor(11);
		//			std::cout << "��";
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
		//	cout << "��ǰFTP�������ļ��б��:" << file_P << endl;
		//	for (int i = 0; i < 1; i++)
		//	{
		//		dowsload_numer = dowsload_numer + 1;
		//		setcolor(14);
		//		cout << "��ǰ�ϴ��ļ���:" << dowsload_numer << endl;
		//		setcolor(3);
		//		cout << "�����ϴ�Ŀ¼�ļ�����:" << tot << endl;
		//		setcolor(15);
		//	}
		//	cout << "�ϴ����ļ�����:" << (const char*)file_path << endl;
		//	cout << "�ϴ���������Ŀ¼������:" <<file_P<<"\\" << server_file_path << endl;
		//	cout << "Զ��FTP����״̬:" << e1.upload_error << endl;
		//	//Sleep(1000);
		//	if (e1.upload_error)
		//	{
		//		setcolor(1);
		//		cout << "ѵ�������ļ��ϴ��ɹ�" << endl;
		//		setcolor(2);
		//		cout << "����·��:" << file_path << endl;
		//		setcolor(15);
		//	}
		//	else
		//	{
		//		setcolor(4);
		//		cout << "�ļ��ϴ�ʧ��!" << endl;
		//		setcolor(15);
		//	}
		//}
		*/