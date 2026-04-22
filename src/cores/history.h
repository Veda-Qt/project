#ifndef HISTORY_H
#define HISTORY_H

#include <QDateTime>

class History
{
public:
    History() = default;
    History(QString number, QString history_id, QString origin_name, QString type,
                     QDateTime timestamp, long long amount, long long balance) :
                     history_id(history_id), origin_name(origin_name), type(type),
                     timestamp(timestamp), amount(amount), balance(balance) {}

    QString getNumber() const { return number; }
    QString getHistoryId() const { return history_id; }
    QString getOriginName() const { return origin_name; }
    QString getType() const { return type; }
    QDateTime getTimestamp() const { return timestamp; }
    QString getFormattedTimestamp() const { return timestamp.toString("yyyy.MM.dd-HH:mm:ss"); }
    long long getAmount() const { return amount; }
    long long getBalance() const { return balance; }

private:
    QString number;
    QString history_id;
    QString origin_name;
    QString type;
    QDateTime timestamp;
    long long amount;
    long long balance;
};

Q_DECLARE_METATYPE(History *)

#endif // HISTORY_H