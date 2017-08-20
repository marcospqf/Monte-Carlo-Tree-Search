#include <iostream>
#include "MCTS.hpp"
using namespace std;
int main()
{
	int n,m;
	cin>>n>>m;
	MCTS test(n);
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int x;
			cin>>x;
			if(i>j and x){
				test.AddEdge(i,j);
			}
		}
	}
	cout<<"MAXIMUM CLICK: "<<test.Process()<<endl;
	test.delete_all();
	return 0;
}
