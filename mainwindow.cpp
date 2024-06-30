#include "mainwindow.h"
#include <string>
#include <fstream>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QInputDialog>


MainWindow::MainWindow(QWidget *parent) 
    : QMainWindow(parent), m_openedDatabase("")
{
    // Initialize stack widget and main menu.
    m_stackWidget = new QStackedWidget(this);
    setupMainMenu();
    setCentralWidget(m_stackWidget);
    setStyleSheet(
        "QWidget {"
        "    background-color: #f0f0f0;"
        "}"
        "QLabel#titleLabel {"
        "    font-size: 24px;"
        "    font-weight: bold;"
        "    color: #333;"
        "    padding: 20px;"
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

    // 5. Add the layout to the stackWidget
    m_stackWidget->addWidget(m_mainMenuWidget);
}


void MainWindow::setupDatabaseMenu()
{
    // 0. Read the database
    //Missing

    // 1. Initialize objects of the database menu
    m_databaseMenuWidget = new QWidget(this);
    m_databaseGridLayout = new QGridLayout(m_databaseMenuWidget);

    // 2.1. Configure the Summary Section (Top Left)
    m_summaryWidget = new QWidget(this);
    m_summaryLayout = new QVBoxLayout(m_summaryWidget);
    m_databaseNameLabel = new QLabel("Database Name: " + m_nameDatabase, this);
    m_accountCountLabel = new QLabel("Number of Accounts: ", this); // Assume the count is provided
    m_accountDetailsLabel = new QLabel("Accounts and Balances:", this); // Assume the details are provided
    m_showLastMovementsButton = new QPushButton("Show Last Movements", this);

    m_summaryLayout->addWidget(m_databaseNameLabel);
    m_summaryLayout->addWidget(m_accountCountLabel);
    m_summaryLayout->addWidget(m_accountDetailsLabel);
    m_summaryLayout->addWidget(m_showLastMovementsButton);

    // 2.2. Configure the Edit Section (Top Right)
    m_editWidget = new QWidget(this);
    m_editLayout = new QVBoxLayout(m_editWidget);
    m_addAccountButton = new QPushButton("Add Account", this);
    m_modifyAccountButton = new QPushButton("Modify Account", this);
    m_addMovementButton = new QPushButton("Add Movement", this);
    m_modifyMovementButton = new QPushButton("Modify Movement", this);
    m_addMovementsfromFileButton = new QPushButton("Add Movements from File", this);

    m_editLayout->addWidget(m_addAccountButton);
    m_editLayout->addWidget(m_modifyAccountButton);
    m_editLayout->addWidget(m_addMovementButton);
    m_editLayout->addWidget(m_modifyMovementButton);
    m_editLayout->addWidget(m_addMovementsfromFileButton);

    // 2.3. Configure the Manage Database Section (Bottom Left)
    m_manageDatabaseWidget = new QWidget(this);
    m_manageDatabaseLayout = new QVBoxLayout(m_manageDatabaseWidget);
    m_saveDatabaseButton = new QPushButton("Save Database", this);
    m_closeDatabaseButton = new QPushButton("Close Database", this);

    m_manageDatabaseLayout->addWidget(m_saveDatabaseButton);
    m_manageDatabaseLayout->addWidget(m_closeDatabaseButton);

    // 2.4. Configure the Analyze Section (Bottom Right)
    m_analyseDatabaseWidget = new QWidget(this);
    m_analyseDatabaseLayout = new QVBoxLayout(m_analyseDatabaseWidget);
    m_analyseDatabaseButton = new QPushButton("Analyze Database", this);

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
    //MISSING

    // 6. Add the layout to the stackWidget
    m_stackWidget->addWidget(m_databaseMenuWidget);
}



void MainWindow::createDatabase()
{
    QString directory = QFileDialog::getExistingDirectory(this, "Escull carpeta", QDir::homePath());

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
        m_nameDatabase = filename;
        m_openedDatabase = filePath;
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
    QString filePath = QFileDialog::getOpenFileName(this, "Obre una base de dades", "Arxius de bases de dades (*.txt)");
    if (filePath.isEmpty()) return; // User canceled the name input or entered an empty name
    std::ifstream file;
    file.open(filePath.toStdString().c_str());

    if (file.is_open())
    {
        std::string line;
        std::getline(file, line);

        if (line == "ACCOUNT_MANAGEMENT_DATABASE\n")
        {
            file.close();
            m_nameDatabase = filePath.split("/").takeLast().split(".").takeFirst();
            m_openedDatabase = filePath;
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