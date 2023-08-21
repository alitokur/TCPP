#include "tcp_client.h"
TCPClient::TCPClient(std::string _ip, std::string _port):
    ip_address{_ip},port{_port}
{
    //
}

TCPClient::~TCPClient()
{
    close(sock);
    freeaddrinfo(p);
}

int TCPClient::create_socket(){

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_flags = AI_PASSIVE;

    int g_addres = getaddrinfo(ip_address.c_str(), port.c_str(), &hints, &p);
    if(g_addres != 0){
        std::cerr << gai_strerror(g_addres) << std::endl;
        return -1;  
    }

    if(p == NULL){
        std::cerr << " No addresses found" << std::endl;
        return -2;
    }

    //socket() call to create a new socket and return its descriptor
    sock = socket(p->ai_family, p->ai_socktype, p->ai_protocol);
    if (sock == -1) {
        std::cerr << "Error while creating socket" << std::endl;
        return -3; 
    }

    //connect() call tries to establish a TCP connection to the 
    //specified server
    int connectR = connect(sock, p->ai_addr, p->ai_addrlen);
    if ( connectR == -1 ) {
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
