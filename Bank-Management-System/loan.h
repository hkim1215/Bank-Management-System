#ifndef LOAN_H
#define LOAN_H

#include "customer.h"

void applyForLoan(CustomerManager* manager, int id, float loanAmount, float interestRate, int durationMonths);
void repayLoan(CustomerManager* manager, int id, int loanIndex, float repaymentAmount);

#endif // LOAN_H

