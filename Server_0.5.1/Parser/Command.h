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
  MoveCommand( double x, double y );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
  double getX() const;

  /** \brief a get function for velY
    *
    * \returns velocity along y-coordinate
    */
  double getY() const;

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
  double m_x;

  /** \brief velocity along y-coordinate
    *
    */
  double m_y;
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
/** \brief a class to maintain parameters of a rest command.
  *        agents can change state to standup with
  *        this command.
  */
class RestCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    */
  RestCommand(  );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
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

};
/** \brief a class to maintain parameters of a rest command.
  *        agents can change state to standup with
  *        this command.
  */
class StandCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    */
  StandCommand(  );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
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

};


/** \brief a class to maintain parameters of a rest command.
  *        agents can change state to standup with
  *        this command.
  */
class LieCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    */
  LieCommand(  );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
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

};


/** \brief a class to maintain parameters of a rest command.
  *        agents can change state to standup with
  *        this command.
  */
class ReadyCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    */
  ReadyCommand(  );

  /** \brief a get function for velX
    *
    * \returns velocity along x-coordinate
    */
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

};

/** \brief a class to maintain parameters of a walk command.
  *        agents can move their physical location using
  *        this command.
  */
class RunCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    * \param velX the velocity vector along x-coordinate
    * \param velY the velocity vector along y-coordinate
    */
  RunCommand( double velX, double velY );

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
/** \brief a class to maintain parameters of a walk command.
  *        agents can move their physical location using
  *        this command.
  */
class EvadeCommand : public Command
{
public:

  /** \brief constructor of the class that takes a force velocity
    *        as its arguments
    * \param velX the velocity vector along x-coordinate
    * \param velY the velocity vector along y-coordinate
    */
  EvadeCommand( double velX, double velY );

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

/** \brief this class is implemented to be the base of command storage classes.
 *        The commands given from agents or users are parsed and then converted
 *        to an instance of a class which is its self inherited from Command class.
 *
 */
class ShootCommand : public Command
{
public:

  ShootCommand( double ang );

  double getAng() const;

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  std::string toString() const;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  std::string getCommandName() const;

private:
  double m_ang;
};


/** \brief this class is implemented to be the base of command storage classes.
 *        The commands given from agents or users are parsed and then converted
 *        to an instance of a class which is its self inherited from Command class.
 *
 */
class XShootCommand : public Command
{
public:

  XShootCommand( double ang );

  double getAng() const;

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  std::string toString() const;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  std::string getCommandName() const;

private:
  double m_ang;
};


/** \brief this class is implemented to be the base of command storage classes.
 *        The commands given from agents or users are parsed and then converted
 *        to an instance of a class which is its self inherited from Command class.
 *
 */
class MineCommand : public Command
{
public:

  MineCommand( double x, double y );

  double getX() const;
  double getY() const;

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  std::string toString() const;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  std::string getCommandName() const;

private:
  double m_x;
  double m_y;
};


/** \brief this class is implemented to be the base of command storage classes.
 *        The commands given from agents or users are parsed and then converted
 *        to an instance of a class which is its self inherited from Command class.
 *
 */
class DemineCommand : public Command
{
public:

  DemineCommand( double x, double y );

  double getX() const;
  double getY() const;

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  std::string toString() const;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  std::string getCommandName() const;

private:
  double m_x;
  double m_y;
};

/** \brief this class is implemented to be the base of command storage classes.
 *        The commands given from agents or users are parsed and then converted
 *        to an instance of a class which is its self inherited from Command class.
 *
 */
class HealCommand : public Command
{
public:

  HealCommand( int id );

  int getId() const;

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  std::string toString() const;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  std::string getCommandName() const;

private:
  int m_id;
};

/** \brief this class is implemented to be the base of command storage classes.
 *        The commands given from agents or users are parsed and then converted
 *        to an instance of a class which is its self inherited from Command class.
 *
 */
class SupportCommand : public Command
{
public:

  SupportCommand( int id );

  int getId() const;

  /** \brief an abstract function to provide a string representation of an instance
    *
    * \returns string representation of an instance
    */
  std::string toString() const;

  /** \brief an abstract function to present the name of command
    *
    * \returns command's name
    */
  std::string getCommandName() const;

private:
  int m_id;

};


#endif

