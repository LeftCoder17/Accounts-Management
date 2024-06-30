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


QString Account::get_name()
{
    return m_name;
}


float Account::get_money()
{
    return m_money;
}