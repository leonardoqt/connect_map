#include <iostream>
#include <stdlib.h>
#include "connector.h"

using namespace std;

void connector :: init(int Dim, vector<int> L)
{
	system("ulimit -s unlimited");
	if(Dim !=L.size())
	{
		cout<<"Error: the dimension of size parameters is wrong."<<endl;
		exit(EXIT_FAILURE);
	}
	dim = Dim;
	nn = 1;
	for (auto& m1:L)
	{
		nn *= m1;
		ll.push_back(m1);
	}
	value.resize(nn);
	if_visit.resize(nn);
	chain.resize(nn);
	for(size_t t1=0; t1<nn; t1++)
	{
		chain[t1].pos = index(t1);
		chain[t1].if_up_p = vector<int>(dim,0);
		chain[t1].if_up_n = vector<int>(dim,0);
		chain[t1].index_p = vector<int>(dim,0);
		chain[t1].index_n = vector<int>(dim,0);
	}
}

void connector :: assign(vector<int> Value)
{
	if(nn != Value.size())
	{
		cout<<"Error: number of sites assigned are wrong"<<endl;
		exit(EXIT_FAILURE);
	}
	value = Value;
}

void connector :: check_chain()
{
	vector<int> i2;
	int i3;
	// clean up chains
	for(auto& m1:chain)
	{
		m1.if_up_p = vector<int>(dim,0);
		m1.if_up_n = vector<int>(dim,0);
	}
	// check chains
	for(size_t t1=0; t1<dim; t1++)
		for(size_t i1=0; i1<nn; i1++)
		{
			if(chain[i1].pos[t1]<ll[t1]-1)
			{
				i2 = chain[i1].pos; i2[t1]++;
				i3 = index(i2);
				if(value[i1] == value[i3])
				{
					chain[i1].if_up_p[t1] = 1;
					chain[i1].index_p[t1] = i3;
				}
			}
			if(chain[i1].pos[t1]>0)
			{
				i2 = chain[i1].pos; i2[t1]--;
				i3 = index(i2);
				if(value[i1] == value[i3])
				{
					chain[i1].if_up_n[t1] = 1;
					chain[i1].index_n[t1] = i3;
				}
			}
		}
}

void connector :: connect_region()
{
	// clean up region
	regions.clear();
	// clean up if_visit
	for(auto& m1:if_visit)
		m1 = 0;
	for(size_t t1=0; t1<nn; t1++)
	{
		if(!if_visit[t1] && value[t1]!=0)
		{
			if_visit[t1] = 1;
			region_tmp.clear();
			region_tmp.push_back(t1);
			regions.push_back(vector<int>());
			int regions_last = regions.size()-1;
			while(region_tmp.size() > 0)
			{
				// find connected neighbors
				for(size_t t2=0; t2<dim; t2++)
				{
					if(chain[region_tmp[0]].if_up_p[t2] && !if_visit[chain[region_tmp[0]].index_p[t2]])
					{
						if_visit[chain[region_tmp[0]].index_p[t2]] = 1;
						region_tmp.push_back(chain[region_tmp[0]].index_p[t2]);
					}
					if(chain[region_tmp[0]].if_up_n[t2] && !if_visit[chain[region_tmp[0]].index_n[t2]])
					{
						if_visit[chain[region_tmp[0]].index_n[t2]] = 1;
						region_tmp.push_back(chain[region_tmp[0]].index_n[t2]);
					}
				}
				// add itself to the region list
				regions[regions_last].push_back(region_tmp[0]);
				// remove it from region_tmp
				region_tmp[0] = region_tmp[region_tmp.size()-1];
				region_tmp.pop_back();
			}
		}
	}
}

int connector :: index(vector<int> i1)
{
	int i2=i1[0];
	for(size_t t1=1; t1<dim; t1++)
		i2=i2*ll[t1]+i1[t1];
	return i2;
}

vector<int> connector :: index(int i1)
{
	vector<int> i2(dim);
	for(int t1=dim-1; t1>=0; t1--)
	{
		i2[t1] = i1%ll[t1];
		i1 = (i1-i2[t1])/ll[t1];
	}
	return i2;
}

vector<vector<int> >& connector :: run()
{
	check_chain();
	connect_region();
	return regions;
}

void connector :: print()
{
	vector<int> tmp;
	for(auto& m1:regions)
	{
		for(auto& m2:m1)
		{
			tmp = index(m2);
			for(auto& m3:tmp)
				cout<<m3<<'\t';
			cout<<endl;
		}
		cout<<endl;
	}
}
