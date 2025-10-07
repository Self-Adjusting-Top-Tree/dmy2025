#include<bits/stdc++.h>
using namespace std;
const int MAXN=2e5;
const int MOD=998244353;
const int INV2=MOD+1>>1;
int qpow(int x,int e){int ret=1;for(;e;e>>=1,x=1ll*x*x%MOD)if(e&1)ret=1ll*ret*x%MOD;return ret;}
int n,m,p[MAXN+5],res;
int main(){
	scanf("%d%d",&n,&m);
	for(int i=1;i<=n;i++)scanf("%d",&p[i]);
	for(int i=1;i<=n;i++){
		int p0=1ll*(1ll*i*(i-1)/2+1ll*(n-i)*(n-i+1)/2)%MOD*qpow(1ll*n*(n+1)/2%MOD,MOD-2)%MOD;
		res=(res+1ll*i*i)%MOD;
		res=(res-(1ll*qpow(p0,m)*p[i]%MOD*i+1ll*(1-qpow(p0,m)+MOD)*p[i]%MOD*(n+1)%MOD*INV2)%MOD+MOD)%MOD;
	}printf("%d\n",1ll*res*qpow(1ll*n*(n+1)/2%MOD,m)%MOD);
	return 0;
}
	