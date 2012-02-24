#ifndef __MESSAGE_H
#define __MESSAGE_H

#include <string>
#include <vector>
#include "Object.h"

/** \file implementation of structures related to
  * messages' storage and retrieval
  *
  */

/** \brief this class is implemented to be the base of message storage classes.
  *        The messages given from server are parsed and then converted
  *        to an instance of a class which is its self inherited from Message class.
  *
  */
class Message
{
public:

  /** \brief the virtual destructor of the Command class
    *
    */
  virtual ~Message();

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  virtual std::string toString() const = 0;

  /** \brief an abstract function to present the name of the message
    *
    * \returns message's name
    */
  virtual std::string getMessageName() const = 0;

};

/** \brief a class for storing Con Message parameters.
  *        this is the first message which will be sent by the server
  *        to the connected monitor which indicates initial state of monitor
  *
  */
class ConMessage : public Message
{
public:
  /** \brief constructor function
    *
    * \param id monitor id
    * \param lx x-coordinate of the field's left side
    * \param rx x-coordinate of the field's right side
    * \param ty y-coordinate of the field's top side
    * \param by y-coordinate of the field's bottom side
    */
  ConMessage( unsigned id, double lx, double rx,
              double ty, double by );


  /** \brief a get function for monitor ID
    *
    * \returns monitor ID
    */
  unsigned getMonitorID() const;

  /** \brief a get function for the field's left x-coordinate
    *
    * \returns field's left x-coordinate
    */
  double getLeftX() const;

  /** \brief a get function for the field's right x-coordinate
    *
    * \returns field's right x-coordinate
    */
  double getRightX() const;

  /** \brief a get function for the field's top y-coordinate
    *
    * \returns field's top y-coordinate
    */
  double getTopY() const;

  /** \brief a get function for the field's bottom y-coordinate
    *
    * \returns field's bottom y-coordinate
    */
  double getBottomY() const;

  /** \brief an overrided function to provide a string representation of
    *        Con Message
    *
    * \returns string representation of Con Message
    */
  std::string toString() const;

  /** \brief getMessageName function

    *
    * \returns message's name
    */
  std::string getMessageName() const;
private:

  /** \brief monitor id
    *
    */
  unsigned m_monID;

  /** \brief left x-coordinate of the field
    *
    */
  double m_lx;

  /** \brief right x-coordinate of the field
    *
    */
  double m_rx;

  /** \brief top y-coordinate of the field
    *
    */
  double m_ty;

  /** \brief bottom y-coordinate of the field
    *
    */
  double m_by;
};


/** \brief this struct is to mainain objects' received parameters
  * 
  */
struct InterObject
{
  InterObject( unsigned _id, double _x, double _y );

  /** \brief id of the object
    *
    */
  unsigned id;

  /** \brief x-coordinate of the object
    *
    */
  double x;

  /** \brief y-coordinate of the object
    *
    */
  double y;
};

/** \brief a class which maintains see message parameters
  *
  */
class SeeMessage : public Message
{
public:

  /** \brief default constructor
    *
    */
  SeeMessage();

  /** \brief this function sets simulation time
    *
    * \param time current simulation time
    */
  void setSimTime( unsigned time );

  /** \brief this function returns simulation time
    *
    * \returns current simulation time
    */
  unsigned getSimTime() const;

  /** \brief adds a new object to the objects' vector
    *
    * \param obj new object
    */
  void addObject( InterObject obj );

  /** \brief returns an object by index
    *
    * \param indx index of the object
    * \returns the object
    */
  const InterObject &getObject( unsigned indx ) const;

  /** \brief a function to access the number of objects stored in an instance
    *
    * \returns the number of objects
    */
  unsigned getNumOfObjects() const;

  /** \brief an overrided function to provide a string representation of
    *        SeeMessage
    *
    * \returns string representation of SeeMessage
    */
  std::string toString() const;

  /** \brief getMessageName function
    *
    * \returns message's name
    */
  std::string getMessageName() const;

private:

  /** \brief objects' vector
    *
    */
  vector<InterObject> m_objects;

  /** \brief current simulation time
    *
    */
  unsigned m_simTime;
};

/** \brief this class is to maintain information which will be sent
  *        by the server when server wants to disconnect the monitor
  *
  */
class DisMessage : public Message
{
public:

  /** \brief DisMessage constructor
    *
    */
  DisMessage();

  /** \brief an overrided function to provide a string representation of
    *        SeeMessage
    *
    * \returns string representation of SeeMessage
    */
  std::string toString() const;

  /** \brief getMessageName function
    *
    * \returns message's name
    */
  std::string getMessageName() const;
private:
};

#endif

