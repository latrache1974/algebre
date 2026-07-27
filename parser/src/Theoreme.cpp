#include "Theoreme.h"

Theoreme::Theoreme()
{
        name="";
        params=NULL;
        Vars=NULL;
        cond=NULL;
        sentences=NULL;
}

Theoreme::~Theoreme()
{
  if (params)
    delete params;
  if (Vars)
    delete Vars;
  if (cond)
    delete cond;
  if (sentences)
    delete sentences;
}

void Theoreme::AssignFromDoubleIdentList(Parameters *ps)
{
  params=ps;
}

void Theoreme::AssignFromCorpsM(CorpsM *cm)
{
  cond=cm->left->Copy();
  sentences=cm->sentences->Copy();
  delete cm;
}

Theoremes::Theoremes()
{
}

Theoremes::~Theoremes()
{
}
