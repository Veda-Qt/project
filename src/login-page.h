#ifndef LOGINPAGE_H
#define LOGINPAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui{
class LoginPage;
}
QT_END_NAMESPACE

class LoginPage: public QWidget
{
    Q_OBJECT
public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage() override;
private:
    Ui::LoginPage *ui;
private slots:

};

#endif // LOGINPAGE_H
