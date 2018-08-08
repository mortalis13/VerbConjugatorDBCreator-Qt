#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>
#include <fstream>

#include <iostream>
#include <vector>
#include <memory>

#include "dbcreators/idbcreator.h"
#include "dbcreators/dbcreator_en.h"
#include "dbcreators/dbcreator_es.h"
#include "dbcreators/dbcreator_de.h"

#include "dbcreators/dbcreator_fr.h"
#include "dbcreators/dbcreator_it.h"
#include "dbcreators/dbcreator_la.h"


namespace Ui {
class MainWindow;
}

using namespace std;

class MainWindow : public QMainWindow
{
  Q_OBJECT
  
public:
  explicit MainWindow(QWidget *parent = 0);
  ~MainWindow();

  void test();
  void runProcess(QString lang);

  void listVerbs(int section);

  void logList(QStringList list);
  void logList(QString listString);
  void log(QString text);
  void status(QString text);
  
  
private:
  Ui::MainWindow *ui;
  
  unique_ptr<IDBCreator> dbcreator;

private:
  void addActions();
  void addShortcuts();
  
private slots:
  void bRunClick();
  void bTestClick();
  void bTest1Click();
  
  void updateLog(QString text);

};

#endif // MAINWINDOW_H
