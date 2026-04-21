#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QLocale>

class Account
{
public:
    explicit Account(const QString &id, const QString &number, const QString &owner_name,
                     const QString &bank_name, long long balance) :
        id(id), number(number), owner_name(owner_name), bank_name(bank_name), balance(balance) {}

    QString getId() const { return id; }
    QString getNumber() const { return number; }
    QString getOwnerName() const { return owner_name; }
    QString getBankName() const { return bank_name; }
    long long getBalance() const { return balance; }
    QString getFormattedBalance() const { return QLocale(QLocale::Korean).toString(balance); }

private:
    QString id;
    QString number;
    QString owner_name;
    QString bank_name;
    long long balance;
};

#endif // ACCOUNT_H
