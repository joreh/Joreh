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

MoveCommand::MoveCommand( double x, double y )
{
  m_x = x;
  m_y = y;
}

double MoveCommand::getX() const
{
  return m_x;
}

double MoveCommand::getY() const
{
  return m_y;
}

string MoveCommand::toString() const
{
  ostringstream out;

  out << "(move " << m_x << " " << m_y << ")";
  return out.str();
}

string MoveCommand::getCommandName() const
{
  return "move";
}
/*********************************************************************
 ************************* Walk Command ******************************
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
/*********************************************************************
 ************************* Rest Command ******************************
 *********************************************************************
 */

RestCommand::RestCommand( )
{
}

string RestCommand::toString() const
{
  ostringstream out;

  out << "(rest)";
  return out.str();
}

string RestCommand::getCommandName() const
{
  return "rest";
}
/*********************************************************************
 ************************* Stand Command ******************************
 *********************************************************************
 */

StandCommand::StandCommand( )
{
}

string StandCommand::toString() const
{
  ostringstream out;

  out << "(stand)";
  return out.str();
}

string StandCommand::getCommandName() const
{
  return "stand";
}
/*********************************************************************
 ************************* Lie Command ******************************
 *********************************************************************
 */

LieCommand::LieCommand( )
{
}

string LieCommand::toString() const
{
  ostringstream out;

  out << "(lie)";
  return out.str();
}

string LieCommand::getCommandName() const
{
  return "lie";
}
/*********************************************************************
 ************************* Ready Command ******************************
 *********************************************************************
 */

ReadyCommand::ReadyCommand( )
{
}

string ReadyCommand::toString() const
{
  ostringstream out;

  out << "(ready)";
  return out.str();
}

string ReadyCommand::getCommandName() const
{
  return "ready";
}
/*********************************************************************
 ************************* Run Command ******************************
 *********************************************************************
 */

RunCommand::RunCommand( double velX, double velY )
{
  m_velX = velX;
  m_velY = velY;
}

double RunCommand::getVelX() const
{
  return m_velX;
}

double RunCommand::getVelY() const
{
  return m_velY;
}

string RunCommand::toString() const
{
  ostringstream out;

  out << "(run " << m_velX << " " << m_velY << ")";
  return out.str();
}

string RunCommand::getCommandName() const
{
  return "run";
}
/*********************************************************************
 ************************* Evade Command ******************************
 *********************************************************************
 */

EvadeCommand::EvadeCommand( double velX, double velY )
{
  m_velX = velX;
  m_velY = velY;
}

double EvadeCommand::getVelX() const
{
  return m_velX;
}

double EvadeCommand::getVelY() const
{
  return m_velY;
}

string EvadeCommand::toString() const
{
  ostringstream out;

  out << "(evade " << m_velX << " " << m_velY << ")";
  return out.str();
}

string EvadeCommand::getCommandName() const
{
  return "evade";
}

/*********************************************************************
 ************************* Shoot Command *****************************
 *********************************************************************
 */


ShootCommand::ShootCommand( double ang )
{
  m_ang = ang;
}

double ShootCommand::getAng() const
{
  return m_ang;
}

string ShootCommand::toString() const
{
  ostringstream out;
  out << "(shoot " << m_ang << ")";
  return out.str(); 
}

string ShootCommand::getCommandName() const
{
  return "shoot";
}


/*********************************************************************
 ************************* XShoot Command ****************************
 *********************************************************************
 */


XShootCommand::XShootCommand( double ang )
{
  m_ang = ang;
}

double XShootCommand::getAng() const
{
  return m_ang;
}

string XShootCommand::toString() const
{
  ostringstream out;
  out << "(xshoot " << m_ang << ")";
  return out.str(); 
}

string XShootCommand::getCommandName() const
{
  return "xshoot";
}

/*********************************************************************
 ************************* Mine Command ******************************
 *********************************************************************
 */


MineCommand::MineCommand( double x, double y )
{
  m_x = x;
  m_y = y;
}

double MineCommand::getX() const
{
  return m_x;
}

double MineCommand::getY() const
{
  return m_y;
}

string MineCommand::toString() const
{
  ostringstream out;
  out << "(mine " << m_x << " " << m_y << ")";
  return out.str(); 
}

string MineCommand::getCommandName() const
{
  return "mine";
}

/*********************************************************************
 ************************* Demine Command *****************************
 *********************************************************************
 */


DemineCommand::DemineCommand( double x, double y )
{
  m_x = x;
  m_y = y;
}

double DemineCommand::getX() const
{
  return m_x;
}

double DemineCommand::getY() const
{
  return m_y;
}

string DemineCommand::toString() const
{
  ostringstream out;
  out << "(demine " << m_x << " " << m_y << ")";
  return out.str(); 
}

string DemineCommand::getCommandName() const
{
  return "demine";
}

/*********************************************************************
 ************************* Heal Command ******************************
 *********************************************************************
 */


HealCommand::HealCommand( int id )
{
  m_id = id;
}

int HealCommand::getId() const
{
  return m_id;
}

string HealCommand::toString() const
{
  ostringstream out;
  out << "(heal " << m_id << ")";
  return out.str(); 
}

string HealCommand::getCommandName() const
{
  return "heal";
}

/*********************************************************************
 ************************* Support Command ******************************
 *********************************************************************
 */


SupportCommand::SupportCommand( int id )
{
  m_id = id;
}

int SupportCommand::getId() const
{
  return m_id;
}

string SupportCommand::toString() const
{
  ostringstream out;
  out << "(support " << m_id << ")";
  return out.str(); 
}

string SupportCommand::getCommandName() const
{
  return "support";
}
