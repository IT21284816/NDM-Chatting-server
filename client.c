#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <unistd.h>

#include <arpa/inet.h>



#define PORT 6001



int main() {

    int client_socket;

    struct sockaddr_in server_address;

    char username[100];

    char password[100];

    char buffer[1024];

    ssize_t bytes_sent, bytes_received;



    // Create socket

    client_socket = socket(AF_INET, SOCK_STREAM, 0);

    if (client_socket == -1) {

        perror("Socket creation failed");

        exit(EXIT_FAILURE);

    }



    // Connect to server

    server_address.sin_family = AF_INET;

    server_address.sin_addr.s_addr = inet_addr("10.0.1.2"); // Change to your server's IP address

    server_address.sin_port = htons(PORT);

    if (connect(client_socket, (struct sockaddr *)&server_address, sizeof(server_address)) == -1) {

        perror("Connection failed");

        exit(EXIT_FAILURE);

    }



    printf("Connected to server. Please register:\n");

    printf("Username: ");

    scanf("%s", username);

    printf("Password: ");

    scanf("%s", password);



    // Send username to server

    bytes_sent = send(client_socket, username, strlen(username), 0);

    if (bytes_sent == -1) {

        perror("Error sending username");

        close(client_socket);

        exit(EXIT_FAILURE);

    }



    // Receive acknowledgement from server

    bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

    if (bytes_received == -1) {

        perror("Error receiving acknowledgement");

        close(client_socket);

        exit(EXIT_FAILURE);

    }

    buffer[bytes_received] = '\0';

    printf("Server: %s\n", buffer);



    // Chat logic - Example: send and receive messages

    while (1) {

        // Send message to server

        printf("You: ");

        fgets(buffer, sizeof(buffer), stdin);

        if (strcmp(buffer, "exit\n") == 0) {

            break;

        }

        bytes_sent = send(client_socket, buffer, strlen(buffer), 0);

        if (bytes_sent == -1) {

            perror("Error sending message");

            close(client_socket);

            exit(EXIT_FAILURE);

        }



        // Receive message from server

        bytes_received = recv(client_socket, buffer, sizeof(buffer), 0);

        if (bytes_received == -1) {

            perror("Error receiving message");

            close(client_socket);

            exit(EXIT_FAILURE);

        }

        buffer[bytes_received] = '\0';

        printf("Server: %s\n", buffer);

    }



    close(client_socket);

    return 0;

}