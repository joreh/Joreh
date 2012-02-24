#ifndef __COMMAND_H
#define __COMMAND_H

#include <string>

/** \file implementation of structures related to
  * commands' storage and retrieval
  *
  */

/** \brief this class is implemented to be the base of command storage classes.
  *        The commands given from agents or users are parsed and then converted
  *        to an instance of a class which is its self inherited from Command class.
  *
  */
class Command
{
public:

  /** \brief the virtual destructor of the Command class
    *
    */
  virtual ~Command();

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  virtual std::string toString() const = 0;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  virtual std::string getCommandName() const = 0;

};

/** \brief a class for storing Init Command parameters.
  *        agents will use this command to introduce themselves
  *        to simulation server. With this command they can specify
  *        their team name and model
  *
  */
class InitCommand : public Command
{
public:
  /** \brief constructor function
    *
    * \param teamName connecting team name
    * \param modelName
    */
  InitCommand( std::string teamName, std::string modelName );

  /** \brief a get function that returns a connecting agent's team name
    *
    * \returns team name
    */
  std::string getTeamName() const;

  /** \brief a get function that returns a connecting agent's model name
    *
    * \returns model name
    */
  std::string getModelName() const;

  /** \brief an overrided function to provide a string representation of
    *        Init Command
    *
    * \returns string representation of init command
    */
  std::string toString() const;

  /** \brief getCommandName function
    *
    * \return init command name
    */
  std::string getCommandName() const;
private:

  /** \brief a string to store a connecting agent's team name
    *
    */
  std::string m_teamName;

  /** \brief a string to store a connecting agent's model name
    *
    */
  std::string m_modelName;
};

/** \brief a class to maintain parameters of a move command.
  *        agents can move their physical location using
  *        this command.
  */
class MoveCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    * \param velX the velocity vector along x-coordinate
    * \param velY the velocity vector along y-coordinate
    */
  MoveCommand( double velX, double velY );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
  double getVelX() const;

  /** \brief a get function for velY
    *
    * \returns velocity along y-coordinate
    */
  double getVelY() const;

  /** \brief an overrided function to provide a string representation of
    *        Move Command
    *
    * \returns string representation of Move command
    */
  std::string toString() const;

  /** \brief getCommandName function
    *
    * \return move command name
    */
  std::string getCommandName() const;

private:

  /** \brief velocity along x-coordinate
    *
    */
  double m_velX;

  /** \brief velocity along y-coordinate
    *
    */
  double m_velY;
};
/** \brief a class to maintain parameters of a walk command.
  *        agents can move their physical location using
  *        this command.
  */
class WalkCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    * \param velX the velocity vector along x-coordinate
    * \param velY the velocity vector along y-coordinate
    */
  WalkCommand( double velX, double velY );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
  double getVelX() const;

  /** \brief a get function for velY
    *
    * \returns velocity along y-coordinate
    */
  double getVelY() const;

  /** \brief an overrided function to provide a string representation of
    *        walk Command
    *
    * \returns string representation of Move command
    */
  std::string toString() const;

  /** \brief getCommandName function
    *
    * \return walk command name
    */
  std::string getCommandName() const;

private:

  /** \brief velocity along x-coordinate
    *
    */
  double m_velX;

  /** \brief velocity along y-coordinate
    *
    */
  double m_velY;
};
#endif

