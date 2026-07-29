#include "WorkPlan.h"

using namespace std;
#include<fstream>

string AlgebreSourceDirectory="../../../parser/algebre/";

WorkPlan::WorkPlan()
{
  Vars=NULL;
  predicats=NULL;
}

WorkPlan::~WorkPlan()
{
  if (Vars)
    delete Vars;
  if (predicats)
    delete predicats;
}

static string QuantifierToString(Quantifier q)
{
  switch(q)
  {
    case _forall:  return "forall";
    case _exists:  return "exists";
    case _existsu: return "existsu";
  }
  return "?";
}

/* Écrit le WorkPlan (variables + prédicats) sous la syntaxe .algebre,
   au format d'un "goal" : var ...; begin pred1 | pred2 | ...; end. */
void WorkPlan::ExportToAlgebre(string filename)
{
  ofstream out(filename.c_str());
  if (!out)
    return;

  if (Vars && Vars->Items.size()>0)
  {
    out << "var ";
    for (size_t i=0; i<Vars->Items.size(); i++)
    {
      Variable *v=Vars->Items[i];
      if (i>0)
        out << "    ";
      out << QuantifierToString(v->q) << " " << v->ident << " : " << v->type;
      if (v->p)
        out << ", " << v->p->ToAlgebre();
      if ( v->depends )
          {
            out << " depends ";
            for (size_t j=0; j<v->depends->Items.size(); j++)
              out << v->depends->Items[j] << " ";
          }
      // TODO : sérialiser v->depends (liste "depends x,z") une fois
      // la structure de NameSpaceList confirmée (pas encore vue ici).
      out << ";" << endl;
    }
  }

  out << "begin" << endl;
  if (predicats && predicats->Items.size()>0)
  {
    for (size_t i=0; i<predicats->Items.size(); i++)
    {
      if (i>0)
        out << " |" << endl;
      out << "  " << predicats->Items[i]->ToAlgebre();
    }
    out << ";" << endl;
  }
  out << "end." << endl;

  out.close();
}

string WorkPlan::ToAlgebre()
{
  string r="";
  if (Vars && Vars->Items.size()>0)
  {
    r += "var ";
    for (size_t i=0; i<Vars->Items.size(); i++)
    {
      Variable *v=Vars->Items[i];
      if (i>0)
        r +=  "    ";
      r +=  QuantifierToString(v->q) + " " + v->ident + " : " + v->type;
      if (v->p)
        r +=  ", " + v->p->ToAlgebre();
      if ( v->depends )
          {
            r +=  " depends " + v->depends->ToAlgebre();
          }
      r +=  ";\n" ;
    }
  }

  r +=  "begin\n  ";
  if (predicats && predicats->Items.size()>0)
  {
    for (size_t i=0; i<predicats->Items.size(); i++)
    {
      if (i>0)
        r +=  " |\n" ;
      r +=  "  " + predicats->Items[i]->ToAlgebre();
    }
    r +=  ";\n" ;
  }
  r +=  "end.\n" ;
  return r;
}
