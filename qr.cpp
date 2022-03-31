#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

int main()
{

    int sock = socket(AF_INET, SOCK_STREAM, 0);

    if (sock < 0)
    {
        cout << "! [UNABLE TO CREATE SOCKET]\n";
        return -1;
    }
    else
    {
        cout << ":) [SOCKET CREATED]\n";
    }

    struct sockaddr_in qr = {'\0', AF_INET, htons(80), {inet_addr("5.9.243.188")}};

    if (connect(sock, (struct sockaddr *)&qr, sizeof(qr)) < 0)
    {
        cout << "! [UNABLE TO CONNECT WITH SERVER]\n";
        return -1;
    }
    else
    {
        cout << ":) [CONNECTED WITH SERVER]\n";
    }

    string base_request = "GET /";
    string data;
    cin >> data;
    base_request = base_request + data + " HTTP/1.1\r\nHost:qrenco.de\r\nUser-Agent:curl/7.35.0\r\n\r\n";
    cout << base_request;
    send(sock, &base_request[0], base_request.length(), 0);

    char response[20480];
    recv(sock, &response[0], 20480, 0);
    cout << response << "\n";

    close(sock);
    return 0;
}
