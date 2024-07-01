#include "database.h"
#include <fstream>
#include <string>
#include <QMessageBox>
#include <QDate>
#include <QString>

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


void Database::store_database(QWidget *parent)
{
    std::ofstream file;
    file.open(m_path.toStdString().c_str());

    if (!file.is_open())
    {
        QMessageBox::critical(parent, "Error", "No s'ha pogut obrir el fitxer");
        return;
    }
    file << "ACCOUNT_MANAGEMENT_DATABASE\n";
    file << "Nombre de comptes: " << m_nAccounts << std::endl;
    for (Account* account : m_accounts)
    {
        file << "##########################################" << std::endl;
        file << "Nom del compte: " << account->get_name().toStdString() << std::endl;
        file << "Diners: " << account->get_money() << std::endl;
        int nTransactions = account->get_nTransactions();
        file << "Nombre de transaccions: " << nTransactions << std::endl;
        file << "-----------------------------" << std::endl;
        for (int index = 0; index < nTransactions; index++)
        {
            Transaction *transaction = account->get_transaction(index);
            std::string transactionType = transaction->m_isPayment ? "Despesa" : "Ingres";
            file << transactionType << "," << transaction->m_type.toStdString() << "," << transaction->m_subtype.toStdString();
            file << "," << transaction->m_value << "," << transaction->m_date.toString().toStdString() << std::endl;
        }
    }
    file.close();
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
