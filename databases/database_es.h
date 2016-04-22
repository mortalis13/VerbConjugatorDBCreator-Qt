#ifndef DATABASE_ES_H
#define DATABASE_ES_H

#include <QObject>
#include <QtSql>

#include "verbitems/verbitem_es.h"
// #include "base.h"

class Database_ES
{
public:
  Database_ES();
  ~Database_ES();
  
  void updateConfig(QString name, QString value);
  QString loadLastOptions();
  QString getOption(QString name);
  void closeConnection();
  
  bool createDatabase();
  
  void insertVerb(QString name, QString value);
  void insertVerbs(const QList<VerbItem_ES>& verbsList);
  
  
private:
  bool connected;
  
  QString options_table="options";
  QString config_table="config";
  QString verbs_table="verbs";
  QString table;
  QString sql;
    
  QSqlDatabase db;  
//  QSqlQuery query;
  
  bool createConnection();
  void initDatabase();
  bool exists(QString table, QString name);
  void updateOption(QString name, QString value, QString dbtable);
  QString getOption(QString name, QString table);
};

#endif // DATABASE_ES_H
