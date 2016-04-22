#include "database_en.h"


Database_EN::Database_EN()
{
  connected = createConnection();
  if(!connected) return;

  initDatabase();
}

Database_EN::~Database_EN()
{
  closeConnection();
}


bool Database_EN::createDatabase(){
  connected = createConnection();
  if(!connected) return false;
  
  initDatabase();
  
  return true;
}

/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database_EN::createConnection(){
  if(db.isOpen()) return true;
  
  QString dbDir = "db_out/";
  QString dbName = "verbs_en";
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

void Database_EN::closeConnection(){
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database_EN::initDatabase(){
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
          pastIndicative TEXT, \
          futureIndicative TEXT, \
          perfectIndicative TEXT, \
          pluperfectIndicative TEXT, \
          futurePerfectIndicative TEXT, \
          presentSubjunctive TEXT, \
          pastSubjunctive TEXT, \
          perfectSubjunctive TEXT, \
          pluperfectSubjunctive TEXT, \
          presentConditional TEXT, \
          perfectConditional TEXT, \
          similarVerbs TEXT \
        )" );

  if( !res ){
    qDebug() << "initDatabase() error: " << query.lastError();
    return;
  }

  qDebug() << "Database_EN initialized!";
}


void Database_EN::insertVerbs(const QList<VerbItem_EN>& verbsList){
  if (!connected) return;
  
  db.transaction();

  QSqlQuery query;
  QString table=verbs_table;
  
  QString sql="insert into "+table+" values( \
                :verb, \
                :impersonalForms, \
                :presentIndicative, \
                :pastIndicative, \
                :futureIndicative, \
                :perfectIndicative, \
                :pluperfectIndicative, \
                :futurePerfectIndicative, \
                :presentSubjunctive, \
                :pastSubjunctive, \
                :perfectSubjunctive, \
                :pluperfectSubjunctive, \
                :presentConditional, \
                :perfectConditional, \
                :similarVerbs \
              )";
    
  foreach(VerbItem_EN item, verbsList){
    query.prepare(sql);
    
    query.bindValue(":verb", item.verb);
    query.bindValue(":impersonalForms", item.impersonalForms.join(","));
    query.bindValue(":presentIndicative", item.presentIndicative.join(","));
    query.bindValue(":pastIndicative", item.pastIndicative.join(","));
    query.bindValue(":futureIndicative", item.futureIndicative.join(","));
    query.bindValue(":perfectIndicative", item.perfectIndicative.join(","));
    query.bindValue(":pluperfectIndicative", item.pluperfectIndicative.join(","));
    query.bindValue(":futurePerfectIndicative", item.futurePerfectIndicative.join(","));
    query.bindValue(":presentSubjunctive", item.presentSubjunctive.join(","));
    query.bindValue(":pastSubjunctive", item.pastSubjunctive.join(","));
    query.bindValue(":perfectSubjunctive", item.perfectSubjunctive.join(","));
    query.bindValue(":pluperfectSubjunctive", item.pluperfectSubjunctive.join(","));
    query.bindValue(":presentConditional", item.presentConditional.join(","));
    query.bindValue(":perfectConditional", item.perfectConditional.join(","));
    query.bindValue(":similarVerbs", item.similarVerbs.join(","));
    
    if(!query.exec()){
      qDebug() << "insertVerbs() error [" << item.verb <<  "]: " << query.lastError();
    }
  }
  
  db.commit();
}

void Database_EN::insertVerb(QString name, QString value){
  if (!connected) return;

  QSqlQuery query;
  QString table=verbs_table;
  QString sql="insert into "+table+" (verb,article) values(:verb, :article)";

  query.prepare(sql);
  query.bindValue(":verb", name);
  query.bindValue(":article", value);

  if( !query.exec() )
    qDebug() << "insertVerb() error: " << query.lastError();
}
