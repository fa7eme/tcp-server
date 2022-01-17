#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include<QThread>
#include<termios.h>
#include<fstream>
#include<iostream>
#include<vector>
#include<pthread.h>
#include <netinet/in.h>



class tcp_server:public QThread
{
    Q_OBJECT

private:
    pthread_mutex_t lock;
    struct sockaddr_in address;
    size_t addrlen=sizeof (address);
    int server_fd=0 , new_socket=0, newFd=0;
    pthread_t new_connection;
    int m_port;
    bool m_b_server_thread_running;
    std::list<uint8_t> clients_instance;

protected:
    static void* acceptClient(void* obj);
public:
    tcp_server(const int &port);
    ~tcp_server();
     void serverInitialization();
protected slots:
//    void dis();
    // QThread interface

protected:
    void run();


};


#endif // TCP_SERVER_H
