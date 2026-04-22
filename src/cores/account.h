#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <QString>
#include <QLocale>

enum Bank {
    KB,
    Shinhan,
    Woori,
    Hana,
    NH,
    Kakao,
    Toss
};

class BankHelper {
public:
    static QString toString(Bank bank) {
        switch(bank) {
        case Bank::KB: return "국민은행";
        case Bank::Shinhan: return "신한은행";
        case Bank::Woori: return "우리은행";
        case Bank::Hana: return "하나은행";
        case Bank::NH: return "농협은행";
        case Bank::Kakao: return "카카오뱅크";
        default: return "알 수 없음";
        }
    }
};

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
