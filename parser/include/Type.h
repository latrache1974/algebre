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
        Predicat *baseType; // type de base optionnel (clause "extend"), NULL si absent
        Type();
        virtual ~Type();
        void AssignFromDoubleIdentList(Parameters *);
        void AssignFromCorps(Corps *);
        Type *Copy();

    protected:

    private:
};

class Types
{
    public:
      vector<Type*> Items;
      Types();
      virtual ~Types();
};

#endif // TYPE_H
