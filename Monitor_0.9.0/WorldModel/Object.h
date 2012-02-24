#ifndef __OBJECT_H
#define __OBJECT_H

#include "Geom/Vector3D.h"
#include <string>

class Object
{
public:
  Object( unsigned id = 0, Vector3D pos = Vector3D( 0.0, 0.0 ),
                           Vector3D vel = Vector3D( 0.0, 0.0 ) );

  Vector3D getPosition() const;

  Vector3D getVelocity() const;

  double getPosFitness() const;


  int getModelID() const;

  void update( Vector3D position, double fitness ,int model_id);

  std::string toString() const;

  unsigned getID() const;

private:

  Vector3D m_pos;

  Vector3D m_vel;

  double m_posFitness;

  unsigned m_id;
  int m_modelid;

};

#endif

