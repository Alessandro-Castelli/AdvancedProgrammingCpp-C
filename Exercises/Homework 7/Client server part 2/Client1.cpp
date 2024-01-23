#include <iostream>
#include <vector>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <sstream>
#include <netinet/in.h>
#include <string.h>
#include <vector>
#include <sstream>
using namespace std;

#define PORT 8080


int main(int argc, char const *argv[]) {
    struct sockaddr_in serv_addr;
    int sock = 0, valread;
    char buffer[1024] = {0};

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        cout << "\nError during socket creation\n";
        return -1;
    }

    memset(&serv_addr, '0', sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);

    if (inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr) <= 0) {
        cout << "\nInvalid address / Address not supported\n";
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        cout << "\nConnection failed\n";
        return -1;
    }

    // Send (a,b,c) command to the server

    cout << "Enter the command (a = Matrix Multiplication, b = BubbleSort, c = Sieve of Eratosthenes): ";
    char command[1024];
    cin.getline(command, sizeof(command));
    send(sock, command, strlen(command), 0);

    if ((strcmp(command, "a") == 0) || (strcmp(command, "b") == 0) || (strcmp(command, "c") == 0)) {
        // Send the input's dimension
        cout << "Insert the input dimension: ";

        string input_size;
        getline(cin, input_size);

        // send input
        send(sock, input_size.c_str(), input_size.length(), 0);

        // Receive the response from the server
        string received_data;
        char temp_buffer[1024];
        
        while (true) {
            // Read from the socket into a temporary buffer
            valread = read(sock, temp_buffer, sizeof(temp_buffer) - 1);
            if (valread <= 0) {
                break;  // Terminate the loop if there is no data to read or an error occurs
            }

            // Add the read data to the string buffer
            temp_buffer[valread] = '\0'; 
            received_data += temp_buffer;

            // Check if the terminator has been received
            if (received_data.find('\0') != string::npos) {
                break;
            }
        }

        // Print the results
        cout << "Server result: " << received_data << endl;
}
    return 0;
}

    