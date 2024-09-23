#ifndef FILE_MANAGER_H
#define FILE_MANAGER_H

#include "customer.h"

void saveCustomersToFile(CustomerManager* manager);
void loadCustomersFromFile(CustomerManager* manager);
void saveTransactionsToFile(CustomerManager* manager);
void loadTransactionsFromFile(CustomerManager* manager);  // Remove 'const' here

#endif // FILE_MANAGER_H

