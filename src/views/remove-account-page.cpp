#include <QMessageBox>
#include <QJsonObject>
#include <QJsonArray>
#include "remove-account-dialog.h"
#include "ui_remove-account-dialog.h"
#include "../cores/db-manager.h"
#include "../cores/account-manager.h"


RemoveAccountDialog::RemoveAccountDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::RemoveAccountDialog)
{
    ui->setupUi(this);

    this->setModal(true);
    this->setWindowTitle("계좌 삭제");
}

RemoveAccountDialog::~RemoveAccountDialog()
{
    delete ui;
}

void RemoveAccountDialog::accept()
{
    QString target_number = ui->ledit_number->text().trimmed();
    QString user_id = ui->ledit_user_id->text();

    if (target_number.isEmpty() | user_id.isEmpty()) {
        QMessageBox::warning(this, "입력 오류", "모든 항목을 입력해주세요.");
        return;
    }

    if (user_id != AccountManager::instance().getOwnerId()) {
        QMessageBox::warning(this, "입력 오류", "아이디가 틀렸습니다.");
        return;
    }

    QJsonObject conditions;
    conditions["number"] = target_number;
    conditions["owner_id"] = user_id;

    QJsonArray account_matched = DbManager::instance().selectItems("accounts", conditions);

    if (account_matched.isEmpty()) {
        QMessageBox::warning(this, "오류", "일치하는 내 계좌를 찾을 수 없습니다.\n계좌번호를 다시 확인해주세요.");
        return;
    }

    long long balance = account_matched[0].toObject()["balance"].toVariant().toLongLong();
    if (balance > 0) {
        QMessageBox::warning(this, "삭제 불가", QString("잔액이 %1원 남아있습니다.\n잔액을 모두 이체한 후 삭제해주세요.").arg(balance));
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "삭제 확인",
                                  QString("[%1] 계좌를 정말 삭제하시겠습니까?\n이 작업은 되돌릴 수 없습니다.").arg(target_number),
                                  QMessageBox::Yes | QMessageBox::No);

    if (reply == QMessageBox::No) {
        return;
    }

    if (DbManager::instance().deleteItem("accounts", conditions)) {
        QMessageBox::information(this, "삭제 완료", "계좌가 성공적으로 삭제되었습니다.");
        QDialog::accept();
    } else {
        QMessageBox::critical(this, "오류", "데이터베이스 삭제에 실패했습니다.");
    }
}