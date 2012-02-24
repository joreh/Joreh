%option noyywrap

%{

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include "MessageParser_yacc.h"

using namespace std;

/** \brief this function duplicate string sourse(can be replaced by strdup)
  *
  * \param srouce the source string
  * \return the duplicated string
  */
char *clone_str( char *source )
{
  char *str = new char[strlen(source)];
  strcpy( str, source );
  return str;
}


%}

DIGIT             [0-9]
LETTER            [a-zA-Z]
INTEGER           ([-+]?{DIGIT}+)
DOUBLE            ([-+]?[0-9]*"."[0-9]+)
EXP               ([-+]?[0-9]*"."?[0-9]+([eE][-+]?[0-9]+))
FLOAT_POINT       ({EXP}|{DOUBLE})
CHAR              ([^\"\']|\\n|\\t|\\b|\\\\|\\\"|\\\')
STRING            (\"({CHAR}|[ \t])*\")
BLANK             ([ \t\r\n])

%%

"("               { return OP;                              }
")"               { return CP;                              }
"con"             { return CON;                             }
"see"             { return SEE;                             }
"bye"             { return DIS;                             }
"models"	  { return MODELS;			    }	
{STRING}          { yylval.str = clone_str( yytext );
                    return STRING;                          }
{DOUBLE}          { yylval.d = atof( yytext );
                    return DOUBLE;                          }
{INTEGER}         { yylval.i = atoi( yytext );
                    return INTEGER;                         }
{BLANK}           {                                         }
%%

/*
int main()
{
  yylex();
  return 0;
}
*/

