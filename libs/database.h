#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <QWidget>
#include <QString>
#include <QDate>
#include "account.h"

class Database
{
public:
    // Default constructor
    Database() = default;
    // Destructor
    ~Database();

    // Read the database to upload the information
    void read_database(QWidget *parent);

    // Store the database
    void store_database(QWidget *parent);

    // Add a new account
    void add_account(QString accountName, float initialMoney);

    // Add a new transaction using the Raw data
    void add_transaction(QString accountName, bool isPayment, QString type, QString subtype, float money, QDate date);

    // Add a new transaction using a transaction structure
    void add_transaction(QString accountName, Transaction *newTransaction);

    // Add transactions from a file
    void add_transactions_from_file(QString filePath, QWidget *parent);

    // Getters

    int get_nAccounts();
    QString get_name();
    QString get_path();
    std::vector<QString> get_accounts_names_vector();
    Account *get_account(int index);

    // Setters

    void set_name(QString name);
    void set_path(QString path);


private: // Members
    QString m_name {};
    QString m_path {};
    int m_nAccounts {0};
    std::vector<Account*> m_accounts {};

};





#endif // DATABASE_H