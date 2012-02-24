#include "Object.h"
#include <sstream>

using namespace std;

Object::Object( unsigned id, Vector3D pos, Vector3D vel )
{
  m_id = id;
  m_pos = pos;
  m_vel = vel;
}

Vector3D Object::getPosition() const
{
  return m_pos;
}

Vector3D Object::getVelocity() const
{
  return m_vel;
}

double Object::getPosFitness() const
{
  return m_posFitness;
}
int Object::getModelID()const
{
    return m_modelid;
}

void Object::update( Vector3D position, double fitness , int model_id )
{
  m_vel = position - m_pos;
  m_pos = position;
  m_posFitness = fitness;
  m_modelid = model_id;
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

