#include "account-list-page.h"
#include "./ui_account-list-page.h"
#include "../cores/account-manager.h"
#include "../models/account-model.h"

AccountListPage::AccountListPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountListPage)
{
    ui->setupUi(this);
    ui->lview_acnt->setModel(AccountManager::instance().getModel());
}

AccountListPage::~AccountListPage()
{
    delete ui;
}

void AccountListPage::on_lview_acnt_doubleClicked(const QModelIndex &index)
{
    qDebug() << "lview_acnt clicked()";
    auto *model = qobject_cast<AccountModel *>(ui->lview_acnt->model());
    if (!model) return;

    Account account = model->getAccount(index.row());
    qDebug() << "selected account: " << account.getNumber();
    emit accountSelected(account);
}