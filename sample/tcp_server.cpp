#include<iostream>
#include<stdio.h>
#include<vector>
#include<stdlib.h>
#include<pthread.h>
#include <netinet/in.h>
#include<zlib.h>
#include <arpa/inet.h>
#include "tcp_server.h"

tcp_server::tcp_server(const int &port): QThread(nullptr)
{
    moveToThread(this);
    setTerminationEnabled(true);
    m_b_server_thread_running = false;
    pthread_mutex_init(&lock, nullptr);
    m_port = port;
    pthread_create(&new_connection, nullptr, tcp_server::acceptClient, this);
   // start();

}
tcp_server::~tcp_server()
{
    shutdown(server_fd, SHUT_RDWR);
    close(server_fd);
    while(m_b_server_thread_running)
    {
        usleep(100*1000);
    }

    quit();
    bool b_quit_ok = wait(2000);
    if(!b_quit_ok)
    {
        terminate();
    }

    std::cerr << "destructor " << __FUNCTION__ << "\n";

}
void tcp_server::serverInitialization()
{
    int opt=1;

    if((server_fd = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    if(setsockopt(server_fd , SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT , &opt, sizeof (opt)))
    {
        std::cerr<<"i'm here";
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }
    address.sin_family=AF_INET;
    address.sin_port=htons(m_port);
    address.sin_addr.s_addr=INADDR_ANY;
    if(bind(server_fd,reinterpret_cast<sockaddr *>(&address), sizeof (address))<0)
    {
        perror("bind failed") ;
        exit(EXIT_FAILURE);
    }
    if(listen(server_fd, 3)<0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }
    std::cerr<<"server intialization\n";

}


void *tcp_server::acceptClient(void* obj)
{
    tcp_server* objectOfClass = reinterpret_cast<tcp_server*>(obj);
    objectOfClass->m_b_server_thread_running = true;
    objectOfClass->serverInitialization();
    int newFd;
    do{
        newFd = accept(objectOfClass->server_fd,reinterpret_cast<sockaddr *>(&objectOfClass->address), reinterpret_cast<socklen_t *>(&objectOfClass->addrlen));
        if(newFd < 0)
        {
            break;
        }

        pthread_mutex_lock(&objectOfClass->lock);
        objectOfClass->clients_instance.push_back(newFd);
        pthread_mutex_unlock(&objectOfClass->lock);

    }while(newFd> 0);

    objectOfClass->m_b_server_thread_running = false;
    std::cerr << "exit server thread...\n";

}


//void tcp_server::dis()
//{
//    std::cerr<<" disconnection signal received..\n";

//}

void tcp_server::run()
{
    exec();
}






