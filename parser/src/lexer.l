%{
    #include <string>
    #include "driver.hh"
    #include "parser.tab.hh"

    // Met à jour driver.location à chaque token reconnu.
    #define YY_USER_ACTION  driver.location.columns(yyleng);
%}

%option noyywrap nounput noinput batch debug

%%

%{
    driver.location.step();
%}

[ \t]+                  { driver.location.step(); }
\n+                     { driver.location.lines(yyleng); driver.location.step(); }
"/*"([^*]|\*+[^*/])*\*+"/"  { /* commentaire multi-lignes ignoré */ }
"//".*                  { /* commentaire ligne ignoré */ }

"include"                { return yy::Parser::make_INCLUDE(driver.location); }
"end"                    { return yy::Parser::make_END(driver.location); }
"type"                   { return yy::Parser::make_TYPE(driver.location); }
"literal"                { return yy::Parser::make_LITERAL(driver.location); }
"function"               { return yy::Parser::make_FUNCTION(driver.location); }
"theoreme"               { return yy::Parser::make_THEOREME(driver.location); }
"notation"               { return yy::Parser::make_NOTATION(driver.location); }
"var"                    { return yy::Parser::make_VAR(driver.location); }
"begin"                  { return yy::Parser::make_BEGIN_(driver.location); }
"goal"                    { return yy::Parser::make_GOAL(driver.location); }

"not"                    { return yy::Parser::make_NOT(driver.location); }
"or"                     { return yy::Parser::make_OR(driver.location); }
"and"                    { return yy::Parser::make_AND(driver.location); }
"xor"                    { return yy::Parser::make_XOR(driver.location); }
"in"                     { return yy::Parser::make_APPARTIENT(driver.location); }
"relation"               { return yy::Parser::make_RELATION(driver.location); }

"=>"                     { return yy::Parser::make_ARROW_IMPLIES(driver.location); }
"<=>"                    { return yy::Parser::make_ARROW_EQUIV(driver.location); }
"="                      { return yy::Parser::make_EQ(driver.location); }
"!="                      { return yy::Parser::make_NEQ(driver.location); }


"forall"                 { return yy::Parser::make_QUANTIFIER(yytext, driver.location); }
"exists"                 { return yy::Parser::make_QUANTIFIER(yytext, driver.location); }
"existsu"                { return yy::Parser::make_QUANTIFIER(yytext, driver.location); }

\"[^\"]*\"               {
                             std::string s(yytext + 1, yyleng - 2); // retire les guillemets
                             return yy::Parser::make_STRING(s, driver.location);
                         }
[a-zA-Z_][a-zA-Z0-9_]*(\.[a-zA-Z_][a-zA-Z0-9_]*)+ { return yy::Parser::make_NAMESPACE(yytext, driver.location); }

[a-zA-Z_][a-zA-Z0-9_]*   { return yy::Parser::make_IDENT(yytext, driver.location); }

"("                      { return yy::Parser::make_LPAREN(driver.location); }
")"                      { return yy::Parser::make_RPAREN(driver.location); }
","                      { return yy::Parser::make_COMMA(driver.location); }
";"                      { return yy::Parser::make_SEMI(driver.location); }
":"                      { return yy::Parser::make_COLON(driver.location); }
"."                      { return yy::Parser::make_DOT(driver.location); }
"|"                      { return yy::Parser::make_PIPE(driver.location); }

.                        {
                             std::cerr << driver.location << ": caractère invalide: "
                                       << yytext << std::endl;
                         }

<<EOF>>                  { return yy::Parser::make_YYEOF(driver.location); }

%%

void Driver::scan_begin()
{
    yyin = fopen(file.c_str(), "r");
    if (!yyin)
    {
        std::cerr << "impossible d'ouvrir " << file << std::endl;
        exit(1);
    }

    // Détecte et saute le BOM UTF-8 (0xEF 0xBB 0xBF) s'il est présent,
    // pour que flex ne le voie jamais comme un "caractère invalide".
    unsigned char bom[3] = {0, 0, 0};
    size_t n = fread(bom, 1, 3, yyin);
    bool has_bom = (n == 3 && bom[0] == 0xEF && bom[1] == 0xBB && bom[2] == 0xBF);
    if (!has_bom)
        fseek(yyin, 0, SEEK_SET);   // pas de BOM : on revient au tout début
    // sinon on laisse le curseur juste après le BOM (3 octets sautés)
}

void Driver::scan_end()
{
    fclose(yyin);
}
