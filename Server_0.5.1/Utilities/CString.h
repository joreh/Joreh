#ifndef __CSTRING_H
#define __CSTRING_H

#include <string>
#include <iostream>

/** \file this file contains Str class implementation
  *
  */

/** \brief this class provides some functionally for
  * more convenient string's conversion by wraping an
  * instance of std::string
  */
class CString
{
public:

  /** \brief class's default constructor
    *
    */
  CString();

  /** \brief class's constructor
    *
    * \param str input std::string
    */
  CString( std::string str );


  /** \brief overloaded class's constructor
    *
    * \param str input char *
    */
  CString( char *str );

  /** \brief set the wraped string
    *
    * \param str the std::string which would be wraped
    */
  void setStdString( std::string str );

  /** \brief converts CString instance to integer
    *
    * \returns integer value of Str
    */
  int toInt() const;

  /** \brief converts CString to double
    *
    * \returns floating point value of Str
    */ 
  double toDouble() const;

  /** \brief converts CString to boolean
    *
    * \returns boolean value of CString
    */
  bool toBool() const;

   /** \brief converts CString to std::String
    *
    * \returns std::string value of CString
    */
  const std::string &toString() const;

  /** \brief introducing a friend function to show the
    *        data stored in an inastance
    *
    */
//  friend std::ostream &operator<<( std::ostream &out, const CString &str );

private:

  /** \brief the string which is wraped by CString
    *
    */
  std::string m_str;

};

/** \brief a function to show an instance of CString via ostream
  *
  * \param out the ostream
  * \param str the CString instance
  */
/*std::ostream &operator<<( std::ostream &out, const CString &str )
{
  out << str.m_str;
}*/

#endif

