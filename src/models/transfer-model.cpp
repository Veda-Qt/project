#include "transfer-model.h"

TransferModel::~TransferModel()
{
    qDeleteAll(accounts);
    accounts.clear();
}

int TransferModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : accounts.size();
}

QVariant TransferModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= accounts.size()) {
        return QVariant();
    }

    const Account *account = accounts.at(index.row());

    switch (role) {
    case NumberRole:
        return account->getNumber();
    case OwnerNameRole:
        return account->getOwnerName();
    case BankNameRole:
        return account->getBankName();
    case ObjectRole:
        return QVariant::fromValue(account);
    case Qt::DisplayRole:
        return QString("%1 %2 | (%3)").arg(account->getOwnerName(),
                                         account->getBankName(),
                                         account->getNumber());
    }

    return QVariant();
}

Account TransferModel::getAccount(int row) const
{
    if (row < 0 || row >= accounts.size()) {
        return Account();
    }

    return *(accounts.at(row));
}

void TransferModel::fetchData()
{
    beginResetModel();
    qDeleteAll(accounts);
    accounts.clear();

    // TODO
    accounts.append(new Account("987-654-321", "김범수", "신한은행"));
    accounts.append(new Account("111-222-333", "아이유", "국민은행"));

    endResetModel();
}

