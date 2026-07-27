#include "UniverseBase.h"

using namespace std;
#include<iostream>
#include<fstream>
#include "driver.hh"

UniverseBase::UniverseBase()
{
        types=new Types();
        functions=new Functions();
        literals=new Literals();
        theoremes=new Theoremes();
        goal=NULL;
        plan=new WorkPlan();
}

UniverseBase::~UniverseBase()
{
  if (types)
    delete types;
  if (functions)
    delete functions;
  if (literals )
    delete literals;
  if (theoremes)
    delete theoremes;
  if (goal)
    delete goal;
  if (plan)
    delete plan;
}

void UniverseBase::AddType(Type *t)
{
  types->Items.push_back(t);
}

void UniverseBase::AddFunction(Function *f)
{
  functions->Items.push_back(f);
}

void UniverseBase::AddLiteral(Literal *l)
{
  literals->Items.push_back(l);
}

void UniverseBase::AddTheoreme(Theoreme *t)
{
  theoremes->Items.push_back(t);
}

void UniverseBase::SetGoal(Goal *g)
{
  goal =g;
}

bool UniverseBase::Parse(string filename,string *msg)
{
    Driver driver;
    cout << "[" << filename << "] Lancement de l'analyse syntaxique..." << std::endl;

    int code_retour = driver.parse(filename);

    if (code_retour == 0) {
        cout << filename << " OK OK OK OK OK OK ." << std::endl;
        return true;
    } else {
        // Les erreurs de syntaxe (ligne/colonne incluses) ont déjà été
        // affichées par yy::Parser::error() pendant driver.parse().
        if (msg)
            *msg = "Des erreurs de syntaxe ont ete detectees.";
        cerr << filename << "  NO NO NO NO!" << std::endl;
        return false;
    }
}

void UniverseBase::CopyFrom(UniverseBase *u)
{
  // On transfère la PROPRIÉTÉ des objets vers l'univers courant plutôt
  // que de les copier en profondeur : Type/Function/Literal/Theoreme
  // n'ont pas de méthode Copy() (contrairement à Predicat/Node), et
  // une copie superficielle sans savoir comment Notation/Parameters/
  // Variables doivent être dupliqués serait fragile. Transférer les
  // pointeurs directement est plus simple et tout aussi sûr, du
  // moment qu'on vide ensuite les listes de u (voir plus bas) pour
  // que son destructeur ne détruise pas ce qu'on vient de récupérer.
  for (size_t i = 0; i < u->types->Items.size(); i++)
    types->Items.push_back(u->types->Items[i]);
  for (size_t i = 0; i < u->functions->Items.size(); i++)
    functions->Items.push_back(u->functions->Items[i]);
  for (size_t i = 0; i < u->literals->Items.size(); i++)
    literals->Items.push_back(u->literals->Items[i]);
  for (size_t i = 0; i < u->theoremes->Items.size(); i++)
    theoremes->Items.push_back(u->theoremes->Items[i]);

  // Un fichier inclus sert de bibliothèque de définitions ; il n'est
  // pas censé porter son propre "goal". On ne touche au goal courant
  // que si le fichier inclus en a effectivement défini un.
  if (u->goal)
  {
    if (goal)
      delete goal;
    goal = u->goal;
    u->goal = NULL;
  }

  // On vide les listes de u : PerformeInclude fait "delete univ" juste
  // après cet appel, et son destructeur (~Types, ~Functions, etc.)
  // pourrait sinon détruire les objets qu'on vient de transférer ici.
  u->types->Items.clear();
  u->functions->Items.clear();
  u->literals->Items.clear();
  u->theoremes->Items.clear();
}

////////////////////////////////////////////////////////////////////////////
// Export vers la syntaxe .algebre
////////////////////////////////////////////////////////////////////////////

static string QuantifierToAlgebre(Quantifier q)
{
  switch (q)
  {
    case _forall:  return "forall";
    case _exists:  return "exists";
    case _existsu: return "existsu";
  }
  return "?";
}

static string ParametersToAlgebre(Parameters *p)
{
  if (!p)
    return "";
  string r = "";
  for (size_t i = 0; i < p->Items.size(); i++)
  {
    if (i > 0)
      r += ",";
    r += p->Items[i]->type + " " + p->Items[i]->ident;
  }
  return r;
}

static string NameSpaceListToAlgebre(NameSpaceList *l)
{
  string r = "";
  if (!l)
    return r;
  for (size_t i = 0; i < l->Items.size(); i++)
  {
    if (i > 0)
      r += ",";
    r += l->Items[i];
  }
  return r;
}

static string NotationToAlgebre(Notation *n)
{
  if (!n)
    return "";
  string r = "notation \"" + n->format + "\"";
  string ns = NameSpaceListToAlgebre(n->params);
  if (ns != "")
    r += " " + ns;
  r += ";\n";
  return r;
}

/* "var quantifier ident : type[, predicat][ depends x,y];" pour chaque
   variable, ou "" si Vars est vide/absent. */
static string VariablesToAlgebre(Variables *vars)
{
  if (!vars || vars->Items.size() == 0)
    return "";
  string r = "var ";
  for (size_t i = 0; i < vars->Items.size(); i++)
  {
    Variable *v = vars->Items[i];
    if (i > 0)
      r += "    ";
    r += QuantifierToAlgebre(v->q) + " " + v->ident + " : " + v->type;
    if (v->p)
      r += ", " + v->p->ToString();
    string deps = NameSpaceListToAlgebre(v->depends);
    if (deps != "")
      r += " depends " + deps;
    r += ";\n";
  }
  return r;
}

static string PredicatsToAlgebre(Predicats *ps)
{
  string r = "";
  if (!ps)
    return r;
  for (size_t i = 0; i < ps->Items.size(); i++)
  {
    if (i > 0)
      r += " | ";
    r += ps->Items[i]->ToString();
  }
  return r;
}

/* Type/Function/Literal partagent le même schéma cond+sentence (issu
   de Corps). NB : Corps distingue "=>" et "<=>" au moment du parsing,
   mais AssignFromCorps() ne garde pas cette info (les deux remplissent
   cond/sentence de la même façon) -- on ne peut donc pas savoir ici
   lequel des deux a été utilisé à l'origine. On réexporte toujours en
   "=>" ; si le fichier source utilisait "<=>" quelque part, l'export
   ne le reproduira pas fidèlement tant que ce champ n'est pas conservé
   dans Type/Function/Literal. */
static string CondSentenceToAlgebre(Predicat *cond, Predicat *sentence)
{
  if (!sentence)
    return "";
  if (cond)
    return cond->ToString() + " => " + sentence->ToString();
  return sentence->ToString();
}

static string TypeToAlgebre(Type *t)
{
  string r = "type " + t->name + "(" + ParametersToAlgebre(t->params) + ")";
  if (t->baseType)
    r += " extend " + t->baseType->ToString();
  r += ";\n";
  r += NotationToAlgebre(t->notation);
  r += VariablesToAlgebre(t->Vars);
  r += "begin\n  " + CondSentenceToAlgebre(t->cond, t->sentence) + ";\n";
  r += "end\n";
  return r;
}

static string FunctionToAlgebre(Function *f)
{
  string r = "function " + f->name + "(" + ParametersToAlgebre(f->params) + ");\n";
  r += NotationToAlgebre(f->notation);
  r += VariablesToAlgebre(f->Vars);
  r += "begin\n  " + CondSentenceToAlgebre(f->cond, f->sentence) + ";\n";
  r += "end\n";
  return r;
}

static string LiteralToAlgebre(Literal *l)
{
  string r = "literal " + l->name + " : " + l->type + ";\n";
  r += NotationToAlgebre(l->notation);
  r += VariablesToAlgebre(l->Vars);
  r += "begin\n  " + CondSentenceToAlgebre(l->cond, l->sentence) + ";\n";
  r += "end\n";
  return r;
}

static string TheoremeToAlgebre(Theoreme *t)
{
  string r = "theoreme \"" + t->name + "\"(" + ParametersToAlgebre(t->params) + ");\n";
  r += VariablesToAlgebre(t->Vars);
  string body = t->cond
                  ? t->cond->ToString() + " => " + PredicatsToAlgebre(t->sentences)
                  : PredicatsToAlgebre(t->sentences);
  r += "begin\n  " + body + ";\n";
  r += "end\n";
  return r;
}

static string GoalToAlgebre(Goal *g)
{
  string r = "goal\n";
  r += VariablesToAlgebre(g->Vars);
  bool hasConds = g->conds && g->conds->Items.size() > 0;
  string body = hasConds
                  ? PredicatsToAlgebre(g->conds) + " => " + PredicatsToAlgebre(g->sentences)
                  : PredicatsToAlgebre(g->sentences);
  r += "begin\n  " + body + ";\n";
  r += "end\n";
  return r;
}

/* Exporte tout l'univers (types, functions, literals, theoremes, goal)
   dans un fichier au format .algebre. Ne gère pas "plan" (WorkPlan a
   déjà sa propre méthode ExportToAlgebre). */
void UniverseBase::ExportToFile(string filename)
{
  ofstream out(filename.c_str());
  if (!out)
    return;

  for (size_t i = 0; i < types->Items.size(); i++)
    out << TypeToAlgebre(types->Items[i]) << endl;
  for (size_t i = 0; i < functions->Items.size(); i++)
    out << FunctionToAlgebre(functions->Items[i]) << endl;
  for (size_t i = 0; i < literals->Items.size(); i++)
    out << LiteralToAlgebre(literals->Items[i]) << endl;
  for (size_t i = 0; i < theoremes->Items.size(); i++)
    out << TheoremeToAlgebre(theoremes->Items[i]) << endl;

  if (goal)
    out << GoalToAlgebre(goal) << endl;

  // Cf. la grammaire : Algebre se termine toujours par "end." même
  // quand il n'y a pas de goal (GoalDefinition peut être vide).
  out << "end." << endl;

  out.close();
}
