#include <stdio.h>
#include <string.h>
#include "customer.h"
#include "file_manager.h"
#include "security.h"

void createAccount(CustomerManager* manager, int id, const char* name, const char* password, float initialBalance) {
    if (manager->count >= MAX_CUSTOMERS) {
        printf("Error: Cannot create new account. Customer limit reached.\n");
        return;
    }

    Customer* customer = &manager->customers[manager->count++];
    customer->id = id;
    strncpy(customer->name, name, NAME_LENGTH);

    // Hash the password before storing it
    char hashedPassword[65];  // 64 chars for SHA-256 + null terminator
    hashPassword(password, hashedPassword);
    strncpy(customer->password, hashedPassword, NAME_LENGTH);

    customer->balance = initialBalance;
    customer->transactionCount = 0;
    customer->loanCount = 0;

    saveCustomersToFile(manager);  // Save customer data to file after creation
    printf("Account created for %s with ID %d.\n", name, id);
}

void viewAccountDetails(CustomerManager* manager, int id) {
    loadCustomersFromFile(manager);  // Load customer data from file before viewing
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

