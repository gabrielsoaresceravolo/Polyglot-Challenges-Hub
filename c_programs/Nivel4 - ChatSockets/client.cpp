#include <iostream>
#include <cstring>
#include <arpa/inet.h>
#include <unistd.h>

const char* SERVER_IP = "127.0.0.1";
const int PORT = 8080;
const int BUFFER_SIZE = 1024;

int main() 
{
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1) 
    {
        std::cerr << "Erro ao criar o socket do cliente" << std::endl;
        return -1;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    inet_pton(AF_INET, SERVER_IP, &serverAddr.sin_addr);

    if (connect(clientSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == -1) 
    {
        std::cerr << "Erro ao conectar ao servidor" << std::endl;
        return -1;
    }

    std::cout << "Conectado ao servidor. Digite 'sair' para sair." << std::endl;

    while (true) 
    {
        std::string message;
        std::getline(std::cin, message);
        if (message == "sair") 
        {
            break;
        }
        send(clientSocket, message.c_str(), message.size(), 0);

        char buffer[BUFFER_SIZE];
        memset(buffer, 0, sizeof(buffer));
        int bytesReceived = recv(clientSocket, buffer, sizeof(buffer), 0);
        if (bytesReceived == -1) 
        {
            std::cerr << "Erro ao receber mensagem do servidor" << std::endl;
            break;
        }
        std::cout << "Resposta do servidor: " << buffer << std::endl;
    }

    close(clientSocket);
    return 0;
}
