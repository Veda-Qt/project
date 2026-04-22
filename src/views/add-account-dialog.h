#ifndef ADD_ACCOUNT_DIALOG_H
#define ADD_ACCOUNT_DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class AddAccountDialog;
}
QT_END_NAMESPACE

class AddAccountDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AddAccountDialog(QWidget *parent = nullptr);
    ~AddAccountDialog() override;

private slots:
    void accept() override;

private:
    QString generateUniqueAccountNumber();

    Ui::AddAccountDialog *ui;
};

#endif // ADD_ACCOUNT_DIALOG_H
