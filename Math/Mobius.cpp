for (ll i=1;i<MAXN;i++) {
	if (i==1) M[i]=1; else if (lpf[i]==i) M[i]=-1;
	else if ((i/lpf[i])%lpf[i]==0) M[i]=0; else M[i]=M[i/lpf[i]]*M[lpf[i]];}
