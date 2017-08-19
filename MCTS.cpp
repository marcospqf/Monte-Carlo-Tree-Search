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
	tree_search.resize(n+1);
	graph.resize(n+1);
	root.idx=0;
	root.reward=root.nvisited=0;
	for(int i=1;i<=n;i++) root.commonNeigh.push_back(i);
}


void MCTS::AddEdge(int u, int v){
	graph[u].push_back(v);
	graph[v].push_back(u);
}

bool MCTS::isTerminal(State &u){
	return (u.commonNeigh.size()>0);
}

State MCTS::BestChild(State &u){
	int nvisited = u.nvisited;
	int node= u.idx;
	double maxi=-INF;
	State best(-1);
	if(tree_search[node].size()==0) {
		cout<<"PAU"<<endl;
		return best;
	}
	for(auto son_u: tree_search[node]){
		double uct= son_u.GetUct(son_u, nvisited);
		if(uct>maxi) maxi=uct, best=son_u;
	}
	//cout<<best.commonNeigh.size()<<endl;
	return best;
}


State MCTS::Expand(State &u){
	int cur_vertex= u.commonNeigh.back();
	u.commonNeigh.pop_back();
	set<int> common;
	for(int x: u.commonNeigh)  common.insert(x);

	State next(sz++);
	next.click=u.click;
	next.click.push_back(cur_vertex);

	for(int v: graph[cur_vertex])
		if(common.count(v)) next.commonNeigh.push_back(v);
	return next;
}



int MCTS::Build(State &u){
	u.nvisited++;
	if(isTerminal(u)){
		State Next= Expand(u);
		if(tree_search.size()<=sz) 
			tree_search.resize(2*sz);
		
		Next.nvisited++;
		int benefit=Simulation(Next);
		Next.reward= benefit;
		u.reward= max(u.reward, benefit);
		tree_search[u.idx].push_back(Next);
		return benefit;
	}
	State Next= BestChild(u);
	if(Next.idx==-1) return -1;
	for(auto &x: tree_search[u.idx]) if(x.idx==Next.idx) x=Next;
	int benefit=Build(Next);
	u.reward= max(u.reward, benefit);
	return benefit;	
}

void MCTS::Process()
{
	int ok=1;
	while(ok>0){
		ok=Build(root);
		//cout<<root.commonNeigh.size()<<endl;
		cout<<"Found click "<<ok<<endl;
		cout<<"Maximal click "<<root.reward<<endl;
	}
}

int MCTS::Simulation(State &u){
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
















