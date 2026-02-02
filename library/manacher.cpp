    for(ll i = 0, w = 0; i < n;){
        while(0 <= i-w && i+w < n && s[i-w] == s[i+w]) w++;
        a[i] = w;
        ll j = 1;
        while(j < w && a[i-j]+j < w){
            a[i+j] = a[i-j];
            j++;
        }
        i += j; w -= j;
    }