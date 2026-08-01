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
    Utils::Debug("fichier : "+filename);

    int code_retour = driver.parse(AlgebreSourceDirectory+filename);

    if (code_retour == 0) {
      //  cout << filename << " OK OK OK OK OK OK ." << std::endl;
        return true;
    } else {
        // Les erreurs de syntaxe (ligne/colonne incluses) ont déjà été
        // affichées par yy::Parser::error() pendant driver.parse().
        if (msg)
            *msg = "           Des erreurs de syntaxe ont ete detectees.";
        Utils::Debug(filename + *msg );
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

/* Exporte tout l'univers (types, functions, literals, theoremes, goal)
   dans un fichier au format .algebre. Ne gère pas "plan" (WorkPlan a
   déjà sa propre méthode ExportToAlgebre). */
void UniverseBase::ExportToFile(string filename)
{
  ofstream out(AlgebreSourceDirectory+filename.c_str());
  if (!out)
    return;
  out << ToAlgebre();
  out.close();
}

string UniverseBase::ToAlgebre()
{
  string r="";
  for (size_t i = 0; i < types->Items.size(); i++)
    r += types->Items[i]->ToAlgebre() + "\n";
  for (size_t i = 0; i < functions->Items.size(); i++)
    r += functions->Items[i]->ToAlgebre() + "\n";
  for (size_t i = 0; i < literals->Items.size(); i++)
    r += literals->Items[i]->ToAlgebre() + "\n";
  for (size_t i = 0; i < theoremes->Items.size(); i++)
    r += theoremes->Items[i]->ToAlgebre() + "\n";

  if (goal)
    r += goal->ToAlgebre() + "\n" ;
  r += "end.\n";
  return r;
}

