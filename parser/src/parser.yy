%skeleton "lalr1.cc"
%require "3.2"
%defines

%define api.namespace {yy}
%define api.parser.class {Parser}
%define api.token.constructor
%define api.value.type variant
%define parse.error verbose
%define parse.trace
%code requires {
    #include <string>
    #include <iostream>
    class Driver; // Déclaration anticipée du gestionnaire de contexte
    #include "Corps.h"
    #include "Type.h"
    #include "Function.h"
    #include "Theoreme.h"
    #include "Goal.h"
    #include "Literal.h"
    #include "Utils.h"
    #include "UniverseBase.h"
}
%locations

/* Configuration automatique du constructeur et de l'appel yylex */
%param { Driver& driver }

%code {
    #include "driver.hh"
    // Rien d'autre ici : avec %param { Driver& driver } et les symboles
    // complets (api.token.constructor), Bison appelle directement
    // yy::Parser::symbol_type yylex(Driver& driver), défini dans lexer.l
    // via YY_DECL (déclaré dans driver.hh).
}

/* Tokens avec valeur sémantique textuelle (gérés via std::variant) */
%token <std::string> IDENT STRING NAMESPACE QUANTIFIER

/* Tokens de mots-clés et opérateurs (Ajout de LITERAL) */
%token INCLUDE END TYPE LITERAL FUNCTION THEOREME NOTATION VAR
%token ARROW_IMPLIES ARROW_EQUIV
%token NOT OR AND XOR
%token APPARTIENT RELATION
%token BEGIN_ EQ NEQ GOAL
%token ANY RETURN TRUE FALSE DEPENDS EXTEND

/* Tokens de ponctuation : noms simples, plus d'alias sur littéral
   caractère. Le mélange nom-symbolique / littéral 'x' dans le corps
   de la grammaire ne fusionnait pas fiablement avec
   api.token.constructor + api.value.type variant (symboles complets
   C++) : le lexer produisait COLON via make_COLON(), alors qu'une
   partie des règles attendait encore le littéral ':' — deux entrées
   distinctes pour Bison, d'où « unexpected COLON, expecting ':' ».
   Un seul nom par token, utilisé partout, règle le problème. */
%token LPAREN
%token RPAREN
%token COMMA
%token SEMI
%token COLON
%token DOT
%token PIPE

/* Priorités et associativités pour résoudre les ambiguïtés logiques */
%left ARROW_EQUIV
%left ARROW_IMPLIES
%left OR XOR
%left AND
%precedence NOT


%type <Type *> TypeDefinition
%type <Function *> FunctionDefinition
%type <Literal *> LiteralDefinition
%type <Theoreme *> TheoremeDefinition
%type <Goal *> GoalDefinition
%type <Notation *> NotationDefinition
%type <NameSpaceList *> NameSpaceList
%type <NameSpaceList *> NameSpaceList1
%type <Parameters *> DoubleIdentList
%type <Parameters *> DoubleIdentList1
%type <std::string> TypeName
%type <std::string> T
%type <Predicat *> ExtendClause
%type <NameSpaceList *> DependsClause
%type <NameSpaceList *> DependsList
%type <Variables *> VariablesDefinitions
%type <Variables *> VariablesDefinitions1
%type <Predicats *> Predicats
%type <Predicats *> Predicats1
%type <Predicat *> Predicat
%type <Predicat *> Atom
%type <Predicats *> Atoms
%type <Predicats *> Atom1
%type <Corps *> Corps
%type <CorpsM *> CorpsM
%type <CorpsMM *> CorpsMM



%%

/* --- Règles de Grammaire Mises à Jour --- */

S : IncludeSection Algebre
  ;

IncludeSection : INCLUDE STRING IncludeSection {Utils::PerformeInclude($2);}
               | /* vide */ { }
               ;

Algebre : TypeDefinition Algebre {universe->AddType($1);}
        | FunctionDefinition Algebre {universe->AddFunction($1);}
        | LiteralDefinition Algebre  {cout << "Literal OK" << endl; universe->AddLiteral($1);}
        | TheoremeDefinition Algebre {universe->AddTheoreme($1);}
        | GoalDefinition END DOT {printf("all is ok\n"); universe->SetGoal($1);}
        ;

TypeDefinition : TYPE IDENT LPAREN DoubleIdentList RPAREN ExtendClause SEMI NotationDefinition VariablesDefinitions Corps
                 {$$=new Type();
                 $$->name=$2;
                 $$->AssignFromDoubleIdentList($4);
                 $$->baseType=$6;
                 $$->notation=$8;
                 $$->Vars=$9;
                 $$->AssignFromCorps($10);}
               ;

/* Type de base optionnel, ex: "extend relation(a,b)" ou "extend ident".
   Réutilise directement Atom (déjà capable de produire ident ou ident(...)),
   pas besoin d'une règle/type dédiés. */
ExtendClause : EXTEND Atom {$$=$2;}
             | /* vide */ {$$=NULL;}
             ;

/* "any" : n'importe quel type, utilisable partout où un nom de type est attendu */
TypeName : IDENT {$$=$1;}
         | ANY {$$="any";}
         | RELATION {$$="relation";}
         ;

LiteralDefinition : LITERAL IDENT COLON TypeName SEMI NotationDefinition VariablesDefinitions Corps
                 {$$=new Literal();
                 $$->name=$2;
                 $$->type=$4;
                 $$->notation=$6;
                 $$->Vars=$7;
                 $$->AssignFromCorps($8);}
                  ;

FunctionDefinition : FUNCTION IDENT LPAREN DoubleIdentList RPAREN SEMI NotationDefinition VariablesDefinitions Corps
                 {$$=new Function();
                 $$->name=$2;
                 $$->AssignFromDoubleIdentList($4);
                 $$->notation=$7;
                 $$->Vars=$8;
                 $$->AssignFromCorps($9);}
                   ;

TheoremeDefinition : THEOREME STRING LPAREN DoubleIdentList RPAREN SEMI VariablesDefinitions CorpsM
                 {$$=new Theoreme();
                 $$->name=$2;
                 $$->AssignFromDoubleIdentList($4);
                 $$->Vars=$7;
                 $$->AssignFromCorpsM($8);}
                   ;

/* FIX : le cas vide ne renseignait pas $$ -> pointeur garbage
   utilisé ensuite dans universe->SetGoal($1). On construit un Goal
   vide plutôt que de laisser $$ indéfini. */
GoalDefinition : GOAL VariablesDefinitions CorpsMM
                    {$$=new Goal();
                    $$->Vars=$2;
                    $$->AssignFromCorpsMM($3);}
               | /* vide */ {$$=new Goal();}
               ;

NotationDefinition : NOTATION STRING NameSpaceList SEMI
                    {$$=new Notation();
                    $$->format=$2;
                    $$->params=$3;}
                   | /* vide */ {$$=NULL;}
                   ;

/* FIX : $3 (la NameSpaceList construite par NameSpaceList) était
   ignorée ci-dessus — on l'utilise maintenant pour $$->params
   au lieu de recréer une liste vide à chaque fois. */

NameSpaceList : NameSpaceList1 {$$=$1;}
              | /* vide */ {$$=new NameSpaceList();}
              ;

/* FIX : $$ n'était jamais initialisé avant l'appel à Add().
   Pattern liste récursive à droite : le cas terminal crée la
   liste, le cas récursif la récupère via $3 et lui ajoute la tête. */
NameSpaceList1 : NAMESPACE COMMA NameSpaceList1 {$$=$3; $$->Add($1);}
              | NAMESPACE  {$$=new NameSpaceList(); $$->Add($1);}
              ;

/* FIX : $$=new Parameters() écrasait $1 (la vraie liste construite
   par DoubleIdentList1) — il fallait juste la faire remonter. */
DoubleIdentList : DoubleIdentList1 {$$=$1;}
                | /* vide */ {$$=NULL;}
                ;

/* FIX : même bug d'initialisation que NameSpaceList1. */
DoubleIdentList1 : TypeName T COMMA DoubleIdentList1 {$$=$4; $$->Add($1,$2);}
                 | TypeName T {$$=new Parameters(); $$->Add($1,$2);}
                 ;
T                 : IDENT {$$=$1;} 
                  | RELATION {$$="relation";} 
                  | NAMESPACE {$$=$1;} ;

/* FIX : $2 (VariablesDefinitions1) était ignoré ; $$=new Variables()
   recréait une liste vide au lieu de récupérer celle construite. */
VariablesDefinitions : VAR VariablesDefinitions1 {$$=$2;}
                     | /* vide */ {$$=NULL;}
                     ;

/* FIX : même bug d'initialisation que les listes précédentes. */
VariablesDefinitions1 : QUANTIFIER IDENT COLON IDENT DependsClause SEMI VariablesDefinitions1 {$$=$7; $$->Add($1, $2, $4, NULL, $5);}
                      | QUANTIFIER IDENT COLON IDENT COMMA Predicat DependsClause SEMI VariablesDefinitions1 {$$=$9; $$->Add($1, $2, $4, $6, $7);}
                      | QUANTIFIER IDENT COLON IDENT DependsClause SEMI {$$=new Variables(); $$->Add($1, $2, $4, NULL, $5);}
                      | QUANTIFIER IDENT COLON IDENT COMMA Predicat DependsClause SEMI {$$=new Variables(); $$->Add($1, $2, $4, $6, $7);}
                      ;

/* "depends x,z" : liste des variables dont dépend la variable courante */
DependsClause : DEPENDS DependsList {$$=$2;}
              | /* vide */ {$$=NULL;}
              ;

DependsList : IDENT COMMA DependsList {$$=$3; $$->Add($1);}
            | IDENT {$$=new NameSpaceList(); $$->Add($1);}
            ;

/* Version mise à jour de Corps */
Corps : BEGIN_ Predicat ARROW_IMPLIES Predicat SEMI END { $$=new Corps(); $$->Assign($2, false, $4);}
      | BEGIN_ Predicat ARROW_EQUIV Predicat SEMI END { $$=new Corps(); $$->Assign($2, true, $4);}
      | BEGIN_ Predicat SEMI  END { $$=new Corps(); $$->AssignLeft($2);}
      | BEGIN_          ARROW_IMPLIES Predicat SEMI END { $$=new Corps(); $$->AssignRight($3);}
      ;

/* Version specifique aux Théorèmes et Objectifs */
CorpsM : BEGIN_ Predicat ARROW_IMPLIES Predicats SEMI END {
            $$=new CorpsM();
            $$->Assign($2, false, $4);
            }
       | BEGIN_ Predicat ARROW_EQUIV Predicat SEMI END {
            $$=new CorpsM();
            $$->Assign($2, true, $4);
            }

       | BEGIN_ Predicats SEMI  END {
            $$=new CorpsM();
            $$->Assign($2); }
       ;
CorpsMM : BEGIN_ Predicats ARROW_IMPLIES Predicats SEMI END {
            $$=new CorpsMM();
            $$->Assign($2, false, $4);
            }
       | BEGIN_ Predicats SEMI  END {
            $$=new CorpsMM();
            $$->Assign($2); }
       ;
////////////////////////////////////////////////////////////////////////////////////////////
/* Liste de prédicats séparés par des barres verticales PIPE */
Predicats : Predicats1 {$$=$1;}
          | /* vide */ {$$=new Predicats();}
          ;

/* FIX : même bug d'initialisation que les autres listes. */
Predicats1 : Predicat PIPE Predicats1 {$$=$3; $$->Add($1);}
           | Predicat {$$=new Predicats(); $$->Add($1);}
           ;


Predicat : NOT Predicat  {$$=Utils::CreateNot($2);}
         | Predicat OR Predicat {$$=Utils::CreateOr($1,$3);}
         | Predicat AND Predicat {$$=Utils::CreateAnd($1,$3);}
         | Predicat XOR Predicat {$$=Utils::CreateXor($1,$3);}
         | Atom EQ Atom {$$=Utils::CreateEq($1,$3);}
         | Atom NEQ Atom {$$=Utils::CreateNEq($1,$3);}
         | LPAREN Predicat RPAREN {$$=$2;}
         | TRUE {$$=Utils::CreateTrue();}
         | FALSE {$$=Utils::CreateFalse();}
         | Atom {$$=$1;}
         ;

Atom : IDENT LPAREN Atoms RPAREN  {$$=Utils::CreateFunction($1,$3);}
     | IDENT {$$=Utils::CreateTerminal($1);}
     | NAMESPACE {$$=Utils::CreateTerminal($1);}
     | RETURN {$$=Utils::CreateReturn();}
     | RETURN LPAREN Atoms RPAREN {$$=Utils::CreateReturn($3);}
     | APPARTIENT LPAREN Atom COMMA Atom RPAREN {$$=Utils::CreateAppartient($3,$5);}
     | RELATION LPAREN Atom COMMA Atom RPAREN {$$=Utils::CreateRelation($3,$5);}
     ;


Atoms : Atom1 {$$=$1;}
          | /* vide */ {$$=new Predicats();}
          ;

/* FIX : même bug d'initialisation que les autres listes. */
Atom1 : Atom COMMA Atoms {$$=$3; $$->Add($1);}
           | Atom {$$=new Predicats(); $$->Add($1);}
           ;

////////////////////////////////////////////////////////////////////////////////////////////

%%

// Gestion des erreurs syntaxiques
// Avec %locations, Bison exige cette signature précise (position + message).
void yy::Parser::error(const location_type& l, const std::string& msg) {
    std::cerr << l << ": " << msg << std::endl;
}
