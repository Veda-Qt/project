#include "history-manager.h"
#include "transfer-manager.h"
#include "../cores/db-manager.h"

TransferManager &TransferManager::instance()
{
    static TransferManager instance;
    return instance;
}

TransferModel *TransferManager::getModel() const
{
    return model;
}

void TransferManager::setSenderAccount(const Account &account)
{
    sender_account = account;
}

Account TransferManager::getSenderAccount() const
{
    return sender_account;
}

void TransferManager::loadRecentTransfers()
{
    if (model) {
        model->fetchData();
    }
}

void TransferManager::requestTransfer(const QString &target_number, const QString &target_bank_name, long long amount)
{
    qDebug() << "request transfer from " << sender_account.getNumber()
             << " -> to " << target_number
             << " | amount: " << amount;

    if (sender_account.getNumber() == target_number) {
        emit transferFailed("출금 계좌와 입금 계좌가 동일합니다.");
        return;
    }
    if (sender_account.getBalance() < amount) {
        emit transferFailed("계좌의 잔액이 부족합니다.");
        return;
    }

    QJsonObject recv_cond;
    recv_cond["number"] = target_number;

    const QJsonArray recv_json = DbManager::instance().selectItems("accounts", recv_cond);
    if (recv_json.isEmpty()) {
        emit transferFailed("입력하신 정보와 일치하는 계좌를 찾을 수 없습니다.");
        return;
    }

    QJsonObject recv_obj = recv_json[0].toObject();
    QString recv_name = recv_obj["owner_name"].toString();
    long long recv_old_balance = recv_obj["balance"].toVariant().toLongLong();

    /* START TRANSATION */
    long long send_new_balance = sender_account.getBalance() - amount;
    long long recv_new_balance = recv_old_balance + amount;

    QJsonObject send_cond;
    send_cond["number"] = sender_account.getNumber();

    QJsonObject send_data;
    send_data["balance"] = send_new_balance;
    DbManager::instance().updateItem("accounts", send_cond, send_data); // 내 계좌 돈 빼기

    QJsonObject recv_data;
    recv_data["balance"] = recv_new_balance;
    DbManager::instance().updateItem("accounts", recv_cond, recv_data); // 상대 계좌 돈 넣기

    QString currentTime = QDateTime::currentDateTime().toString(Qt::ISODate);

    // 내 거래 내역 (이체)
    QJsonObject send_history;
    send_history["number"] = sender_account.getNumber();
    send_history["origin_name"] = recv_name;
    send_history["type"] = "이체";
    send_history["amount"] = amount;
    send_history["balance"] = send_new_balance;
    send_history["timestamp"] = currentTime;
    // for current transfer accounts
    send_history["origin_number"] = target_number;
    send_history["origin_bank_name"] = target_bank_name;
    DbManager::instance().insertItem("histories", send_history);

    // 상대방 거래 내역 (입금)
    QJsonObject recv_history;
    recv_history["number"] = target_number;
    recv_history["origin_name"] = sender_account.getOwnerName();
    recv_history["type"] = "입금";
    recv_history["amount"] = amount;
    recv_history["balance"] = recv_new_balance;
    recv_history["datetime"] = currentTime;
    DbManager::instance().insertItem("histories", recv_history);
    /* END TRANSACTION */

    sender_account.setBalance(send_new_balance);

    emit transferSuccess();
}