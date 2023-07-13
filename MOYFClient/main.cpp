#include <boost/asio.hpp>
#include <iostream>

using tcp = boost::asio::ip::tcp;
namespace asio = boost::asio;

int main(int argc, char* argv[])
{
    try {
        asio::io_context io_context;
        tcp::resolver resolver(io_context);

        tcp::resolver::results_type endpoints = resolver.resolve("127.0.0.1", "1337");
        tcp::socket socket(io_context);

        asio::connect(socket, endpoints);

        for(;;)
        {
            boost::system::error_code error;
            std::array<char, 128> buff {};

            size_t len = socket.read_some(asio::buffer(buff), error);

            if(error == asio::error::eof)
            {
                break;
            } else if(error) {
                throw boost::system::system_error(error);
            }

            std::cout.write(buff.data(), len);
        }

    } catch (std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}