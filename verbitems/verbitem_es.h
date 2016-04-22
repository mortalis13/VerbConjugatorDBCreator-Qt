#ifndef VERBITEM_ES_H
#define VERBITEM_ES_H


struct VerbItem_ES{

  QString verb;
  
  QStringList impersonalForms;

  QStringList presentIndicative;
  QStringList preteritImperfectIndicative;
  QStringList preteritPerfectSimpleIndicative;
  QStringList futureIndicative;
  QStringList preteritPerfectIndicative;
  QStringList preteritPluperfectIndicative;
  QStringList preteritPreviuousIndicative;
  QStringList futurePerfectIndicative;

  QStringList presentSubjunctive;
  QStringList preteritPerfectSubjunctive;
  QStringList preteritImperfectSubjunctive;
  QStringList preteritPluperfectSubjunctive;
  QStringList futureSubjunctive;
  QStringList futurePerfectSubjunctive;

  QStringList conditionalSimple;
  QStringList conditionalComplex;

  QStringList imperative;
  QStringList imperativeNegative;

  QStringList similarVerbs;


  void clear(){
    verb.clear();

    impersonalForms.clear();

    presentIndicative.clear();
    preteritPerfectIndicative.clear();
    preteritImperfectIndicative.clear();
    preteritPluperfectIndicative.clear();
    preteritPerfectSimpleIndicative.clear();
    preteritPreviuousIndicative.clear();
    futureIndicative.clear();
    futurePerfectIndicative.clear();

    presentSubjunctive.clear();
    preteritImperfectSubjunctive.clear();
    futureSubjunctive.clear();
    preteritPerfectSubjunctive.clear();
    preteritPluperfectSubjunctive.clear();
    futurePerfectSubjunctive.clear();

    conditionalSimple.clear();
    conditionalComplex.clear();

    imperative.clear();
    imperativeNegative.clear();

    similarVerbs.clear();
  }

};

#endif // VERBITEM_ES_H
