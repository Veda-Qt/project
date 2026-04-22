#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "../cores/account-manager.h"
#include "../cores/history-manager.h"
#include "../cores/transfer-manager.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    account_list_page = new AccountListPage(this);
    account_history_page = new AccountHistoryPage(this);
    transfer_page = new TransferPage(this);

    ui->stackedWidget->addWidget(account_list_page);
    ui->stackedWidget->addWidget(account_history_page);
    ui->stackedWidget->addWidget(transfer_page);

    ui->stackedWidget->setCurrentWidget(account_list_page);
    // TEST: input dummy user_id
    AccountManager::instance().loadAccounts("214");

    connect(account_list_page, &AccountListPage::accountSelected,
            this, qOverload<const Account &>(&MainWindow::showAccountHistory));

    connect(account_history_page, &AccountHistoryPage::backRequested,
            this, qOverload<>(&MainWindow::showAccountList));

    connect(account_history_page, &AccountHistoryPage::transferRequested,
            this, &MainWindow::showTransfer);

    connect(transfer_page, &TransferPage::backRequested,
            this, qOverload<>(&MainWindow::showAccountHistory));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showAccountList()
{
    ui->stackedWidget->setCurrentWidget(account_list_page);
}

void MainWindow::showAccountList(const QString &owner_id)
{
    AccountManager::instance().loadAccounts(owner_id);
    ui->stackedWidget->setCurrentWidget(account_list_page);
}

void MainWindow::showAccountHistory()
{
    ui->stackedWidget->setCurrentWidget(account_history_page);
}

void MainWindow::showAccountHistory(const Account &account)
{
    HistoryManager::instance().loadHistories(account);
    ui->stackedWidget->setCurrentWidget(account_history_page);
}

void MainWindow::showTransfer()
{
    Account sender_account = HistoryManager::instance().getOwnerAccount();
    TransferManager::instance().setSenderAccount(sender_account);
    TransferManager::instance().loadRecentTransfers();
    ui->stackedWidget->setCurrentWidget(transfer_page);
}