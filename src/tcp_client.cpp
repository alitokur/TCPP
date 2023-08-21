#include "tcp_client.h"
#include <sys/socket.h>
TCPClient::TCPClient(std::string _ip, int _port):
    ip_address{_ip},port{_port}
{
    //
}

TCPClient::~TCPClient()
{
    close(sock);
}

int TCPClient::create_socket(){
    sock = socket(AF_INET, SOCK_STREAM, 0);
    server_address.sin_family = AF_INET;
    server_address.sin_port = htons(port);
    inet_pton(AF_INET, ip_address.c_str(), &(server_address.sin_addr)); 

    // if (sock == -1) {
    //     std::cerr << "Error while creating socket" << std::endl;
    //     return -3; 
    // }
    
    int connect_status = connect(sock, (struct sockaddr*)&server_address, sizeof(server_address));
    if ( connect_status == -1 ) {
        close(sock); //unistd.h
        std::cerr << " Error while connecting socket " << std::endl;
        return -4;
    }
    return 0;
}

void TCPClient::send_message(std::string message){
    if(send(sock, message.c_str(), message.size(), 0)==-1)
        std::cerr<< " Cannot send message" << std::endl;
}

int TCPClient::read_message(){
    memset(buffer, 0, sizeof(buffer));
    auto bytes_recv = recv(sock, buffer ,sizeof(buffer), 0);
    if(bytes_recv == -1){
        std::cerr << "Error while receiving bytes" << std::endl;
        return -1;
    }
    else if(bytes_recv>0){
        std::cout << "Client recieved: " << buffer << std::endl;
    }
    return 0;
}
