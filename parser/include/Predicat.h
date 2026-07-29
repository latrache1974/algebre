#ifndef PREDICAT_H
#define PREDICAT_H
using namespace std;
#include<string>
#include<vector>
#include"Node.h"

class Predicat
{
    public:
        Node *Axiom;
        Predicat();
        virtual ~Predicat();
        Predicat *Copy();
        string ToAlgebre();
        static Predicat * And(Predicat *, Predicat *);
        static Predicat * Or(Predicat *, Predicat *);
    protected:

    private:
};

#endif // PREDICAT_H
