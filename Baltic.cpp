/*
 * let's iterate over all the possible ways to choose the rows and try to match the columns in the best way using dp 
 * we will need to fill MX[l][r] for each combination , the maximum value of a rectangle if we set columns l , r 
*/
#define fast ios_base::sync_with_stdio(0),cin.tie(0),cout.tie(0)
#include <bits/stdc++.h>
using namespace std;
#define sqr 200
#define mid (l+r)/2
#define pb push_back
#define ppb pop_back
#define fi first
#define se second
#define lb lower_bound
#define ub upper_bound
#define ins insert
#define era erase
#define C continue
#define mem(dp,i) memset(dp,i,sizeof(dp))
#define mset multiset
typedef long long ll;
typedef short int si;
typedef long double ld;
typedef pair<int,int> pi;
typedef pair<ll,ll> pll;
typedef vector<int> vi;
typedef vector<ll> vll;
typedef vector<pi> vpi;
typedef vector<pll> vpll;
const ll mod=1e15 + 37;
const ll inf=1e18*4;
const ld pai=acos(-1);
int n , m , r , c ;
ll a[19][19] , bs[19][19] ;
ll sum ( int i , int l , int r ) {
	ll ans = bs[i][r] ;
	if ( l ) ans -= bs[i][l-1] ;
	return ans ;
}
ll Mx[19][19] ;
void fill ( int mask ) {
	for ( int l = 0 ; l < m ; l ++ ) {
		for ( int r = l ; r < m ; r ++ ){
			ll crnt = 0 , mx = 0 ;
			for ( int i = 0 ; i < n ; i ++ ) {
				if ( ( mask & ( 1<<i ) ) ) crnt = 0 ;
				crnt += sum ( i , l , r ) ;
				mx = max ( mx , crnt ) ;
			}
			Mx [l][r] = mx ;
		}
	}
}
ll dp[19][19] ;
ll bt ( int pos , int crnt ) {
	if ( crnt > c ) return inf ;
	if ( crnt == c ) return Mx[pos][m-1] ;
	if ( pos == m ) return 0ll ;
	ll &ret=dp[pos][crnt];
	if ( ret != -1 ) return ret ;
	ret = inf ;
	for ( int nxt = pos+1 ; nxt < m ; nxt ++ ) {
		ll cost = Mx [pos][nxt-1] ;
		ret = min ( ret , max ( cost , bt ( nxt , crnt+1 ) ) ) ;
	}
	return ret ; 
}
int main () {
	cin >> n >> m >> r >> c ;
	for ( int i = 0 ; i < n ; i ++ ) {
		for ( int j = 0 ; j < m ; j ++ ) {
			cin >> a [i][j] ;
			bs [i][j] = a [i][j] ;
			if ( j ) bs[i][j] += bs[i][j-1] ;
		}
	}
	ll ans = inf ; 
	for ( int mask = 1 ; mask < (1<<n) ; mask ++ ) {
		if ( __builtin_popcount ( mask ) != r || ( mask & 1 ) ) C ;
		mem ( dp , -1 ) ;
		fill ( mask ) ;
		ans = min ( ans , bt ( 0 , 0 ) ) ;
	}
	cout << ans << endl ; 	
}
