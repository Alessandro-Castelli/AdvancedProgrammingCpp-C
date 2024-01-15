#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <vector>
#include <chrono> 
#include <random> 
#include <omp.h>

using namespace std;

#define PORT 8080
/**The following 7 functions are the same as those used in the previous homework and are essential for performing matrix multiplication, BubbleSort, and the Sieve of Eratosthenes series.*/

vector<vector<int>> makeMatrix(int rows, int columns) {
    
    auto seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 gen(seed);
    uniform_int_distribution<int> distribution(0, 99);

    vector<vector<int>> matrix(rows, vector<int>(columns, 0));
    
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < columns; ++j) {
            matrix[i][j] = distribution(gen);
        }
    }

    return matrix;
}

vector<vector<int>> mulPar(const vector<vector<int>>& MatrixA, const vector<vector<int>>& MatrixB, int t) {

    int r1 = MatrixA.size();
    int c1 = MatrixA[0].size();
    int r2 = MatrixB.size();
    int c2 = MatrixB[0].size();

    vector<vector<int>> result(r1, vector<int>(c2, 0));

    omp_set_num_threads(t);
    #pragma omp parallel for
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
            for (int k = 0; k < c1; ++k) {
                //#pragma omp atomic
                result[i][j] += MatrixA[i][k] * MatrixB[k][j];
            }
        }
    }

    cout << "Number of threads used: " << omp_get_max_threads() << std::endl;
    cout << "Number of processors: " << omp_get_num_procs() << std::endl;
    
    return result;
}

void fillRandomNumbers(vector<int>& arr, int size) {
    for (int i = 0; i < size; ++i) {
        arr.push_back(rand() % 100); 
    }
}

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void exchange(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

void bubbleSortParallel(vector<int>& arr) {
    int n = arr.size();

    for (int k = 0; k < n - 1; k++) {
        if (k % 2 == 0) {
            #pragma omp parallel for
            for (int i = 0; i < n / 2; i++) {
                int index = 2 * i;
                if (index + 1 < n && arr[index] > arr[index + 1]) {
                    #pragma omp critical
                    {
                        exchange(arr[index], arr[index + 1]);
                    }
                }
            }
        } else {
            #pragma omp parallel for
            for (int i = 0; i < n / 2; i++) {
                int index = 2 * i + 1;
                if (index + 1 < n && arr[index] > arr[index + 1]) {
                    #pragma omp critical
                    {
                        exchange(arr[index], arr[index + 1]);
                    }
                }
            }
        }
    }
}

vector<long long int> eratosthenesPar(long long int n) {
    vector<int> prime(n + 1, 1); 
    vector<long long int> result;
    const int end_p = sqrt(n);

    #pragma omp parallel for
    for (int p = 2; p <= end_p; p++) {
        if (prime[p] == 1) {
            for (int i = p * p; i <= n; i += p) {
                prime[i] = 0; 
            }
        }
    }

    for (int p = 2; p <= n; p++) {
        if (prime[p] == 1) {
            result.push_back(p);
        }
    }
    return result;
}


void handle_client(int new_socket) {
    char buffer[1024] = {0};
    int valread = read(new_socket, buffer, 1024);
    string option(buffer);

    if (option == "a") {
        
        cout << "Option A selected." << endl;

        // Read the input dimensions
        valread = read(new_socket, buffer, 1024);
        string input_size(buffer);
        cout << "Input Dimension: " << input_size << std::endl;

        vector<vector<int>> MatrixA = makeMatrix(stoi(input_size), stoi(input_size));
        vector<vector<int>> MatrixB = makeMatrix(stoi(input_size), stoi(input_size));
        vector<vector<int>> result = mulPar(MatrixA, MatrixB, omp_get_max_threads());

        /**
        for (int i = 0; i < result.size(); i++)
        {
            for (int j = 0; j < result.size(); j++)
            {
                cout << result[i][j] << " ";
            }
            cout << endl;
        }
        */

        // Send the resulting matrix to the client.
        for (const auto& row : result) {
            for (int value : row) {
                string cell_value = to_string(value) + " ";
                send(new_socket, cell_value.c_str(), cell_value.length(), 0);
            }
        }

         cout << "The matrix multiplication has been calculated and sent to the client." << endl;

    } else if (option == "b") {
        
        cout << "Option b Selected" << endl;

        // Read the input dimensions
        valread = read(new_socket, buffer, 1024);
        string input_size(buffer);
        cout << "Input dimension: " << input_size << std::endl;
        vector<int> arr;
        fillRandomNumbers(arr, stoi(input_size));  

        cout<<"The vector created to be sorted is: ";
        for (int i = 0; i < arr.size(); i++)
        {
           cout << arr[i]<< " ";
        }
        cout<<endl;
        cout << flush;
    
        bubbleSortParallel(arr);

        cout<<"The sorted vector to be sent to the client is: ";
        for (int i = 0; i < arr.size(); i++)
        {
           cout << arr[i]<< ",";
        }
        cout<<endl;
        cout << flush; 

        string arrString;
        for (int value : arr) {
            arrString += to_string(value) + " ";
        }

        // Send the string representing the vector to the client
        send(new_socket, arrString.c_str(), arrString.length(), 0);

        cout << "The BubbleSort has been calculated and sent to the client." << endl;


    } else if (option == "c") {
        cout << "Option c Selected" << endl;

        // Read the input dimensions
        valread = read(new_socket, buffer, 1024);
        string input_size(buffer);
        cout << "Input dimension: " << input_size << std::endl;

        vector<long long int> res = eratosthenesPar(stoi(input_size));    

        string arrString;
        for (int value : res) {
            arrString += std::to_string(value) + " ";
        }

        // Send the string representing the vector to the client
        send(new_socket, arrString.c_str(), arrString.length(), 0);    
         cout << "The Sieve has been calculated and sent to the client." << endl;

    }
    close(new_socket);
}

int main(int argc, char const *argv[]) {
    int server_fd, new_socket;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT, &opt, sizeof(opt))) {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    while (1) {
        if ((new_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0) {
            perror("accept");
            exit(EXIT_FAILURE);
        }
        thread(handle_client, new_socket).detach();
    }
    return 0;
}
