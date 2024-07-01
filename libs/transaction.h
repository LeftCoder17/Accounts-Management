#ifndef TRANSACTION_H
#define TRANSACTION_H

#include "labels.h"
#include <QDate>

struct Transaction
{
    // Members
    bool m_isPayment {};
    QString m_type {};
    QString m_subtype {};
    float m_value {};
    QDate m_date {};

    // Default constructor
    Transaction() = default;
    // Constructor
    Transaction(bool isPayment, QString type, QString subtype, float money, QDate date);
    // Default destructor
    ~Transaction() = default;
};



#endif // TRANSACTION_H