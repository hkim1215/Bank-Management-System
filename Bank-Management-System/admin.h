#ifndef ADMIN_H
#define ADMIN_H

#include "customer.h"  // Include necessary headers for function definitions

// Declare admin functions
void adminViewAllAccounts(CustomerManager* manager);
void adminViewTotalBalance(CustomerManager* manager);
void adminViewAllTransactions(CustomerManager* manager);

#endif // ADMIN_H
