#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
using namespace std;

#define PORT 8080 // Defines the port on which the server will listen

int main(int argc, char const *argv[])
{
    int server_fd, new_socket, valread;
    struct sockaddr_in address; // Declaration of a socket structure named address
    int opt = 1; // Option for the setsockopt call
    int addrlen = sizeof(address); // Length of the address
    char buffer[1024] = {0}; // Buffer for incoming data
    const char *hello = "Hello from server"; // Message to send to the client

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) // Creates a socket and checks for errors.
    /*
    * AF_INET: This is the socket domain, specifying the protocol family to be used for network communications. AF_INET indicates the use of the IPv4 protocol.
    * SOCK_STREAM: This is the socket type, specifying the socket communication characteristics. 
    * A value of 0 indicates the use of the default protocol for the specified socket type. 
    */
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) // Sets socket options and checks for errors.
    /*
     * server_fd: This is the file descriptor of the socket to which you want to apply the options.
     * SOL_SOCKET: This is the level at which the option is defined. SOL_SOCKET is used for options that apply to sockets in general, not just to a specific protocol.
     * SO_REUSEADDR | SO_REUSEPORT: These are the specific options you want to set. SO_REUSEADDR allows the socket to use a local address that is currently in use. SO_REUSEPORT allows multiple sockets to listen on the same port, as long as all have set the SO_REUSEPORT option before binding to the port.
     * &opt: This is a pointer to the value of the option. In this case, opt is an integer that has been set to 1, so the option will be enabled.
     * sizeof(opt): This is the length of the option value. Since opt is an integer, the length will be the size of an integer.
    */
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET; // Sets the address type.
    address.sin_addr.s_addr = INADDR_ANY; // Sets the IP address.
    address.sin_port = htons(PORT); // Sets the port.

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) // Binds the socket to the address and checks for errors
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) // Puts the server in listening mode and checks for errors.
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) // Accepts a new connection and checks for errors.
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buffer, 1024); // Reads incoming data.
    cout << "These are the data received from the client: " << buffer << endl; // Prints the received data.
    send(new_socket, hello, strlen(hello), 0); // Sends a message to the client.
    cout << "Hello message sent" << endl;

    return 0;
}
