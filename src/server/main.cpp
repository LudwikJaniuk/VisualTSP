#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

using namespace std;
using boost::asio::ip::tcp;
using boost::property_tree::ptree;
using boost::property_tree::read_json;

typedef vector<int> path_t;

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
			cout << "Received json:\n===========\n" << msg << "\n==========" << endl;

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

path_t nodes_from_tree(ptree tree) {
	path_t nodes;
	for (auto child: tree) {
		nodes.push_back(child.second.get<int>("x"));
	}
	return nodes;
}

void tsp_solve(path_t& nodes) {
	reverse(nodes.begin(), nodes.end());
}

ptree tree_from_nodes(const path_t& nodes) {
	ptree nodes_tree;
	for (auto x: nodes) {
		ptree node;
		node.put("x", x);
		node.put("y", 2);
		node.put("z", 3);
		nodes_tree.push_back(make_pair("", node)); 
	}
	return nodes_tree;
}

string msg_from_json(string json) 
{
	ptree pt;
	istringstream is(json);
	read_json(is, pt);
	ptree nodes_tree = pt.get_child("nodes");
	path_t nodes = nodes_from_tree(nodes_tree);

	tsp_solve(nodes);

	pt.clear();
	pt.put_child("nodes", tree_from_nodes(nodes));

	ostringstream buf;
	write_json(buf, pt, false); 

	return buf.str();
}

