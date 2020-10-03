// Banker's Algorithm

#include <stdio.h>

int n, m;

void initFinish(int finish[n]) {
	for (int i = 0; i < n; i++) {
		finish[i] = 0;
	}
}

void initWork(int work[m], int available[m]) {
	for (int i = 0; i < n; i++) {
		work[i] = available[i];
	}
}

void printMatrix(int allocation[n][m], int max[n][m], int need[n][m]) {
	printf("\nPROCESS \t ALLOCATION \t MAX \t\t NEED ");
	for(int i=0; i<n; i++) {
		printf("\nP%d \t\t",i+1);
		for (int j=0; j<m; j++) {
			printf("%d  ", allocation[i][j]);
		}
		printf("\t");
		for (int j=0; j<m; j++) {
			printf("%d  ", max[i][j]);
		}
		printf("\t");
		for (int j=0; j<m; j++) {
			printf("%d  ", need[i][j]);
		}
	}	
}

void needMatrix(int max[n][m], int allocation[n][m], int need[n][m]) {
	
	for (int i=0; i<n; i++) {
		for (int j=0; j<m; j++) 
			need[i][j] = max[i][j] - allocation[i][j];
	}
}

int compare(int process, int work[m], int need[n][m]) {
	for(int i=0; i<m; i++) {
		if(need[process][i] > work[i]) { //Request[i] > Need[i]   need>work
			return 0;
		}
	}
	return 1;
}

void workCalc(int index, int work[m], int allocation[n][m]) {
	for (int i = 0; i < m; i++) {
		work[i] = work[i] + allocation[index][i];
	}
}

void BankersAlgo(int work[m], int allocation[n][m], int need[n][m], int finish[n], int max[n][m]) {
	initFinish(finish);
	int val = 0;
	int count= 0;
	int safesequence[n];
	while(count<n) {
		for (int i=0; i<n; i++) {
			if(finish[i] == 0) {
				val = compare(i, work, need);
				if (val == 1) {
					workCalc(i, work, allocation);
					finish[i] = 1;
					safesequence[count] = i+1;
					count++;
				}
			}
		}
	}
	printf("\nSAFE STATE\nSafe Sequence: ");
	for (int i=0; i<n; i++) {
		printf("P%d  ", safesequence[i]);
	}
	printMatrix(allocation, max, need);
}

void request(int need[n][m], int available[m], int allocation[m][n], int work[m], int finish[n], int max[n][m]) {
	initFinish(finish);
	int process, requestArray[n], val;
	int op = 0;
	while(op != 1) {
		printf("\nProcess to be requested from: ");
		scanf("%d", &process);
		printf("No. of instances for each resource:\n");
		for(int i = 0; i < m; i++) {
			scanf("%d", &requestArray[i]);
		}
		for(int j=0; j<m; j++) {
			if(requestArray[j]<=need[process-1][j]) {
                if(requestArray[j]<=available[j]) {
					available[j] = available[j] - requestArray[j];
                    allocation[process-1][j] = allocation[process-1][j] + requestArray[j];
                    need[process-1][j] = need[process-1][j] - requestArray[j];	
				}
				else {
					printf("\nResource is not available");
					break;
				}
			}
			
			else {
				printf("Process has exceeded its maximum claim"); 
				break;
			}
		}
		initWork(work, available);
		BankersAlgo(work, allocation, need, finish, max);
		printf("\nRwquest new resource [Yes:0/No:1] : ");
		scanf("%d", &op);
	} 
}

void main() {
	int ch = 0;
	printf("No. of processes and resources:");
	scanf("%d %d", &n, &m);

	int max[n][m], allocation[n][m], available[m], need[n][m], work[m], finish[n];
	printf("No. of processes and resources : ");
	scanf("%d %d", &n, &m);
	printf("\nMaximum demand : \n");
	for (int i=0; i<n; i++) {
		printf("Process %d  ", i+1);
		for (int j=0; j<m; j++) {
			scanf("%d", &max[i][j]);
		}
	}
	printf("\nAllocation : \n");
	for (int i=0; i<n; i++) {
		printf("Process %d  ", i+1);
		for (int j=0; j<m; j++) {
			scanf("%d", &allocation[i][j]);
		}
	}
	printf("\nAvailable :\n");
	printf("Resource instances : \n");
	for (int i=0; i<m; i++) {
		scanf("%d", &available[i]);
	}
	initWork(work, available);

	do {	
		printf("\nDEADLOCK AVOIDANCE METHOD");
		printf("\n1. Banker's Algorithm \n2. Resource-Request Algorithm \n3. Exit");	
		printf("\nEnter choice : ");
		scanf("%d", &ch);

		needMatrix(max, allocation, need);
		if (ch == 1)
			BankersAlgo(work, allocation, need, finish, max);
		else if (ch == 2)
			request(need, available, allocation, work, finish, max);

	} while(ch!=3);
}