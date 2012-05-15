#ifndef __OBJECT_H
#define __OBJECT_H

#include "Geom/Vector3D.h"
#include "Model/model.h"
#include <string>
#include <map>

class Object
{
public:
  Object( unsigned id = 0, Vector3D pos = Vector3D( 0.0, 0.0 ),
                           Vector3D vel = Vector3D( 0.0, 0.0 ), 
                           std::string teamName = "",
                           Model* fm = NULL );

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
  void printAgentAttr();

  void setTeamName( std::string name );
  const std::string &getTeamName() const;
  double getMaxSpeed() const;
  void setMaxSpeed(double speed);

  Model *getModel() const;

  double getAttrVal( std::string attr );
  void setAttrVal( std::string attr, double value );

/*  void setStateCoef(double sc=0);
  double getStateCoef() const;
  double getAmo() const;
  void setAmo(double amo);
  double getFood() const;
  void setFood(double food);	
  double getFirePower() const;
  void setFirePower(double firePower);
  double getFireAccr() const;
  void setFireAccr(double fireAccr);	
  double getFireNoise() const;
  void setFireNoise(double fireNoise);
  double getWeaponRange() const;
  void setWeaponRange(double range);  
  double getColdArmRange() const;
  void setColdArmRange(double car);
  double getSoundRange() const;
  void setSoundRange(double sr);
  double getDataRange() const;
  void setDataRange(double dataRange);	
  double getEffectiveVision() const;
  void setEffectiveVision(double effVis);
  double getMaxVision() const;
  void setMaxVision(double maxVision);
  double getBeingSeen() const;
  void setBeingSeen(double bs);
  double getMoveNoise() const;
  void setMoveNoise(double mn);
  double getSpirit() const;
  void setSpirit(double spirit);
  double getTiredness() const;
  void setTiredness(double t);
  double getWellness() const;
  void setWellness(double wellness);
  double getStress() const;
  void setStress(double stress);
  double getVision() const;
  void setVision(double vision);*/

private:
  std::string m_teamName;
  Vector3D m_pos;
  Vector3D m_vel;
  unsigned m_id;

  Model *m_model;

  std::map<std::string, double> m_attrVal;

/*  double m_stateCoef;
  double m_amo;
  double m_food;
  double m_firePower;
  double m_fireAccr;
  double m_speed;
  double m_fireNoise;
  double m_weaponRange;
  double m_coldArmRange;
  double m_soundRange;
  double m_dataRange;
  double m_effectiveVision;
  double m_maxVision;
  double m_vision;
  double m_beingSeen;
  double m_moveNoise;
  double m_spirit;
  double m_tiredNess;
  double m_wellness;
  double m_stress;
  double m_posFitness;
  unsigned m_modelId;
  unsigned m_id;*/

};

#endif

