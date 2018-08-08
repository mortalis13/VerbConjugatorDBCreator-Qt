#include "database_la.h"


Database_LA::Database_LA() {
  connected = createConnection();
  if (!connected) return;

  initDatabase();
}

Database_LA::~Database_LA() {
  closeConnection();
}


/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database_LA::createConnection() {
  if (db.isOpen()) return true;
  
  QString dbDir = "db_out/";
  QString dbName = "verbs_la";
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

void Database_LA::closeConnection() {
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database_LA::initDatabase() {
  if (!connected) return;

  QSqlQuery query;
  if (!query.exec("DROP TABLE IF EXISTS verbs")) {
    qDebug() << "cannot delete table: " << query.lastError();
    return;
  }

  bool res = query.exec("CREATE TABLE IF NOT EXISTS verbs ( \
          verb TEXT UNIQUE PRIMARY KEY, \
          lookupWord TEXT, \
          impersonalActive TEXT, \
          presentIndicativeActive TEXT, \
          imperfectIndicativeActive TEXT, \
          future1IndicativeActive TEXT, \
          perfectIndicativeActive TEXT, \
          pluperfectIndicativeActive TEXT, \
          future2IndicativeActive TEXT, \
          presentConjunctiveActive TEXT, \
          imperfectConjunctiveActive TEXT, \
          perfectConjunctiveActive TEXT, \
          pluperfectConjunctiveActive TEXT, \
          impersonalPassive TEXT, \
          presentIndicativePassive TEXT, \
          imperfectIndicativePassive TEXT, \
          future1IndicativePassive TEXT, \
          perfectIndicativePassive TEXT, \
          pluperfectIndicativePassive TEXT, \
          future2IndicativePassive TEXT, \
          presentConjunctivePassive TEXT, \
          imperfectConjunctivePassive TEXT, \
          perfectConjunctivePassive TEXT, \
          pluperfectConjunctivePassive TEXT, \
          imperativeI TEXT, \
          imperativeII TEXT, \
          similarVerbs TEXT \
        )" );

  if ( !res ) {
    qDebug() << "initDatabase() error: " << query.lastError();
    return;
  }

  qDebug() << "Database_LA initialized!";
}


void Database_LA::insertVerbs(const QList<VerbItem_LA>& verbsList) {
  if (!connected) return;
  
  db.transaction();

  QSqlQuery query;
  QString table = verbs_table;
  
  QString sql = "insert into " + table + " values( \
                :verb, \
                :lookupWord, \
                :impersonalActive, \
                :presentIndicativeActive, \
                :imperfectIndicativeActive, \
                :future1IndicativeActive, \
                :perfectIndicativeActive, \
                :pluperfectIndicativeActive, \
                :future2IndicativeActive, \
                :presentConjunctiveActive, \
                :imperfectConjunctiveActive, \
                :perfectConjunctiveActive, \
                :pluperfectConjunctiveActive, \
                :impersonalPassive, \
                :presentIndicativePassive, \
                :imperfectIndicativePassive, \
                :future1IndicativePassive, \
                :perfectIndicativePassive, \
                :pluperfectIndicativePassive, \
                :future2IndicativePassive, \
                :presentConjunctivePassive, \
                :imperfectConjunctivePassive, \
                :perfectConjunctivePassive, \
                :pluperfectConjunctivePassive, \
                :imperativeI, \
                :imperativeII, \
                :similarVerbs \
              )";
    
  foreach (VerbItem_LA item, verbsList) {
    query.prepare(sql);
    
    query.bindValue(":verb", item.verb);
    query.bindValue(":lookupWord", item.lookupWord.join(","));
    query.bindValue(":impersonalActive", item.impersonalActive.join(","));
    query.bindValue(":presentIndicativeActive", item.presentIndicativeActive.join(","));
    query.bindValue(":imperfectIndicativeActive", item.imperfectIndicativeActive.join(","));
    query.bindValue(":future1IndicativeActive", item.future1IndicativeActive.join(","));
    query.bindValue(":perfectIndicativeActive", item.perfectIndicativeActive.join(","));
    query.bindValue(":pluperfectIndicativeActive", item.pluperfectIndicativeActive.join(","));
    query.bindValue(":future2IndicativeActive", item.future2IndicativeActive.join(","));
    query.bindValue(":presentConjunctiveActive", item.presentConjunctiveActive.join(","));
    query.bindValue(":imperfectConjunctiveActive", item.imperfectConjunctiveActive.join(","));
    query.bindValue(":perfectConjunctiveActive", item.perfectConjunctiveActive.join(","));
    query.bindValue(":pluperfectConjunctiveActive", item.pluperfectConjunctiveActive.join(","));
    query.bindValue(":impersonalPassive", item.impersonalPassive.join(","));
    query.bindValue(":presentIndicativePassive", item.presentIndicativePassive.join(","));
    query.bindValue(":imperfectIndicativePassive", item.imperfectIndicativePassive.join(","));
    query.bindValue(":future1IndicativePassive", item.future1IndicativePassive.join(","));
    query.bindValue(":perfectIndicativePassive", item.perfectIndicativePassive.join(","));
    query.bindValue(":pluperfectIndicativePassive", item.pluperfectIndicativePassive.join(","));
    query.bindValue(":future2IndicativePassive", item.future2IndicativePassive.join(","));
    query.bindValue(":presentConjunctivePassive", item.presentConjunctivePassive.join(","));
    query.bindValue(":imperfectConjunctivePassive", item.imperfectConjunctivePassive.join(","));
    query.bindValue(":perfectConjunctivePassive", item.perfectConjunctivePassive.join(","));
    query.bindValue(":pluperfectConjunctivePassive", item.pluperfectConjunctivePassive.join(","));
    query.bindValue(":imperativeI", item.imperativeI.join(","));
    query.bindValue(":imperativeII", item.imperativeII.join(","));
    query.bindValue(":similarVerbs", item.similarVerbs.join(","));
    
    if (!query.exec()) {
      qDebug() << "insertVerbs() error [" << item.verb <<  "]: " << query.lastError();
    }
  }
  
  db.commit();
}
