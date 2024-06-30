#include "mainwindow.h"
#include <QVBoxLayout>
#include <QFileDialog>
#include <QFont>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), m_openedDatabase("")
{
    m_stackWidget = new QStackedWidget(this);
    setupMainMenu();
    setupDatabaseMenu();
    setupDatabaseOpenedMenu();
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
}

void MainWindow::setupMainMenu()
{
    m_mainMenuWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_mainMenuWidget);

    m_titleLabel = new QLabel("Account Management App", this);
    m_titleLabel->setObjectName("titleLabel");
    m_titleLabel->setAlignment(Qt::AlignCenter);
    
    m_openDatabaseButton = new QPushButton("Open Database", this);
    m_exitButton = new QPushButton("Exit Program", this);

    layout->addWidget(m_titleLabel);
    layout->addWidget(m_openDatabaseButton);
    layout->addWidget(m_exitButton);

    connect(m_openDatabaseButton, &QPushButton::clicked, this, &MainWindow::openDatabaseMenu);
    connect(m_exitButton, &QPushButton::clicked, this, &MainWindow::exitProgram);

    layout->setSpacing(20);
    layout->setContentsMargins(50, 50, 50, 50);

    m_mainMenuWidget->setLayout(layout);
    m_stackWidget->addWidget(m_mainMenuWidget);
}

void MainWindow::setupDatabaseMenu()
{
    m_databaseMenuWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_databaseMenuWidget);

    m_createNewDatabaseButton = new QPushButton("Create and Open New Database", this);
    m_openExistingDatabaseButton = new QPushButton("Open Existing Database", this);
    m_backButton = new QPushButton("Back to Menu", this);

    layout->addWidget(m_createNewDatabaseButton);
    layout->addWidget(m_openExistingDatabaseButton);
    layout->addWidget(m_backButton);

    connect(m_createNewDatabaseButton, &QPushButton::clicked, this, &MainWindow::createNewDatabase);
    connect(m_openExistingDatabaseButton, &QPushButton::clicked, this, &MainWindow::openExistingDatabase);
    connect(m_backButton, &QPushButton::clicked, this, &MainWindow::backToMainMenu);

    layout->setSpacing(20);
    layout->setContentsMargins(50, 50, 50, 50);

    m_databaseMenuWidget->setLayout(layout);
    m_stackWidget->addWidget(m_databaseMenuWidget);
}

void MainWindow::setupDatabaseOpenedMenu()
{
    m_databaseOpenedWidget = new QWidget(this);
    QVBoxLayout *layout = new QVBoxLayout(m_databaseOpenedWidget);

    m_openedDatabaseLabel = new QLabel("Opened Database: " + m_openedDatabase, this);
    m_openedDatabaseLabel->setAlignment(Qt::AlignCenter);

    m_editButton = new QPushButton("Edit", this);
    m_saveButton = new QPushButton("Save", this);
    m_analyseButton = new QPushButton("Analyse", this);
    m_closeDatabaseButton = new QPushButton("Close Database", this);
    m_exitFromOpenedButton = new QPushButton("Exit Program", this);

    layout->addWidget(m_openedDatabaseLabel);
    layout->addWidget(m_editButton);
    layout->addWidget(m_saveButton);
    layout->addWidget(m_analyseButton);
    layout->addWidget(m_closeDatabaseButton);
    layout->addWidget(m_exitFromOpenedButton);

    connect(m_editButton, &QPushButton::clicked, this, &MainWindow::editDatabase);
    connect(m_saveButton, &QPushButton::clicked, this, &MainWindow::saveDatabase);
    connect(m_analyseButton, &QPushButton::clicked, this, &MainWindow::analyseDatabase);
    connect(m_closeDatabaseButton, &QPushButton::clicked, this, &MainWindow::closeDatabase);
    connect(m_exitFromOpenedButton, &QPushButton::clicked, this, &MainWindow::exitProgram);

    layout->setSpacing(20);
    layout->setContentsMargins(50, 50, 50, 50);

    m_databaseOpenedWidget->setLayout(layout);
    m_stackWidget->addWidget(m_databaseOpenedWidget);
}

void MainWindow::openDatabaseMenu()
{
    m_stackWidget->setCurrentWidget(m_databaseMenuWidget);
}

void MainWindow::exitProgram()
{
    close();
}

void MainWindow::backToMainMenu()
{
    m_stackWidget->setCurrentWidget(m_mainMenuWidget);
}

void MainWindow::createNewDatabase()
{
    // Logic to create a new database
    m_openedDatabase = "New Database";
    m_openedDatabaseLabel->setText("Opened Database: " + m_openedDatabase);
    m_stackWidget->setCurrentWidget(m_databaseOpenedWidget);
}

void MainWindow::openExistingDatabase()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Open Database", "", "Database Files (*.db)");
    if (!fileName.isEmpty())
    {
        m_openedDatabase = fileName;
        m_openedDatabaseLabel->setText("Opened Database: " + m_openedDatabase);
        m_stackWidget->setCurrentWidget(m_databaseOpenedWidget);
    }
}

void MainWindow::closeDatabase()
{
    m_openedDatabase = "";
    m_stackWidget->setCurrentWidget(m_mainMenuWidget);
}

void MainWindow::editDatabase()
{
    // Implement the edit database functionality
}

void MainWindow::saveDatabase()
{
    // Implement the save database functionality
}

void MainWindow::analyseDatabase()
{
    // Implement the analyse database functionality
}