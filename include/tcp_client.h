/* 
 * tcp_client.h
 */

#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>

const auto BUFFER_SIZE = 1024;

class TCPClient{
    public:
        TCPClient(std::string ip, std::string port);
        ~TCPClient();

        int create_socket();
        void send_message(std::string login_message);
        int read_message();

        TCPClient() = delete;
        TCPClient(const TCPClient& t) = delete;
    private:
        std::string ip_address; std::string port;
        int sock; addrinfo hints, *p;   // >>> netdb.h    
        char buffer[BUFFER_SIZE];
};
