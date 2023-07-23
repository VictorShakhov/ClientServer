#pragma once

#include <boost/asio.hpp>

namespace MOYF {
    using boost::asio::ip::tcp;

    class TCPConnection {
    public:
        using pointer = std::shared_ptr<TCPConnection>;

        static pointer Create(boost::asio::io_context& ioContext) {
            return pointer(new TCPConnection(ioContext));
        }

        void Start();

        tcp::socket& Socket() {
            return _socket;
        }
    private:
        explicit TCPConnection(boost::asio::io_context& ioContext);
        tcp::socket _socket;
        std::string _message{"Hello, client!\n"};
    };
}
