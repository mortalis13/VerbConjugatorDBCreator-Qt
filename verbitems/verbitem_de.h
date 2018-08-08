#ifndef VERBITEM_DE_H
#define VERBITEM_DE_H


struct VerbItem_DE {

  QString verb;
  
  QStringList impersonalForms;

  QStringList presentIndicative;
  QStringList preteritIndicative;
  QStringList futureIndicative;
  QStringList perfectIndicative;
  QStringList pluperfectIndicative;
  QStringList futurePerfectIndicative;
  QStringList presentSubjunctive;
  QStringList preteritSubjunctive;

  QStringList perfectSubjunctive;
  QStringList pluperfectSubjunctive;
  QStringList presentConditional;
  QStringList perfectConditional;
  QStringList imperative;
  QStringList similarVerbs;
  

  void clear() {
    verb.clear();

    impersonalForms.clear();

    presentIndicative.clear();
    preteritIndicative.clear();
    futureIndicative.clear();
    perfectIndicative.clear();
    pluperfectIndicative.clear();
    futurePerfectIndicative.clear();
    presentSubjunctive.clear();
    preteritSubjunctive.clear();

    perfectSubjunctive.clear();
    pluperfectSubjunctive.clear();
    presentConditional.clear();
    perfectConditional.clear();
    imperative.clear();
    similarVerbs.clear();
  }

};

#endif // VERBITEM_DE_H
