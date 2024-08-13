#include<stdio.h>

void main() {
    int num_processes, num_resources;

    printf("Enter the number of processes: ");
    scanf("%d", &num_processes);

    printf("Enter the number of resources: ");
    scanf("%d", &num_resources);

    int allocation[num_processes][num_resources];
    int max[num_processes][num_resources];
    int available[num_resources];
    int need[num_processes][num_resources];
    int safe_sequence[num_processes];
    int finished[num_processes];

    for (int i = 0; i < num_processes; i++) {
        finished[i] = 0;
    }

    // Input Allocation Matrix
    printf("Enter the allocation matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Max Matrix
    printf("Enter the max matrix:\n");
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the available resources:\n");
    for (int i = 0; i < num_resources; i++) {
        scanf("%d", &available[i]);
    }

    //Need Matrix
    for (int i = 0; i < num_processes; i++) {
        for (int j = 0; j < num_resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Bankers Algorithm Implementation
    int index = 0;
    for (int k = 0; k < num_processes; k++) {
        for (int i = 0; i < num_processes; i++) {
            if (!finished[i]) {
                int can_allocate = 1;
                for (int j = 0; j < num_resources; j++) {
                    if (need[i][j] > available[j]) {
                        can_allocate = 0;
                        break;
                    }
                }
                if (can_allocate) {
                    for (int j = 0; j < num_resources; j++) {
                        available[j] += allocation[i][j];
                    }
                    safe_sequence[index++] = i;
                    finished[i] = 1;
                }
            }
        }
    }

    int safe = 1;
    for (int i = 0; i < num_processes; i++) {
        if (!finished[i]) {
            safe = 0;
            printf("The system is not in a safe state.\n");
            break;
        }
    }

    // Print the Safe Sequence
    if (safe) {
        printf("The system is in a safe state.\nSafe sequence is: ");
        for (int i = 0; i < num_processes; i++) {
            printf("P%d", safe_sequence[i]);
            if (i != num_processes - 1) printf(" -> ");
        }
        printf("\n");
    }
}
