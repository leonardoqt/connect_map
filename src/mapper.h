#ifndef __CONNECT_MAP_MAPPER__
#define __CONNECT_MAP_MAPPER__
#include <vector>

class connector;
class mapper;

class connector
{
public:
	std::vector<int> pos;
	std::vector<int> if_up_p;
	std::vector<int> if_up_n;
	std::vector<int> index_p;
	std::vector<int> index_n;
};

class mapper
{
private:
	int dim;	// dimension of the system
	int nn;
	std::vector<int> ll;	// size of the system
	std::vector<int> value;		// value of each site
	std::vector<int> if_visit;	// if already visited
	std::vector<connector> chain;	// if neighbor are connected
	std::vector<std::vector<int> > regions;	// connected regions
	std::vector<int> region_tmp;
public:
	void init(int Dim, std::vector<int> L);
	void assign(std::vector<int> Value);
	void check_chain();
	void connect_region();

	int index(std::vector<int>);
	std::vector<int> index(int);

	void print();
};
#endif
