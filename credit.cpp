#include "credit.h"

#include "calc.h"
#include "ui_credit.h"

// int type;

Credit::Credit(QWidget *parent) : QDialog(parent), ui(new Ui::Credit) {
  ui->setupUi(this);
}

Credit::~Credit() { delete ui; }

void Credit::on_pushButton_grafs_clicked() {
  double sum, proc;
  double payment, over, total;
  int month;
  sum = (ui->Sum->text()).toDouble();
  month = (ui->Month->text()).toInt();
  proc = (ui->Proc->text()).toDouble();
  int type_1 = 0;
  if (ui->Annuitet->isChecked()) {
    type_1 = 1;
  } else if (ui->Diff->isChecked()) {
    type_1 = 2;
  }
  int error = credit_func(sum, month, proc, &payment, &over, &total, type_1);
  qDebug() << sum << month << proc << type_1 << error;
  if (error == 0) {
    QString Str_to_payment = QString::number(payment, 'g', 6);
    ui->payment->setText(Str_to_payment);
    qDebug() << Str_to_payment;
    QString Str_to_over = QString::number(over, 'g', 6);
    ui->over->setText(Str_to_over);
    QString Str_to_total = QString::number(total, 'g', 6);
    ui->total->setText(Str_to_total);
  } else {
    ui->payment->setText("Error");
  }
}
