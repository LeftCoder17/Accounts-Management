#include "mainwindow.h"
#include <string>
#include <fstream>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>
#include <QCoreApplication>
#include <QDialog>
#include <QComboBox>
#include <QStringList>
#include <QDateEdit>
#include <QDate>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    // Initialize stack widget and main menu.
    resize(800, 600);
    m_stackWidget = new QStackedWidget(this);
    setupMainMenu();
    setCentralWidget(m_stackWidget);
    setStyleSheet(
        "QWidget {"
        "    background-color: #f0f0f0;"
        "}"
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-size: 16px;"
        "    padding: 10px 20px;"
        "    border: none;"
        "    border-radius: 5px;"
        "    margin: 10px 0;"
        "}"
        "QPushButton:hover {"
        "    background-color: #45a049;"
        "}"
        "QPushButton:pressed {"
        "    background-color: #3e8e41;"
        "}"
    );
}

MainWindow::~MainWindow()
{
    // When finished, delete all allocated memory
}

void MainWindow::setupMainMenu()
{
    // 1. Initialize objects of the main menu
    m_mainMenuWidget = new QWidget(this);
    m_mainMenuLayout = new QVBoxLayout(m_mainMenuWidget);

    m_titleLabel = new QLabel("GESTIO I ANALISIS DE COMPTES", this);
    m_titleLabel->setAlignment(Qt::AlignCenter);
    m_titleLabel->setStyleSheet(
        "font-size: 30px;"
        "font-weight: bold;"
        "color: #333;"
        "padding: 20px;"
        "background-color: #e0e0e0;"
        "border-radius: 10px;"
        "margin-bottom: 20px;"
    );

    m_createDatabaseButton = new QPushButton("Crear una nova base de dades", this);
    m_openDatabaseButton = new QPushButton("Obrir una base de dades existent", this);
    m_exitButton = new QPushButton("Tancar el programa", this);

    // 2. Add objects to the main manu
    m_mainMenuLayout->addWidget(m_titleLabel);
    m_mainMenuLayout->addWidget(m_createDatabaseButton);
    m_mainMenuLayout->addWidget(m_openDatabaseButton);
    m_mainMenuLayout->addWidget(m_exitButton);

    // 3. Connect buttons with functions
    connect(m_createDatabaseButton, &QPushButton::clicked, this, &MainWindow::createDatabase);
    connect(m_openDatabaseButton, &QPushButton::clicked, this, &MainWindow::openDatabase);
    connect(m_exitButton, &QPushButton::clicked, this, &MainWindow::exitProgram);

    // 4. Set up the distribution
    m_mainMenuLayout->setSpacing(20);
    m_mainMenuLayout->setContentsMargins(50, 50, 50, 50);
    m_mainMenuLayout->setAlignment(Qt::AlignCenter);

    // 5. Add the layout to the stackWidget
    m_stackWidget->addWidget(m_mainMenuWidget);
}


void MainWindow::setupDatabaseMenu()
{
    // 0. Read the database and the transaction labels
    // Missing
    m_transactionLabels = new TransactionLabels();
    m_unsavedChanges = false;

    // 1. Initialize objects of the database menu
    m_databaseMenuWidget = new QWidget(this);
    m_databaseGridLayout = new QGridLayout(m_databaseMenuWidget);

    // 2.1. Configure the Summary Section (Top Left)
    m_summaryWidget = new QWidget(this);
    m_summaryLayout = new QVBoxLayout(m_summaryWidget);
    m_databaseNameLabel = new QLabel("Nom de la base de dades: " + m_database->get_name(), this);
    m_accountCountLabel = new QLabel(this);
    m_accountDetailsLabel = new QLabel(this);
    update_summary();
    m_showLastTransactionsButton = new QPushButton("Ultimes transaccions", this);

    m_databaseNameLabel->setStyleSheet("font-size: 20px; font-weight: bold; color: #333;");
    m_accountCountLabel->setStyleSheet("font-size: 16px; color: #555;");
    m_accountDetailsLabel->setStyleSheet("font-size: 16px; color: #555;");
    m_showLastTransactionsButton->setStyleSheet("padding: 10px; background-color: #0A4EAD; color: black; border: none; border-radius: 5px;");

    m_summaryWidget->setStyleSheet("background-color: #cce3e6; border: 1px solid #a7ffeb; border-radius: 10px; padding: 15px;");

    m_summaryLayout->addWidget(m_databaseNameLabel);
    m_summaryLayout->addWidget(m_accountCountLabel);
    m_summaryLayout->addWidget(m_accountDetailsLabel);
    m_summaryLayout->addWidget(m_showLastTransactionsButton);

    // 2.2. Configure the Edit Section (Top Right)
    m_editWidget = new QWidget(this);
    m_editLayout = new QVBoxLayout(m_editWidget);
    m_addAccountButton = new QPushButton("Afegeix un compte", this);
    m_modifyAccountButton = new QPushButton("Modifica un compte", this);
    m_addTransactionButton = new QPushButton("Afegeix una transaccio", this);
    m_modifyTransactionButton = new QPushButton("Modifica una transaccio", this);
    m_addTransactionsfromFileButton = new QPushButton("Afegeix transaccions des d'un fitxer", this);

    m_addAccountButton->setStyleSheet("padding: 10px; background-color: #a52727; color: black; border: none; border-radius: 5px;");
    m_modifyAccountButton->setStyleSheet("padding: 10px; background-color: #a52727; color: black; border: none; border-radius: 5px;");
    m_addTransactionButton->setStyleSheet("padding: 10px; background-color: #a52727; color: black; border: none; border-radius: 5px;");
    m_modifyTransactionButton->setStyleSheet("padding: 10px; background-color: #a52727; color: black; border: none; border-radius: 5px;");
    m_addTransactionsfromFileButton->setStyleSheet("padding: 10px; background-color: #a52727; color: black; border: none; border-radius: 5px;");

    m_editWidget->setStyleSheet("background-color: #ffebee; border: 1px solid #ffcdd2; border-radius: 10px; padding: 15px;");

    m_editLayout->addWidget(m_addAccountButton);
    m_editLayout->addWidget(m_modifyAccountButton);
    m_editLayout->addWidget(m_addTransactionButton);
    m_editLayout->addWidget(m_modifyTransactionButton);
    m_editLayout->addWidget(m_addTransactionsfromFileButton);

    // 2.3. Configure the Manage Database Section (Bottom Left)
    m_manageDatabaseWidget = new QWidget(this);
    m_manageDatabaseLayout = new QVBoxLayout(m_manageDatabaseWidget);
    m_saveDatabaseButton = new QPushButton("Desa la base de dades", this);
    m_closeDatabaseButton = new QPushButton("Tanca la base de dades", this);

    m_saveDatabaseButton->setStyleSheet("padding: 10px; background-color: #d9a73e; color: black; border: none; border-radius: 5px;");
    m_closeDatabaseButton->setStyleSheet("padding: 10px; background-color: #d9a73e; color: black; border: none; border-radius: 5px;");

    m_manageDatabaseWidget->setStyleSheet("background-color: #fff8e1; border: 1px solid #ffecb3; border-radius: 10px; padding: 15px;");

    m_manageDatabaseLayout->addWidget(m_saveDatabaseButton);
    m_manageDatabaseLayout->addWidget(m_closeDatabaseButton);

    // 2.4. Configure the Analyze Section (Bottom Right)
    m_analyseDatabaseWidget = new QWidget(this);
    m_analyseDatabaseLayout = new QVBoxLayout(m_analyseDatabaseWidget);
    m_analyseDatabaseButton = new QPushButton("Analitza la base de dades", this);

    m_analyseDatabaseButton->setStyleSheet("padding: 10px; background-color: #2d6f31; color: black; border: none; border-radius: 5px;");

    m_analyseDatabaseWidget->setStyleSheet("background-color: #e8f5e9; border: 1px solid #c8e6c9; border-radius: 10px; padding: 15px;");

    m_analyseDatabaseLayout->addWidget(m_analyseDatabaseButton);

    // 3. Add objects to the database menu grid layout
    m_databaseGridLayout->addWidget(m_summaryWidget, 0, 0);
    m_databaseGridLayout->addWidget(m_editWidget, 0, 1);
    m_databaseGridLayout->addWidget(m_manageDatabaseWidget, 1, 0);
    m_databaseGridLayout->addWidget(m_analyseDatabaseWidget, 1, 1);

    // 4. Set up the distribution
    m_databaseGridLayout->setRowStretch(0, 2); // More height for top elements
    m_databaseGridLayout->setRowStretch(1, 1); // Less height for bottom elements
    m_databaseGridLayout->setColumnStretch(0, 1);
    m_databaseGridLayout->setColumnStretch(1, 1);

    // 5. Connect buttons with functions
    connect(m_showLastTransactionsButton, &QPushButton::clicked, this, &MainWindow::show_last_transactions);
    connect(m_addAccountButton, &QPushButton::clicked, this, &MainWindow::addAccount);
    connect(m_modifyAccountButton, &QPushButton::clicked, this, &MainWindow::modifyAccount);
    connect(m_addTransactionButton, &QPushButton::clicked, this, &MainWindow::addTransaction);
    connect(m_modifyTransactionButton, &QPushButton::clicked, this, &MainWindow::modifyTransaction);
    connect(m_addTransactionsfromFileButton, &QPushButton::clicked, this, &MainWindow::addTransactionsfromFile);
    connect(m_saveDatabaseButton, &QPushButton::clicked, this, &MainWindow::saveDatabase);
    connect(m_closeDatabaseButton, &QPushButton::clicked, this, &MainWindow::closeDatabase);
    connect(m_analyseDatabaseButton, &QPushButton::clicked, this, &MainWindow::analyseDatabase);
    // Missing

    // 6. Add the layout to the stackWidget
    m_stackWidget->addWidget(m_databaseMenuWidget);
}


void MainWindow::createDatabase()
{
    QString exeDirPath = QCoreApplication::applicationDirPath();
    QDir dir(exeDirPath);
    dir.cdUp();
    dir.cdUp();
    QString appRootPath = dir.absolutePath();
    QString directory = QFileDialog::getExistingDirectory(this, "Escull carpeta", appRootPath);

    if (directory.isEmpty()) return; // User canceled the directory selection

    bool ok;
    QString filename = QInputDialog::getText(this, "Crea una base de dades", "Escriu el nom:",
                                             QLineEdit::Normal, "", &ok);

    if (!ok || filename.isEmpty()) return; // User canceled the name input or entered an empty name

    QString filePath = directory + "/" + filename + ".txt";

    if (QFile::exists(filePath))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("El fitxer ja existeix");
        msgBox.setText("Vols reemplaçar-lo?");
        QAbstractButton *yesButton = msgBox.addButton(tr("Si"), QMessageBox::YesRole);
        QAbstractButton *noButton = msgBox.addButton(tr("No"), QMessageBox::YesRole);
        msgBox.exec();

        if (msgBox.clickedButton() == noButton) return; // User canceled the action 
    }
    std::ofstream file;
    file.open(filePath.toStdString().c_str());

    if (file.is_open())
    {
        file << "ACCOUNT_MANAGEMENT_DATABASE\n";
        file.close();
        m_database = new Database();
        m_database->set_name(filename);
        m_database->set_path(filePath);
        m_database->read_database();
        setupDatabaseMenu();
        m_stackWidget->setCurrentWidget(m_databaseMenuWidget);
    }
    else
    {
        QMessageBox::critical(this, "Error", "No s'ha creat be la base de dades");
    }
}


void MainWindow::openDatabase()
{
    QString exeDirPath = QCoreApplication::applicationDirPath();
    QDir dir(exeDirPath);
    dir.cdUp();
    dir.cdUp();
    QString appRootPath = dir.absolutePath();

    QString filePath = QFileDialog::getOpenFileName(this, "Obre una base de dades", appRootPath, "Arxius de bases de dades (*.txt)");
    if (filePath.isEmpty()) return; // User canceled the name input or entered an empty name
    std::ifstream file;
    file.open(filePath.toStdString().c_str());

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);

        if (line == "ACCOUNT_MANAGEMENT_DATABASE")
        {
            file.close();
            m_database = new Database();
            m_database->set_name(filePath.split("/").takeLast().split(".").takeFirst());
            m_database->set_path(filePath);
            m_database->read_database();
            setupDatabaseMenu();
            m_stackWidget->setCurrentWidget(m_databaseMenuWidget);
        }
        else
        {
            QMessageBox::critical(this, "Error", "L'arxiu no correspon a una base de dades");
        }
    }
    else
    {
        QMessageBox::critical(this, "Error", "No s'ha obert be la base de dades");
    }

}


void MainWindow::exitProgram()
{
    close();
}


void MainWindow::update_summary()
{
    m_accountCountLabel->setText("Number of Accounts: " + QString::number(m_database->get_nAccounts()));
    QString detailsText = "Comptes i balanços:\n";
    
    for (int i = 0; i < m_database->get_nAccounts(); i++)
    {
        Account* account = m_database->get_account(i);
        if (account)
        {
            detailsText += QString("%1: %2\n").arg(account->get_name()).arg(account->get_money());
        }
    }
    
    m_accountDetailsLabel->setText(detailsText);
}


void MainWindow::show_last_transactions()
{
    QMessageBox::critical(this, "Perdona", "Encara no s'ha implementat aquesta opcio");
}


void MainWindow::addAccount()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Afegeix un compte");

    QLabel bankLabel = QLabel("Banc:", &dialog);
    QLineEdit bankLineEdit = QLineEdit(&dialog);

    QLabel initialMoneyLabel = QLabel("Diners inicials (Ex: 43.86):", &dialog);
    QLineEdit initialMoneyLineEdit = QLineEdit(&dialog);

    QPushButton okButton = QPushButton("OK", &dialog);
    QPushButton cancelButton = QPushButton("Cancella", &dialog);

    connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    QVBoxLayout layout = QVBoxLayout(&dialog);
    layout.addWidget(&bankLabel);
    layout.addWidget(&bankLineEdit);
    layout.addWidget(&initialMoneyLabel);
    layout.addWidget(&initialMoneyLineEdit);
    layout.addWidget(&okButton);
    layout.addWidget(&cancelButton);

    dialog.setStyleSheet(
        "QLabel { font-weight: bold; }"
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-size: 14px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3e8e41; }"
    );

    if (dialog.exec() == QDialog::Accepted)
    {
        QString bank = bankLineEdit.text();
        QString initialMoneyStr = initialMoneyLineEdit.text();
        
        bool conversionOk;
        double initialMoney = initialMoneyStr.toFloat(&conversionOk);
        
        if (!conversionOk || initialMoney <= 0.0) {
            QMessageBox::critical(this, "Error", "Valor dels diners invalid. Escriu un numero valid i positiu");
            return;
        }
        m_database->add_account(bank, initialMoney);
        update_summary();
        m_unsavedChanges = true;
        QMessageBox::information(this, "Compte afegit amb exit!", QString("Banc: %1\nDiners inicials: %2").arg(bank).arg(initialMoney));
    }
}


void MainWindow::modifyAccount()
{
    QMessageBox::critical(this, "Perdona", "Encara no s'ha implementat aquesta opcio");
}


void MainWindow::addTransaction()
{
    QDialog dialog(this);
    dialog.setWindowTitle("Afegeix una transaccio");

    // 1. Select the account

    QLabel accountLabel = QLabel("Selecciona Compte:", &dialog);
    QComboBox accountComboBox(&dialog);
    std::vector<QString> accountsNames = m_database->get_accounts_names_vector();
    QStringList accountItems;
    for (const QString& option : accountsNames) {
        accountItems << option;
    }
    accountComboBox.addItems(QStringList::fromVector(accountItems));

    // 2. Select transaction type

    QLabel transactionTypeLabel = QLabel("Selecciona tipus de transaccio:", &dialog);
    QComboBox transactionTypeComboBox(&dialog);
    QStringList transactionTypeItems = {"Despesa", "Ingres"};
    transactionTypeComboBox.addItems(transactionTypeItems);
    
    // 3. Select Payment/Income type

    QLabel typeLabel = QLabel("Tipus:", &dialog);
    QComboBox *typeComboBox = new QComboBox(&dialog);

    connect(&transactionTypeComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, [=](const QString& transactionType)
    {
        typeComboBox->clear();
        QStringList typeItems;
        if (transactionType == "Despesa")
        {
            for (const LabelType& labelType : m_transactionLabels->m_paymentTypes)
            {
                typeItems << labelType.label;
            }
        }
        else if (transactionType == "Ingres")
        {
            for (const LabelType& labelType : m_transactionLabels->m_incomeTypes)
            {
                typeItems << labelType.label;
            }
        }
        typeComboBox->addItems(typeItems);
        typeComboBox->setCurrentIndex(0); // Default
    });

    // 4. Select subtype

    QLabel subtypeLabel = QLabel("Subtipus:", &dialog);
    QComboBox *subtypeComboBox = new QComboBox(&dialog);

    connect(typeComboBox, QOverload<const QString&>::of(&QComboBox::currentTextChanged), this, [=, &transactionTypeComboBox](const QString& typeLabel)
    {
        subtypeComboBox->clear();
        QStringList subtypeItems;
        int typeCode;
        QString transactionType = transactionTypeComboBox.currentText();
        if (transactionType == "Despesa")
        {
            for (const LabelType& labelType : m_transactionLabels->m_paymentTypes)
            {
                if (typeLabel == labelType.label)
                {
                    typeCode = labelType.code;
                    break;
                }
            }
            for (const LabelSubtype& subtype : m_transactionLabels->m_paymentTypes[typeCode].subtypes)
            {
                subtypeItems << subtype.label;
            }
        }
        else
        {
            for (const LabelType& labelType : m_transactionLabels->m_incomeTypes)
            {
                if (typeLabel == labelType.label)
                {
                    typeCode = labelType.code;
                    break;
                }
            }
            for (const LabelSubtype& subtype : m_transactionLabels->m_incomeTypes[typeCode].subtypes)
            {
                subtypeItems << subtype.label;
            }
        }
        subtypeComboBox->addItems(subtypeItems);
        subtypeComboBox->setCurrentIndex(0); // Default
    });

    transactionTypeComboBox.setCurrentText("Ingres"); // Default type

    // 5. Put the value

    QLabel moneyLabel = QLabel("Indica el valor, en positiu (Ex: 34.21):", &dialog);
    QLineEdit moneyLineEdit = QLineEdit(&dialog);

    // 6. Select the date
    QLabel dateLabel = QLabel("Selecciona el dia (avui per defecte):", &dialog);
    QDateEdit* dateEdit = new QDateEdit(&dialog);
    dateEdit->setCalendarPopup(true);
    dateEdit->setDate(QDate::currentDate());

    // 7. Prepare the layout

    QPushButton okButton = QPushButton("OK", &dialog);
    QPushButton cancelButton = QPushButton("Cancella", &dialog);
    connect(&okButton, &QPushButton::clicked, &dialog, &QDialog::accept);
    connect(&cancelButton, &QPushButton::clicked, &dialog, &QDialog::reject);

    QVBoxLayout layout = QVBoxLayout(&dialog);
    layout.addWidget(&accountLabel);
    layout.addWidget(&accountComboBox);
    layout.addWidget(&transactionTypeLabel);
    layout.addWidget(&transactionTypeComboBox);
    layout.addWidget(&typeLabel);
    layout.addWidget(typeComboBox);
    layout.addWidget(&subtypeLabel);
    layout.addWidget(subtypeComboBox);
    layout.addWidget(&moneyLabel);
    layout.addWidget(&moneyLineEdit);
    layout.addWidget(&dateLabel);
    layout.addWidget(dateEdit);
    layout.addWidget(&okButton);
    layout.addWidget(&cancelButton);

    dialog.setStyleSheet(
        "QLabel { font-weight: bold; }"
        "QPushButton {"
        "    background-color: #4CAF50;"
        "    color: white;"
        "    font-size: 14px;"
        "    padding: 8px 16px;"
        "    border: none;"
        "    border-radius: 5px;"
        "}"
        "QPushButton:hover { background-color: #45a049; }"
        "QPushButton:pressed { background-color: #3e8e41; }"
        "QComboBox {"
        "    padding: 6px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "}"
        "QLineEdit {"
        "    padding: 6px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "}"
        "QDateEdit {"
        "    padding: 6px;"
        "    border: 1px solid #ccc;"
        "    border-radius: 5px;"
        "}"
    );
    
    // 8. Check the data and process it if correct
    if (dialog.exec() == QDialog::Accepted)
    {
        QString account = accountComboBox.currentText();
        QString transaction = transactionTypeComboBox.currentText();
        bool isPayment = transaction == "Despesa" ? true : false;
        QString type = typeComboBox->currentText();
        QString subtype = subtypeComboBox->currentText();
        QString moneyStr = moneyLineEdit.text();
        QDate date = dateEdit->date();
        
        bool conversionOk;
        double money = moneyStr.toFloat(&conversionOk);

        if (account.isEmpty())
        {
            QMessageBox::critical(this, "Error", "Cal seleccionar compte");
            return;
        }

        if (subtype.isEmpty())
        {
            QMessageBox::critical(this, "Error", "Cal fer seleccio de transaccio, tipus i subtipus");
            return;
        }
        
        if (!conversionOk || money <= 0.0)
        {
            QMessageBox::critical(this, "Error", "Valor dels diners invalid. Escriu un numero valid i positiu");
            return;
        }
        m_database->add_transaction(account, isPayment, type, subtype, money, date);
        update_summary();
        m_unsavedChanges = true;
        QMessageBox::information(this, "Transaccio afegida amb exit!",
                                QString("Banc: %1\nTransaccio: %2\nTipus: %3\nSubtipus: %4\nValor: %5\nData: %6").arg(account).arg(transaction).arg(type).arg(subtype).arg(moneyStr).arg(date.toString()));
    }
}


void MainWindow::modifyTransaction()
{
    QMessageBox::critical(this, "Perdona", "Encara no s'ha implementat aquesta opcio");
}


void MainWindow::addTransactionsfromFile()
{
    QMessageBox::critical(this, "Perdona", "Encara no s'ha implementat aquesta opcio");
}


void MainWindow::saveDatabase()
{
    if (!m_unsavedChanges)
    {
        QMessageBox::information(this, "Avis",
                                QString("No hi ha hagut canvis des de que s'ha obert o desat l'arxiu per ultim cop"));
        return;
    }
    m_database->store_database(this);
    m_unsavedChanges = false;
    QMessageBox::information(this, "Finalitzat",
                                QString("La base de dades s'ha desat amb exit"));
}


void MainWindow::closeDatabase()
{
    QMessageBox::critical(this, "Perdona", "Encara no s'ha implementat aquesta opcio");
}


void MainWindow::analyseDatabase()
{
    QMessageBox::critical(this, "Perdona", "Encara no s'ha implementat aquesta opcio");
}
