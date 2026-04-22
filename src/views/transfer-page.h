#ifndef TRANSFERPAGE_H
#define TRANSFERPAGE_H

#include <QWidget>
#include <QModelIndex>
#include "../cores/account.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class TransferPage;
}
QT_END_NAMESPACE

class TransferPage : public QWidget
{
    Q_OBJECT

public:
    explicit TransferPage(QWidget *parent = nullptr);
    ~TransferPage() override;

signals:
    // switch to history page.
    void backRequested();
    // request transfer at this account.
    void transferRequested(const QString &target_number, const QString &target_bank_name, long long amount);

private slots:
    void on_btn_back_clicked();
    void on_btn_ok_clicked();
    void on_lview_acnt_histry_doubleClicked(const QModelIndex &index);
    void on_transferSuccess();
    void on_transferFailed(const QString &errorMessage);
private:
    Ui::TransferPage *ui;
};

#endif // TRANSFERPAGE_H
