#ifndef CUSTOMER_H
#define CUSTOMER_H

#define MAX_CUSTOMERS 100
#define NAME_LENGTH 100
#define MAX_TRANSACTIONS 100
#define MAX_LOANS 10

// Transaction structure
typedef struct {
    float amount;
    char description[NAME_LENGTH];
} Transaction;

// Loan structure
typedef struct {
    float amount;
    float interestRate;
    int durationMonths;
} Loan;

// Customer structure
typedef struct {
    int id;
    char name[NAME_LENGTH];
    float balance;
    Transaction transactions[MAX_TRANSACTIONS];
    int transactionCount;
    Loan loans[MAX_LOANS];
    int loanCount;
    char password[NAME_LENGTH];
} Customer;

// CustomerManager structure
typedef struct {
    Customer customers[MAX_CUSTOMERS];
    int count;
} CustomerManager;

// Function declarations
void createAccount(CustomerManager* manager, int id, const char* name, const char* password, float initialBalance);
void viewAccountDetails(CustomerManager* manager, int id);  // Remove 'const' from CustomerManager*

#endif // CUSTOMER_H


