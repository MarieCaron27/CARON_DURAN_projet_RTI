#include "Socket_lib.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>
#include <iostream>

const int MAX_CONNECTIONS = 5; // Nombre maximal de connexions en attente
const int BUFFER_SIZE = 1024;  // Taille du buffer de réception

// Crée un socket serveur lié à un port donné
int ServerSocket(int port) {
   if ((serverSocket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
	{
	perror("Erreur de socket()");
	exit(1);
	}

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Accepte toutes les connexions
    serverAddr.sin_port = htons(port);

    // Lier le socket à une adresse et un port
    if (bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Erreur de bind()");
        exit(1);
    }

    // Écouter les connexions entrantes
    if (listen(serverSocket, MAX_CONNECTIONS) < 0) {
        perror("Erreur de listen()");
        exit(1);
    }

    return serverSocket;
}

// Accepte une connexion entrante et récupère l'adresse IP du client
int Accept(int sEcoute, char *ipClient) {
    sockaddr_in clientAddr;
    socklen_t clientAddrLen = sizeof(clientAddr);

    if (clientSocket = accept(sEcoute, (struct sockaddr *)&clientAddr, &clientAddrLen) == -1) {
        perror("Erreur de accept()");
        exit(1);
    }

    // Convertit l'adresse IP du client en chaîne de caractères
    inet_ntop(AF_INET, &clientAddr.sin_addr, ipClient, INET_ADDRSTRLEN);
    return clientSocket;
}

// Crée un socket client et se connecte à un serveur
int ClientSocket(const char* ipServeur, int portServeur) {
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket < 0) {
        perror("Erreur de socket()");
        exit(1);
    }

    sockaddr_in serverAddr;
    memset(&serverAddr, 0, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portServeur);

    if (inet_pton(AF_INET, ipServeur, &serverAddr.sin_addr) <= 0) {
        perror("adresse ip invalide");
        close(clientSocket);
        exit(1);
    }

    // Connexion au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("erreur de connect");
        close(clientSocket);
        exit(1);
    }

    return clientSocket;
}

// Envoie des données via un socket
int Send(int sSocket, const char* data, int taille) {
    int bytesSent = send(sSocket, data, taille, 0);
    if (bytesSent < 0) {
        perror("erreur de send");
    	exit(1);
}

// Reçoit des données depuis un socket
int Receive(int sSocket, char* data) {
    char buffer[BUFFER_SIZE];
    memset(buffer, 0, BUFFER_SIZE);
    
    int bytesReceived = recv(sSocket, buffer, BUFFER_SIZE, 0);
    if (bytesReceived < 0) {
        perror("erreur de recv");
        exit(1);
    }

    memcpy(data, buffer, bytesReceived);
    return bytesReceived;
}

// Ferme le socket
void CloseSocket(int sSocket) {
    close(sSocket);
}
