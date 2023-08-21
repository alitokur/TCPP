#include <cstring>
#include <iostream>
#include <string>
#include <sstream>

#include <netdb.h>
#include <unistd.h>
#include "tcp_client.h"
// #include <arpa/inet.h>
// #include <sys/socket.h>
// #include <sys/types.h>
int main (int argc, char *argv[]) {
    std::string ip_address = "127.0.0.1";
    std::string port = "9090";

    if(argc == 3)
    {
        std::cerr << " Run program as ./session_server <ip_adddress>"
            " <port>"  << std::endl;
        ip_address = argv[1];
        port = argv[2];
    }

    TCPClient client(ip_address, stoi(port));
    try{
        int socket_code = client.create_socket();
        if(socket_code == 0){
            //do nothing
        }
        else{
            throw (socket_code);
        }
    }
    catch(int error_code){
        std::cout << "socket not created | reason: " << error_code << 
            std::endl;
        return 0;
    }
    std::string login_message = "hey!";
    client.send_message(login_message);
    while(true) {
        if(client.read_message()==-1)
            return -1;
    }
    return 0;
}
