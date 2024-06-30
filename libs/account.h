#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <QString>

#include "transaction.h"

class Account
{
public:
    // Default constructor
    Account();
    // Constructor
    Account(QString accountName, float initialMoney);
    // Destructor
    ~Account();

    // Getters
    QString get_name();
    float get_money();



    // Setters


private: // Members
    QString m_name {};
    float m_money {};
    int m_nTransactions {0};
    std::vector<Transaction*> m_transactions {};

};





#endif // ACCOUNT_H