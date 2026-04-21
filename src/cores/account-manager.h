#ifndef ACCOUNT_MANAGER_H
#define ACCOUNT_MANAGER_H

#include <QObject>
#include "account.h"

class AccountManager : public QObject
{
    Q_OBJECT

public:
    static AccountManager &instance();

    void loadAccounts();
    void addAccount(Account *account);
    const QList<Account *> &getAccounts() const { return accounts; }

signals:
    void accountsChanged();

private:
    AccountManager(QObject *parent = nullptr) : QObject(parent) {}
    ~AccountManager();

    QList<Account *> accounts;

};

#endif // ACCOUNT_MANAGER_H
