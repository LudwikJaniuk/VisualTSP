#include <ctime>
#include <iostream>
#include <string>
#include <boost/asio.hpp>

using namespace std;
using boost::asio::ip::tcp;

int port = 3000;

std::string make_daytime_string()
{
  time_t now = time(0);
  return ctime(&now);
}

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

		cout << "Wating for connections." << endl;

		while (true)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			cout << "Got a connection" << endl;

			string msg = make_daytime_string();

			boost::system::error_code ignored_err;
			boost::asio::write(socket, boost::asio::buffer(msg), ignored_err);
		}
	}
	catch(std::exception& e)
	{
		cerr << "Error: " << e.what() << endl;
	}
	return 0;
}
