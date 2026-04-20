#include "mainwindow.h"
#include "./ui_mainwindow.h"

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

    connect(account_list_page, &AccountListPage::account_selected,
            this, &MainWindow::on_account_clicked);
    // connect(account_list_page, &AccountListPage::account_selected,
    //         this, &MainWindow::on_account_clicked);
    // connect(account_list_page, &AccountListPage::account_selected,
    //         this, &MainWindow::on_account_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_account_clicked(int account_id)
{
}