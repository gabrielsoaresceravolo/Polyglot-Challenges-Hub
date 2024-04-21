#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <netinet/in.h>
#include <unistd.h>
#include <cstring>

const int PORT = 8080;
const int MAX_CLIENTS = 5;

std::vector<int> clients;
std::mutex mtx;

void handleClient(int clientSocket) 
{
    char buffer[1024];
    while (true) 
    {
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived <= 0) 
        {
            std::lock_guard<std::mutex> lock(mtx);
            clients.erase(std::remove(clients.begin(), clients.end(), clientSocket), clients.end());
            close(clientSocket);
            break;
        }
        std::lock_guard<std::mutex> lock(mtx);
        for (int client : clients) 
        {
            if (client != clientSocket) 
            {
                send(client, buffer, bytesReceived, 0);
            }
        }
    }
}

int main() 
{
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1) 
    {
        std::cerr << "Erro ao criar o socket do servidor" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
    {
        std::cerr << "Erro ao fazer o bind do socket do servidor" << std::endl;
        return -1;
    }

    if (listen(serverSocket, MAX_CLIENTS) == -1) 
    {
        std::cerr << "Erro ao ouvir as conexões do servidor" << std::endl;
        return -1;
    }

    std::cout << "Servidor aguardando conexões na porta " << PORT << std::endl;

    while (true) 
    {
        sockaddr_in clientAddr;
        socklen_t clientAddrSize = sizeof(clientAddr);
        int clientSocket = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrSize);
        if (clientSocket == -1) {
            std::cerr << "Erro ao aceitar a conexão do cliente" << std::endl;
            continue;
        }

        std::lock_guard<std::mutex> lock(mtx);
        clients.push_back(clientSocket);

        std::thread clientThread(handleClient, clientSocket);
        clientThread.detach(); // Libera a thread para execução independente
    }

    close(serverSocket);
    return 0;
}
