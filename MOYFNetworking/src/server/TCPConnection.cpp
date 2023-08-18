#include "MOYFNetworking/server/TCPConnection.h"

#include <iostream>

namespace MOYF {

    TCPConnection::TCPConnection(boost::asio::ip::tcp::socket&& socket) : _socket(std::move(socket)) {

    }

    void TCPConnection::Start() {
        auto strongThis = shared_from_this();
        
        boost::asio::async_write(_socket, boost::asio::buffer(_message), 
            [strongThis](const boost::system::error_code& error, size_t bytesTransfered){
                if(error) {
                    std::cout << "Failed to send message!\n";
                } else {
                    std::cout << "Sent " << bytesTransfered << " bytes of data!\n";
                }
            });
        

        boost::asio::streambuf buffer;

        _socket.async_receive(buffer.prepare(512), [this](const boost::system::error_code& error, size_t bytesTransfered){
            if(error == boost::asio::error::eof)
            {
                std::cout << "Client disconnected properly! \n";
            } else if(error) {
                std::cout << "Client disconnected in bad way! \n";
            }
        });
    }
}
