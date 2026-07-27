#include "Goal.h"

Goal::Goal()
{
        Vars=NULL;
        conds=NULL;
        sentences=NULL;
}

Goal::~Goal()
{
  if (Vars)
    delete Vars;
  if (conds)
    delete conds;
  if (sentences)
    delete sentences;
}

void Goal::AssignFromCorpsMM(CorpsMM *cmm)
{
  conds=cmm->conds->Copy();
  sentences=cmm->sentences->Copy();
}
