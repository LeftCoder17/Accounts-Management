#ifndef LABELS_H
#define LABELS_H

#include <string>

typedef struct
{
    std::string label;
    int code;
} LabelSubtype;

typedef struct LabelType
{
    std::string label;
    int code;
    int nSubtypes;
    LabelSubtype *subtypes;
} LabelType;

class TransactionTypes
{
public:
    // Constructor
    TransactionTypes();
    // Destructor
    ~TransactionTypes();

public: // Members
    int m_nPaymentTypes {};
    int m_nIncomeTypes {};
    LabelType *m_paymentTypes {nullptr};
    LabelType *m_incomeTypes {nullptr};
};

#endif // LABELS_H