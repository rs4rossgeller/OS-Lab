// Disk Scheduling

#include<stdio.h>
#include<stdlib.h>

int total, n, prev, current, count, mode;
int seekTime = 0;
int leftvar = 0;
int rightvar = 0;

void PrintHeadMovements(headMovementslist[], int m) {
	printf("\nNo: of Head Movements : %d", m);
	printf("\nHead Movement: ");
	for(int i=0; i<m; i++)
		printf("%d  ", headMovements[i]);
}

void Sort(int list[], int n) {
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (list[i] > list[j]) {
				int a =  list[i];
				list[i] = list[j];
				list[j] = a;
            }
        }
	}
}

void CalculateSeekTime(int order[], int length) {
	seekTime = 0;
	seekTime += abs(current - order[0]);
	for(int i=0; i<length-1; i++)
		seekTime += abs(order[i] - order[i+1]);
	printf("\nSeek Time: %d\n", seekTime);
}

void FCFS(int requests[]) {
	printf("\nFCFS");
	int order[n];
	for (int i = 0; i < n; i++) {
		order[i] = requests[i];
	}
	PrintHeadMovements(order, n);
	CalculateSeekTime(order, n);
}

void SCAN(int requests[], int mode) {
	int right[n], left[n];
	count = 0;
	leftvar = 0;
    rightvar = 0;
    if(mode == 1)
    	printf("\nSCAN");
	else
		printf("\nC-SCAN");
	for (int i=0; i<n; i++) {
		if(requests[i] < current)
			left[leftvar++] = requests[i];
		else
			right[rightvar++] = requests[i];
	}
	Sort(left, leftvar);
	Sort(right, rightvar);
	int order[leftvar + rightvar + 1];
	
	if(prev > current) { // left
		for (int i = leftvar - 1; i > 0; i--) {
			order[count] = left[i];
			count++;
		}
		order[count++] = 0;
		if (mode == 1) {
			// SCAN
			for (int i = 0; i < rightvar; i++) {
				order[count] = right[i];
				count++;
			}
		}
		else if (mode == 2) {
			// CSCAN
			for (int i = rightvar - 1; i >= 0; i--) {
				order[count] = right[i];
				count++;
			}
		}		
	}
	else { // right
		for (int i = 0; i < rightvar; i++) {
			order[count++] = right[i];
		}
		order[count++] = total - 1;
		//SCAN
		if (mode == 1) {
			for (int i = leftvar - 1; i >= 0; i--) {
				order[count] = left[i];
				count++;
			}
		}	
		// CSCAN
		else if (mode == 2) {
			order[count++] = 0;
			for (int i = 0; i < leftvar; i++) {
				order[count++] = left[i];
			}
		}
	}
	PrintHeadMovements(order, count);
	CalculateSeekTime(order, count);
}


void main() {
	int ch;
	printf("No. of Cylinders: ");
	scanf("%d", &total);
	printf("No. of Requests: ");
	scanf("%d", &n);
	int requests[n];
	printf("Requests: ");
	for(int i=0; i<n; i++) 
		scanf("%d", &requests[i]);

	printf("Previous request: ");
	scanf("%d", &prev);
	printf("Current requests: ");
	scanf("%d", &current);
	do{
		printf("\nDISK SCHEDULING");
		printf("\n1. FCFS\n2. SCAN\n3. C-SCAN\n4. Exit");
		printf("\nEnter choice:");
		scanf("%d",&ch);
		if (ch == 1){
			FCFS(requests);
		}
		else if (ch == 2) {
			mode =1;
			SCAN(requests, mode); // SCAN: mode =1 CSCAN: mode=2
		}
		else if (ch == 3) {
			mode = 2;
			SCAN(requests, mode); // SCAN: mode =1 CSCAN: mode=2
		}
	}while(ch != 4);
}
