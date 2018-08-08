#ifndef DBCREATOR_ES_H
#define DBCREATOR_ES_H

#include "idbcreator.h"

#include "databases/database_es.h"
#include "verbitems/verbitem_es.h"


class DBCreator_ES : public IDBCreator
{
  
public:
  DBCreator_ES();
  
  virtual void runProcess(string path, bool useFolder, int startNum);
  QStringList getFilesInFolder(string path);
  void processFile(string path);
  
  void run();
  void done();  
  
private:
  QStringList getFormsList(const QWebElement &parent);
  void nextRow(bool first = false, int col = 0);
  QString checkVerb(VerbItem_ES verb);
  
  void processImpersonalForms(const QWebElement &row);
  void processIndicative(const QWebElement &row);
  void processSubjunctive(const QWebElement &row);
  void processConditional(const QWebElement &row);
  void processImperative(const QWebElement &row);
  void processSimilarVerbs(const QWebElement &htmlElement);
  
private:
  QList<VerbItem_ES> verbsList;
  VerbItem_ES currentVerb;
  QWebElement globalRow;
  QStringList list1, list2;
  
  string scanPath;
  bool useFolder;
  
};

#endif // DBCREATOR_ES_H
