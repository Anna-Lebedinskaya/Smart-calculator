#ifndef CREDIT_H
#define CREDIT_H

#include <QDebug>
#include <QDialog>
#include <QRadioButton>

extern "C" {
#include "calc.h"
}

namespace Ui {
class Credit;
}

class Credit : public QDialog {
  Q_OBJECT

 public:
  explicit Credit(QWidget *parent = nullptr);
  ~Credit();

 private slots:
  //    void credit_graph();
  //    void Annuitet_clicked1(bool checked);
  //    void Diff_clicked1(bool checked);
  void on_pushButton_grafs_clicked();

 private:
  Ui::Credit *ui;
};

#endif  // CREDIT_H
