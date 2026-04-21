#include "account-model.h"

QString Account::getBankName() const {
    switch (bank) {
    case Bank::KB:      return QStringLiteral("국민은행");
    case Bank::WOORI:   return QStringLiteral("우리은행");
    case Bank::HANA:    return QStringLiteral("하나은행");
    case Bank::SHINHAN: return QStringLiteral("신한은행");
    case Bank::KAKAO:   return QStringLiteral("카카오뱅크");
    case Bank::TOSS:    return QStringLiteral("토스뱅크");
    default:            return QStringLiteral("알 수 없는 은행");
    }
}

int AccountModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : accounts.count();
}

QVariant AccountModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid() || index.row() >= accounts.count()) return QVariant();

    const auto &account = accounts[index.row()];

    if (role == IdRole) return account.getId();
    else if (role == NameRole) return account.getName();
    else if (role == NumberRole) return account.getNumber();
    else if (role == BalanceRole) return account.getFormattedBalance();
    else if (role == BankRole) return account.getBankName();

    return QVariant();
}

void AccountModel::setAccounts(const QList<Account> &accounts)
{
    beginResetModel();
    this->accounts = accounts;
    endResetModel();
}