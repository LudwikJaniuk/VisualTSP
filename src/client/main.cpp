#include <iostream>
#include <sstream>

#include <boost/array.hpp>
#include <boost/asio.hpp>
#include <boost/asio/ip/tcp.hpp>

#include "common.h"

using namespace std;
using boost::asio::ip::tcp;

string port = "3000";
bool pretty_json = false;

string make_json();

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

		boost::array<char, 128> buf;
		boost::system::error_code err;

		string msg = make_json();
		cout << "Client Sending: " << msg << endl;
		socket.write_some(boost::asio::buffer(msg, msg.length()), err);

		if (err) {
			cout << "Error sending data: " <<  err << endl;
		}
		cout << "Received: ";

		while (true)
		{
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
		cout << endl;
	}
	catch (std::exception& e) 
	{
		cerr << e.what() << endl;
	}
	return 0;
}

string make_json() 
{
	path_t nodes;
	for (int i = 0; i < 10; i++) {
		Node node{point_t(i, 2, 3), i};
		nodes.push_back(node); 
	}
	return path_to_json(nodes);
}
