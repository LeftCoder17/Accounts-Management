#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QStackedWidget>
#include <QString>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openDatabaseMenu();
    void exitProgram();
    void backToMainMenu();
    void createNewDatabase();
    void openExistingDatabase();
    void closeDatabase();
    void editDatabase();
    void saveDatabase();
    void analyseDatabase();

private:
    void setupMainMenu();
    void setupDatabaseMenu();
    void setupDatabaseOpenedMenu();

    QStackedWidget *m_stackWidget;
    QWidget *m_mainMenuWidget;
    QWidget *m_databaseMenuWidget;
    QWidget *m_databaseOpenedWidget;
    QString m_openedDatabase;

    // Main Menu Widgets
    QLabel *m_titleLabel;
    QPushButton *m_openDatabaseButton;
    QPushButton *m_exitButton;

    // Open Database Menu Widgets
    QPushButton *m_createNewDatabaseButton;
    QPushButton *m_openExistingDatabaseButton;
    QPushButton *m_backButton;

    // Database Opened Menu Widgets
    QLabel *m_openedDatabaseLabel;
    QPushButton *m_editButton;
    QPushButton *m_saveButton;
    QPushButton *m_analyseButton;
    QPushButton *m_closeDatabaseButton;
    QPushButton *m_exitFromOpenedButton;
};

#endif // MAINWINDOW_H