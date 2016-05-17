#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/geometry.hpp>
#include "common.h"

using namespace std;
using boost::asio::ip::tcp;
using boost::property_tree::ptree;
using boost::property_tree::read_json;
namespace bg = boost::geometry;
int port = 3000;

string msg_from_json(string json);

int main()
{
	try
	{
		boost::asio::io_service io_service;
		tcp::acceptor acceptor(io_service, tcp::endpoint(tcp::v4(), port));

		cout << "Waiting for connections." << endl;

		while (true)
		{
			tcp::socket socket(io_service);
			acceptor.accept(socket);
			cout << "Got a connection" << endl;

			int bytesRead = 0;
			const int inputSize = 1024;
			char readBuf[inputSize] = {0};
			bytesRead = socket.read_some(boost::asio::buffer(readBuf, inputSize));
			string msg(readBuf, bytesRead);
			cout << "Received json:\n===========\n" << msg << "\n==========" << endl;

			msg = msg_from_json(msg);

			cout << "Server sending: " << msg << endl;

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

void tsp_solve(path_t& nodes) {
	reverse(nodes.begin(), nodes.end());
}

void tsp_nearest_neighbor(path_t& nodes) {
	for (int i = 0; i < nodes.size(); i++) {
		for (int j = i+1; j < nodes.size() ; j++) {
			if (bg::distance(nodes[i].pos, nodes[j].pos) < bg::distance(nodes[i].pos, nodes[i+1].pos)) {
				swap(nodes[i+1], nodes[j]);
			}
		}
	}
}

string msg_from_json(string json) 
{
	ptree pt;
	istringstream is(json);
	read_json(is, pt);
	path_t nodes = nodes_from_tree(pt);

	tsp_solve(nodes);

	ptree sol_pt = tree_from_nodes(nodes);
	ostringstream buf;
	write_json(buf, sol_pt, false); 

	return buf.str();
}


