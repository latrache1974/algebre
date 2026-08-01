#ifndef TYPE_H
#define TYPE_H
using namespace std;
#include<string>
#include"Notation.h"
#include"Parameters.h"
#include"Variables.h"
#include"Corps.h"

class Type
{
    public:
        string name;
        Notation *notation;
        Parameters *params;
        Variables *Vars;
        Predicat *cond, *sentence;
        string baseType; // type de base optionnel (clause "extend"), NULL si absent
        Type();
        virtual ~Type();
        void AssignFromDoubleIdentList(Parameters *);
        void AssignFromCorps(Corps *);
        Type *Copy();
        string ToAlgebre();

    protected:

    private:
};

class Types
{
    public:
      vector<Type*> Items;
      Types();
      virtual ~Types();
      Type *GetFromName(string );
};

#endif // TYPE_H
