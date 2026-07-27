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
  for(size_t i=0; i<u->types->Items.size(); i++)
    types->Items.push_back(u->types->Items[i]->Copy());
/*        Types *types;
        Functions *functions;
        Literals *literals;
        Theoremes *theoremes;
        Goal *goal;
        WorkPlan *plan;*/

}
