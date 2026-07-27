#ifndef VARIABLES_H
#define VARIABLES_H

using namespace std;
#include<string>
#include<vector>
#include"Predicat.h"


enum Quantifier { _forall, _exists, _existsu};

class Variable {
  public:
  Quantifier q;
  string ident, type;
  Predicat *p;
};

class Variables
{
    public:
        vector <Variable*> Items;
        Variables();
        virtual ~Variables();
        void Add(string ,string ,string );
        void Add(string ,string ,string ,Predicat *);

    protected:

    private:
};

#endif // VARIABLES_H
