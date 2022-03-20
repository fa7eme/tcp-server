#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include<termios.h>
#include<fstream>
#include<iostream>
#include<vector>
#include <netinet/in.h>
#include <list>


class tcp_server
{
private:
    pthread_mutex_t lock;
    struct sockaddr_in address;
    size_t addrlen=sizeof (address);
    int server_fd=0 , new_socket=0, newFd=0;
    int m_port;
    bool m_b_server_thread_running;
    std::list<uint8_t> clients_instance;
 static void acceptClient();

public:
    tcp_server(const int &port);
    ~tcp_server();
     void serverInitialization();

protected:
    void run();


};


#endif // TCP_SERVER_H
