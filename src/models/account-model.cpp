#include "account-model.h"

AccountModel::~AccountModel()
{
    qDeleteAll(accounts);
    accounts.clear();
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : accounts.size();
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= accounts.size()) {
        return QVariant();
    }

    const Account *account = accounts.at(index.row());

    switch (role) {
    case ObjectRole:
        return QVariant::fromValue(account);
    case Qt::DisplayRole:
        return QString("[%1] %2 | 잔액: %3원").arg(account->getNumber())
                                             .arg(account->getBankName())
                                             .arg(account->getFormattedBalance());
    }

    return QVariant();
}

Account AccountModel::getAccount(int row) const
{
    if (row < 0 || row >= accounts.size()) {
        return Account();
    }

    return *(accounts.at(row));
}

void AccountModel:: fetchData(const QString &owner_id)
{
    beginResetModel();
    qDeleteAll(accounts);
    accounts.clear();

    // TODO: fetch data
    accounts.append(new Account("333312345", "qwer123", "박건영", "국민은행", 50000000));
    accounts.append(new Account("3345342345", "asdf777", "박건영", "토스은행", 10000));
    accounts.append(new Account("3212345", "gusese", "홍진기", "우리은행", 23243513));

    endResetModel();
}