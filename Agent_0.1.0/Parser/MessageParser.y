%{

#include <iostream>
#include <string>
#include <vector>

#include "WorldModel.h"
#include "SwarmException.h"

using namespace std;


typedef struct yy_buffer_state *YY_BUFFER_STATE;

extern YY_BUFFER_STATE yy_scan_string( const char * );
extern void yy_delete_buffer( YY_BUFFER_STATE );


#ifndef YACC_EXTERM
#define YACC_EXTERM

extern int yylex();
extern int yyparse();

#endif

void yyerror( const char *s );

WorldModel *world_model;

void update_object( int id, double x, double y, double fitness , int mID )
{
  try
  {
    world_model->setObject( id ).update( Vector3D( x, y, 0.0 ), fitness , mID );
  }
  catch( SwarmException &exp )
  {
    world_model->addObject( Object( id, Vector3D( x, y, 0.0 ) ) );
    world_model->setObject( id ).update( Vector3D( x, y, 0.0 ), fitness,mID );
  }
}


%}

%token OP
%token CP
%token CON
%token SEE
%token DIS
%token MODELS
%token DOUBLE
%token INTEGER
%token STRING
%token BLANK

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

data           :
                  OP messages CP
                  {                                      };

messages       :
                  OP message CP messages
                  {                                      }
               | /* empty */
                  {                                      };
message        :
                  CON INTEGER DOUBLE DOUBLE DOUBLE DOUBLE
                  { world_model->setAgentID( $2 );
                    world_model->setField().setFieldGeom(
                              $3, $4, $5, $6 );          }
               |
                  DIS
                  { world_model->gameFinished();         }
               |  MODELS model_params
                  {	}
               |  SEE INTEGER see_parameters
                  { world_model->setCurCycle( $2 );      };
model_params   :  OP model_param CP model_params
                  {					 }

                |/*empty*/
                {               };
model_param    :  INTEGER INTEGER
                  {world_model->addModel($1,$2)          };
see_parameters :  OP see_parameter CP see_parameters
                  {                                      }
               |  /*empty*/
                  {                                      };


see_parameter  :  INTEGER DOUBLE DOUBLE DOUBLE INTEGER
                  { update_object( $1, $2, $3, $4 ,$5 );     };

%%

/** \brief this function directs error string to standard output
  *
  * \param error_str error message
  */
void yyerror( const char *error_str )
{

  std::cout << "\nerror line: "
            << 1 << " "
            << error_str << std::endl;
}

void update_world_model( std::string msg, WorldModel *wm )
{
  world_model = wm;

  yy_buffer_state *currentBuffer =
               yy_scan_string( (char *)msg.c_str() );
  yyparse();
  yy_delete_buffer( currentBuffer );
}

