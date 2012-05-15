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
%token REST
%token READY
%token RUN
%token EVADE
%token SHOOT
%token XSHOOT
%token MINE
%token DEMINE
%token HEAL
%token SUPPORT
%token STAND
%token LIE

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
                       new MoveCommand( $2, $3 ) );    }
               |  WALK DOUBLE DOUBLE
                  { commands->push_back(
                       new WalkCommand( $2, $3 ) );    }
               |  REST
                  { commands->push_back(
                       new RestCommand() );            }
               |  READY
                  { commands->push_back(
                       new ReadyCommand() );           }
               |  STAND
                  { commands->push_back(
                       new StandCommand() );           }
               |  LIE
                  { commands->push_back(
                       new LieCommand() );             }
               |  RUN DOUBLE DOUBLE
                  { commands->push_back(
                       new RunCommand( $2, $3 ) );     }
               |  EVADE DOUBLE DOUBLE
                  { commands->push_back(
                       new EvadeCommand( $2, $3 ) );   }
               |  SHOOT DOUBLE
                  { commands->push_back(
                       new ShootCommand( $2 ) );       }
               |  XSHOOT DOUBLE
                  { commands->push_back(
                       new XShootCommand( $2 ) );      }
               |  MINE DOUBLE DOUBLE
                  { commands->push_back(
                       new MineCommand( $2, $3 ) );    }
               |  DEMINE DOUBLE DOUBLE
                  { commands->push_back(
                       new DemineCommand( $2, $3 ) );  }
               |  HEAL INTEGER
                  { commands->push_back(
                       new HealCommand( $2 ) );        }
               |  SUPPORT INTEGER
                  { commands->push_back(
                       new SupportCommand( $2 ) );     };


%%

/** \brief this function directs error string to standard output
  *
  * \param error_str error message
  */
void yyerror( const char *error_str )
{
  cout << "test" << endl;
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

