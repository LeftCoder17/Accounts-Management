#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QString>

#include "libs/database.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor
    MainWindow(QWidget *parent = nullptr);
    // Default destructor
    ~MainWindow();

private slots:
    // 1. Main Menu Slots

    // Opens a File Dialog to Create a new Database and open it
    void createDatabase();
    // Opens a File Dialog to Choose a Database and open it
    void openDatabase();
    // Exits the program
    void exitProgram();

    // 2. Database menu slots

    // 2.1. Summary of the database
    
    // Updates the informatin shown in the summary
    void update_summary();
    // Show the last transactions added
    void show_last_transactions();
    

    // 2.2. Edit database
    
    // Adds an account to the database
    void addAccount();
    // Modifies an account from the database
    void modifyAccount();
    // Adds a transaction to the database
    void addTransaction();
    // Modifies a transaction from the database
    void modifyTransaction();
    // Add transactions from a file to the database
    void addTransactionsfromFile();

    // 2.3. Manage database

    // Saves the changes of a database
    void saveDatabase();
    // Close the opened database
    void closeDatabase();

    // 2.4. Analyse database

    // Analyse the database
    void analyseDatabase();
    

private:
    // Configure the Main Menu
    void setupMainMenu();
    // Configure the Database Menu
    void setupDatabaseMenu();


private: // Private members
    // Stack with the main menu widget and the database menu widget
    QStackedWidget *m_stackWidget;
    // Widget of the main menu
    QWidget *m_mainMenuWidget;
    // Widget of the database menu
    QWidget *m_databaseMenuWidget;

    // 1. Main Menu Widgets

    // Layout for the Main menu
    QVBoxLayout *m_mainMenuLayout;
    // Label of the Main menu title
    QLabel *m_titleLabel;
    // Button to create and open a Database
    QPushButton *m_createDatabaseButton;
    // Button to open a Database
    QPushButton *m_openDatabaseButton;
    // Button to exit the program
    QPushButton *m_exitButton;

    // 2. Database Menu Widgets

    // Layout for the Database menu
    QGridLayout *m_databaseGridLayout;
    // Opened Database
    Database *m_database;
    // Transaction labels
    TransactionLabels *m_transactionLabels;
    // Controls if there are changes without being saved
    bool m_unsavedChanges;

    // 2.1. Summary of the database

    // Widget with the summary of the database
    QWidget *m_summaryWidget;
    // Layout for the summary of the database
    QVBoxLayout *m_summaryLayout;
    // Label of the name of the database
    QLabel *m_databaseNameLabel;
    // Label of the number of accounts
    QLabel *m_accountCountLabel;
    // Label with details of the accounts
    QLabel *m_accountDetailsLabel;
    // Button to show the last transactions of the database
    QPushButton *m_showLastTransactionsButton;

    // 2.2. Edit database

    // Widget with the edit options of the database
    QWidget *m_editWidget;
    // Layout for the edit options of the database
    QVBoxLayout *m_editLayout;
    // Button to add an account
    QPushButton *m_addAccountButton;
    // Button to modify an account
    QPushButton *m_modifyAccountButton;
    // Button to add a transaction
    QPushButton *m_addTransactionButton;
    // Button to modify a transaction
    QPushButton *m_modifyTransactionButton;
    // Button to add transactions from file
    QPushButton *m_addTransactionsfromFileButton;

    // 2.3. Manage the database

    // Widget with the save and close database options
    QWidget *m_manageDatabaseWidget;
    // Layout for the save and close options of the database
    QVBoxLayout *m_manageDatabaseLayout;
    // Button to save the changes of the database
    QPushButton *m_saveDatabaseButton;
    // Button to close the database
    QPushButton *m_closeDatabaseButton;

    // 2.4. Analyse the database

    // Widget with the analyse options of the database
    QWidget *m_analyseDatabaseWidget;
    // Layout for the analyse options of the database
    QVBoxLayout *m_analyseDatabaseLayout;
    // Button to analyse the database
    QPushButton *m_analyseDatabaseButton;

};

#endif // MAINWINDOW_H