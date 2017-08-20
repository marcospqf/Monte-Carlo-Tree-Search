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
int n,k;
ll g[41];
ll dp[(1<<20)];
ll dp2[(1<<20)];
int t1,t2;
ll Adam_Sendler()
{
	t1=n/2;
	t2=n-t1;
	ll r=0;
	for(ll mask=1;mask<(1ll<<t1);mask++){
		for(ll j=0;j<t1;j++)
			if(mask&(1ll<<j)) {
				ll outra= mask-(1ll<<j);
				ll r1= __builtin_popcountll(dp[mask]);
				ll r2= __builtin_popcountll(dp[outra]);
				if(r2>r1) dp[mask] = dp[outra];
			}
		bool click=true;
		for(ll j=0;j<t1;j++)
			if( (1ll<<j)&mask)
				if( ((g[j]^mask)&mask)) click=false;
		if(click) dp[mask]=mask;
		ll r1= __builtin_popcountll(dp[mask]);
		r=max(r,r1);
	}

	for(ll mask=1;mask<(1ll<<t2);mask++){
		for(ll j=0;j<t2;j++)
			if(mask&(1ll<<j)) {
				ll outra= mask-(1ll<<j);
				ll r1= __builtin_popcountll(dp2[mask]);
				ll r2= __builtin_popcountll(dp2[outra]);
				if(r2>r1) dp2[mask] = dp2[outra];
			}
		bool click=true;
		for(ll j=0;j<t2;j++){
			if( (1ll<<j)&mask){
				ll m1= g[j+t1];
				ll cara= mask<<t1;
				if((m1^cara)&cara){
					click=false;
				}
			}
		}
		if(click) {
			dp2[mask]=mask;
		}
		ll r1= __builtin_popcountll(dp2[mask]);
		if(r1==0) db(mask);
		r=max(r,r1);	
	}

	for(ll mask=0;mask<(1ll<<t1);mask++){
		ll tudo= (1ll<<n) -1;
		for(ll j=0;j<t1;j++)
			if( (1ll<<j)&mask) tudo&=g[j];

		tudo>>=t1;
		ll x=__builtin_popcountll(dp[mask]);
		ll y=__builtin_popcountll(dp2[tudo]);
		r=max(r, x+y);
	}
	return r;
}
int main()
{
	sc2(n,k);
	for(int i=0;i<n;i++){
		g[i]|=(1ll<<i);
		for(int j=0;j<n;j++){
			int x;
			sc(x);
			if(x){
				g[i]|=(1ll<<j);
			}
		}
	}
	int m=Adam_Sendler();
	cout<<"CLICK MAXIMA = "<<m<<endl;
	return 0;
}
