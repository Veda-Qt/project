#include "account-list-page.h"
#include "./ui_account-list-page.h"

AccountListPage::AccountListPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountListPage)
{
    ui->setupUi(this);
}

AccountListPage::~AccountListPage()
{
    delete ui;
}

