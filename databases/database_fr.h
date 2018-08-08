#ifndef DATABASE_FR_H
#define DATABASE_FR_H

#include <QObject>
#include <QtSql>

#include "verbitems/verbitem_fr.h"

class Database_FR
{
public:
  Database_FR();
  ~Database_FR();
  
  void updateConfig(QString name, QString value);
  QString loadLastOptions();
  QString getOption(QString name);
  void closeConnection();
  
  void insertVerbs(const QList<VerbItem_FR>& verbsList);
  
  
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

#endif // DATABASE_FR_H
