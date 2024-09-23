#include <stdio.h>
#include "loan.h"

void applyForLoan(CustomerManager* manager, int id, float loanAmount, float interestRate, int durationMonths) {
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            Customer* customer = &manager->customers[i];
            if (customer->loanCount >= MAX_LOANS) {
                printf("Error: Cannot apply for more loans. Loan limit reached.\n");
                return;
            }

            Loan* loan = &customer->loans[customer->loanCount++];
            loan->amount = loanAmount;
            loan->interestRate = interestRate;
            loan->durationMonths = durationMonths;

            printf("Loan of %.2f applied with %.2f%% interest for %d months.\n", loanAmount, interestRate, durationMonths);
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

void repayLoan(CustomerManager* manager, int id, int loanIndex, float repaymentAmount) {
    for (int i = 0; i < manager->count; ++i) {
        if (manager->customers[i].id == id) {
            Customer* customer = &manager->customers[i];
            if (loanIndex >= 0 && loanIndex < customer->loanCount) {
                Loan* loan = &customer->loans[loanIndex];
                loan->amount -= repaymentAmount;

                if (loan->amount <= 0) {
                    printf("Loan fully repaid.\n");
                } else {
                    printf("Remaining loan amount: %.2f\n", loan->amount);
                }

                // Update customer's balance
                customer->balance -= repaymentAmount;
                printf("New balance after repayment: %.2f\n", customer->balance);
                return;
            }
            printf("Error: Invalid loan index.\n");
            return;
        }
    }
    printf("Error: Account with ID %d not found.\n", id);
}

