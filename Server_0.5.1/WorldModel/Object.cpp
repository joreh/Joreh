#include "Object.h"
#include <sstream>

using namespace std;

Object::Object( unsigned id, Vector3D pos, Vector3D vel,unsigned mId )
{
  m_id = id;
  m_pos = pos;
  m_vel = vel;
  m_modelId = mId;

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

void Object::setPosFitness( double fitness )
{
  m_posFitness = fitness;
}

double Object::getPosFitness() const
{
  return m_posFitness;
}

void Object::setID( unsigned id )
{
  m_id = id;
}

unsigned Object::getModelId() const
{

    return m_modelId;
}

unsigned Object::getID() const
{
  return m_id;
}

string Object::toString() const
{
  ostringstream out;

  out << "(" << m_id << " " << m_pos.getX() << " "
      << m_pos.getY() << " " << m_posFitness << ")";

  return out.str();
}
