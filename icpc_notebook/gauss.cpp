void Gauss(int n) {
	for(int i = 0; i < n; i++) {
		for(int j = i; j < n; j++) {
			if(P[j][i] != 0) {
				for(int k = 0; k <= n; k++) {
					swap(P[j][k], P[i][k]);
				}
				break;
			}
		}

		if(P[i][i] == 0) continue;
		for(int j = 0; j < n; j++) {
			if(i == j) continue;
			num coef = P[j][i] / P[i][i];
			for(int k = 0; k <= n; k++) P[j][k] -= P[i][k] * coef;
		}
	}

	for(int i = 0; i < n; i++) C[i] = P[i][n] / P[i][i];
	degree = n - 1;
}
