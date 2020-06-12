#pragma comment(lib, "ws2_32.lib")
#pragma warning(disable : 4996)
#include <Winsock2.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <ctime>
#include <math.h>
#include <string>
#define SERVICE_PORT 1500 
using namespace std;

int send_string(SOCKET s, const char* sString);

int main(void) {
	SOCKET  S;
	SOCKET  NS;
	sockaddr_in serv_addr;
	WSADATA     wsadata;
	char        sName[128];
	bool        bTerminate = false;

	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0) {
		cout << "Error in dll" << endl;
		exit(1);
	}
	gethostname(sName, sizeof(sName));
	cout << endl << "Server host: " << sName << endl;
	if ((S = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
		fprintf(stderr, "Can't create socket\n");
		exit(1);
	}
	memset(&serv_addr, 0, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons((u_short)SERVICE_PORT);
	if (bind(S, (sockaddr*)&serv_addr, sizeof(serv_addr)) == INVALID_SOCKET) {
		fprintf(stderr, "Can't bind\n");
		exit(1);
	}
	if (listen(S, 5) == INVALID_SOCKET) {
		fprintf(stderr, "Can't listen\n");
		exit(1);
	}
	cout << "Server listen on " << inet_ntoa(serv_addr.sin_addr) << ":" << ntohs(serv_addr.sin_port) << endl;
	while (!bTerminate) {
		cout << "Wait for connections.....\n";
		sockaddr_in clnt_addr;
		int addrlen = sizeof(clnt_addr);
		memset(&clnt_addr, 0, sizeof(clnt_addr));
		NS = accept(S, (sockaddr*)&clnt_addr, &addrlen);
		if (NS == INVALID_SOCKET) {
			fprintf(stderr, "Can't accept connection\n");
			break;
		}
		addrlen = sizeof(serv_addr);
		getsockname(NS, (sockaddr*)&serv_addr, &addrlen);
		cout << "Accepted connection on " << inet_ntoa(serv_addr.sin_addr) << ":" << ntohs(serv_addr.sin_port) << " from client " << inet_ntoa(clnt_addr.sin_addr) << ":" << ntohs(clnt_addr.sin_port) << endl;
		send_string(NS, "* * * Welcome to TCP-server * * *\r\n");
		char sReceiveBuffer[1024] = { 0 };
		while (true) {
			int nReaded = recv(NS, sReceiveBuffer, sizeof(sReceiveBuffer) - 1, 0);
			if (nReaded <= 0) 
				break;
			sReceiveBuffer[nReaded] = 0;
			double* arr = new double[5];
			int count = 0;
			for (char* pPtr = sReceiveBuffer; *pPtr != 0; pPtr++) {
				if (*pPtr == '*')
					*pPtr = '\0';
				if (isdigit(*pPtr)) {
					arr[count] = *pPtr;
					arr[count] -= 48;
					count++;
					*pPtr = '\0';
				}
				if (*pPtr == '\n' || *pPtr == '\r') {
					*pPtr = 0;
					break;
				}
			}
			if (sReceiveBuffer[0] == 0) 
				continue;
			printf("Received data: %s\n", sReceiveBuffer);
			if (strcmp(sReceiveBuffer, "log") == 0) {
				string l;
				double k = 0;
				if (count == 1)
					k = log(arr[0]);
				if (count == 2)
					k = log(arr[0] * 10 + arr[1]);
				if (count == 3)
					k = log(arr[0] * 100 + arr[1] * 10 + arr[2]);
				if (count == 4)
					k = log(arr[0] * 1000 + arr[1] * 100 + arr[2] * 10 + arr[3]);
				if (count == 5)
					k = log(arr[0] * 10000 + arr[1] * 1000 + arr[2] * 100 + arr[3] * 10 + arr[4]);
				l = std::to_string(k);
				char *cl = &l[0];
				send_string(NS, "Log ");
				send_string(NS, cl);
				send_string(NS, "\r\n");
			}else if (strcmp(sReceiveBuffer, "info") == 0) {
				send_string(NS, "Khomenkova Polina Ivanovna\r\n");
			} else if (strcmp(sReceiveBuffer, "help") == 0) {
				send_string(NS, "\tinfo\n\ttime\n\tlog*[number]\n\ttask\n\texit\n\tshutdown\n");
			} else if (strcmp(sReceiveBuffer, "time") == 0) {
				time_t now = time(0);
				tm* localtm = localtime(&now);
				send_string(NS, "The local date and time is: ");
				send_string(NS, asctime(localtm));
				send_string(NS, "\r");
			} else if (strcmp(sReceiveBuffer, "task") == 0) {
				send_string(NS, "Variant 22\r\n");
				send_string(NS, "Add support for an additional team to the service,\r\nrealizing the receipt of the logarithm of a number.\r\nInput parameter : number.\r\nServer response : logarithm of a given number.\r\n");
			} else if (strcmp(sReceiveBuffer, "exit") == 0) {
				send_string(NS, "Bye...\r\n");
				printf("Client initialize disconnection.\r\n");
				break;
			} else if (strcmp(sReceiveBuffer, "shutdown") == 0) {
				send_string(NS, "Server go to shutdown.\r\n");
				bTerminate = true;
				break;
			} else {
				char sSendBuffer[1024];
				_snprintf(sSendBuffer, sizeof(sSendBuffer), "Server reply: %s\r\n",
					_strupr(sReceiveBuffer));
				send_string(NS, sSendBuffer);
			}
		}
		closesocket(NS);
		printf("Client disconnected.\n");
	}
	closesocket(S);
	WSACleanup();
	return 0;
}

int send_string(SOCKET s, const char* sString) {
	return send(s, sString, strlen(sString), 0);
}