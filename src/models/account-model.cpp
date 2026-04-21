#include "account-model.h"

AccountModel::AccountModel(QObject *parent) : QAbstractListModel(parent)
{
    connect(&AccountManager::instance(), &AccountManager::accountsChanged,
            this, &AccountModel::updateData);
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return AccountManager::instance().getAccounts().count();
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= rowCount()) {
        return QVariant();
    }

    const Account *account = AccountManager::instance().getAccounts().at(index.row());

    switch (role) {
    case IdRole:
        return account->getId();
    case NumberRole:
        return account->getNumber();
    case OwnerNameRole:
        return account->getOwnerName();
    case BankNameRole:
        return account->getBankName();
    case BalanceRole:
        return account->getFormattedBalance();
    case Qt::DisplayRole:
        return QString("[%1] %2 | 잔액: %3원").arg(account->getNumber())
                                             .arg(account->getBankName())
                                             .arg(account->getFormattedBalance());
    }

    return QVariant();
}

void AccountModel::updateData()
{
    beginResetModel();
    // All Account data is in AccountManager, so just request to update AccountListPage.
    endResetModel();
}