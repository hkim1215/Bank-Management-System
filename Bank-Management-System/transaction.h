#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "customer.h"

void processTransaction(CustomerManager* manager, int id, float amount, const char* description);
void viewTransactionHistory(CustomerManager* manager, int id);

#endif // TRANSACTION_H

