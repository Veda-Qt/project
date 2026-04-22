#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <QObject>
#include "../models/account-model.h"

class AccountManager : public QObject
{
    Q_OBJECT

public:
    static AccountManager &instance();

    void loadAccounts(const QString &owner_id);
    QString getOwnerId() const;
    AccountModel *getModel() const;

signals:
    // void accountsChanged();

private:
    explicit AccountManager(QObject *parent = nullptr) : QObject(parent), model(new AccountModel(this)) {}

    QString owner_id;
    AccountModel *model = nullptr;
};

#endif // ACCOUNT_MANAGER_H
