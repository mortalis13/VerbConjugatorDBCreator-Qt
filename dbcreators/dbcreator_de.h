#ifndef DBCREATOR_DE_H
#define DBCREATOR_DE_H

#include "idbcreator.h"

#include "databases/database_de.h"
#include "verbitems/verbitem_de.h"

// #include "base.h"


class DBCreator_DE : public IDBCreator
{
  
public:
  DBCreator_DE();
  
  virtual void runProcess(string path, bool useFolder, int startNum);
  QStringList getFilesInFolder(string path);
  void processFile(string path);
  
  void run();
  void done();  
  
private:
  QStringList getFormsList(const QWebElement &parent);
  void nextRow(bool first = false, int col = 0);
  QString checkVerb(VerbItem_DE verb);
  
  void processImpersonalForms(const QWebElement &row);
  void processIndicative(const QWebElement &row);
  void processSubjunctive(const QWebElement &row);
  void processConditional(const QWebElement &row);
  void processImperative(const QWebElement &row);
  void processSimilarVerbs(const QWebElement &htmlElement);
  
private:
  QList<VerbItem_DE> verbsList;
  VerbItem_DE currentVerb;
  QWebElement globalRow;
  QStringList list1, list2;
  
  string scanPath;
  bool useFolder;
  
};

#endif // DBCREATOR_DE_H
