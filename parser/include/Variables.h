#ifndef VARIABLES_H
#define VARIABLES_H

using namespace std;
#include<string>
#include<vector>
#include"Predicat.h"
#include"NameSpaceList.h"


enum Quantifier { _forall, _exists, _existsu};

class Variable {
  public:
  Quantifier q;
  string ident, type;
  Predicat *p;
  NameSpaceList *depends;
  Variable *Copy();
  static string QuantifierToAlgebre(Quantifier q);
};

class Variables
{
    public:
        vector <Variable*> Items;
        Variables();
        virtual ~Variables();
        void Add(string ,string ,string );
        void Add(string ,string ,string ,Predicat *);
        void Add(string ,string ,string ,Predicat *,NameSpaceList *);
        Variables *Copy();
        string ToAlgebre();

    protected:

    private:
};

#endif // VARIABLES_H
