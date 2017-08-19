#ifndef _mcts_hpp
#define _mcts_hpp
#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <cmath>
using namespace std;
class State{
	public:
		vector<int> commonNeigh, click;
		int reward, nvisited;
		int idx;
		State(int i);
		State();
		double GetUct(State u, int nvis);
};

class MCTS
{
	private:
		State root;
		vector< vector<State> > tree_search;
		vector< vector<int> > graph;
	public:
		//build graph;
		static int sz;
		static double Cp;
		void AddEdge(int u, int v);

		//State in MCTS methods:
		State BestChild(State &u);
		bool isTerminal(State &u);
		State Expand(State &u);

		//MCTS metods
		MCTS(int n);
		int Build(State &u);
		int Simulation(State &u);
		void Process();
};

#endif
