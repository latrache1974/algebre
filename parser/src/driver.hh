#ifndef DRIVER_HH
#define DRIVER_HH

#include <string>
#include <map>
#include "parser.tab.hh"

// Déclaration forward pour éviter d'inclure le header généré par flex
// dans ce header (évite les inclusions circulaires).
#define YY_DECL \
    yy::Parser::symbol_type yylex(Driver& driver)
YY_DECL;

class Driver
{
public:
    Driver();

    // Lance l'analyse d'un fichier. Retourne 0 si OK.
    int parse(const std::string& filename);

    // Utilisé par le lexer / parser pour rapporter des erreurs
    void scan_begin();
    void scan_end();

    // Nom du fichier courant (pour les messages d'erreur)
    std::string file;

    // Position courante (mise à jour par YY_USER_ACTION dans le lexer)
    yy::location location;

    // Active le mode debug du lexer flex (%option debug)
    bool trace_scanning = false;
    // Active le mode debug du parser bison (%debug)
    bool trace_parsing = false;

    // Exemple de contexte partagé entre lexer et parser
    // (ex: table de symboles, résultat final, etc.)
    // Adapte selon ton propre "universe" / AST.
    void* result = nullptr;
};

#endif // DRIVER_HH
