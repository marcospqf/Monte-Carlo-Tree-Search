#include <algorithm>
#include <bitset>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <string>
#include <utility>
#include <vector>
using namespace std;
#define sc(a) scanf("%d", &a)
#define sc2(a, b) scanf("%d%d", &a, &b)
#define sc3(a, b, c) scanf("%d%d%d", &a, &b, &c)
#define scs(a) scanf("%s", a)
#define pri(x) printf("%d\n", x)
#define prie(x) printf("%d ", x)
#define mp make_pair
#define pb push_back
#define BUFF ios::sync_with_stdio(false);
#define db(x) cerr << #x << " == " << x << endl
typedef long long int ll;
typedef long double ld;
typedef pair<int, int> ii;
typedef vector<int> vi;
typedef vector<vector<int> > vvi;
typedef vector<ii> vii;
typedef vector< vii> vvii;
const int INF = 0x3f3f3f3f;
const ll LINF = 0x3f3f3f3f3f3f3f3fll;
const ld pi = acos(-1);
const int MOD = 1e9 + 7;
int g[40][40];
int main()
{
	srand(time(NULL));
	cout<<40<<" "<<"40"<<endl;
	int n=40;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			int x=rand()%2;
			if(x)
				g[i][j]=g[j][i]=1;
		}
	}
	for(int i=0;i<n;i++) g[i][i]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			prie(g[i][j]);
		}
		cout<<endl;
	}
	return 0;
}
