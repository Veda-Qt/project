#ifndef ACCOUNTLISTPAGE_H
#define ACCOUNTLISTPAGE_H

#include <QWidget>
#include <QModelIndex>
#include "../cores/account.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class AccountListPage;
}
QT_END_NAMESPACE;

class AccountListPage : public QWidget
{
    Q_OBJECT

public:
    explicit AccountListPage(QWidget *parent = nullptr);
    ~AccountListPage() override;

signals:
    void accountSelected(const Account &account);

private slots:
    void on_lview_acnt_doubleClicked(const QModelIndex &index);

private:
    Ui::AccountListPage *ui;
};

#endif // ACCOUNTLISTPAGE_H
