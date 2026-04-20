#ifndef ACCOUNTHISTORYPAGE_H
#define ACCOUNTHISTORYPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class AccountHistoryPage;
}
QT_END_NAMESPACE

class AccountHistoryPage : public QWidget
{
    Q_OBJECT

public:
    explicit AccountHistoryPage(QWidget *parent = nullptr);
    ~AccountHistoryPage() override;

private:
    Ui::AccountHistoryPage *ui;
};

#endif // ACCOUNTHISTORYPAGE_H
