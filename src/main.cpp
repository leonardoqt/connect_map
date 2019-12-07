#include <iostream>
#include <vector>
#include "mapper.h"

using namespace std;

int main()
{
	mapper sys1;
	int dim = 2;
	vector<int> ll(dim);
	int index;
	ll[0] = 11;
	ll[1] = 11;
	vector<int> value(ll[0]*ll[1]);
	for(size_t t1=0; t1<ll[0]; t1++)
	for(size_t t2=0; t2<ll[1]; t2++)
	{
		index = t1*ll[0]+t2;
		if( (t1-5)*(t1-5)+(t2-5)*(t2-5) <= 25)
			value[index] = 1;
		else
			value[index] = 0;
	}
	sys1.init(dim,ll);
	sys1.assign(value);
	sys1.check_chain();
	sys1.connect_region();
	sys1.print();
	return 0;
}
