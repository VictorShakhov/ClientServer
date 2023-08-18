#pragma once

#include <boost/asio.hpp>

namespace MOYF {
    using boost::asio::ip::tcp;

class TCPConnection : public std::enable_shared_from_this<TCPConnection> {
    public:
        using pointer = std::shared_ptr<TCPConnection>;

        static pointer Create(boost::asio::ip::tcp::socket&& socket) {
            return pointer(new TCPConnection(std::move(socket)));
        }

        void Start();

        tcp::socket& Socket() {
            return _socket;
        }
    private:

        explicit TCPConnection(boost::asio::ip::tcp::socket&& socket);

        tcp::socket _socket;
        std::string _message{"Hello, client!\n"};
    };
}
