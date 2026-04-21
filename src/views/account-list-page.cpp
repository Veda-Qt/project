#include "account-list-page.h"
#include "./ui_account-list-page.h"

AccountListPage::AccountListPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountListPage)
    , model(new AccountModel)
{
    ui->setupUi(this);
    ui->lview_acnt->setModel(model);

    AccountManager::instance().loadAccounts(); // load data
}

AccountListPage::~AccountListPage()
{
    delete ui;
}

void AccountListPage::on_lview_acnt_doubleClicked(const QModelIndex &index)
{
    int id = index.data(Qt::UserRole).toInt();
    emit accountSelected(id);
}