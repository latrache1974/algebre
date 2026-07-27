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
        string ToString();

    protected:

    private:
};

#endif // PREDICAT_H
