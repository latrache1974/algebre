#ifndef LEXER_HH
#define LEXER_HH

#ifndef __FLEX_LEXER_H
#include <FlexLexer.h>
#endif

// Ce fichier est généré par Bison et contient les définitions de types
#include "parser.tab.hh"

// Notre classe de Lexer qui hérite de la classe C++ de base de Flex
class Lexer : public yyFlexLexer {
public:
    Lexer(std::istream* in = nullptr, std::ostream* out = nullptr) : yyFlexLexer(in, out) {}
    
    // Wrapper indispensable utilisé par Bison pour lire les jetons
    int yylex_wrapper(yy::Parser::semantic_type* yylval) {
        return this->yylex(yylval);
    }

    // Déclaration obligatoire de la fonction virtuelle de base de Flex
    // pour éviter l'erreur de référence indéfinie au linking
    int yylex() override {
        return 0; 
    }

private:
    // Notre fonction de scan sémantique réelle implémentée dans lexer.l
    int yylex(yy::Parser::semantic_type* yylval);
};

#endif
