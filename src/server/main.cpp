#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/geometry.hpp>
#include "common.h"

using namespace std;
using boost::asio::ip::tcp;
namespace bg = boost::geometry;
int port = 3000;

string msg_from_json(string json);
int calculate_path_distance(path_t& nodes);

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
			cout << "Server received json:\n===========\n" << msg << "\n==========" << endl;

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

void tsp_solve(path_t& nodes, string algo) {
	if (algo == "christo") {
		tsp_christofides(nodes);
	}
	else if (algo == "nn") {
		tsp_nearest_neighbor(nodes);
	}
	else if (algo == "total") {
		tsp_total_search(nodes);
	}
	else { throw "Invalid TSP algorithm"; }
}

void tsp_christofides(path_t& nodes) {
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

void tsp_total_search(path_t& nodes) {
	path_t shortestPath = nodes;
	coord_t shortestPathDist = calculate_path_distance(shortestPath);
	for {
		if 
	}
}

int calculate_path_distance(path_t& nodes) {
	totalDist = 0;
	for (int i = 1; i < nodes.size(); i++) {
		totalDist += bg::distance(nodes[i].pos, nodes[i-1].pos)
	}
	return totalDist;
}

string msg_from_json(string json) 
{
	path_t path = json_to_path(json);
	tsp_solve(path);
	return path_to_json(path);
}

