#ifndef DBCREATOR_IT_H
#define DBCREATOR_IT_H

#include "idbcreator.h"

#include "databases/database_it.h"
#include "verbitems/verbitem_it.h"


class DBCreator_IT : public IDBCreator
{
  
public:
  DBCreator_IT();
  
  virtual void runProcess(string path, bool useFolder, int startNum);
  QStringList getFilesInFolder(string path);
  void processFile(string path);
  
  void run();
  void done();  
  
private:
  QStringList getFormsList(const QWebElement &parent);
  void nextRow(bool first = false, int col = 0);
  // QString checkVerb(VerbItem_IT verb);
  
  void printList(QStringList);
  
  void processImpersonalForms(const QWebElement &row);
  void processIndicative(const QWebElement &row);
  void processSubjunctive(const QWebElement &row);
  void processConditional(const QWebElement &row);
  void processImperative(const QWebElement &row);
  void processSimilarVerbs(const QWebElement &htmlElement);
  
private:
  QList<VerbItem_IT> verbsList;
  VerbItem_IT currentVerb;
  QWebElement globalRow;
  QStringList list1, list2;
  
  string scanPath;
  bool useFolder;
  
};

#endif // DBCREATOR_IT_H
