#include "Command.h"
#include <sstream>

using namespace std;

/*********************************************************************
 ****************************** Command ******************************
 *********************************************************************
 */

Command::~Command()
{
}

/*********************************************************************
 ************************* Init Command ******************************
 *********************************************************************
 */
InitCommand::InitCommand( string teamName, string modelName )
{
  m_teamName = teamName;
  m_modelName = modelName;
}

string InitCommand::getTeamName() const
{
  return m_teamName;
}

string InitCommand::getModelName() const
{
  return m_modelName;
}

string InitCommand::toString() const
{
  ostringstream out;

  out << "(init " << m_teamName << " " << m_modelName << ")";
  return out.str();
}

string InitCommand::getCommandName() const
{
  return "init";
}

/*********************************************************************
 ************************* Move Command ******************************
 *********************************************************************
 */

MoveCommand::MoveCommand( double velX, double velY )
{
  m_velX = velX;
  m_velY = velY;
}

double MoveCommand::getVelX() const
{
  return m_velX;
}

double MoveCommand::getVelY() const
{
  return m_velY;
}

string MoveCommand::toString() const
{
  ostringstream out;

  out << "(move " << m_velX << " " << m_velY << ")";
  return out.str();
}

string MoveCommand::getCommandName() const
{
  return "move";
}
/*********************************************************************
 ************************* Init Command ******************************
 *********************************************************************
 */

WalkCommand::WalkCommand( double velX, double velY )
{
  m_velX = velX;
  m_velY = velY;
}

double WalkCommand::getVelX() const
{
  return m_velX;
}

double WalkCommand::getVelY() const
{
  return m_velY;
}

string WalkCommand::toString() const
{
  ostringstream out;

  out << "(walk " << m_velX << " " << m_velY << ")";
  return out.str();
}

string WalkCommand::getCommandName() const
{
  return "walk";
}

