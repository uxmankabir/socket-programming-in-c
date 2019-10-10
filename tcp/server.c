#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){

        char server_message[2000], client_message[2000];
        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));

        int socket_desc = socket(AF_INET, SOCK_STREAM, 0);
        if (socket_desc < 0){
                perror("Socket Creation Failed ");
                exit(EXIT_FAILURE);
        }
        else{
                perror("Socket Created ");
        }

        struct sockaddr_in server_addr;
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(2000);
        server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

        if (bind(socket_desc, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0){
                perror("Bind Failed ");
                exit(EXIT_FAILURE);
        }
        else{
                perror("Bind Done ");
        }

        if (listen(socket_desc, 1) < 0){
                perror("Listening Failed ");
                exit(EXIT_FAILURE);
        }
        else{
                perror("Listening ");
        }

        struct sockaddr_in client_addr;
        int client_size = sizeof(client_addr);
        int client_sock = accept(socket_desc, (struct sockaddr *)&client_addr, &client_size);

        if (client_sock < 0){
                perror("Accept Failed ");
                exit(EXIT_FAILURE);
        }
        else{
                perror("Client Connected ");
        }

        if (recv(client_sock, client_message, sizeof(client_message), 0) < 0){
                perror("Message Receive Failed ");
                exit(EXIT_FAILURE);
        }

        printf("Client Message: %s\n", client_message);

        strcpy(server_message, client_message);

        if (send(client_sock, server_message, sizeof(server_message), 0) < 0){
                perror("Message Send Failed ");
                exit(EXIT_FAILURE);
        }

        memset(server_message, '\0', sizeof(server_message));
        memset(client_message, '\0', sizeof(client_message));

        close(client_sock);
        close(socket_desc);

        return 0;
}
