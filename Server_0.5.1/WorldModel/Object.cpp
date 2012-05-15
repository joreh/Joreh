#include "Object.h"
#include <iostream>
#include <sstream>

using namespace std;

Object::Object( unsigned id, Vector3D pos, Vector3D vel, 
                string teamName, Model* fm )
{
  m_pos = pos;
  m_vel = vel;
  m_id = id;
  m_model = fm;
  m_attrVal = fm->getAttrValMap();

  setTeamName( teamName );

  cout << m_attrVal.size() << endl;

  printAgentAttr();
}


void Object::printAgentAttr()
{
  for( map<string, double>::iterator itr = m_attrVal.begin();
       itr != m_attrVal.end(); itr ++ )
    cout << itr->first << "=" << itr->second << " ";
  cout << endl;
}

void Object::setPosition( Vector3D position )
{
  m_pos = position;
}

Vector3D Object::getPosition() const
{
  return m_pos;
}

void Object::setVelocity( Vector3D vel )
{
  m_vel = vel;
}

Vector3D Object::getVelocity() const
{
  return m_vel;
}

void Object::setID( unsigned id )
{
  m_id = id;
}

unsigned Object::getID() const
{
  return m_id;
}

void Object::setTeamName( string teamName )
{
  m_teamName = teamName;
}

const string &Object::getTeamName() const
{
  return m_teamName;
}

string Object::toString() const
{
  ostringstream out;

  out << "(" << m_id << " " << m_pos.getX() << " "
      << m_pos.getY() << ")";

  return out.str();
}

Model *Object::getModel() const
{
  return m_model;
}

double Object::getAttrVal( string attr )
{
  if( m_attrVal.find( attr ) == m_attrVal.end() )
    cerr << "no " << attr << " attribute" << endl;
  return m_attrVal[attr];
}

void Object::setAttrVal( string attr, double value )
{
  m_attrVal[attr] = value;
}

/*
double Object::getMaxSpeed() const
{

  return m_speed;
}

void Object::setMaxSpeed(double speed)
{		
  m_speed = speed;
}

double Object::getStateCoef() const
{
  return m_stateCoef;
}
void Object::setStateCoef(double sc) 
{
  m_stateCoef = sc;
}

double Object::getAmo() const
{
  return m_amo;
}

void Object::setAmo( double amo )
{
  m_amo = amo;
}

double Object::getFood() const
{
  return m_food;
}

void Object::setFood( double food )
{
  m_food = food;
}

double Object::getFirePower() const
{
  return m_firePower;
}

void Object::setFirePower( double firePower )
{
  m_firePower = firePower;
}

double Object::getFireAccr() const
{
  return m_fireAccr;
}

void Object::setFireAccr( double fireAccr )
{
  m_fireAccr = fireAccr;
}

double Object::getFireNoise() const
{
  return m_fireNoise;
}

void Object::setFireNoise( double fireNoise )
{
  m_fireNoise = fireNoise;
}

double Object::getWeaponRange() const
{
  return m_weaponRange;
}

void Object::setWeaponRange( double weaponRange )
{
  m_weaponRange = weaponRange;
}

double Object::getColdArmRange() const
{
  return m_coldArmRange;
}

void Object::setColdArmRange( double coldArmRange )
{
  m_coldArmRange = coldArmRange;
}

double Object::getSoundRange() const
{
  return m_soundRange;
}

void Object::setSoundRange( double soundRange )
{
  m_soundRange = soundRange;
}

double Object::getDataRange() const
{
  return m_dataRange;
}

void Object::setDataRange( double dataRange )
{
  m_dataRange = dataRange;
}

double Object::getEffectiveVision() const
{
  return m_effectiveVision;
}

void Object::setEffectiveVision(  double effectiveVision )
{
  m_effectiveVision = effectiveVision;
}

double Object::getMaxVision() const
{
  return m_maxVision;
}

void Object::setMaxVision( double maxVision )
{
  m_maxVision = maxVision;
}

double Object::getBeingSeen() const
{
  return m_beingSeen;
}

void Object::setBeingSeen( double beingSeen )
{
  m_beingSeen = beingSeen;
}

double Object::getMoveNoise() const
{
  return m_moveNoise;
}

void Object::setMoveNoise( double moveNoise )
{
  m_moveNoise = moveNoise;
}

double Object::getSpirit() const
{
  return m_spirit;
}

void Object::setSpirit( double spirit )
{
  m_spirit = spirit;
}

double Object::getTiredness() const
{
  return m_tiredNess;
}

void Object::setTiredness( double tiredness )
{
  m_tiredNess = tiredness;
}

double Object::getWellness() const
{
  return m_wellness;
}

void Object::setWellness( double wellness )
{
  m_wellness = wellness;
}

double Object::getStress() const
{
  return m_stress;
}

void Object::setStress( double stress )
{
  m_stress = stress;
}

double Object::getVision() const
{
  return m_vision;
}

void Object::setVision( double vision )
{
  m_vision = vision;
}*/
