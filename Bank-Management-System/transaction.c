#include <stdio.h>
#include <string.h>
#include "transaction.h"
#include "file_manager.h"
#include "security.h"

void processTransaction(CustomerManager* manager, int id, float amount, const char* description) {
    loadTransactionsFromFile(manager);  // Load transaction history before making a change

    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            Customer* customer = &manager->customers[i];
            if (customer->transactionCount >= MAX_TRANSACTIONS) {
                printf("Error: Cannot process transaction. Transaction log full.\n");
                return;
            }

            customer->balance += amount;

            // Record the transaction
            Transaction* transaction = &customer->transactions[customer->transactionCount++];
            transaction->amount = amount;

            // Encrypt transaction description
            char encryptedDescription[NAME_LENGTH];
            strncpy(encryptedDescription, description, NAME_LENGTH);
            encryptData(encryptedDescription, "bank_key");

            strncpy(transaction->description, encryptedDescription, NAME_LENGTH);

            printf("Transaction processed. New balance for %s: %.2f\n", customer->name, customer->balance);
            saveTransactionsToFile(manager);  // Save transaction data after making a change
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

void viewTransactionHistory(CustomerManager* manager, int id) {
    loadTransactionsFromFile(manager);  // Load transaction data before viewing
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            Customer* customer = &manager->customers[i];  // Non-const Customer pointer
            printf("Transaction history for %s (ID: %d):\n", customer->name, customer->id);
            for (int j = 0; j < customer->transactionCount; ++j) {
                printf("Transaction %d: Amount: %.2f, Description: %s\n",
                       j + 1, customer->transactions[j].amount, customer->transactions[j].description);
            }
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}
