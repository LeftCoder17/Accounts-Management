#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <QString>
#include "account.h"

class Database
{
public:
    // Default constructor
    Database();
    // Destructor
    ~Database();

    // Read the database to upload the information
    void read_database();

    // Store the database
    void store_database();

    // Add a new account
    void add_account(QString accountName, float initialMoney);

    // Getters

    int get_nAccounts();
    QString get_name();
    QString get_path();
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