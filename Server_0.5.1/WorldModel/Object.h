#ifndef __OBJECT_H
#define __OBJECT_H

#include "Geom/Vector3D.h"
#include <string>

class Object
{
public:
  Object( unsigned id = 0, Vector3D pos = Vector3D( 0.0, 0.0 ),
                           Vector3D vel = Vector3D( 0.0, 0.0 ),unsigned mId = 0 );

  void setPosition( Vector3D position );
  Vector3D getPosition() const;

  void setVelocity( Vector3D vel );
  Vector3D getVelocity() const;

  void setPosFitness( double fitness );
  double getPosFitness() const;

  void setID( unsigned id );
  unsigned getID() const;
  unsigned getModelId() const;

  std::string toString() const;


private:

  Vector3D m_pos;

  Vector3D m_vel;

  double m_posFitness;
  unsigned m_modelId;
  unsigned m_id;

};

#endif

