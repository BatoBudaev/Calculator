#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QCalendarWidget>
#include <QDateEdit>
#include <QDialog>
#include <QStandardItemModel>
#include <QTableView>

extern "C" {
#include "../s21_bank.h"
}

namespace Ui {
class Deposit;
}

class Deposit : public QDialog {
  Q_OBJECT

 public:
  explicit Deposit(QWidget *parent = nullptr);
  ~Deposit();

 private slots:
  void on_radioButton_1_clicked();

  void on_radioButton_2_clicked();

  void on_depositComboBox_currentIndexChanged(int index);

  void on_withdrawalsComboBox_currentIndexChanged(int index);

  void on_pushButton_clicked();

  void getDeposit();

 private:
  Ui::Deposit *ui;
};

#endif  // DEPOSIT_H
