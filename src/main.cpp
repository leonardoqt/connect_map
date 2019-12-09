#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "connector.h"

using namespace std;

int main(int argc, char** argv)
{
	srand(time(0));
	int dim = 2;
	int index;
	int len = 1001;
	double pp = argc > 1 ? atof(argv[1]) : 0.5;
	connector sys1;
	vector<int> ll(dim);
	vector<int> index2;
	vector<vector<int> > result;
	ll[0] = len;
	ll[1] = len;
	vector<int> value(ll[0]*ll[1]);
	for(size_t t1=0; t1<ll[0]; t1++)
	for(size_t t2=0; t2<ll[1]; t2++)
	{
		index = t1*ll[0]+t2;
		if(rand()/(double)RAND_MAX < pp)
			value[index] = 1;
		else
			value[index] = 2;
	}
	sys1.init(dim,ll);
	sys1.assign(value);
	result = sys1.run();
	for(auto& m1:result)
	{
		if(m1.size() > 100)
		{
			for(auto& m2:m1)
			{
				index2=sys1.index(m2);
				for(auto& m3:index2)
					cout<<m3<<'\t';
				cout<<endl;
			}
			cout<<endl;
		}
	}

	return 0;
}
