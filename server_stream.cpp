#include <iostream>
#include <pthread.h>
#include "Common.hpp"
#include "Transactional_Commands.hpp"
#include "Helper.hpp"
#include "Interface.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;



/*
 
 struct sockaddr_in {
 short            sin_family;   // e.g. AF_INET
 unsigned short   sin_port;     // e.g. htons(3490)
 struct in_addr   sin_addr;     // see struct in_addr, below
 char             sin_zero[8];  // zero this if you want to
 };
 
 struct in_addr {
 unsigned long s_addr;  // load with inet_aton()
 };
 */

Interface i;

void terminate_with_error (const char * error_msg,int sock)
{
    perror("Error Binding Socket:");
    if (sock != -1)
    {
        close (sock);
        exit(1);
    }
}

void setupServer(int& sock)
{
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) terminate_with_error("Error Creating Socket",sock);
    cout << "\nSocket server has been created..." << endl;
}

void *connection_handler(void *sock) // works with mac
//void *connection_handler(void *sock)
{
    // // Get the socket descriptor
    int newsock = *(int*)sock;
    // int read_size;
    // char *message, client_message[2000];
    // // Send some messages to the client
    // // message = "Greetings! I am your connection handler\n";
    // // write(sock, message, strlen(message));
    // // message = "Now type something and i shall repeat what you type \n";
    // // write(sock, message, strlen(message));
    // // Receive a message from client
    // while( (read_size = recv(sock, client_message, 2000, 0)) > 0 )  {
    // 	// end of string marker
    // 	client_message[read_size] = '\0';
    // 	// Send the message back to client
    // 	write(sock, client_message, strlen(client_message));
    // 	// clear the message buffer
    // 	memset(client_message, 0, 2000);
    // }
    // if(read_size == 0) {
    // 	puts("Client disconnected");
    // 	fflush(stdout);
    // }
    // else if(read_size == -1) {
    // 	perror("recv failed");
    // }
    // return 0;
    cout << "Client Connected" << endl;
    int maxBytes = 1024;
    char buffer[maxBytes];
    memset(buffer,0,maxBytes);
    string s;
    const char* c;
    // strcpy(buffer, "Connected to the server\n");
    // // print "Connected to the server"
    //       send(newsock, buffer, maxBytes, 0);
    //       memset(buffer,0,maxBytes);
    //       string s = i.start();
    //       const char* c = s.c_str();
    // strcpy(buffer, c);
    // // print startup message
    //       send(newsock, buffer, maxBytes, 0);
    bool stop = false;
    int bytes_read;
    bool newClient = true;
    while ( !stop )
    {
        // print welcome messages for new client connections
        if ( newClient )
        {
            strcpy(buffer, "Connected to the server\n");
            // print "Connected to the server"
            send(newsock, buffer, maxBytes, 0);
            memset(buffer,0,maxBytes);
            // print welcome message
            s = i.start();
            c = s.c_str();
            strcpy(buffer, c);
            send(newsock, buffer, maxBytes, 0);
            newClient = false;
        }
        memset(buffer,0,maxBytes);
        s = i.display();
        c = s.c_str();
        strcpy(buffer, c);
        // print interface display
        send(newsock, buffer, maxBytes, 0);
        memset(buffer,0,maxBytes);
        bytes_read = recv (newsock,buffer,maxBytes,0);
        if ( toupper(*buffer) == 'Q' )
        {
            stop = true;
            cout << "Client disconnected.\n";
            i.clientInput(buffer);
            strcpy(buffer, "Disconnected.\n");
            send(newsock,buffer,maxBytes,0);
            close(newsock);
        }
        else
        {
            // if ( bytes_read > 0 ) printf ("Received Message from %s:%d\n%s\n",(char *)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port,buffer);
            if ( bytes_read > 0 )
            {
                // printf ("Received Message from %s:%d\n%s\n",(char *)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port,buffer);
                cout << "\n----------------------------------------\n";
                printf ("Received Message: %s\n",buffer);
                s = i.clientInput(buffer);
                c = s.c_str();
                memset(buffer,0,maxBytes);
                strcpy(buffer, c);
                send(newsock, buffer, maxBytes, 0);
            }
            else
            {
                stop = true;
                perror("Error Receiving Message:");
            }
        }
    }
    return nullptr;
}

int main (int argc,char ** argv)
{
    // Interface i;
    static int sock;
    static int portNum = 9999;
    struct sockaddr_in serverAddr;
    struct sockaddr_in clientAddr;
    socklen_t sin_size = sizeof(struct sockaddr_in);
    setupServer(sock);
    
    int sock_opt = 1;
    setsockopt(sock,SOL_SOCKET,SO_REUSEADDR,(void *)&sock_opt,sizeof (sock_opt));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(portNum);
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(serverAddr.sin_zero), 8);
//        if (bind(sock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1) terminate_with_error("Error Binding",sock);
    if (::bind(sock, (struct sockaddr *)&serverAddr, sizeof(struct sockaddr)) == -1) terminate_with_error("Error Binding",sock); // works with mac
    cout << "Looking for clients..." << endl;
    // while(true)
    // {
    if (listen(sock, 10) == -1) terminate_with_error("Error Listening: ",sock);
    int newsock;
    pthread_t thread_id;
    while((newsock = accept(sock, (struct sockaddr *)&clientAddr, &sin_size))) {
        cout << "Connection accepted\n";
        if(pthread_create(&thread_id, NULL,  connection_handler, (void*) &newsock) < 0) {
            perror("could not create thread");
            return 1	;
        }
    }
    
    // int newsock = accept(sock, (struct sockaddr *)&clientAddr,&sin_size);
    // if ( newsock < 1 ) terminate_with_error("Error Accepting Socket",0);
    // else
    // {
    // 	cout << "Client Connected" << endl;
    // 	int maxBytes = 1024;
    // 	char buffer[maxBytes];
    // 	memset(buffer,0,maxBytes);
    // 	strcpy(buffer, "Server connected...\n");
    //        send(newsock, buffer, maxBytes, 0);
    //        bool stop = false;
    //        while ( stop != true )
    //        {
    //         memset(buffer,0,maxBytes);
    // 		int bytes_read = recv (newsock,buffer,maxBytes,0);
    // 		if ( *buffer == '#' )
    // 		{
    // 			stop = true;
    // 			close(newsock);
    // 		}
    // 		else if ( test(buffer).compare("This function returned something!") == 0 )
    // 		{
    // 			cout << test(buffer) << endl;
    // 		}
    // 		else
    // 		{
    // 			if ( bytes_read > 0 ) printf ("Received Message from %s:%d\n%s\n",(char *)inet_ntoa(clientAddr.sin_addr),clientAddr.sin_port,buffer);
    // 			else perror("Error Receiving Message:");
    // 		}
				
    // 	}
    // }
    // }
    close(sock);
    return 0;
}

