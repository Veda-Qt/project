#ifndef HISTORY_H
#define HISTORY_H

#include <QDateTime>

class History
{


private:
    QString history_id;
    QString account_id;
    QDateTime time;
    long long amount;
    long long balance;
};

#endif // HISTORY_H
