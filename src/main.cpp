#include <iostream>
#include <vector>
#include "connector.h"

using namespace std;

int main()
{
	connector sys1;
	int dim = 3;
	vector<int> ll(dim);
	int index;
	int len = 21;
	vector<vector<int> > result;
	ll[0] = len;
	ll[1] = len;
	ll[2] = len;
	vector<int> value(ll[0]*ll[1]*ll[2]);
	for(size_t t1=0; t1<ll[0]; t1++)
	for(size_t t2=0; t2<ll[1]; t2++)
	for(size_t t3=0; t3<ll[2]; t3++)
	{
		index = (t1*ll[0]+t2)*ll[1]+t3;
		if( (t1-len/2)*(t1-len/2)+(t2-len/2)*(t2-len/2)+(t3-len/2)*(t3-len/2) <= (len/2)*(len/2))
			value[index] = 1;
		else
			value[index] = 2;
	}
	sys1.init(dim,ll);
	sys1.assign(value);
	result = sys1.run();

	return 0;
}
