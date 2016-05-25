#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <boost/asio.hpp>
#include <boost/geometry.hpp>
#include <boost/property_tree/json_parser.hpp>
#include "common.h"

using namespace std;
using boost::asio::ip::tcp;
using boost::property_tree::json_parser::json_parser_error;
namespace bg = boost::geometry;

struct Path
{
	path_t path;
	coord_t length;
};

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
			cout << "Got a connection." << endl;

			boost::array<char, 512> buf;
			boost::system::error_code err;
			ostringstream buf_stream;
			
			
			while (true) {
				size_t len = socket.read_some(boost::asio::buffer(buf), err);
				
				bool quit = false;
				for (int i = 0; i < buf.size(); i++) {
					if (buf[i] == '#') {
						buf_stream.write(buf.data(), len);
						quit = true;
					}
				}
				
				if (quit) {
					break;
				}
				if (err)
				{
					throw boost::system::system_error(err);
				}
				buf_stream.write(buf.data(), len);
				cout << "Reading input data." << endl;
			}
			string msg = buf_stream.str();
			msg.erase(msg.length()-1, 1);
			cout << "Server received json data." << endl;

			try {
				msg = msg_from_json(msg);
			}
			catch (json_parser_error& e) {
				continue;
			}

			cout << "Server sending solution data." << endl;

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

coord_t calculate_path_distance(path_t& nodes) {
	coord_t totalDist = 0;
	for (int i = 1; i < nodes.size(); i++) {
		totalDist += bg::distance(nodes[i].pos, nodes[i-1].pos);
	}
	return totalDist;
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
		if ((i + 1) % 5 == 0) {
			cout << "NN: Ready up to node " << i+1 << "." << endl;
		}
	}
}

void update_shortestPath(path_t& nodes, Path& shortestPath) {
	coord_t currentPathDist = calculate_path_distance(nodes);
	if (currentPathDist < shortestPath.length) {
		shortestPath = {nodes, currentPathDist};
	}
}

void tsp_total_search(path_t& nodes) {
	sort(begin(nodes), end(nodes));
	Path shortestPath = {nodes, calculate_path_distance(nodes)};
	
	int it = 1;
	while (next_permutation(nodes.begin(), nodes.end())) {
		update_shortestPath(nodes, shortestPath);
		if (it % 50 == 0) {
			cout << "TS: On permutation " << it << "." << endl;
		}
	}
	nodes = shortestPath.path;
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

string msg_from_json(string json)
{
	path_t path = json_to_path(json);
	string algo;
	if (path.size() < 10) {
		algo = "total";
	}
	else {algo = "nn";}
	tsp_solve(path, algo);
	return path_to_json(path);
}

