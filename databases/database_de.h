#ifndef DATABASE_DE_H
#define DATABASE_DE_H

#include <QObject>
#include <QtSql>

#include "verbitems/verbitem_de.h"

class Database_DE
{
public:
  Database_DE();
  ~Database_DE();
  
  void updateConfig(QString name, QString value);
  QString loadLastOptions();
  QString getOption(QString name);
  void closeConnection();
  
  void insertVerbs(const QList<VerbItem_DE>& verbsList);
  
  
private:
  bool connected;
  
  QString options_table="options";
  QString config_table="config";
  QString verbs_table="verbs";
  QString table;
  QString sql;
    
  QSqlDatabase db;  
  
  bool createConnection();
  void initDatabase();
  bool exists(QString table, QString name);
  void updateOption(QString name, QString value, QString dbtable);
  QString getOption(QString name, QString table);
};

#endif // DATABASE_DE_H
