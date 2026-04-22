#ifndef LOGIN_PAGE_H
#define LOGIN_PAGE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class LoginPage;
}
QT_END_NAMESPACE

struct User
{
    QString id;
    QString pwd;
};

class LoginPage : public QWidget
{
    Q_OBJECT

public:
    explicit LoginPage(QWidget *parent = nullptr);
    ~LoginPage() override;

    QString currentUserId() const; // 현재 로그인한 id 반환

signals:
    void loginSuccess(const QString &id); // 로그인 성공 신호

private slots:
    void on_btn_adduser_clicked(); // 회원가입 버튼 클릭 시
    void on_btn_login_clicked(); // 로그인 버튼 클릭 시

private:
    bool checkUser(const QString &id, const QString &pwd);
    bool registerUser(const QString &id, const QString &pwd);

    Ui::LoginPage *ui;
    QString id;
};

#endif // LOGIN_PAGE_H
