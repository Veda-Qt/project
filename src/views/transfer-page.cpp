#include "transfer-page.h"
#include "./ui_transfer-page.h"
#include "../cores/transfer-manager.h"
#include "../models/transfer-model.h"

TransferPage::TransferPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::TransferPage)
{
    ui->setupUi(this);
    ui->lview_acnt_histry->setModel(TransferManager::instance().getModel());

    QRegularExpression rxAccount("^[0-9-]+$");
    ui->ledit_acnt_num->setValidator(new QRegularExpressionValidator(rxAccount, this));

    QRegularExpression rxMoney("^[0-9]+$");
    ui->ledit_money->setValidator(new QRegularExpressionValidator(rxMoney, this));

    ui->combobox_bank->addItem(BankHelper::toString(Bank::KB), static_cast<int>(Bank::KB));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Shinhan), static_cast<int>(Bank::Shinhan));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Woori), static_cast<int>(Bank::Woori));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Hana), static_cast<int>(Bank::Hana));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::NH), static_cast<int>(Bank::NH));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Kakao), static_cast<int>(Bank::Kakao));
    ui->combobox_bank->setCurrentIndex(-1);

    connect(this, &TransferPage::transferRequested,
            &TransferManager::instance(), &TransferManager::requestTransfer);
}

TransferPage::~TransferPage()
{
    delete ui;
}

void TransferPage::on_btn_back_clicked()
{
    emit backRequested();
}

void TransferPage::on_btn_ok_clicked()
{
    QString target_number = ui->ledit_acnt_num->text().trimmed();
    QString bank_name = ui->combobox_bank->currentText();
    QString amount_str = ui->ledit_money->text().trimmed();

    if (target_number.isEmpty() || amount_str.isEmpty()) {
        qWarning() << "Invalid Input.";
        return;
    }

    if (ui->combobox_bank->currentIndex() == -1) {
        qWarning() << "Select bank.";
        return;
    }

    long long amount = amount_str.toLongLong();

    if (amount <= 0) {
        qWarning() << "Value on ledit_money must be over zero.";
        return;
    }

    emit transferRequested(target_number, bank_name, amount);
}

void TransferPage::on_lview_acnt_histry_doubleClicked(const QModelIndex &index)
{
    if (!index.isValid()) return;

    auto *model = qobject_cast<TransferModel *>(ui->lview_acnt_histry->model());
    if (!model) return;

    Account target_account = model->getAccount(index.row());
    qDebug() << "selected account: " << target_account.getNumber();
    ui->ledit_acnt_num->setText(target_account.getNumber());
}

