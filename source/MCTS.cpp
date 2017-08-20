#include "MCTS.hpp"
const int INF=0x3f3f3f3f;
double MCTS::Cp=1.5;

State::State()
{
	commonNeigh.clear();
	click.clear();
	reward=nvisited=0;
	son.clear();
}

double State::GetUct(State* u, int nvis){
	if(u->nvisited==0) return INF;
	return u->reward/(double)u->nvisited + 	(MCTS::Cp)*sqrt( (2*log(nvis))/(double)u->nvisited);
}

/*-------------*/ 


MCTS::MCTS(int n)
{
	graph.clear();
	graph.resize(n+1);
	root= new State();
	for(int i=1;i<=n;i++) root->commonNeigh.push_back(i);
}


void MCTS::AddEdge(int u, int v){
	graph[u].push_back(v);
	graph[v].push_back(u);
}

bool MCTS::isTerminal(State* &u){
	return (u->commonNeigh.size()>0);
}

State* MCTS::BestChild(State* &u){
	int nvisited = u->nvisited;
	double maxi=-INF;
	State* best=NULL;
	if(u->son.size()==0){
		return best;
	}
	for(auto son_u: u->son){
		double uct= son_u->GetUct(son_u, nvisited);
		if(uct>maxi) maxi=uct, best=son_u;
	}
	return best;
}


State* MCTS::Expand(State* &u){
	int cur_vertex= u->commonNeigh.back();
	u->commonNeigh.pop_back();
	set<int> common;
	for(int x: u->commonNeigh)  common.insert(x);
	
	State* next= new State();
	next->click=u->click;
	next->click.push_back(cur_vertex);
	next->nvisited=1;

	for(int v: graph[cur_vertex])
		if(common.count(v)) next->commonNeigh.push_back(v);
	return next;
}



int MCTS::Build(State* &u){
	u->nvisited++;
	if(isTerminal(u)){
		State *Next= Expand(u);
		int benefit=Simulation(Next);
		Next->reward= benefit;
		u->reward= max(u->reward, benefit);
		u->son.push_back(Next);
		return benefit;
	}
	State *Next= BestChild(u);
	if(Next==NULL) return -1;
	int benefit=Build(Next);
	u->reward= max(u->reward, benefit);
	return benefit;	
}

int MCTS::Process()
{
	int ok=1;
	while(ok>0){
		ok=Build(root);
		cout<<"Found click "<<ok<<endl;
		cout<<"Maximal click "<<root->reward<<endl;
		cout<<ok<<endl;
	}
	return root->reward;
}

int MCTS::Simulation(State* &u){
	set<int> neig;
	for(int x: u->commonNeigh) neig.insert(x);
	int click= u->click.size();
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

void MCTS::clear(State *u){
	for(auto son_u: u->son)
		clear(son_u);
	u->son.clear();
	delete u;
}

void MCTS::delete_all(){
	clear(root);
}














