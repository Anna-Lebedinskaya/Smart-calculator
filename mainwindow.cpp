#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "credit.h"

extern "C" {
#include "calc.h"
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(digits_numbers()));
  connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(digits_numbers()));

  connect(ui->pushButton_p, SIGNAL(clicked()), this, SLOT(point_l1_l2()));

  connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func()));
  connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func()));

  connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_openbracket, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_closebracket, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_plus, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_pow, SIGNAL(clicked()), this, SLOT(other()));
  connect(ui->pushButton_x, SIGNAL(clicked()), this, SLOT(other()));

  connect(ui->pushButton_minus, SIGNAL(clicked()), this, SLOT(minus()));

  connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear_calc()));

  connect(ui->pushButton_res, SIGNAL(clicked()), this, SLOT(get_result()));

  connect(ui->radioButton_2, SIGNAL(clicked()), this, SLOT(credit_clicked()));
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::count_digit(QLineEdit *line) {
  //    line = ui->value_x;
  QPushButton *button = (QPushButton *)sender();
  double num;
  QString new_value_x;

  if (line->text().contains(".") && button->text() == "0") {
    new_value_x = line->text() + button->text();
  } else {
    num = (line->text() + button->text()).toDouble();
    new_value_x = QString::number(num, 'g', 15);
  }

  line->setText(new_value_x);
}

void MainWindow::check_point(QLineEdit *line) {
  //    line = ui->value_x;
  if (!(line->text().contains('.'))) line->setText(line->text() + ".");
}

void MainWindow::check_minus(QLineEdit *line) {
  QPushButton *button = (QPushButton *)sender();
  double num;
  QString new_label;
  if (button->text() == "-") {
    num = (line->text()).toDouble();
    num = num * (-1);
    new_label = QString::number(num, 'g', 15);
    line->setText(new_label);
  }
}

void MainWindow::digits_numbers() {
  if (ui->Show_result->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    QString str = ui->Show_result->text() + button->text();
    ui->Show_result->setText(str);
  } else if (ui->value_x->hasFocus()) {
    count_digit(ui->value_x);
  } else if (ui->value_x_3->hasFocus()) {
    count_digit(ui->value_x_3);
  } else if (ui->value_x_4->hasFocus()) {
    count_digit(ui->value_x_4);
  }
}

void MainWindow::point_l1_l2() {
  if (ui->Show_result->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    QString str = ui->Show_result->text() + button->text();
    ui->Show_result->setText(str);
  } else if (ui->value_x->hasFocus()) {
    check_point(ui->value_x);
  } else if (ui->value_x_3->hasFocus()) {
    check_point(ui->value_x_3);
  } else if (ui->value_x_4->hasFocus()) {
    check_point(ui->value_x_4);
  }
}

void MainWindow::func() {
  if (ui->Show_result->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    QString str = ui->Show_result->text() + button->text() + "(";
    ui->Show_result->setText(str);
  }
}

void MainWindow::other() {
  if (ui->Show_result->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    QString str = ui->Show_result->text() + button->text();
    ui->Show_result->setText(str);
  }
}

void MainWindow::minus() {
  if (ui->Show_result->hasFocus()) {
    QPushButton *button = (QPushButton *)sender();
    QString str = ui->Show_result->text() + button->text();
    ui->Show_result->setText(str);
  } else if (ui->value_x->hasFocus()) {
    check_minus(ui->value_x);
  } else if (ui->value_x_3->hasFocus()) {
    check_minus(ui->value_x_3);
  } else if (ui->value_x_4->hasFocus()) {
    check_minus(ui->value_x_4);
  }
}

void MainWindow::clear_calc() {
  if (ui->Show_result->hasFocus())
    ui->Show_result->setText("");
  else
    ui->value_x->setText("");
}

void MainWindow::get_result() {
  QString str = ui->Show_result->text();
  double x = (ui->value_x->text()).toDouble();
  double result = 0;

  char str1[255] = {0};
  const QByteArray stringData = str.toUtf8();
  str1[str.size()] = '\0';
  std::copy(stringData.constBegin(),
            stringData.constBegin() + stringData.size(), str1);

  int error = main_func(str1, &x, &result);
  if (error == 0) {
    QString res_to_str = QString::number(result, 'g', 15);
    ui->Show_result->setText(res_to_str);
  } else {
    ui->Show_result->setText("Error");
  }
}

void MainWindow::on_pushButton_grafs_clicked() {
  ui->widget->clearGraphs();
  ui->widget->replot();
  x.clear();
  y.clear();

  h = 0.1;
  Ymin = 1000000;
  Ymax = -1000000;
  double result = 0;
  int error = 0;

  x1 = (ui->value_x_3->text()).toDouble();
  x2 = (ui->value_x_4->text()).toDouble();

  if ((x1 == 0) || (x2 == 0)) {
    x1 = -5;
    x2 = 5;
  }

  xBegin = x1;
  xEnd = x2 + h;

  if (xBegin < -1000) {
    xBegin = -1000;
  }
  if (xEnd > 1000) {
    xEnd = 1000;
  }

  if (xBegin == xEnd) {
    xBegin = -1;
    xEnd = 1;
  }

  if (xBegin > xEnd) {
    double temp = xBegin;
    xBegin = xEnd;
    xEnd = temp;
  }

  QString str = ui->Show_result->text();

  char str1[255] = {0};
  const QByteArray stringData = str.toUtf8();
  str1[str.size()] = '\0';
  std::copy(stringData.constBegin(),
            stringData.constBegin() + stringData.size(), str1);

  //           qDebug()<<xBegin<<xEnd;
  for (X = xBegin; X <= xEnd; X += h) {
    error = main_func(str1, &X, &result);

    if (error == 0) {
      x.push_back(X);
      if (result < Ymin) {
        Ymin = result;
      }
      if (result > Ymax) {
        Ymax = result;
      }
      y.push_back(result);
    } else {
      x.clear();
      y.clear();
      ui->Show_result->setText("Error");
      break;
    }
  }

  ui->widget->yAxis->setRange(x1, x2);
  ui->widget->yAxis->setRange(Ymin * 1.05, Ymax * 1.05);
  ui->widget->addGraph();
  ui->widget->graph(0)->addData(x, y);
  ui->widget->replot();
  ui->widget->setInteraction(QCP::iRangeZoom, true);
  ui->widget->setInteraction(QCP::iRangeDrag, true);
}

void MainWindow::credit_clicked() {
  Credit window;
  window.setModal(true);
  window.exec();
}
