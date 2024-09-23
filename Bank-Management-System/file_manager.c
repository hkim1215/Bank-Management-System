#include <stdio.h>
#include <stdlib.h>
#include "file_manager.h"

// Static cache for customer data (if needed)
static CustomerManager cachedManager;

// Save customer data to a file
void saveCustomersToFile(CustomerManager* manager) {
    FILE *file = fopen("customer.dat", "wb");
    if (!file) {
        printf("Error: Could not open file for saving customer data.\n");
        return;
    }
    fwrite(manager, sizeof(CustomerManager), 1, file);
    fclose(file);
    cachedManager = *manager;  // Optional: update cache
}

// Load customer data from a file
void loadCustomersFromFile(CustomerManager* manager) {
    if (cachedManager.count == 0) {  // Load from file only if cache is empty
        FILE *file = fopen("customer.dat", "rb");
        if (!file) {
            printf("Error: Could not open file for loading customer data.\n");
            return;
        }
        fread(manager, sizeof(CustomerManager), 1, file);
        cachedManager = *manager;  // Optional: update cache
        fclose(file);
    } else {
        *manager = cachedManager;  // Use cached data if available
    }
}

// Save transaction data to a file
void saveTransactionsToFile(CustomerManager* manager) {
    FILE *file = fopen("transactions.dat", "wb");
    if (!file) {
        printf("Error: Could not open file for saving transaction data.\n");
        return;
    }

    for (int i = 0; i < manager->count; ++i) {
        fwrite(manager->customers[i].transactions, sizeof(Transaction), manager->customers[i].transactionCount, file);
    }
    fclose(file);
}

// Load transaction data from a file
void loadTransactionsFromFile(CustomerManager* manager) {
    FILE *file = fopen("transactions.dat", "rb");
    if (!file) {
        printf("Error: Could not open file for loading transaction data.\n");
        return;
    }

    for (int i = 0; i < manager->count; ++i) {
        fread(manager->customers[i].transactions, sizeof(Transaction), manager->customers[i].transactionCount, file);
    }
    fclose(file);
}

