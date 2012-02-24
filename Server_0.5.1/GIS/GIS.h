#ifndef __GIS_H
#define __GIS_H

#include "Vector3D.h"
#include <QImage>
#include <string>

enum GroundType
{
  // it should be filled with the names of GIS layers
};


// implement map which will be sent to the agents
class Map
{
public:


  std::string toString(); 
  // this string will be sent to the agents through network

private:

};

class GIS
{
public:

  GIS( std::string host, std::string db,
         std::string user, std::string passwd );
  ~GIS();

  double getHeight( Vector3D pos ) const;
  bool isObservable( Vector3D orgPos, Vector3D destPos ) const;
  bool canGo( Vector3D source, Vector3D target ) const;
  GroundType getGroundType( Vector3D pos ) const;
  Map getMap() const;

  void update();

  void setAgentPosition( Vector3D pos );
  // color = R ^ 3 + G ^ 2 + B
  void setAgentTeamColor( unsigned num, unsigned color );
  void setAgentTypeColor( unsigned num, unsigned color );
  

private:


};


#endif

