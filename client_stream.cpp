#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <string.h>
using namespace std;

void terminate_with_error (int sock)
{
    close (sock);
    perror("Error Binding Socket:");
    exit(1);
}

int main (int argc,char ** argv)
{
    // const char* ip = "127.0.0.1";
    int bufsize = 1024;
    char buffer[bufsize];
    int portNum = 6969;
    char * addr = argv[1];
    if ( argc != 2)
    {
        printf ("Usage: ./client <server-address>\n");
        exit(1);
    }
    bool newserver = true;
    while( newserver )
    {
        newserver = false;
        int sock;
        struct sockaddr_in serverAddr;
        socklen_t sin_size = sizeof(struct sockaddr_in);
        
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
        {
            perror("Error Creating Socket");
            exit(1);
        }
        cout << "Socket client has been created." << endl;
        
        memset((char *) &serverAddr, 0,sizeof(serverAddr));
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(portNum);
        
        struct hostent *server = gethostbyname(addr);
        
        if ( server == NULL )
        {
            terminate_with_error(sock);
        }
        
        memcpy((char *)&serverAddr.sin_addr.s_addr,(char *)server->h_addr, server->h_length);
        memset(&(serverAddr.sin_zero), 0, 8);
        
        int bytes_read;
        if (connect(sock,(sockaddr *)&serverAddr,sizeof(serverAddr)) == -1 )
        {
            terminate_with_error(sock);
        }
        // connected
        // display startup messages
        else
        {
            recv(sock, buffer, bufsize, 0);
            cout << buffer << endl;
            recv(sock, buffer, bufsize, 0);
            cout << buffer << endl;
        }
        string input ="";
        while ( input.compare("QUIT") != 0 )
        {
            // display interface message
            bytes_read = recv(sock, buffer, bufsize, 0);
            // cout << buffer << endl;
            if ( bytes_read > 0 )
            {
                cout << buffer;
            }
            memset(buffer,0,bufsize);
            getline(cin,input);
            strcpy(buffer, input.c_str());
            send (sock,buffer,strlen(buffer),0);
            // get response
            recv(sock,buffer,bufsize,0);
            cout << buffer << endl;
            for( int i = 0; i < input.size(); i++)
            {
                input[i]=toupper(input[i]);
            }
        }
        close(sock);
        string serverReq;
        cout << "Do you wish to connect to a different server? If so, type in the ip address you wish to connect to or type 'no' to quit. ";
        getline(cin,serverReq);
        for( int i = 0; i < input.size(); i++)
        {
            serverReq[i]=toupper(serverReq[i]);
        }
        if ( serverReq.compare("NO") == 0 )
        {
            cout << "Goodbye!";
            return 0;
        }
        else
        {
            cout << "Attempting to connect to " << serverReq << endl;
            newserver = true;
            const char* temp = serverReq.c_str();
            strcpy(addr,temp);
        }
    }	
    return 0;
}
