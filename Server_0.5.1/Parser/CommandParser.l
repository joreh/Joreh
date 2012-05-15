%option noyywrap

%{

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include "CommandParser_yacc.h"

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
EXP               ([-+]?[0-9]*"."?[0-9]*([eE][-+]?[0-9]+))
FLOAT_POINT       ({EXP}|{DOUBLE})
CHAR              ([^\"\']|\\n|\\t|\\b|\\\\|\\\"|\\\')
STRING            (\"({CHAR}|[ \t\n])*\")
BLANK             ([ \t\r\n])

%%

"("               { return OP;                              }
")"               { return CP;                              }
"init"            { return INIT;                            }
"move"            { return MOVE;                            }
"walk"            { return WALK;                            }
"rest"            { return REST;                            }
"ready"           { return READY;                           }
"run"             { return RUN;                             }
"evade"           { return EVADE;                           }
"shoot"           { return SHOOT;                           }
"xshoot"          { return XSHOOT;                          }
"mine"            { return MINE;                            }
"demine"          { return DEMINE;                          }
"heal"            { return HEAL;                            }
"support"         { return SUPPORT;                         }
"stand"           { return STAND;                           }
"lie"             { return LIE;                             }

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

