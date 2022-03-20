#include "tcp_server.h"
int main(int argc, char *argv[])
{
    tcp_server *tcp;
    tcp = new tcp_server(1234);

    delete tcp;
}
