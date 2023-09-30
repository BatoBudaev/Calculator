#ifndef GRAPH_H
#define GRAPH_H

#include <QDialog>
#include <QVector>

class MainWindow;

namespace Ui {
class Graph;
}

class Graph : public QDialog {
  Q_OBJECT

 public:
  explicit Graph(QWidget *parent = nullptr);
  ~Graph();

  Graph(const QString &text, MainWindow *mainWindow, QWidget *parent = nullptr);

  void setMainWindowRef(MainWindow *newMainWindowRef);

  MainWindow *getMainWindowRef() const;

 private slots:
  void on_pushButton_clicked();
  void drawGraph(const QString &text);
  void setValidators();

 private:
  Ui::Graph *ui;
  MainWindow *mainWindowRef;

  double xBegin, xEnd, h, X;
  int N;
  QVector<double> x, y;
};

#endif  // GRAPH_H
