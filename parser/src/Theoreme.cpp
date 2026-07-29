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
  if (cm->left)
    cond=cm->left->Copy();
  if (cm->sentences)
    sentences=cm->sentences->Copy();
  delete cm;
}

Theoremes::Theoremes()
{
}

Theoremes::~Theoremes()
{
}

string Theoreme::ToAlgebre()
{
  string r = "theoreme \"" + name + "\"" ;
  if (params)
    r += "(" + params->ToAlgebre() + ");\n";
  if (Vars)
    r += Vars->ToAlgebre();
  r += "begin\n  " ;
  if (cond)
    r += cond->ToAlgebre() + " => " ;
  if (sentences)
    r += sentences->ToAlgebre();
  r += ";\nend\n";
  return r;
}

Theoreme *Theoremes::GetFromName(string name)
{
  for(size_t i=0; i<Items.size(); i++)
    if ( Items[i]->name == name )
      return Items[i];
  return NULL;
}
