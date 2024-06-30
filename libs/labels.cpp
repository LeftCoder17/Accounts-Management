#include "labels.h"
#include <fstream>
#include <sstream>

TransactionTypes::TransactionTypes()
{
    // 1. Open file
    std::ifstream labelsFile;
    labelsFile.open("labels.txt");

    std::string line;
    int index_type, index_subtype;

    std::getline(labelsFile, line); // Ignore

    // 2. Read Payment Types
    std::getline(labelsFile, line);
    m_nPaymentTypes = std::stoi(line);
    m_paymentTypes = new LabelType[m_nPaymentTypes];

    for (index_type = 0; index_type < m_nPaymentTypes; index_type++)
    {
        std::getline(labelsFile, line);

        std::istringstream ss(line);
        std::string code, label;

        ss >> code >> label;

        m_paymentTypes[index_type].code = std::stoi(code);
        m_paymentTypes[index_type].label = label;
    }

    // 3. Read Payment Subtypes
    for (index_type = 0; index_type < m_nPaymentTypes; index_type++)
    {
        std::getline(labelsFile, line); // Ignore
        std::getline(labelsFile, line);
        m_paymentTypes[index_type].nSubtypes = std::stoi(line);
        m_paymentTypes[index_type].subtypes = new LabelSubtype[m_paymentTypes[index_type].nSubtypes];

        for (index_subtype = 0; index_subtype < m_paymentTypes[index_type].nSubtypes; index_subtype++)
        {
            std::getline(labelsFile, line);

            std::istringstream ss(line);
            std::string code, label;

            ss >> code >> label;

            m_paymentTypes[index_type].subtypes[index_subtype].code = std::stoi(code);
            m_paymentTypes[index_type].subtypes[index_subtype].label = label;
        }
    }

    // 4. Read Income Types
    std::getline(labelsFile, line); // Ignore
    std::getline(labelsFile, line);
    m_nIncomeTypes = std::stoi(line);
    m_incomeTypes = new LabelType[m_nIncomeTypes];

    for (index_type = 0; index_type < m_nIncomeTypes; index_type++)
    {
        std::getline(labelsFile, line);

        std::istringstream ss(line);
        std::string code, label;

        ss >> code >> label;

        m_incomeTypes[index_type].code = std::stoi(code);
        m_incomeTypes[index_type].label = label;
    }

    // 5. Read Income Subtypes
    for (index_type = 0; index_type < m_nPaymentTypes; index_type++)
    {
        std::getline(labelsFile, line); // Ignore
        std::getline(labelsFile, line);
        m_incomeTypes[index_type].nSubtypes = std::stoi(line);
        m_incomeTypes[index_type].subtypes = new LabelSubtype[m_incomeTypes[index_type].nSubtypes];

        for (index_subtype = 0; index_subtype < m_incomeTypes[index_type].nSubtypes; index_subtype++)
        {
            std::getline(labelsFile, line);

            std::istringstream ss(line);
            std::string code, label;

            ss >> code >> label;

            m_incomeTypes[index_type].subtypes[index_subtype].code = std::stoi(code);
            m_incomeTypes[index_type].subtypes[index_subtype].label = label;
        }
    }

    // 6. Close file
    labelsFile.close();
}

TransactionTypes::~TransactionTypes()
{
    int index;
    for (index = 0; index < m_nPaymentTypes; index++)
    {
        delete m_paymentTypes[index].subtypes;
    }
    for (index = 0; index < m_nIncomeTypes; index++)
    {
        delete m_incomeTypes[index].subtypes;
    }
    delete m_paymentTypes;
    delete m_incomeTypes;
}