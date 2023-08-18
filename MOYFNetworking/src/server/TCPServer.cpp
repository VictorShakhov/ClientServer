#include <iostream>

#include "MOYFNetworking/server/TCPServer.h"

namespace MOYF {
    using boost::asio::ip::tcp;

    TCPServer::TCPServer(IPV ipv, int port) : _ipVersion(ipv), _port(port), 
        _acceptor(_ioContext, tcp::endpoint(_ipVersion == IPV::V4 ? tcp::v4() : tcp::v6(), _port))
    {
        
    }


    int TCPServer::Run()
    {
        try
        {
            startAccept();
            _ioContext.run();
        }
        catch(const std::exception& e)
        {
            std::cerr << e.what() << std::endl;
            return -1;
        }
        
        return 0;
    }

    void TCPServer::Broadcast(const std::string& message)
    {

    }


    void TCPServer::startAccept()
    {
        _socket.emplace(_ioContext);

        _acceptor.async_accept(*_socket, [this](const boost::system::error_code& error){
            auto connection = TCPConnection::Create(std::move(*_socket));

            _connections.insert(connection);

            if(!error)
            {
                connection->Start();
            }
            
            startAccept();
        });


    }
}
