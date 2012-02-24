%{

#include <iostream>
#include <string>
#include <vector>

#include "Parser/Command.h"
#include "CommandParser_yacc.h"
#include "Utilities/SwarmException.h"

using namespace std;


typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern int yylex();
extern YY_BUFFER_STATE yy_scan_string( const char * );
extern void yy_delete_buffer( YY_BUFFER_STATE );

void yyerror( const char *s );

vector<Command *> *commands;

%}

%token OP
%token CP
%token INIT
%token MOVE
%token WALK
%token DOUBLE
%token INTEGER
%token STRING

%union
{
  char *str;
  double d;
  int i;
};

%type <str> STRING
%type <d> DOUBLE
%type <i> INTEGER

%%

messages       :  
                  OP commands CP
                  {                                     }
               |  OP command CP
                  {                                     };

commands       :  
                  OP command CP commands
                  {                                     }
               |  /*empty*/
                  {                                     };

command        :
                  INIT STRING STRING
                  { commands->push_back(
                       new InitCommand( $2, $3 ) );    }
               |  MOVE DOUBLE DOUBLE
                  { commands->push_back(
                       new MoveCommand( $2, $3 ) );     }
               |  WALK DOUBLE DOUBLE
                  { commands->push_back(
                       new WalkCommand( $2, $3 ) ); };


%%

/** \brief this function directs error string to standard output
  *
  * \param error_str error message
  */
void yyerror( const char *error_str )
{
  for( vector<Command *>::iterator itr = commands->begin();
       itr != commands->end(); itr ++ )
    delete (*itr);

  delete commands;

  std::cout << "error line: " 
            << 1 << " " 
            << error_str << std::endl;
}

vector<Command *> *parseCommandMessage( std::string str )
{
  commands = new vector<Command *>();

  yy_buffer_state *currentBuffer =
               yy_scan_string( (char *)str.c_str() );
  yyparse();
  yy_delete_buffer( currentBuffer ); 

  return commands;
}

