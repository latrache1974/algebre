#ifndef PREDICATS_H
#define PREDICATS_H
using namespace std;
#include<string>
#include<vector>
#include"Predicat.h"

class Predicats
{
    public:
        vector<Predicat*> Items;
        Predicats();
        virtual ~Predicats();
        void Add(Predicat *);
        Predicats *Copy();
        string ToAlgebre();

    protected:

    private:
};

#endif // PREDICATS_H
