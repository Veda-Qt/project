#ifndef ACCOUNTHISTORYPAGE_H
#define ACCOUNTHISTORYPAGE_H

#include <QWidget>
#include "../cores/account.h"

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

signals:
    void backRequested();
    void transferRequested();

private slots:
    void on_btn_back_clicked();
    void on_btn_transfer_clicked();
    void updateAccountLabel(const Account &account);

private:
    Ui::AccountHistoryPage *ui;
};

#endif // ACCOUNTHISTORYPAGE_H
