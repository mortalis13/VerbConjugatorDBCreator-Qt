#ifndef DBCREATOR_FR_H
#define DBCREATOR_FR_H

#include "idbcreator.h"

#include "databases/database_fr.h"
#include "verbitems/verbitem_fr.h"

// #include "base.h"


class DBCreator_FR : public IDBCreator
{
  
public:
  DBCreator_FR();
  
  virtual void runProcess(string path, bool useFolder, int startNum);
  QStringList getFilesInFolder(string path);
  void processFile(string path);
  
  void run();
  void done();  
  
private:
  QStringList getFormsList(const QWebElement &parent);
  void nextRow(bool first = false, int col = 0);
  // QString checkVerb(VerbItem_FR verb);
  
  void processImpersonalForms(const QWebElement &row);
  void processIndicative(const QWebElement &row);
  void processSubjunctive(const QWebElement &row);
  void processConditional(const QWebElement &row);
  void processImperative(const QWebElement &row);
  void processSimilarVerbs(const QWebElement &htmlElement);
  
private:
  QList<VerbItem_FR> verbsList;
  VerbItem_FR currentVerb;
  QWebElement globalRow;
  QStringList list1, list2;
  
  string scanPath;
  bool useFolder;
  
};

#endif // DBCREATOR_FR_H
