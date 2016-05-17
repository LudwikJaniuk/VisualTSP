#include "common.h"

using namespace std;
using boost::property_tree::ptree;

path_t nodes_from_tree(ptree tree) {
	path_t nodes;
	for (auto child: tree) {
		coord_t x = child.second.get<coord_t>("x");
		nodes.push_back(Node{point_t(x, x, x), 0});
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
	return nodes_tree;
}

