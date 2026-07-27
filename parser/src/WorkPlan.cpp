#include "WorkPlan.h"

using namespace std;
#include<fstream>

WorkPlan::WorkPlan()
{
  Vars=new Variables();
  predicats=new Predicats();
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

  out << "goal" << endl;

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
        out << ", " << v->p->ToString();
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
      out << "  " << predicats->Items[i]->ToString();
    }
    out << ";" << endl;
  }
  out << "end." << endl;

  out.close();
}
