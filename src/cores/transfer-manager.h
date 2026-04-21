#ifndef TRANSFER_MANAGER_H
#define TRANSFER_MANAGER_H

#include <QObject>
#include "account.h"
#include "../models/transfer-model.h"

class TransferManager : public QObject
{
    Q_OBJECT

public:
    static TransferManager &instance();

    // 1. 상태 세팅: "지금 이 계좌(출금 계좌)에서 돈을 보낼 거야!"
    void setSenderAccount(const Account &account);

    // 2. 모델 지시: "최근 이체 내역 불러와서 모델에 세팅해!"
    void loadRecentTransfers();

    // 3. 이체 실행 (UI에서 버튼을 눌렀을 때 호출됨)
    void requestTransfer(const QString &target_number, long long amount);
    TransferModel *getModel() const;

signals:
    void transferSuccess();
    void transferFailed(const QString &errorMessage);

private:
    explicit TransferManager(QObject *parent = nullptr) : QObject(parent), model(new TransferModel(this)) {}
    ~TransferManager() = default;

    Account sender_account;
    TransferModel *model = nullptr;
};

#endif // TRANSFER_MANAGER_H
