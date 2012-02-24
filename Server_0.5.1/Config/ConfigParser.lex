%option noyywrap

%{

#include <iostream>
#include <cstring>
#include <string>
#include <map>
#include "ConfigParser.y.h"

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
DOUBLE            ([-+]?{INTEGER}"."{INTEGER})
EXP               (({DOUBLE}|{INTEGER})("e"|"E")({DOUBLE}|{INTEGER}))
FLOAT_POINT       ({EXP}|{DOUBLE})
BLANK             ([ \t\n\r]*)
CHAR              ([^\"\']|\\n|\\t|\\b|\\\\|\\\"|\\\')
STRING            (\"({CHAR}|[ \t])*\")
BOOLEAN           ("True"|"true"|"False"|"false")
END_LINE          "\n"

VALUE             ({STRING}|{FLOAT_POINT}|{INTEGER}|{BOOLEAN})
VARNAME           ({LETTER}({LETTER}|{DIGIT})*)
COMMENT           ("#".*)

%%

"="               { return EQUAL;                          }
"begin"           { return BEGIN_TK;                       }
"BEGIN"           { return BEGIN_TK;                       }
"end"             { return END_TK;                         }
"END"             { return END_TK;                         }
{VALUE}           { yylval.str = clone_str( yytext );
                    return VALUE;                          }
{VARNAME}         { yylval.str = clone_str( yytext );
                    return VARNAME;                        }
{COMMENT}         {                                        }
{BLANK}           {                                        }
<<EOF>>           { yyterminate();                         }

%%


/*
int main()
{
  yylex();
  return 0;
}

*/

