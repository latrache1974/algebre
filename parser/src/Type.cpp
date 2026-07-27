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
