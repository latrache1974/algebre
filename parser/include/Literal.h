#ifndef LITERAL_H
#define LITERAL_H

using namespace std;
#include<string>
#include"Notation.h"
#include"Variables.h"
#include"Corps.h"

class Literal
{
    public:
        string type, name;
        Notation *notation;
        Variables *Vars;
        Predicat *cond, *sentence;
        Literal();
        virtual ~Literal();
        void AssignFromCorps(Corps *);

    protected:

    private:
};

class Literals
{
    public:
    vector <Literal*> Items;
    Literals();
    virtual ~Literals();
};

#endif // LITERAL_H
