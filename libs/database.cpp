#include "database.h"
#include <fstream>
#include <string>
#include <sstream>
#include <QMessageBox>
#include <QDate>
#include <QString>


Database::~Database()
{
    for (Account *account : m_accounts)
    {
        delete account;
    }
}



void Database::read_database(QWidget *parent)
{
    std::ifstream file;
    file.open(m_path.toStdString().c_str());

    if (!file.is_open())
    {
        QMessageBox::critical(parent, "Error", "No s'ha pogut obrir el fitxer");
        return;
    }

    std::string line;
    std::getline(file, line); // Ignore header

    // 1. Read number of accounts

    std::getline(file, line);
    std::istringstream iss(line);
    std::string aux;
    int nAccounts;
    iss >> aux >> aux >> aux >> nAccounts;

    // 2. Read accounts

    for (int index = 0; index < nAccounts; index++)
    {
        std::getline(file, line); // Ignore separator

        // 2.1. Add account

        std::getline(file, line); // Account name
        std::string accountName;
        std::istringstream accountLine(line);
        accountLine >> aux >> aux >> aux >> accountName;
        std::getline(file, line); // Money
        std::string moneyStr;
        std::istringstream moneyLine(line);
        moneyLine >> aux >> moneyStr;
        float money = std::stof(moneyStr);

        add_account(QString::fromStdString(accountName), money);

        // 2.2. Add transactions
        std::getline(file, line); // Number of transactions
        std::string nTransactionStr;
        std::istringstream nTransactionsLine(line);
        nTransactionsLine >> aux >> aux >> aux >> nTransactionStr;
        int numTransactions = std::stoi(nTransactionStr);
        std::getline(file, line); // Ignore separator
        for (int transIndex = 0; transIndex < numTransactions; transIndex++)
        {
            std::getline(file, line); // Transaction
            std::string transactionType, type, subtype, valueStr, dateStr;
            std::istringstream transactionLine(line);
            std::getline(transactionLine, transactionType, ',');
            std::getline(transactionLine, type, ',');
            std::getline(transactionLine, subtype, ',');
            std::getline(transactionLine, valueStr, ',');
            std::getline(transactionLine, dateStr);
            
            bool isPayment = (transactionType == "Despesa");
            float value = std::stoi(valueStr);
            QDate date = QDate::fromString(QString::fromStdString(dateStr));

            add_transaction(QString::fromStdString(accountName),
                            isPayment,
                            QString::fromStdString(type),
                            QString::fromStdString(subtype),
                            value,
                            date);
        }
        Account *currAccount = get_account(index);
        currAccount->set_money(money);
    }

    // 3. Close file
    file.close();
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
