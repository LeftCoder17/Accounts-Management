#include "account.h"

Account::Account(QString accountName, float initialMoney)
{
    m_name = accountName;
    m_money = initialMoney;
}


Account::~Account()
{
    for (Transaction *transaction : m_transactions)
    {
        delete transaction;
    }
}


void Account::add_transaction(bool isPayment, QString type, QString subtype, float money, QDate date)
{
    Transaction *transaction = new Transaction(isPayment, type, subtype, money, date);
    m_nTransactions++;
    m_transactions.push_back(transaction);
    m_money += isPayment ? (- money) : (money);
}


QString Account::get_name()
{
    return m_name;
}


float Account::get_money()
{
    return m_money;
}


int Account::get_nTransactions()
{
    return m_nTransactions;
}


Transaction* Account::get_transaction(int index)
{
    return m_transactions.at(index);
}