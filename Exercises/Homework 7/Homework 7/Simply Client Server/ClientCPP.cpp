#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
using namespace std;

#define PORT 8080

int main(int argc, char const *argv[])
{
    struct sockaddr_in serv_addr;
    int sock = 0, valread;
    char *hello = "Hello from client";
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        cout << "\n Socket creation error \n";
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0)
    {
        cout << "\nInvalid address/ Address not supported\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
        cout << "\nConnection Failed\n";
        return -1;
    }

    send(sock, hello, strlen(hello), 0);
    cout << "Hello message sent" << endl;
    
    valread = read(sock, buffer, 1024);
    cout << "Hello message received: " << buffer<<endl;

    return 0;
}
