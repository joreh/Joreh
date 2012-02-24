#include "Config.h"
#include "../Utilities/SwarmException.h"

#include <sstream>

using namespace std;

/** \brief an extern function which provides access to a function
  *        implemented in a bison file(this class must be compiled
  *        with the output C code of the bison file)
  *
  */
extern map<string, CONFIG *> *read_config_file( string file_name );

Config::Config( string fileName )
{
  m_configMap = read_config_file( fileName );
}

Config::~Config()
{
  map<string, CONFIG *>::iterator tmpItr;

  for( map<string, CONFIG *>::iterator itr = m_configMap->begin();
       itr != m_configMap->end(); )
  {
    tmpItr = itr;
    itr ++;
    delete tmpItr->second;
  }

  delete m_configMap;
}

CONFIG &Config::operator[]( string groupName )
{
  if( !isGroupValid( groupName ) )
    throw SwarmException( "(Config::operator[]) " +
                          groupName + " is not valid" );

  return *(*m_configMap)[groupName];
}

bool Config::isGroupValid( string groupName ) const
{
  return ( m_configMap->find( groupName ) != m_configMap->end() );
}

bool Config::isParamValid( string groupName, string param ) const
{
  return ( isGroupValid( groupName ) &&
           (*m_configMap)[groupName]->find( param ) != 
           (*m_configMap)[groupName]->end() );
}

vector<string> Config::getGroupsNames() const
{
  vector<string> groupsNamesVec;
  for( map<string, CONFIG *>::iterator itr = m_configMap->begin();
       itr != m_configMap->end(); itr ++ )
    groupsNamesVec.push_back( itr->first );

  return groupsNamesVec;
}


map<string, CONFIG *>::iterator Config::getFirstGroupPair() const
{
  return m_configMap->begin();
}

map<string, CONFIG *>::iterator Config::getLastGroupPair() const
{
  return m_configMap->end();
}

string Config::toString() const
{
  ostringstream out;
  for( map<string, CONFIG *>::iterator itr = m_configMap->begin();
       itr != m_configMap->end(); itr ++ )
  {
    out << itr->first << endl;

    for( CONFIG::iterator itrs = itr->second->begin();
         itrs != itr->second->end(); itrs ++ )
      out << "\t" << itrs->first << " = " << itrs->second.toString() << endl;
  }

  return out.str();
}


int main()
{
  Config config( "config.txt" );

  cout << config.toString() << endl;

  vector<string> vec = config.getGroupsNames();

  for( vector<string>::iterator itr = vec.begin(); itr != vec.end(); itr ++ )
    cout << *itr << endl;

  cout << config["test"]["var1"].toString() << endl;

}

