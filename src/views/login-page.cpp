#include "login-page.h"
#include "./ui_login-page.h"
#include "../cores/db-manager.h"

LoginPage::LoginPage(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::LoginPage)
{
    ui->setupUi(this);
}

LoginPage::~LoginPage()
{
    delete ui;
}

void LoginPage::on_btn_adduser_clicked()
{
    QString id = ui->ledit_id->text().trimmed();
    QString pwd = ui->ledit_pw->text().trimmed();

    if (id.isEmpty() || pwd.isEmpty()) {
        ui->lbl_message->setStyleSheet("color: red;");
        ui->lbl_message->setText("아이디와 비밀번호를 모두 입력해주세요.");
        return;
    }

    if (registerUser(id, pwd)) {
        ui->lbl_message->setStyleSheet("color: blue;");
        ui->lbl_message->setText("회원가입이 완료되었습니다. 로그인해주세요.");
        ui->ledit_id->clear();
        ui->ledit_pw->clear();
        ui->ledit_id->setFocus();
    } else {
        ui->lbl_message->setStyleSheet("color: red;");
        ui->lbl_message->setText("이미 존재하는 아이디입니다.");
    }
}

void LoginPage::on_btn_login_clicked()
{
    QString id = ui->ledit_id->text().trimmed();
    QString pwd = ui->ledit_pw->text().trimmed();

    if (id.isEmpty() || pwd.isEmpty()) {
        ui->lbl_message->setStyleSheet("color: red;");
        ui->lbl_message->setText("아이디와 비밀번호를 모두 입력해주세요.");
        return;
    }

    if (checkUser(id, pwd)) {
        this->id = id;

        ui->ledit_id->clear();
        ui->ledit_pw->clear();

        emit loginSuccess(this->id);
    } else {
        ui->lbl_message->setStyleSheet("color: red;");
        ui->lbl_message->setText("아이디 또는 비밀번호가 일치하지 않습니다.");
    }
}

bool LoginPage::checkUser(const QString &id, const QString &pwd)
{
    QJsonObject conditions;
    conditions["id"] = id;
    conditions["pwd"] = pwd;

    // DbManager에게 "users 테이블에서 id랑 pwd 둘 다 일치하는 녀석 찾아와!" 라고 명령
    QJsonArray users = DbManager::instance().selectItems("users", conditions);

    // 배열이 비어있지 않다 = 일치하는 유저가 존재한다!
    return !users.isEmpty();
}

bool LoginPage::registerUser(const QString &id, const QString &pwd)
{
    QJsonObject conditions;
    conditions["id"] = id;
    if (!DbManager::instance().selectItems("users", conditions).isEmpty()) {
        return false; // id is already used.
    }

    QJsonObject new_user;
    new_user["id"] = id;
    new_user["pwd"] = pwd;
    new_user["name"] = "사용자"; // TODO: align dummy name
    return DbManager::instance().insertItem("users", new_user);
}