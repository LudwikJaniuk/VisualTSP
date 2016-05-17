#include <boost/property_tree/json_parser.hpp>
#include "common.h"

using namespace std;
using boost::property_tree::ptree;
using boost::property_tree::read_json;

path_t nodes_from_tree(ptree tree) {
	ptree nodes_tree = tree.get_child("nodes");
	path_t nodes;
	for (auto child: nodes_tree) {
		coord_t x = child.second.get<coord_t>("x");
		coord_t y = child.second.get<coord_t>("y");
		coord_t z = child.second.get<coord_t>("z");
		int id = child.second.get<int>("id");
		nodes.push_back(Node{point_t(x, y, z), id});
	}
	return nodes;
}

ptree tree_from_nodes(const path_t& nodes) {
	ptree nodes_tree;
	for (auto node: nodes) {
		point_t pos = node.pos;

		ptree node_tree;
		node_tree.put("x", pos.get<0>());
		node_tree.put("y", pos.get<1>());
		node_tree.put("z", pos.get<2>());
		node_tree.put("id", node.id);
		nodes_tree.push_back(make_pair("", node_tree)); 
	}
	ptree pt;
	pt.put_child("nodes", nodes_tree);
	return pt;
}

string path_to_json(path_t& path) {
	ptree pt = tree_from_nodes(path);
	ostringstream buf;
	write_json(buf, pt, false); 
	return buf.str();
}

path_t json_to_path(string& json) {
	istringstream is(json);
	ptree pt;
	read_json(is, pt);
	return nodes_from_tree(pt);
}

