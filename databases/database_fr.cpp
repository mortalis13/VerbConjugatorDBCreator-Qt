#include "database_fr.h"


Database_FR::Database_FR() {
  connected = createConnection();
  if(!connected) return;

  initDatabase();
}

Database_FR::~Database_FR() {
  closeConnection();
}


/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database_FR::createConnection(){
  if(db.isOpen()) return true;
  
  QString dbDir = "db_out/";
  QString dbName = "verbs_fr";
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

void Database_FR::closeConnection(){
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database_FR::initDatabase(){
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
          imperfectIndicative TEXT, \
          futureIndicative TEXT, \
          pastIndicative TEXT, \
          pastComplexIndicative TEXT, \
          pluperfectIndicative TEXT, \
          futurePerfectIndicative TEXT, \
          pastPerfectIndicative TEXT, \
          presentSubjunctive TEXT, \
          imperfectSubjunctive TEXT, \
          pastComplexSubjunctive TEXT, \
          pluperfectSubjunctive TEXT, \
          presentConditional TEXT, \
          pastConditional TEXT, \
          imperative TEXT, \
          similarVerbs TEXT \
        )" );

  if( !res ){
    qDebug() << "initDatabase() error: " << query.lastError();
    return;
  }

  qDebug() << "Database_FR initialized!";
}


void Database_FR::insertVerbs(const QList<VerbItem_FR>& verbsList){
  if (!connected) return;
  
  db.transaction();

  QSqlQuery query;
  QString table=verbs_table;
  
  QString sql="insert into "+table+" values( \
                :verb, \
                :impersonalForms, \
                :presentIndicative, \
                :imperfectIndicative, \
                :futureIndicative, \
                :pastIndicative, \
                :pastComplexIndicative, \
                :pluperfectIndicative, \
                :futurePerfectIndicative, \
                :pastPerfectIndicative, \
                :presentSubjunctive, \
                :imperfectSubjunctive, \
                :pastComplexSubjunctive, \
                :pluperfectSubjunctive, \
                :presentConditional, \
                :pastConditional, \
                :imperative, \
                :similarVerbs \
              )";
    
  foreach(VerbItem_FR item, verbsList){
    query.prepare(sql);
    
    query.bindValue(":verb", item.verb);
    query.bindValue(":impersonalForms", item.impersonalForms.join(","));
    query.bindValue(":presentIndicative", item.presentIndicative.join(","));
    query.bindValue(":imperfectIndicative", item.imperfectIndicative.join(","));
    query.bindValue(":futureIndicative", item.futureIndicative.join(","));
    query.bindValue(":pastIndicative", item.pastIndicative.join(","));
    query.bindValue(":pastComplexIndicative", item.pastComplexIndicative.join(","));
    query.bindValue(":pluperfectIndicative", item.pluperfectIndicative.join(","));
    query.bindValue(":futurePerfectIndicative", item.futurePerfectIndicative.join(","));
    query.bindValue(":pastPerfectIndicative", item.pastPerfectIndicative.join(","));
    query.bindValue(":presentSubjunctive", item.presentSubjunctive.join(","));
    query.bindValue(":imperfectSubjunctive", item.imperfectSubjunctive.join(","));
    query.bindValue(":pastComplexSubjunctive", item.pastComplexSubjunctive.join(","));
    query.bindValue(":pluperfectSubjunctive", item.pluperfectSubjunctive.join(","));
    query.bindValue(":presentConditional", item.presentConditional.join(","));
    query.bindValue(":pastConditional", item.pastConditional.join(","));
    query.bindValue(":imperative", item.imperative.join(","));
    query.bindValue(":similarVerbs", item.similarVerbs.join(","));
    
    if(!query.exec()){
      qDebug() << "insertVerbs() error [" << item.verb <<  "]: " << query.lastError();
    }
  }
  
  db.commit();
}
