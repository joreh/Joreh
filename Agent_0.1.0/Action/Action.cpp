#include "Action/Action.h"
#include <sstream>

using namespace std;
StandupAction::StandupAction()
{

}
RunAction::RunAction()
{

}
FleeAction::FleeAction()
{

}
WarmupAction::WarmupAction()
{

}
LieAction::LieAction()
{

}

InitAction::InitAction( string teamName, string modelName )
{
  setTeamName( teamName );
  setModelName( modelName );
}

void InitAction::setTeamName( string teamName )
{
  m_teamName = teamName;
}

string InitAction::getTeamName() const
{
  return m_teamName;
}

void InitAction::setModelName( string modelName )
{
  m_modelName = modelName;
}

string InitAction::getModelName() const
{
  return m_modelName;
}

string InitAction::toString() const
{
  ostringstream out;

  out << "(init \"" << m_teamName << "\" \"" << m_modelName << "\")";

  return out.str();
}
string WalkAction::toString() const
{
    ostringstream out;
    out << showpoint << fixed << "(walk " << posX << " " << posY << ")";
    return out.str();
}
WalkAction::WalkAction(double x, double y)
{
    posX = x;
    posY = y;
}
void WalkAction::setX(double e){
    posX = e;
}
void WalkAction::setY(double e){
    posY = e;
}

MoveAction::MoveAction( double velX, double velY )
{
  setVelX( velX );
  setVelY( velY );
}

void MoveAction::setVelX( double velX )
{
  m_velX = velX;
}

double MoveAction::getVelX() const
{
  return m_velX;
}

void MoveAction::setVelY( double velY )
{
  m_velY = velY;
}

double MoveAction::getVelY() const
{
  return m_velY;
}

string MoveAction::toString() const
{
  ostringstream out;
  out << showpoint << fixed << "(move " << m_velX << " " << m_velY << ")";
  return out.str();
}

