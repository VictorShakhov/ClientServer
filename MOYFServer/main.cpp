#include <iostream>

#include "MOYFNetworking/server/TCPServer.h"

int main(int argc, char* argv[])
{
    MOYF::TCPServer server{MOYF::IPV::V4, 1337};

    server.Run();
}