#include "Function.h"

Function::Function()
{
        name="";
        notation=NULL;
        params=NULL;
        Vars=NULL;
        cond=NULL;
        sentence=NULL;
}

Function::~Function()
{
  if (notation)
    delete notation;
  if (params)
    delete params;
  if (Vars )
    delete Vars;
  if (cond)
    delete cond;
  if (sentence)
    delete sentence;
}

void Function::AssignFromDoubleIdentList(Parameters *ps)
{
  params=ps;
}

void Function::AssignFromCorps(Corps *c)
{
    if ( c->eq )
    {
        sentence=NULL;
        cond=Predicat::Or(c->left, c->right);
        eq=c->eq;
        delete c;
        return;
    }
    if ( c->left )
      cond=c->left->Copy();
    if ( c->right )
      sentence=c->right->Copy();
  eq=c->eq;
  delete c;
}

Functions::Functions()
{
}

Functions::~Functions()
{
}

string Function::ToAlgebre()
{
  string r = "function " + name;
  if (params)
    r +=  "(" + params->ToAlgebre() + ");\n";
  r += notation->ToAlgebre();
  if ( Vars )
    r += Vars->ToAlgebre();
  r += "begin\n  ";
  if (cond)
    r += cond->ToAlgebre() +  " => ";
  if (sentence)
    r += sentence->ToAlgebre() + ";\n";
  r += "end\n";
  return r;
}

Function *Functions::GetFromName(string name)
{
  for(size_t i=0; i<Items.size(); i++)
    if ( Items[i]->name == name )
      return Items[i];
  return NULL;
}
