#ifndef LITERAL_H
#define LITERAL_H

using namespace std;
#include<string>
#include<iostream>
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
        bool eq;
        Literal();
        virtual ~Literal();
        void AssignFromCorps(Corps *);
        string ToAlgebre();

    protected:

    private:
};

class Literals
{
    public:
    vector <Literal*> Items;
    Literals();
    virtual ~Literals();
    Literal *GetFromName(string );
};

#endif // LITERAL_H
