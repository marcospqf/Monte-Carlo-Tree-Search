#include <iostream>
#include "MCTS.hpp"
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	MCTS test(n);
	for(int i=0;i<m;i++){
		int u,v;
		cin>>u>>v;
		test.AddEdge(u,v);
	}
	test.Process();
	return 0;
}
