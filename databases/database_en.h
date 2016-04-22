#ifndef DATABASE_EN_H
#define DATABASE_EN_H

#include <QObject>
#include <QtSql>

#include "verbitems/verbitem_en.h"

class Database_EN
{
public:
  Database_EN();
  ~Database_EN();
  
  void updateConfig(QString name, QString value);
  QString loadLastOptions();
  QString getOption(QString name);
  void closeConnection();
  
  bool createDatabase();
  
  void insertVerb(QString name, QString value);
  void insertVerbs(const QList<VerbItem_EN>& verbsList);
  
  
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

#endif // DATABASE_EN_H
