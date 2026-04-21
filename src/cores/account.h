#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QLocale>

class Account
{
public:
    Account() = default;

    Account(const QString &number, const QString &owner_name, const QString &bank_name) :
            number(number), owner_name(owner_name), bank_name(bank_name) {}

    Account(const QString &number, const QString &owner_id, const QString &owner_name,
            const QString &bank_name, long long balance) :
            number(number), owner_id(owner_id), owner_name(owner_name),
            bank_name(bank_name), balance(balance) {}

    QString getNumber() const { return number; }
    QString getOwnerId() const { return owner_id; }
    QString getOwnerName() const { return owner_name; }
    QString getBankName() const { return bank_name; }
    long long getBalance() const { return balance; }
    QString getFormattedBalance() const { return QLocale(QLocale::Korean).toString(balance); }

private:
    QString number;
    QString owner_id;
    QString owner_name;
    QString bank_name;
    long long balance;
};

Q_DECLARE_METATYPE(Account *)

#endif // ACCOUNT_H
