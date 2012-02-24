%{

#include <iostream>
#include <string>
#include <cstdio>
#include <map>


#include "ConfigParser.y.h"
#include "../Utilities/CString.h"
#include "../Utilities/SwarmException.h"

using namespace std;

extern int yylex();
extern int yyparse();
extern FILE *yyin;

void yyerror( const char *s );

#define CONFIG map<string, CString>

CONFIG *config_sub = NULL;
map<string, CONFIG *> *config_root = NULL;

/** \brief this function stores a scope in a std::map
  *
  * \param scope_name the scope name
  */
void store_scope( char *scope_name )
{
  if( !config_root )
    config_root = new map<string, CONFIG *>();

  config_root->insert( pair<string, CONFIG *>(
                       string( scope_name ), config_sub ) );

  config_sub = NULL;
}

/** \brief this function stores a config assignment in a std::map
  *
  * \param key the key of mapping
  * \param value the value of the key
  */
void store_to_map( char *key, char *value )
{
  if( !config_sub )
    config_sub = new CONFIG();

  string e_str( value );

  if( e_str[0] == '\"' && e_str[e_str.size()-1] == '\"' )
    e_str = e_str.substr( 1, e_str.size() - 2 );

  if( config_sub->find( string( key ) ) != config_sub->end() )
    cerr << "config: multiple definition for " << key << endl;

  config_sub->insert( pair<string, CString>( string( key ), CString( e_str ) ) );



  delete[] key;
  delete[] value;
}

%}


%token BEGIN_TK
%token END_TK
%token EQUAL
%token VARNAME
%token VALUE

%right EQUAL

%union
{
  char *str;
};

%type <str> VALUE VARNAME

%%

config         :
                  begin_end config | /*empty*/
                  {                                      };

begin_end      :
                  BEGIN_TK VARNAME declarations END_TK
                  { store_scope( $2 );                   };

declarations   :
                  declaration declarations | /*empty*/
                  {                                      };

declaration    :
                  VARNAME EQUAL VARNAME
                  { store_to_map( $1, $3 );              }
               |  VARNAME EQUAL VALUE
                  { store_to_map( $1, $3 );              };

%%

/** \brief this function directs error string to standard output
  *
  * \param error_str error message
  */
void yyerror( const char *error_str )
{
  for( map<string, CONFIG *>::iterator itr = config->begin();
       itr != config->end(); itr ++ )
  {
    cout << itr->first << " : " << endl;

    delete itr->second;
  }

  delete config;


  std::cout << "(ConfigParser)error line: " 
            << 1 << " " 
            << error_str << std::endl;
}

/** \brief this function loads the input file into a hash map struct
  *
  * \param file_name config file name
  * \param mp a hash map storage for config parameters
  */
map<string, CONFIG *> *read_config_file( string file_name )
{
  yyin = fopen( file_name.c_str(), "r" );

  if( !yyin )
    throw SwarmException( "(read_config_file)" +
                     file_name + " is not valid !" );

  do
  {
    yyparse();
  } while( !feof( yyin ) );


  fclose( yyin );

  config_sub = NULL;

  map<string, CONFIG *> *mp = config_root;

  config_root = NULL;
  return mp;
}

/*
int main()
{
  map<string, CONFIG *> *config = read_config_file( "config.txt" );
  for( map<string, CONFIG *>::iterator itr = config->begin();
       itr != config->end(); itr ++ )
  {
    cout << itr->first << " : " << endl;

    for( CONFIG::iterator itrs = itr->second->begin();
         itrs != itr->second->end(); itrs ++ )
      cout << itrs->first << " = " << itrs->second.toString() << endl;
  }
}
*/

