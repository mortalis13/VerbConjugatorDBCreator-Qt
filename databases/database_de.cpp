#include "database_de.h"


Database_DE::Database_DE() {
  connected = createConnection();
  if(!connected) return;

  initDatabase();
}

Database_DE::~Database_DE() {
  closeConnection();
}


/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database_DE::createConnection(){
  if(db.isOpen()) return true;
  
  QString dbDir = "db_out/";
  QString dbName = "verbs_de";
  dbName = dbDir + dbName;
  
  QString temp = dbName + "_1";
  int num = 0;
  
  
  QFile dbfile(dbName + "_1" + ".db");
  while(dbfile.exists()){
    temp = dbName + "_" + QString::number(++num);
    dbfile.setFileName(temp + ".db");
  }
  dbName = temp;


  // QFile dbfile(dbName + ".db");
  // while(dbfile.exists()){
  //   temp = dbName + "_" + QString::number(++num);
  //   dbfile.setFileName(temp + ".db");

  //   // qDebug() << "trying to remove";
  //   // bool res = dbfile.remove();
  //   // if(res){
  //   //   qDebug() << "removed";
  //   // }
  // }
  // dbName = temp;


  qDebug() << "dbname:" << dbName;

  db = QSqlDatabase::addDatabase("QSQLITE");
  db.setDatabaseName(dbName + ".db");
  
  // qDebug() << "Transactions:" << db.driver()->hasFeature(QSqlDriver::Transactions);

  if( !db.open() )
  {
    qDebug() << db.lastError();
    qFatal( "Failed to connect." );
    return false;
  }
  qDebug( "Connected!" );

  return true;
}

void Database_DE::closeConnection(){
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database_DE::initDatabase(){
  if(!connected) return;

  QSqlQuery query;
  if(!query.exec("DROP TABLE IF EXISTS verbs")){
    qDebug() << "cannot delete table: " << query.lastError();
    return;
  }

  // bool res = query.exec(
  //       "CREATE TABLE IF NOT EXISTS verbs ( verb VARCHAR(200) UNIQUE PRIMARY KEY, article LONGTEXT )" );
  
  bool res = query.exec("CREATE TABLE IF NOT EXISTS verbs ( \
          verb TEXT UNIQUE PRIMARY KEY, \
          impersonalForms TEXT, \
          presentIndicative TEXT, \
          preteritIndicative TEXT, \
          futureIndicative TEXT, \
          perfectIndicative TEXT, \
          pluperfectIndicative TEXT, \
          futurePerfectIndicative TEXT, \
          presentSubjunctive TEXT, \
          preteritSubjunctive TEXT, \
          perfectSubjunctive TEXT, \
          pluperfectSubjunctive TEXT, \
          presentConditional TEXT, \
          perfectConditional TEXT, \
          imperative TEXT, \
          similarVerbs TEXT \
        )" );

  if( !res ){
    qDebug() << "initDatabase() error: " << query.lastError();
    return;
  }

  qDebug() << "Database_DE initialized!";
}


void Database_DE::insertVerbs(const QList<VerbItem_DE>& verbsList){
  if (!connected) return;
  
  db.transaction();

  QSqlQuery query;
  QString table=verbs_table;
  
  QString sql="insert into "+table+" values( \
                :verb, \
                :impersonalForms, \
                :presentIndicative, \
                :preteritIndicative, \
                :futureIndicative, \
                :perfectIndicative, \
                :pluperfectIndicative, \
                :futurePerfectIndicative, \
                :presentSubjunctive, \
                :preteritSubjunctive, \
                :perfectSubjunctive, \
                :pluperfectSubjunctive, \
                :presentConditional, \
                :perfectConditional, \
                :imperative, \
                :similarVerbs \
              )";
    
  foreach(VerbItem_DE item, verbsList){
    query.prepare(sql);
    
    query.bindValue(":verb", item.verb);
    query.bindValue(":impersonalForms", item.impersonalForms.join(","));
    query.bindValue(":presentIndicative", item.presentIndicative.join(","));
    query.bindValue(":preteritIndicative", item.preteritIndicative.join(","));
    query.bindValue(":futureIndicative", item.futureIndicative.join(","));
    query.bindValue(":perfectIndicative", item.perfectIndicative.join(","));
    query.bindValue(":pluperfectIndicative", item.pluperfectIndicative.join(","));
    query.bindValue(":futurePerfectIndicative", item.futurePerfectIndicative.join(","));
    query.bindValue(":presentSubjunctive", item.presentSubjunctive.join(","));
    query.bindValue(":preteritSubjunctive", item.preteritSubjunctive.join(","));
    query.bindValue(":perfectSubjunctive", item.perfectSubjunctive.join(","));
    query.bindValue(":pluperfectSubjunctive", item.pluperfectSubjunctive.join(","));
    query.bindValue(":presentConditional", item.presentConditional.join(","));
    query.bindValue(":perfectConditional", item.perfectConditional.join(","));
    query.bindValue(":imperative", item.imperative.join(","));
    query.bindValue(":similarVerbs", item.similarVerbs.join(","));
    
    if(!query.exec()){
      qDebug() << "insertVerbs() error [" << item.verb <<  "]: " << query.lastError();
    }
  }
  
  db.commit();
}
