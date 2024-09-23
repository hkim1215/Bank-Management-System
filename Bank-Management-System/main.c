#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>  // Include pthread for multi-threading
#include "customer.h"
#include "transaction.h"
#include "loan.h"
#include "admin.h"
#include "file_manager.h"
#include "security.h"

// ASCII art for a simple bank logo
void printBankLogo() {
    printf("=======================================\n");
    printf("     Welcome to XYZ Bank System\n");
    printf("=======================================\n");
}

void printMainMenu() {
    printf("\nMain Menu:\n");
    printf("1. Customer Login\n");
    printf("2. Admin Login\n");
    printf("3. Simulate Multi-threaded Transactions\n");  // New option for multi-threading
    printf("4. Exit\n");
    printf("Choose an option: ");
}

void printCustomerMenu() {
    printf("\nCustomer Menu:\n");
    printf("1. View Account Details\n");
    printf("2. Deposit\n");
    printf("3. Withdraw\n");
    printf("4. View Transaction History\n");
    printf("5. Apply for Loan\n");
    printf("6. Repay Loan\n");
    printf("7. Log Out\n");
    printf("Choose an option: ");
}

void printAdminMenu() {
    printf("\nAdmin Menu:\n");
    printf("1. View All Accounts\n");
    printf("2. View Total Balance\n");
    printf("3. View All Transactions\n");
    printf("4. Log Out\n");
    printf("Choose an option: ");
}

// Simulate customer operations with multi-threading
void* customerOperations(void* arg) {
    CustomerManager* manager = (CustomerManager*)arg;
    // Simulate a customer performing some transactions
    processTransaction(manager, 1, 100.0f, "Deposit");
    processTransaction(manager, 1, -50.0f, "Withdrawal");
    viewTransactionHistory(manager, 1);
    return NULL;
}

int main() {
    CustomerManager manager = {0};  // Initialize manager with zero customers
    loadCustomersFromFile(&manager);  // Load existing customers from file

    printBankLogo();

    int choice;
    while (1) {
        printMainMenu();
        scanf("%d", &choice);

        if (choice == 1) {  // Customer Login
            int customerID;
            char password[NAME_LENGTH];
            printf("Enter Customer ID: ");
            scanf("%d", &customerID);
            printf("Enter Password: ");
            scanf("%s", password);

            // Check if customer exists and verify password
            for (int i = 0; i < manager.count; ++i) {
                if (manager.customers[i].id == customerID &&
                    verifyPassword(password, manager.customers[i].password)) {

                    int customerChoice;
                    while (1) {
                        printCustomerMenu();
                        scanf("%d", &customerChoice);

                        if (customerChoice == 1) {
                            viewAccountDetails(&manager, customerID);
                        } else if (customerChoice == 2) {
                            float depositAmount;
                            printf("Enter amount to deposit: ");
                            scanf("%f", &depositAmount);
                            processTransaction(&manager, customerID, depositAmount, "Deposit");
                        } else if (customerChoice == 3) {
                            float withdrawAmount;
                            printf("Enter amount to withdraw: ");
                            scanf("%f", &withdrawAmount);
                            processTransaction(&manager, customerID, -withdrawAmount, "Withdrawal");
                        } else if (customerChoice == 4) {
                            viewTransactionHistory(&manager, customerID);
                        } else if (customerChoice == 5) {
                            float loanAmount;
                            float interestRate;
                            int durationMonths;
                            printf("Enter loan amount: ");
                            scanf("%f", &loanAmount);
                            printf("Enter interest rate: ");
                            scanf("%f", &interestRate);
                            printf("Enter duration (in months): ");
                            scanf("%d", &durationMonths);
                            applyForLoan(&manager, customerID, loanAmount, interestRate, durationMonths);
                        } else if (customerChoice == 6) {
                            int loanIndex;
                            float repayAmount;
                            printf("Enter loan index to repay: ");
                            scanf("%d", &loanIndex);
                            printf("Enter repayment amount: ");
                            scanf("%f", &repayAmount);
                            repayLoan(&manager, customerID, loanIndex, repayAmount);
                        } else if (customerChoice == 7) {
                            printf("Logging out...\n");
                            break;
                        }
                    }
                } else {
                    printf("Error: Invalid Customer ID or Password\n");
                }
            }
        } else if (choice == 2) {  // Admin Login
            char adminPassword[NAME_LENGTH];
            printf("Enter Admin Password: ");
            scanf("%s", adminPassword);

            if (strcmp(adminPassword, "adminpass") == 0) {
                int adminChoice;
                while (1) {
                    printAdminMenu();
                    scanf("%d", &adminChoice);

                    if (adminChoice == 1) {
                        adminViewAllAccounts(&manager);
                    } else if (adminChoice == 2) {
                        adminViewTotalBalance(&manager);
                    } else if (adminChoice == 3) {
                        adminViewAllTransactions(&manager);
                    } else if (adminChoice == 4) {
                        printf("Logging out...\n");
                        break;
                    }
                }
            } else {
                printf("Error: Invalid Admin Password\n");
            }
        } else if (choice == 3) {  // Multi-threaded simulation
            printf("Simulating multi-threaded customer operations...\n");

            pthread_t thread1, thread2;

            // Create two threads simulating two customers performing operations simultaneously
            pthread_create(&thread1, NULL, customerOperations, (void*)&manager);
            pthread_create(&thread2, NULL, customerOperations, (void*)&manager);

            // Wait for both threads to finish
            pthread_join(thread1, NULL);
            pthread_join(thread2, NULL);

            printf("Multi-threaded operations completed.\n");
        } else if (choice == 4) {
            printf("Exiting system...\n");
            break;
        } else {
            printf("Invalid choice, please try again.\n");
        }
    }

    saveCustomersToFile(&manager);  // Save customers to file on exit
    return 0;
}

