#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDebug>
#include <QLineEdit>
#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow();

 private:
  Ui::MainWindow* ui;
  void count_digit(QLineEdit* line);
  void check_point(QLineEdit* line);
  void check_minus(QLineEdit* line);
  double xBegin, xEnd, h, X, x1, x2, Ymin, Ymax;
  QVector<double> x, y;

 private slots:
  void digits_numbers();
  void point_l1_l2();
  void func();
  void other();
  void minus();
  void clear_calc();
  void get_result();
  void on_pushButton_grafs_clicked();

  void credit_clicked();
};
#endif  // MAINWINDOW_H
