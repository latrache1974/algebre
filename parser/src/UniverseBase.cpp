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
    cout << "[Compilateur] Lancement de l'analyse syntaxique..." << std::endl;

    int code_retour = driver.parse(filename);

    if (code_retour == 0) {
        cout << "[Succes] Le fichier respecte la grammaire." << std::endl;
        return true;
    } else {
        // Les erreurs de syntaxe (ligne/colonne incluses) ont déjà été
        // affichées par yy::Parser::error() pendant driver.parse().
        if (msg)
            *msg = "Des erreurs de syntaxe ont ete detectees.";
        cerr << "[Echec] Des erreurs de syntaxe ont ete detectees." << std::endl;
        return false;
    }

}
