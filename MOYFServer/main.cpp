#include <boost/asio.hpp>
#include <iostream>
#include <set>
#include <vector>

using tcp = boost::asio::ip::tcp;
namespace asio = boost::asio;

int main(int argc, char* argv[])
{
    try {
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), 1337));

        for(;;)
        {
            std::cout << "Accepting connection on port 1337!\n";

            tcp::socket socket(io_context);
            acceptor.accept(socket);

            std::cout << "Client connecting!\n";

            std::string hello_message = "Hello, client!\n";
            boost::system::error_code error;

            asio::write(socket, asio::buffer(hello_message), error);

        }
    } catch (std::exception& e) {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}