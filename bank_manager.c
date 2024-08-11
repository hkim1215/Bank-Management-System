#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CUSTOMERS 100
#define NAME_LENGTH 100
#define MAX_TRANSACTIONS 100

typedef struct {
    float amount;
    char description[NAME_LENGTH];
} Transaction;

typedef struct {
    int id;
    char name[NAME_LENGTH];
    float balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
} Customer;

typedef struct {
    Customer customers[MAX_CUSTOMERS];
    int count;
} CustomerManager;

void createAccount(CustomerManager* manager, int id, const char* name, float initialBalance) {
    if (manager->count >= MAX_CUSTOMERS) {
        printf("Error: Cannot create new account. Customer limit reached.\n");
        return;
    }

    Customer* customer = &manager->customers[manager->count++];
    customer->id = id;
    strncpy(customer->name, name, NAME_LENGTH);
    customer->balance = initialBalance;
    customer->transactionCount = 0;
    printf("Account created for %s with ID %d.\n", name, id);
}

void updateAccount(CustomerManager* manager, int id, const char* newName, float newBalance) {
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            strncpy(manager->customers[i].name, newName, NAME_LENGTH);
            manager->customers[i].balance = newBalance;
            printf("Account updated for ID %d.\n", id);
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

void deleteAccount(CustomerManager* manager, int id) {
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            for (int j = i; j < manager->count - 1; ++j) {
                manager->customers[j] = manager->customers[j + 1];
            }
            --manager->count;
            printf("Account with ID %d deleted.\n", id);
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

void viewAccountDetails(const CustomerManager* manager, int id) {
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            printf("Account ID: %d\n", manager->customers[i].id);
            printf("Name: %s\n", manager->customers[i].name);
            printf("Balance: %.2f\n", manager->customers[i].balance);
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

void processTransaction(CustomerManager* manager, int id, float amount, const char* description) {
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
            strncpy(transaction->description, description, NAME_LENGTH);

            printf("Transaction processed. New balance for %s: %.2f\n", customer->name, customer->balance);
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

void viewTransactionHistory(const CustomerManager* manager, int id) {
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            Customer* customer = &manager->customers[i];
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

int main() {
    CustomerManager manager = {0};  // Initialize manager with zero customers

    createAccount(&manager, 1, "John Doe", 1000.00f);
    createAccount(&manager, 2, "Jane Smith", 1500.00f);

    viewAccountDetails(&manager, 1);
    processTransaction(&manager, 1, 500.00f, "Deposit");
    processTransaction(&manager, 1, -200.00f, "Withdrawal");
    viewAccountDetails(&manager, 1);
    viewTransactionHistory(&manager, 1);

    updateAccount(&manager, 2, "Jane Doe", 2000.00f);
    viewAccountDetails(&manager, 2);

    deleteAccount(&manager, 1);
    viewAccountDetails(&manager, 1); 

    return 0;
}
