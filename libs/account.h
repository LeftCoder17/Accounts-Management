#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <vector>
#include <QString>
#include <QDate>
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

    // Add a new transaction
    void add_transaction(bool isPayment, QString type, QString subtype, float money, QDate date);

    // Getters
    QString get_name();
    float get_money();
    int get_nTransactions();
    Transaction* get_transaction(int index);



    // Setters


private: // Members
    QString m_name {};
    float m_money {};
    int m_nTransactions {0};
    std::vector<Transaction*> m_transactions {};

};





#endif // ACCOUNT_H