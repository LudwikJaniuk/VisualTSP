#include <iostream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

using namespace std;
using boost::asio::ip::tcp;

string port = "3000";

int main(int argc, char** argv)
{
	try
	{
		if (argc != 2) {
			cout << "Usage: client <host>" << endl;
			return 1;
		}

		boost::asio::io_service io_service;
		tcp::resolver resolver(io_service);
		tcp::resolver::query query(argv[1], port);
		tcp::resolver::iterator endpoint_iterator = resolver.resolve(query);

		tcp::socket socket(io_service);
		boost::asio::connect(socket, endpoint_iterator);
		// Now the connection is open, and we need to read the response.

		while (true)
		{
			boost::array<char, 128> buf;
			boost::system::error_code err;
			size_t len = socket.read_some(boost::asio::buffer(buf), err);

			if (err == boost::asio::error::eof) // Clean close
			{
				break;
			} 
			else if (err)
			{
				throw boost::system::system_error(err);
			}

			cout.write(buf.data(), len);
		}
	}
	catch (std::exception& e) 
	{
		cerr << e.what() << endl;
	}
	return 0;
}
