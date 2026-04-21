#include "account-history-page.h"
#include "./ui_account-history-page.h"
#include "../cores/history-manager.h"

AccountHistoryPage::AccountHistoryPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AccountHistoryPage)
{
    ui->setupUi(this);
    ui->lview_hstry->setModel(HistoryManager::instance().getModel());

    connect(&HistoryManager::instance(), &HistoryManager::accountChanged,
            this, &AccountHistoryPage::updateAccountLabel);
}

AccountHistoryPage::~AccountHistoryPage()
{
    delete ui;
}

void AccountHistoryPage::on_btn_back_clicked()
{
    qDebug() << "back_btn clicked()";
    emit backRequested();
}

void AccountHistoryPage::on_btn_transfer_clicked()
{
    qDebug() << "transfer_btn clicked()";
    emit transferRequested();
}

void AccountHistoryPage::updateAccountLabel(const Account &account)
{
    qDebug() << account.getNumber();
    ui->lbl_acnt_name->setText(account.getOwnerName() + " " + account.getNumber());
}