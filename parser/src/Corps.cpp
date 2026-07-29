#include "Corps.h"

Corps::Corps()
{
        left=NULL;
        right=NULL;
        eq=false;
}

Corps::~Corps()
{
    if ( left)
      delete left;
    if (right)
      delete right;
}

void Corps::Assign(Predicat * l,bool e,Predicat * r)
{
   left=l;
   right=r;
   eq=e;
}

void Corps::AssignRight(Predicat *p)
{
  right=p;
  eq=false;
}

void Corps::AssignLeft(Predicat *p)
{
  left=p;
  eq=false;
}


CorpsM::CorpsM()
{
        left=NULL;
        right=NULL;
        sentences=NULL;
}

CorpsM::~CorpsM()
{
    if ( left)
      delete left;
    if (right)
      delete right;
    if (sentences)
      delete sentences;
}

void CorpsM::Assign(Predicat *l,bool e,Predicats *ps)
{
        eq=e;
        left=l;
        sentences=ps;
}

void CorpsM::Assign(Predicat * l,bool e,Predicat * r)
{
        left=l;
        right=r;
        eq=e;
}

void CorpsM::Assign(Predicats *ps)
{
  eq=false;
  sentences=ps;
}
//////////////////////////////////////////////////////////////////////

CorpsMM::CorpsMM()
{
        conds=NULL;
        sentences=NULL;
        eq=false;
}

CorpsMM::~CorpsMM()
{
    if ( conds)
      delete conds;
    if (sentences)
      delete sentences;
}

void CorpsMM::Assign(Predicats *l,bool e,Predicats *ps)
{
        conds=l;
        eq=e;
        sentences=ps;
}

void CorpsMM::Assign(Predicats *ps)
{
  eq=false;
  sentences=ps;
}
