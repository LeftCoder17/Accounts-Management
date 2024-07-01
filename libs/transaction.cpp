#include "transaction.h"

Transaction::Transaction(bool isPayment, QString type, QString subtype, float money, QDate date)
{
    m_isPayment = isPayment;
    m_type = type;
    m_subtype = subtype;
    m_value = money;
    m_date = date;
}
