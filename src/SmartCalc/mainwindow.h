#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <credit.h>
#include <deposit.h>
#include <graph.h>

#include <QDebug>
#include <QMainWindow>
#include <QPushButton>
#include <QtWidgets>

extern "C" {
#include "../s21_postfix.h"
#include "../s21_stack.h"
}

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

  bool getEqualsState() const { return equalsState; }

  void setEqualsState(bool state) { equalsState = state; }

  double getY(const QString &text, double X);

 private slots:
  void buttons_clicked();
  void operators_clicked();
  void functions_clicked();
  void sign_clicked();

  void on_pushButton_Equals_clicked();
  void on_pushButton_Ac_clicked();
  void on_pushButton_Mod_clicked();
  void on_pushButton_Graph_clicked();

  void on_actionCredit_triggered();

  void on_actionDeposit_triggered();

 private:
  Ui::MainWindow *ui;
  bool equalsState = false;
  Graph *graphWindow;
  Credit *creditWindow;
  Deposit *depositWindow;
};
#endif  // MAINWINDOW_H
