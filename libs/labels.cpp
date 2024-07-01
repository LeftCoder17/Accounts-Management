#include "labels.h"
#include <QDebug>
#include <QFile>
#include <QTextStream>


TransactionLabels::TransactionLabels()
{
    // 1. Open file using QFile
    QFile file(":/labels.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qCritical() << "Failed to open labels file:" << file.errorString();
        return;
    }

    QTextStream labelsFile(&file);

    // 2. Read the first line (if needed)
    QString line = labelsFile.readLine(); // Read first line

    // 3. Read Payment Types
    line = labelsFile.readLine(); // Read next line
    m_nPaymentTypes = line.toInt();

    for (int index_type = 0; index_type < m_nPaymentTypes; index_type++)
    {
        line = labelsFile.readLine().trimmed(); // Read next line and trim whitespace

        QStringList parts = line.split(" ");
        if (parts.size() >= 2) {
            LabelType newLabelType;
            newLabelType.code = parts[0].toInt();
            newLabelType.label = parts.mid(1).join(" ");
            m_paymentTypes.push_back(newLabelType);
        }
    }

    // 4. Read Payment Subtypes
    for (int index_type = 0; index_type < m_nPaymentTypes; index_type++)
    {
        labelsFile.readLine(); // Ignore
        line = labelsFile.readLine().trimmed();

        int nSubtypes = line.toInt();
        m_paymentTypes[index_type].nSubtypes = nSubtypes;

        for (int index_subtype = 0; index_subtype < nSubtypes; index_subtype++)
        {
            line = labelsFile.readLine().trimmed();

            QStringList parts = line.split(" ");
            if (parts.size() >= 2) {
                LabelSubtype newLabelSubtype;
                newLabelSubtype.code = parts[0].toInt();
                newLabelSubtype.label = parts.mid(1).join(" ");
                m_paymentTypes[index_type].subtypes.push_back(newLabelSubtype);
            }
        }
    }

    // 5. Read Income Types
    labelsFile.readLine(); // Ignore
    line = labelsFile.readLine().trimmed();
    m_nIncomeTypes = line.toInt();

    for (int index_type = 0; index_type < m_nIncomeTypes; index_type++)
    {
        line = labelsFile.readLine().trimmed();

        QStringList parts = line.split(" ");
        if (parts.size() >= 2) {
            LabelType newLabelType;
            newLabelType.code = parts[0].toInt();
            newLabelType.label = parts.mid(1).join(" ");
            m_incomeTypes.push_back(newLabelType);
        }
    }

    // 6. Read Income Subtypes
    for (int index_type = 0; index_type < m_nIncomeTypes; index_type++)
    {
        labelsFile.readLine(); // Ignore
        line = labelsFile.readLine().trimmed();

        int nSubtypes = line.toInt();
        m_incomeTypes[index_type].nSubtypes = nSubtypes;

        for (int index_subtype = 0; index_subtype < nSubtypes; index_subtype++)
        {
            line = labelsFile.readLine().trimmed();

            QStringList parts = line.split(" ");
            if (parts.size() >= 2) {
                LabelSubtype newLabelSubtype;
                newLabelSubtype.code = parts[0].toInt();
                newLabelSubtype.label = parts.mid(1).join(" ");
                m_incomeTypes[index_type].subtypes.push_back(newLabelSubtype);
            }
        }
    }

    // 7. Close file
    file.close();
}

TransactionLabels::~TransactionLabels()
{
}
