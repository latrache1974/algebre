#ifndef GOAL_H
#define GOAL_H

using namespace std;
#include"Variables.h"
#include"Predicats.h"
#include"Corps.h"

class Goal
{
    public:
        Variables *Vars;
        Predicats *conds, *sentences;
        Goal();
        virtual ~Goal();
        void AssignFromCorpsMM(CorpsMM *);
        string ToAlgebre();

    protected:

    private:
};

#endif // GOAL_H
