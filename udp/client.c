#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <arpa/inet.h>

int main(int argc, char *argv[]){
        
        char server_message[2000], client_message[2000];
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        int socket_desc = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
        
        if(socket_desc < 0){
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

        printf("Enter Message: ");
        fgets(client_message, sizeof(client_message), stdin);
        
        int server_struct_size = sizeof(server_addr);
        if(sendto(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*)&server_addr, server_struct_size) < 0){
                perror("Message Send Failed ");
                exit(EXIT_FAILURE);
        }
        
        if(recvfrom(socket_desc, server_message, sizeof(server_message),0, (struct sockaddr*)&server_addr, &server_struct_size) < 0){
                perror("Message Receive Failed ");
                exit(EXIT_FAILURE);
        }
        
        printf("Server Message: %s\n",server_message);
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        close(socket_desc);
        
        return 0;
}
