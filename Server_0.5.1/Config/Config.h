#ifndef __CONFIG_H
#define __CONFIG_H

#include "../Utilities/CString.h"
#include <string>
#include <vector>
#include <map>

/** \file this file contains implementation of Config class
  *
  */

/** \brief type definition for CONFIG
  * this definition implies a sub config
  */
typedef std::map<std::string, CString> CONFIG;

/** \brief the class loads and stores config parameters and their value
  * in a way that provides easy access
  */
class Config
{
public:
  
  /** \brief class's default constructor which loads the config file
    * 
    * \param fileName config file address
    */
  Config( std::string fileName );

  /** \brief class's destructor
    *
    */
  ~Config();

  /** \brief an overloaded operator to access a set
    *        of parameteres located in a group
    *
    * \param groupName the name of parameters' groups
    * \returns a CONFIG type to provide access to the group's parameters
    */
  CONFIG &operator[]( std::string groupName );


  /** \brief check the validation of a groupName
    *
    * \param groupName the name of group to be checked
    * \returns true if group exist
    */
  bool isGroupValid( std::string groupName ) const;

  /** \brief check the validation of a parameter inside a group
    *
    * \param groupName the name of group that may contains the parameter
    * \param param the param to be checked
    * \returns true if the param exist
    */
  bool isParamValid( std::string groupName, std::string param ) const;

  /** \brief return a vector which contains the names of all groups in
    *        an instance of Config class
    *
    * \returns groups vector
    */
  std::vector<std::string> getGroupsNames() const;

  /** \brief a get function to access the first member of group-parameters
    *        map in order to provide an easy way for iterations
    *
    * \returns an iterator pointer to the first group-parameter pair
    */
  std::map<std::string, CONFIG *>::iterator getFirstGroupPair() const;

  /** \brief a get function access the last member of group-parameters
    *        map in order to provide an easy way for iterations
    *
    * \returns an iterator pointer to the last group-parameter pair
    */
  std::map<std::string, CONFIG *>::iterator getLastGroupPair() const;

  /** \brief this function converts the data exist in an instance to
    *        a string which is human readable
    *
    * \returns encrypted string
    */
  std::string toString() const;

private:
  /** \brief a map structure to store parameters and groups
    *
    */
  std::map<std::string, CONFIG *> *m_configMap;
  

};

#endif

