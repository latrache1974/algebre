#include "Literal.h"

Literal::Literal()
{
        type="";
        name="";
        notation=NULL;
        Vars=NULL;
        cond=NULL;
        sentence=NULL;
}

Literal::~Literal()
{
  if (notation)
      delete notation;
  if (Vars )
    delete Vars;
  if (cond)
    delete cond;
  if (sentence)
    delete sentence;
}

void Literal::AssignFromCorps(Corps *c)
{
  if ((  c->type=="=>" ) || ( c->type=="<=>" ) )
   {
     cond=c->left->Copy();
     sentence=c->right->Copy();
   }
  if ( type=="sentence" )
     sentence=c->sentence->Copy();
  delete c;
}

Literals::Literals()
{
}

Literals::~Literals()
{
}
