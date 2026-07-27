#include "Corps.h"

Corps::Corps()
{
        left=NULL;
        right=NULL;
        sentence=NULL;
        type="";
}

Corps::~Corps()
{
    if ( left)
      delete left;
    if (right)
      delete right;
    if (sentence)
      delete sentence;
}

void Corps::Assign(Predicat * l,string t,Predicat * r)
{
   left=l;
   right=r;
   type=t;
}

void Corps::Assign(Predicat *p)
{
  sentence=p;
  type="sentence";
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

void CorpsM::Assign(Predicat *l,string t,Predicats *ps)
{
        left=l;
        type=t;
        sentences=ps;
}

void CorpsM::Assign(Predicat * l,string t,Predicat * r)
{
        left=l;
        right=r;
        type=t;
}

void CorpsM::Assign(Predicats *ps)
{
  type="sentences";
  sentences=ps;
}
//////////////////////////////////////////////////////////////////////

CorpsMM::CorpsMM()
{
        conds=NULL;
        sentences=NULL;
        type="";
}

CorpsMM::~CorpsMM()
{
    if ( conds)
      delete conds;
    if (sentences)
      delete sentences;
}

void CorpsMM::Assign(Predicats *l,string t,Predicats *ps)
{
        conds=l;
        type=t;
        sentences=ps;
}

void CorpsMM::Assign(Predicats *ps)
{
  type="sentences";
  sentences=ps;
}
