#include "Type.h"

Type::Type()
{
        name="";
        notation=NULL;
        params=NULL;
        Vars=NULL;
        cond=NULL;
        sentence=NULL;
}

Type::~Type()
{
  if (notation)
    delete notation;
  if (params)
    delete params;
  if (Vars)
    delete Vars;
  if (cond)
    delete cond;
  if (sentence)
    delete sentence;
}

void Type::AssignFromDoubleIdentList(Parameters *ps)
{
  params=ps;
}

void Type::AssignFromCorps(Corps *c)
{
  if ((  c->type=="=>" ) || ( c->type=="<=>" ) )
   {
     cond=c->left->Copy();
     sentence=c->right->Copy();
   }
  if ( c->type=="sentence" )
     sentence=c->sentence->Copy();
  delete c;
}

Types::Types()
{
}

Types::~Types()
{
}

Type *Type::Copy()
{
  Type *r=new Type();
  r->name=name;
  if (notation)
    r->notation=notation->Copy();
  if (params)
    r->params=params->Copy();
  if (Vars)
    r->Vars=Vars->Copy();
  if (cond)
    r->cond=cond->Copy();
  if (sentence)
    r->sentence=sentence->Copy();
  if (baseType)
    r->baseType=baseType->Copy();
  return r;
}

string Type::ToAlgebre()
{
  string r = "type " + name;
  if (params)
       r += " (" + params->ToAlgebre() + ")";
  if (baseType)
    r += " extend " + baseType->ToAlgebre();
  r += ";\n";
  if (notation)
    r += notation->ToAlgebre();
  if (Vars)
    r += Vars->ToAlgebre();
  r += "begin\n  ";
  if (cond)
    r += cond->ToAlgebre() +  " => ";
  if (sentence)
    r += sentence->ToAlgebre() + ";\n";
  r += "end\n";
  return r;
}

Type *Types::GetFromName(string name)
{
  for(size_t i=0; i<Items.size(); i++)
    if ( Items[i]->name == name )
      return Items[i];
  return NULL;
}
