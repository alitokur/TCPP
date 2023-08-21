/* 
 * tcp_client.h
 */

#include <netdb.h>
#include <unistd.h>
#include <string>
#include <cstring>
#include <iostream>
#include <arpa/inet.h>
const auto BUFFER_SIZE = 1024;

class TCPClient{
    public:
        TCPClient(std::string ip, int port);
        ~TCPClient();

        int create_socket();
        void send_message(std::string login_message);
        int read_message();

        TCPClient() = delete;
        TCPClient(const TCPClient& t) = delete;
    private:
        struct sockaddr_in server_address;
        std::string ip_address; 
        int port;
        int sock; 
        char buffer[BUFFER_SIZE];
};
