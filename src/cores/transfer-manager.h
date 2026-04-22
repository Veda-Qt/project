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

    // init member
    void setSenderAccount(const Account &account);
    Account getSenderAccount() const;
    void loadRecentTransfers();
    void requestTransfer(const QString &target_number, const QString &target_bank_name, long long amount);
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
