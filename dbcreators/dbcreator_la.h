#ifndef DBCREATOR_LA_H
#define DBCREATOR_LA_H

#include "idbcreator.h"

#include "databases/database_la.h"
#include "verbitems/verbitem_la.h"

// #include "base.h"


class DBCreator_LA : public IDBCreator
{
  
public:
  DBCreator_LA();
  
  virtual void runProcess(string path, bool useFolder, int startNum);
  QStringList getFilesInFolder(string path);
  void processFile(string path);
  
  void run();
  void done();  
  
private:
  QStringList getFormsList(const QWebElement &parent);
  void nextRow(bool first = false, int col = 0);
  // QString checkVerb(VerbItem_LA verb);
  
  void processLookupWord(const QWebElement &row);
  void processImpersonalForms(const QWebElement &row);
  void processActive(const QWebElement &row);
  void processPassive(const QWebElement &row);
  void processImperative(const QWebElement &row);
  void processSimilarVerbs(const QWebElement &htmlElement);
  
private:
  QList<VerbItem_LA> verbsList;
  VerbItem_LA currentVerb;
  QWebElement globalRow;
  QStringList list1, list2;
  
  string scanPath;
  bool useFolder;
  
};

#endif // DBCREATOR_LA_H
