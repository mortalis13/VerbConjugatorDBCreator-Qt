#ifndef VERBITEM_FR_H
#define VERBITEM_FR_H


struct VerbItem_FR {

  QString verb;
  
  QStringList impersonalForms;

  QStringList presentIndicative;
  QStringList imperfectIndicative;
  QStringList futureIndicative;
  QStringList pastIndicative;
  QStringList pastComplexIndicative;
  QStringList pluperfectIndicative;
  QStringList futurePerfectIndicative;
  QStringList pastPerfectIndicative;

  QStringList presentSubjunctive;
  QStringList imperfectSubjunctive;
  QStringList pastComplexSubjunctive;
  QStringList pluperfectSubjunctive;
  QStringList presentConditional;
  QStringList pastConditional;
  QStringList imperative;
  QStringList similarVerbs;
  

  void clear() {
    verb.clear();

    impersonalForms.clear();

    presentIndicative.clear();
    imperfectIndicative.clear();
    futureIndicative.clear();
    pastIndicative.clear();
    pastComplexIndicative.clear();
    pluperfectIndicative.clear();
    futurePerfectIndicative.clear();
    pastPerfectIndicative.clear();

    presentSubjunctive.clear();
    imperfectSubjunctive.clear();
    pastComplexSubjunctive.clear();
    pluperfectSubjunctive.clear();
    presentConditional.clear();
    pastConditional.clear();
    imperative.clear();
    similarVerbs.clear();
  }

};

#endif // VERBITEM_FR_H
