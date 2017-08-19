#include "MCTS.hpp"
const int INF=0x3f3f3f3f;
double MCTS::Cp=1.5;
int MCTS::sz=1;

State::State(int i)
{
	commonNeigh.clear();
	click.clear();
	reward=nvisited=0;
	idx=i;
}
State::State() {}

double State::GetUct(State u, int nvis){
	if(u.nvisited==0) return INF;
	return reward/(double)nvisited + 	(MCTS::Cp)*sqrt( (2*log(nvis))/(double)u.nvisited);
}

/*-------------*/ 


MCTS::MCTS(int n)
{
	graph.clear();
	tree_search.clear();
	graph.resize(n+1);
	for(int i=1;i<=n;i++) root.commonNeigh.push_back(i);
}


void MCTS::AddEdge(int u, int v){
	graph[u].push_back(v);
	graph[v].push_back(u);
}

bool MCTS::isTerminal(State u){
	return (u.commonNeigh.size()>0);
}

State MCTS::BestChild(State u){
	int nvisited = u.nvisited;
	int node= u.idx;
	double maxi=-INF;
	State best(-1);
	if(tree_search[node].size()==-1) return best;
	for(auto son_u: tree_search[node]){
		double uct= son_u.GetUct(son_u, nvisited);
		if(uct>maxi) maxi=uct, best=son_u;
	}
	return best;
}


State MCTS::Expand(State u){
	int idx= u.commonNeigh.back();
	set<int> common;
	for(int x: u.commonNeigh) common.insert(x);

	State next((MCTS::sz)++);
	next.click=u.click;
	next.click.push_back(u.commonNeigh[idx]);
	int cur_vertex= u.commonNeigh[idx];

	for(int v: graph[cur_vertex])
		if(common.count(v)) next.commonNeigh.push_back(v);
	u.commonNeigh.pop_back();
	return next;
}



int MCTS::Build(State u){
	u.nvisited++;
	if(isTerminal(u)){
		State Next= Expand(u);
		Next.nvisited++;
		int benefit=Simulation(u);
		Next.reward= max(Next.reward, benefit);
		u.reward= max(u.reward, benefit);
		return benefit;
	}
	State Next= BestChild(u);
	if(Next.idx==-1) return -1;
	int benefit=Build(Next);
	u.reward= max(u.reward, benefit);
	return benefit;	
}

void MCTS::Process()
{
	int ok=1;
	while(ok>0){
		ok=Build(root);
	}
}

int MCTS::Simulation(State u){
	set<int> neig;
	for(int x: u.commonNeigh) neig.insert(x);
	int click= u.click.size();
	while(neig.size()>0){
		int next=-1;
		int maxi=0;
		for(int x: neig){
			int n=0;
			for(int y: graph[x])
				if(neig.count(y)) n++;
			if(n>=maxi) maxi=n, next=x;
		}
		set<int> prox;
		for(int x: graph[next])
				if(neig.count(x)) prox.insert(x);
		neig=prox;
		click++;
	}
	return click;
}
















