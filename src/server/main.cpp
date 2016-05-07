#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::property_tree::ptree;
using boost::property_tree::read_json;

int port = 3000;

string make_daytime_string();
string msg_from_json(string json);

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

			int bytesRead = 0;
			int inputSize = 1024;
			char readBuf[inputSize] = {0};
			bytesRead = socket.read_some(boost::asio::buffer(readBuf, inputSize));
			string msg(readBuf, bytesRead);

			msg = msg_from_json(msg);

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

string make_daytime_string()
{
	time_t now = time(0);
	return ctime(&now);
}

string msg_from_json(string json) 
{
	ptree pt;
	istringstream is(json);
	read_json(is, pt);
	string msg = pt.get<string>("message");
	int rep = pt.get<int>("repeat_times");
	string result;
	for (int i = 0; i < rep; i++) 
	{
		result.append(msg);
	}
	return result;
}

