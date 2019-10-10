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
        
        if(bind(socket_desc, (struct sockaddr*)&server_addr, sizeof(server_addr))<0){
                perror("Bind Failed ");
                exit(EXIT_FAILURE);
        }
        else{
                perror("Bind Done ");
        }

        printf("Listening for Messages...\n");
        
        struct sockaddr_in client_addr;
        int client_struct_size = sizeof(client_addr);
        if (recvfrom(socket_desc, client_message, sizeof(client_message), 0, (struct sockaddr*)&client_addr,&client_struct_size) < 0){
                perror("Message Receive Failed ");
                exit(EXIT_FAILURE);
        }
  
        printf("Client Message: %s\n",client_message);
        
        strcpy(server_message, client_message);
        
        if (sendto(socket_desc, server_message, sizeof(server_message), 0, (struct sockaddr*)&client_addr,client_struct_size)<0){
                perror("Message Send Failed ");
                exit(EXIT_FAILURE);
        }
        
        memset(server_message,'\0',sizeof(server_message));
        memset(client_message,'\0',sizeof(client_message));
        
        close(socket_desc);
        return 0;       
}
