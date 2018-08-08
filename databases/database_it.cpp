#include "database_it.h"


Database_IT::Database_IT() {
  connected = createConnection();
  if (!connected) return;

  initDatabase();
}

Database_IT::~Database_IT() {
  closeConnection();
}


/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database_IT::createConnection() {
  if (db.isOpen()) return true;
  
  QString dbDir = "db_out/";
  QString dbName = "verbs_it";
  dbName = dbDir + dbName;
  
  QString temp = dbName + "_1";
  int num = 0;
  
  
  QFile dbfile(dbName + "_1" + ".db");
  if (dbfile.exists()) {
    temp = dbName + "_" + QString::number(++num);
    dbfile.setFileName(temp + ".db");
  }
  dbName = temp;

  qDebug() << "dbname:" << dbName;

  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(dbName + ".db");
  
  // qDebug() << "Transactions:" << db.driver()->hasFeature(QSqlDriver::Transactions);

  if ( !db.open() )
  {
    qDebug() << db.lastError();
    qFatal( "Failed to connect." );
    return false;
  }
  qDebug( "Connected!" );

  return true;
}

void Database_IT::closeConnection() {
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database_IT::initDatabase() {
  if (!connected) return;

  QSqlQuery query;
  if (!query.exec("DROP TABLE IF EXISTS verbs")) {
    qDebug() << "cannot delete table: " << query.lastError();
    return;
  }

  bool res = query.exec("CREATE TABLE IF NOT EXISTS verbs ( \
          verb TEXT UNIQUE PRIMARY KEY, \
          impersonalForms TEXT, \
          presentIndicative TEXT, \
          imperfectIndicative TEXT, \
          futureIndicative TEXT, \
          pastRemoteIndicative TEXT, \
          pastIndicative TEXT, \
          pluperfectIndicative TEXT, \
          futurePerfectIndicative TEXT, \
          pluperfectRemoteIndicative TEXT, \
          presentSubjunctive TEXT, \
          imperfectSubjunctive TEXT, \
          pastSubjunctive TEXT, \
          pluperfectSubjunctive TEXT, \
          presentConditional TEXT, \
          pastConditional TEXT, \
          imperative TEXT, \
          similarVerbs TEXT \
        )" );

  if ( !res ) {
    qDebug() << "initDatabase() error: " << query.lastError();
    return;
  }

  qDebug() << "Database_IT initialized!";
}


void Database_IT::insertVerbs(const QList<VerbItem_IT>& verbsList) {
  if (!connected) return;
  
  db.transaction();

  QSqlQuery query;
  QString table = verbs_table;
  
  QString sql = "insert into " + table + " values( \
                :verb, \
                :impersonalForms, \
                :presentIndicative, \
                :imperfectIndicative, \
                :futureIndicative, \
                :pastRemoteIndicative, \
                :pastIndicative, \
                :pluperfectIndicative, \
                :futurePerfectIndicative, \
                :pluperfectRemoteIndicative, \
                :presentSubjunctive, \
                :imperfectSubjunctive, \
                :pastSubjunctive, \
                :pluperfectSubjunctive, \
                :presentConditional, \
                :pastConditional, \
                :imperative, \
                :similarVerbs \
              )";
    
  foreach (VerbItem_IT item, verbsList) {
    query.prepare(sql);
    
    query.bindValue(":verb", item.verb);
    query.bindValue(":impersonalForms", item.impersonalForms.join(","));
    query.bindValue(":presentIndicative", item.presentIndicative.join(","));
    query.bindValue(":imperfectIndicative", item.imperfectIndicative.join(","));
    query.bindValue(":futureIndicative", item.futureIndicative.join(","));
    query.bindValue(":pastRemoteIndicative", item.pastRemoteIndicative.join(","));
    query.bindValue(":pastIndicative", item.pastIndicative.join(","));
    query.bindValue(":pluperfectIndicative", item.pluperfectIndicative.join(","));
    query.bindValue(":futurePerfectIndicative", item.futurePerfectIndicative.join(","));
    query.bindValue(":pluperfectRemoteIndicative", item.pluperfectRemoteIndicative.join(","));
    query.bindValue(":presentSubjunctive", item.presentSubjunctive.join(","));
    query.bindValue(":imperfectSubjunctive", item.imperfectSubjunctive.join(","));
    query.bindValue(":pastSubjunctive", item.pastSubjunctive.join(","));
    query.bindValue(":pluperfectSubjunctive", item.pluperfectSubjunctive.join(","));
    query.bindValue(":presentConditional", item.presentConditional.join(","));
    query.bindValue(":pastConditional", item.pastConditional.join(","));
    query.bindValue(":imperative", item.imperative.join(","));
    query.bindValue(":similarVerbs", item.similarVerbs.join(","));
    
    if (!query.exec()) {
      qDebug() << "insertVerbs() error [" << item.verb <<  "]: " << query.lastError();
    }
  }
  
  db.commit();
}
