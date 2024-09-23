#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "customer.h"

void createAccount(CustomerManager* manager, int id, const char* name, const char* password, float initialBalance);

#endif // ACCOUNT_H
