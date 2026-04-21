#include "account-history-page.h"
#include "./ui_account-history-page.h"

AccountHistoryPage::AccountHistoryPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountHistoryPage)
{
    ui->setupUi(this);
}

AccountHistoryPage::~AccountHistoryPage()
{
    delete ui;
}

void AccountHistoryPage::loadHistory(int account_id)
{

}