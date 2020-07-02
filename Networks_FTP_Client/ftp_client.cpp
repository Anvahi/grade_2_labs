#pragma warning(disable: 4996)
#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "Wsock32.lib")
#include <winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <iostream>
#include <sstream>
#define PORT "21"
char ADDR[512] = { 0 };
using namespace std;

SOCKET init_sock();
int readServ(SOCKET s);
SOCKET init_data(SOCKET s);
int login(SOCKET s);
int get(SOCKET s, SOCKET NS, char* file);

int main() {
	SOCKET s;
	SOCKET NS;
	cout << "Enter the IP address of the server: ";
	cin >> ADDR;
	s = init_sock();
	readServ(s);
	login(s);
	cout << "\n> list of supported commands. " << endl;
	send(s, "HELP\r\n", strlen("HELP\r\n"), 0);
	readServ(s);
	int number = 0;
	do {
		cout << "\n\n> selected action: " << endl;
		cout << "\t [1]  -  list of files and folders in the root directory. " << endl;
		cout << "\t [2]  -  list of supported commands. " << endl;
		cout << "\t [3]  -  get help for a specific command. " << endl;
		cout << "\t [4]  -  read file. " << endl;
		cout << "\t [5]  -  exit. " << endl;
		cout << "> your selection: ";
		cin >> number;

		switch (number) {
		case 1: {
			NS = init_data(s);
			cout << "\n> list of files and folders in the root directory. " << endl;
			send(s, "LIST\r\n", strlen("LIST\r\n"), 0);
			readServ(s);
			char buff[2048] = { ' ' };
			recv(NS, buff, 1024, 0);
			cout << buff; ////выводим на экран полученную от сервера строку

		}break;
		case 2: {
			cout << "\n> list of supported commands. " << endl;
			send(s, "HELP\r\n", strlen("HELP\r\n"), 0);
			readServ(s);
		} break;
		case 3: {
			char command[512] = { 0 };
			cout << "\n> get help for a specific command." << endl;
			cout << "enter the command: ";
			cin >> command;
			char buffer[1024] = { 0 };
			strcat(buffer, "HELP ");
			strcat(buffer, command);
			strcat(buffer, "\r\n");

			send(s, buffer, strlen(buffer), 0);
			readServ(s);
		}break;
		case 4: {

			char fileName[256] = "";
			cout << "Name file: ";
			cin >> fileName;
			NS = init_data(s);
			//readServ(s);
			char str[1024];
			sprintf(str, "RETR %s\r\n", fileName);
			send(s, str, strlen(str), 0);
			char buff[2048] = { ' ' };
			recv(NS, buff, 1024, 0);
			cout << buff; ////выводим на экран полученную от сервера строку
		}break;
		case 5: {
			send(s, "QUIT\r\n", strlen("QUIT\r\n"), 0);

		}break;
		}

	} while (number != 5);

	closesocket(s);  ///закрытие соединения
	closesocket(NS);
	return 0;
}

SOCKET init_sock() {
	int len;
	sockaddr_in address;
	WSADATA     wsadata;
	int result;
	SOCKET s;
	WSAStartup(MAKEWORD(2, 2), &wsadata);
	s = socket(AF_INET, SOCK_STREAM, 0);
	memset(&address, 0, sizeof(address));
	address.sin_family = AF_INET;   ///интернет домен
	address.sin_addr.s_addr = inet_addr(ADDR);   ///соединяемся с адресом
	address.sin_port = htons(21);    /// 21 порт
	bind(s, (sockaddr*)&address, sizeof(address));
	len = sizeof(address);
	result = connect(s, (sockaddr*)&address, len);   ///установка соединения
	if (result == -1) {
		perror("oops: client");
		return -1;
	}
	return s;
}

int readServ(SOCKET s) {
	int rc;
	fd_set fdr;
	FD_ZERO(&fdr);
	FD_SET(s, &fdr);
	timeval timeout;
	timeout.tv_sec = 1;   ///зададим  структуру времени со значением 1 сек
	timeout.tv_usec = 0;
	do {
		char buff[2048] = { ' ' };
		recv(s, buff, 2048, 0);   ///получаем данные из потока
		cout << buff;
		rc = select(s, &fdr, NULL, NULL, &timeout);    ///ждём данные для чтения в потоке 1 сек. 
	} while (rc);     ///проверяем результат
	return 2;
}

SOCKET init_data(SOCKET s) {
	send(s, "PASV\r\n", strlen("PASV\r\n"), 0);
	char buff[128] = { ' ' };
	recv(s, buff, 128, 0);
	cout << buff; ////выводим на экран полученную от сервера строку
	int a, b;
	char* tmp_char;
	tmp_char = strtok(buff, "(");
	tmp_char = strtok(NULL, "(");
	tmp_char = strtok(tmp_char, ")");
	int c, d, e, f;
	sscanf(tmp_char, "%d,%d,%d,%d,%d,%d", &c, &d, &e, &f, &a, &b);

	int len;
	sockaddr_in address;
	int result;
	int port = a * 256 + b;

	SOCKET ds = socket(AF_INET, SOCK_STREAM, 0);
	address.sin_family = AF_INET;
	address.sin_addr.s_addr = inet_addr(ADDR);    ///addr - у меня глобальная переменная с адресом сервера
	address.sin_port = htons(port);
	len = sizeof(address);
	result = connect(ds, (sockaddr*)&address, len);
	if (result == -1) {
		perror("oops: client");
		return -1;
	}
	return ds;
}

int login(SOCKET s) {
	cout << "USER "; char name[64]; cin >> name;
	char str[512];
	sprintf(str, "USER %s\r\n", name);
	send(s, str, strlen(str), 0);
	readServ(s);
	cout << "PASS "; char pass[64]; cin >> pass;
	sprintf(str, "PASS %s\r\n", pass);
	send(s, str, strlen(str), 0);
	readServ(s);
	return 0;
}

int get(SOCKET s, SOCKET NS, char* file) {
	char str[1024];
	sprintf(str, "RETR %s\r\n", file);
	send(s, str, strlen(str), 0);

	/* получение размера файла */
	char size[1024];
	recv(s, size, 1024, 0);
	cout << size;

	char* tmp_size;
	tmp_size = strtok(size, "(");
	tmp_size = strtok(NULL, "(");
	tmp_size = strtok(tmp_size, ")");
	tmp_size = strtok(tmp_size, " ");

	char namefilein[1024] = { 0 };
	char namefile[1024] = { 0 };
	for (int i = strlen(file) - 1, j = 0; i > 0; i--, j++)
	{
		if (file[i] == '/' || file[i] == '\\') {
			break;
		}
		namefilein[j] = file[i];

	}
	for (int i = 0, j = strlen(namefilein) - 1; i < strlen(namefilein); i++, j--)
	{
		namefile[i] = namefilein[j];
	}
	int file_size;
	sscanf(tmp_size, "%d", &file_size);
	FILE* f;
	f = fopen(namefile, "wb");   ///важно чтобы файл писался в бинарном режиме
	int read = 0;  ///изначально прочитано 0 байт
	do {
		char buff[2048];   ////буфе для данных
		int readed = recv(NS, buff, sizeof(buff), 0);   ///считываем данные с сервера. из сокета данных
		fwrite(buff, 1, readed, f);   ///записываем считанные данные в файл
		read += readed;  ///увеличиваем количество скачанных данных
	} while (read < file_size);
	fclose(f);
	cout << "OK...\n";
	return 0;
}