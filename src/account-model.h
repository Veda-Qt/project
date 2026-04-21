#ifndef ACCOUNTMODEL_H
#define ACCOUNTMODEL_H

#include <QString>
#include <QAbstractListModel>
#include <QModelIndex>
#include <QLocale>

class Account
{
public:
    enum class Bank { KB, WOORI, HANA, SHINHAN, KAKAO, TOSS };

    explicit Account(int id, int balance, QString name, QString number, Bank bank) :
                     id(id), balance(balance), name(name), number(number), bank(bank) {}

    int getId() const { return id; }
    int getBalance() const { return balance; }
    QString getName() const { return name; }
    QString getNumber() const { return number; }
    QString getFormattedBalance() const { return QLocale(QLocale::Korean).toString(balance); }
    QString getBankName() const;

private:
    int id;
    int balance;
    QString name;
    QString number;
    Bank bank;
};

class AccountModel : public QAbstractListModel
{
public:
    enum AccountRoles { IdRole = Qt::UserRole + 1, NameRole, NumberRole, BalanceRole, BankRole };

    explicit AccountModel(QObject *parent = nullptr) : QAbstractListModel(parent) {};
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    void setAccounts(const QList<Account> &accounts);

private:
    QList<Account> accounts;
};

#endif // ACCOUNTMODEL_H
