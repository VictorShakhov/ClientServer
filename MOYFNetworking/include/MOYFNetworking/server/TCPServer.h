#pragma once

#include <boost/asio.hpp>
#include <functional>
#include <optional>
#include <unordered_set>

#include "TCPConnection.h"

namespace MOYF {
    enum class IPV {
        V4,
        V6
    };

    class TCPServer {
    public:
        TCPServer(IPV ipv, int port);

        int Run();

        void Broadcast(const std::string& message);

    private:
        void startAccept();

    private:
        IPV _ipVersion;
        int _port;

        boost::asio::io_context _ioContext;
        boost::asio::ip::tcp::acceptor _acceptor;

        std::optional<boost::asio::ip::tcp::socket> _socket;

        std::unordered_set<TCPConnection::pointer> _connections {};
    };
}
