#include "MOYFNetworking/TCPConnection.h"

#include <iostream>

namespace MOYF {

    TCPConnection::TCPConnection(boost::asio::io_context& ioContext) : _socket(ioContext) {

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
    }
}
