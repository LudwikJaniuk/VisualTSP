#include <boost/property_tree/ptree.hpp>
#include <boost/geometry.hpp>

using namespace std;
using boost::property_tree::ptree;
namespace bg = boost::geometry;

typedef float coord_t;
typedef bg::model::point<coord_t, 3, bg::cs::cartesian> point_t;
struct Node {
	point_t pos;
	int id;
};
typedef vector<Node> path_t;

path_t nodes_from_tree(ptree tree);
ptree tree_from_nodes(const path_t& nodes);
