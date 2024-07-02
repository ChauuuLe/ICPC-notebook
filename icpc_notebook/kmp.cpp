void kmp (string &s) {
	// KMP
	s = " " + s;
    for (int i = 2; i <= n; i++) {
        int j = p[i - 1];
        while (j > 0 && s[j + 1] != s[i]) 
            j = p[j];
        if (s[j + 1] == s[i]) p[i] = j + 1;
    }
    // Automation
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j < C; j++) {
            int t = i;
            while (t > 0 && s[t + 1] != 'a' + j) 
                t = p[t];
            if(s[t + 1] == 'a' + j) f[i][j] = t + 1;
        }
    }	
}
