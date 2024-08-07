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

    // Add a new transaction using Raw data
    void add_transaction(bool isPayment, QString type, QString subtype, float money, QDate date);

    // Add a new transaction using a transaction structure
    void add_transaction(Transaction *newTransaction);

    // Getters
    
    QString get_name();
    float get_money();
    int get_nTransactions();
    Transaction* get_transaction(int index);

    // Setters
    void set_name(QString name);
    void set_money(float money);


private: // Members
    QString m_name {};
    float m_money {};
    int m_nTransactions {0};
    std::vector<Transaction*> m_transactions {};

};





#endif // ACCOUNT_H