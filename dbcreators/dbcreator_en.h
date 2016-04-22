#ifndef DBCREATOR_EN_H
#define DBCREATOR_EN_H

#include <QThread>

#include "idbcreator.h"

#include "databases/database_en.h"
#include "verbitems/verbitem_en.h"

// #include "base.h"


class DBCreator_EN : public IDBCreator, QThread
{
  
public:
  DBCreator_EN();
  
  virtual void runProcess(string path, bool useFolder, int startNum);
  QStringList getFilesInFolder(string path);
  void processFile(string path);
  
  void run();
  void done();  
  
private:
  QStringList getFormsList(const QWebElement &parent);
  void nextRow(bool first = false, int col = 0);
  QString checkVerb(VerbItem_EN verb);
  
  void processImpersonalForms(const QWebElement &row);
  void processIndicative(const QWebElement &row);
  void processSubjunctive(const QWebElement &row);
  void processConditional(const QWebElement &row);
  void processSimilarVerbs(const QWebElement &htmlElement);
  
private:
  QList<VerbItem_EN> verbsList;
  VerbItem_EN currentVerb;
  QWebElement globalRow;
  QStringList list1, list2;
  
  string scanPath;
  bool useFolder;
  
};

#endif // DBCREATOR_EN_H
