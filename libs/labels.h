#ifndef LABELS_H
#define LABELS_H

#include <QString>
#include <vector>

typedef struct
{
    QString label;
    int code;
} LabelSubtype;

typedef struct LabelType
{
    QString label;
    int code;
    int nSubtypes;
    std::vector<LabelSubtype> subtypes;
} LabelType;

class TransactionLabels
{
public:
    // Constructor
    TransactionLabels();
    // Destructor
    ~TransactionLabels();



public: // Members
    int m_nPaymentTypes {};
    int m_nIncomeTypes {};
    std::vector<LabelType> m_paymentTypes {};
    std::vector<LabelType> m_incomeTypes {};
};

#endif // LABELS_H