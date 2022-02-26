#include "../HeaderFiles/Client.h"


/*this method is responsible for a socket creation
 * it uses socket() from socket programming library
 * AF_NET: it means we're using IPv4
 * SOCK_STREAM: connection type. In this case, it means TCP
 * 0: it means we're using IP protocol */
int createSocket(){
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1)
    {
        return 1;
    }

    else return sock;
}

/*information for socket connection*/
sockaddr_in createHint(){
    int port = 54000;   //server's app port 
    string ipAddress = "127.0.0.1";     //loopback address (local machine)

    sockaddr_in hint;       //defining IPv4 format
    hint.sin_family = AF_INET;  
    hint.sin_port = htons(port);    //converting host byte order to network byte order
    //converting internet address (IPv4 or IPv6) to binary form
    inet_pton(AF_INET, ipAddress.c_str(), &hint.sin_addr);

    return hint;
}

/*this method handles the connection between client and server app*/
int conToServer(int sock, sockaddr_in hint){
    //opening a connection with server's application 
    int connectRes = connect(sock, (sockaddr*)&hint, sizeof(hint));
    //displaying error message if connection failed
    if (connectRes == -1)
    {
        cout << "Could not send to server!\n";
        return 1;
    }

    //returning 0 if connection is good 
    else return 0;
}

