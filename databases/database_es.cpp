#include "database_es.h"


Database_ES::Database_ES()
{
  connected = createConnection();
  if(!connected) return;

  initDatabase();
}

Database_ES::~Database_ES()
{
  closeConnection();
}


bool Database_ES::createDatabase(){
  connected = createConnection();
  if(!connected) return false;
  
  initDatabase();
  
  return true;
}

/*
 * Connects to the local .db file (SQLite database)
 * if no file then creates it
 */
bool Database_ES::createConnection(){
  if(db.isOpen()) return true;
  
  QString dbDir = "db_out/";
  QString dbName = "verbs_es";
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

void Database_ES::closeConnection(){
  db.close();
}

/*
 * Creates tables in the database if they don't exist
 */
void Database_ES::initDatabase(){
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
          preteritImperfectIndicative TEXT, \
          preteritPerfectSimpleIndicative TEXT, \
          futureIndicative TEXT, \
          preteritPerfectIndicative TEXT, \
          preteritPluperfectIndicative TEXT, \
          preteritPreviuousIndicative TEXT, \
          futurePerfectIndicative TEXT, \
          presentSubjunctive TEXT, \
          preteritPerfectSubjunctive TEXT, \
          preteritImperfectSubjunctive TEXT, \
          preteritPluperfectSubjunctive TEXT, \
          futureSubjunctive TEXT, \
          futurePerfectSubjunctive TEXT, \
          conditionalSimple TEXT, \
          conditionalComplex TEXT, \
          imperative TEXT, \
          imperativeNegative TEXT, \
          similarVerbs TEXT \
        )" );

  if( !res ){
    qDebug() << "initDatabase() error: " << query.lastError();
    return;
  }

  qDebug() << "Database_ES initialized!";
}


void Database_ES::insertVerbs(const QList<VerbItem_ES>& verbsList){
  if (!connected) return;
  
  db.transaction();

  QSqlQuery query;
  QString table=verbs_table;
  
  QString sql="insert into "+table+" values( \
                :verb, \
                :impersonalForms, \
                :presentIndicative, \
                :preteritImperfectIndicative, \
                :preteritPerfectSimpleIndicative, \
                :futureIndicative, \
                :preteritPerfectIndicative, \
                :preteritPluperfectIndicative, \
                :preteritPreviuousIndicative, \
                :futurePerfectIndicative, \
                :presentSubjunctive, \
                :preteritPerfectSubjunctive, \
                :preteritImperfectSubjunctive, \
                :preteritPluperfectSubjunctive, \
                :futureSubjunctive, \
                :futurePerfectSubjunctive, \
                :conditionalSimple, \
                :conditionalComplex, \
                :imperative, \
                :imperativeNegative, \
                :similarVerbs \
              )";

  
  foreach(VerbItem_ES item, verbsList){
    query.prepare(sql);
    
    query.bindValue(":verb", item.verb);
    query.bindValue(":impersonalForms", item.impersonalForms.join(","));
    query.bindValue(":presentIndicative", item.presentIndicative.join(","));
    query.bindValue(":preteritImperfectIndicative", item.preteritImperfectIndicative.join(","));
    query.bindValue(":preteritPerfectSimpleIndicative", item.preteritPerfectSimpleIndicative.join(","));
    query.bindValue(":futureIndicative", item.futureIndicative.join(","));
    query.bindValue(":preteritPerfectIndicative", item.preteritPerfectIndicative.join(","));
    query.bindValue(":preteritPluperfectIndicative", item.preteritPluperfectIndicative.join(","));
    query.bindValue(":preteritPreviuousIndicative", item.preteritPreviuousIndicative.join(","));
    query.bindValue(":futurePerfectIndicative", item.futurePerfectIndicative.join(","));
    query.bindValue(":presentSubjunctive", item.presentSubjunctive.join(","));
    query.bindValue(":preteritPerfectSubjunctive", item.preteritPerfectSubjunctive.join(","));
    query.bindValue(":preteritImperfectSubjunctive", item.preteritImperfectSubjunctive.join(","));
    query.bindValue(":preteritPluperfectSubjunctive", item.preteritPluperfectSubjunctive.join(","));
    query.bindValue(":futureSubjunctive", item.futureSubjunctive.join(","));
    query.bindValue(":futurePerfectSubjunctive", item.futurePerfectSubjunctive.join(","));
    query.bindValue(":conditionalSimple", item.conditionalSimple.join(","));
    query.bindValue(":conditionalComplex", item.conditionalComplex.join(","));
    query.bindValue(":imperative", item.imperative.join(","));
    query.bindValue(":imperativeNegative", item.imperativeNegative.join(","));
    query.bindValue(":similarVerbs", item.similarVerbs.join(","));
    
    if(!query.exec()){
      qDebug() << "insertVerbs() error [" << item.verb <<  "]: " << query.lastError();
    }
  }
  
  db.commit();
}

void Database_ES::insertVerb(QString name, QString value){
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
