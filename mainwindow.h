#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <string>
#include <fstream>

#include <iostream>
#include <vector>
#include <memory>

// #include "database.h"
// #include "base.h"

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
//  void examineChildElements(const QWebElement &parentElement);

  void listVerbs(int section);

  void logList(QStringList list);
  void logList(QString listString);
  void log(QString text);
  void status(QString text);
  
  
private:
  Ui::MainWindow *ui;
  
  unique_ptr<IDBCreator> dbcreator;

  // QWebElement globalRow;
  // QString listString1, listString2;
  // QStringList list1, list2;
  
  // Database* db;

  // QList<VerbItem> verbsList;
  // VerbItem currentVerb;

private:
  void addActions();
  void addShortcuts();
  
  // void nextRow(bool first = false, int col = 0);
  // QStringList getFormsList(const QWebElement &parent);
  // QString checkVerb(VerbItem verb);
  
  // void processImpersonalForms(const QWebElement &row);
  // void processIndicative(const QWebElement &row);
  // void processSubjunctive(const QWebElement &row);
  // void processConditional(const QWebElement &row);
  // void processImperative(const QWebElement &row);
  // void processSimilarVerbs(const QWebElement &htmlElement);

private slots:
  void bRunClick();
  void bTestClick();
  void bTest1Click();
  
  void updateLog(QString text);

};

#endif // MAINWINDOW_H
