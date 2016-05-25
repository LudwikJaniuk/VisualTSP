#ifndef COMMON_H
#define COMMON_H
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
	
	inline bool operator<(const Node& n) {
        return id < n.id;
    }
};
typedef vector<Node> path_t;

inline ostream& operator << (ostream& o, const point_t& p) {
	coord_t x = p.get<0>();
	coord_t y = p.get<1>();
	coord_t z = p.get<2>();
	o << "(" << x << ", " << y << ", " << z << ")";
	return o;
}

string path_to_json(path_t&);
path_t json_to_path(string&);

#endif
