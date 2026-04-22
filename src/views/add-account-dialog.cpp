#include <QRandomGenerator>
#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include "add-account-dialog.h"
#include "ui_add-account-dialog.h"
#include "../cores/db-manager.h"
#include "../cores/account-manager.h"

AddAccountDialog::AddAccountDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::AddAccountDialog)
{
    ui->setupUi(this);

    this->setModal(true);
    this->setWindowTitle("새 계좌 추가");

    ui->combobox_bank->addItem(BankHelper::toString(Bank::KB), static_cast<int>(Bank::KB));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Shinhan), static_cast<int>(Bank::Shinhan));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Woori), static_cast<int>(Bank::Woori));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Hana), static_cast<int>(Bank::Hana));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::NH), static_cast<int>(Bank::NH));
    ui->combobox_bank->addItem(BankHelper::toString(Bank::Kakao), static_cast<int>(Bank::Kakao));
    ui->combobox_bank->setCurrentIndex(-1);
}

AddAccountDialog::~AddAccountDialog()
{
    delete ui;
}

QString AddAccountDialog::generateUniqueAccountNumber()
{
    QString newNumber;

    while (true) {
        // 1,000,000,000 ~ 9,999,999,999 사이의 10자리 숫자 생성
        long long randomNum = QRandomGenerator::global()->generate64() % 9000000000LL + 1000000000LL;
        newNumber = QString::number(randomNum).insert(3, "-").insert(7, "-");

        QJsonObject conditions;
        conditions["number"] = newNumber;
        if (DbManager::instance().selectItems("accounts", conditions).isEmpty()) {
            break;
        }
    }

    return newNumber;
}

void AddAccountDialog::accept()
{
    QString name = ui->ledit_name->text().trimmed();
    QString bank_name = ui->combobox_bank->currentText();

    if (name.isEmpty() || bank_name.isEmpty()) {
        QMessageBox::warning(this, "입력 오류", "모든 항목을 입력해주세요.");
        return;
    }

    QString number = generateUniqueAccountNumber();

    QJsonObject new_account;
    new_account["number"] = number;
    new_account["owner_id"] = AccountManager::instance().getOwnerId();
    new_account["owner_name"] = name;
    new_account["bank_name"] = bank_name;
    new_account["balance"] = 0;

    if (DbManager::instance().insertItem("accounts", new_account)) {
        QMessageBox::information(this, "계좌 개설 성공",
                                 QString("계좌가 성공적으로 개설되었습니다.\n\n[계좌번호]\n%1").arg(number));
        QDialog::accept();
    } else {
        QMessageBox::critical(this, "오류", "데이터베이스 저장에 실패했습니다.");
    }
}