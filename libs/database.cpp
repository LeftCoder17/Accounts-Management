#include "database.h"

Database::Database()
{
}


Database::~Database()
{
    for (Account *account : m_accounts)
    {
        delete account;
    }
}



void Database::read_database()
{
    // Missing
}


void Database::store_database()
{
    // Missing
}


void Database::add_account(QString accountName, float initialMoney)
{
    Account *newAccount = new Account(accountName, initialMoney);
    m_nAccounts += 1;
    m_accounts.push_back(newAccount);
}


void Database::add_transaction(QString accountName, bool isPayment, QString type, QString subtype, float money, QDate date)
{
    for (Account *account : m_accounts)
    {
        if (account->get_name() == accountName)
        {
            account->add_transaction(isPayment, type, subtype, money, date);
            break;
        }
    }
}


int Database::get_nAccounts()
{
    return m_nAccounts;
}


QString Database::get_name()
{
    return m_name;
}


QString Database::get_path()
{
    return m_path;
}


Account* Database::get_account(int index)
{
    if (index >= 0 && index < m_accounts.size()) {
        return m_accounts[index];
    }
    return nullptr;
}


std::vector<QString> Database::get_accounts_names_vector()
{
    std::vector<QString> namesVector {};
    for (Account *account : m_accounts)
    {
        namesVector.push_back(account->get_name());
    }
    return namesVector;
}


void Database::set_name(QString name)
{
    m_name = name;
}
void Database::set_path(QString path)
{
    m_path = path;
}
