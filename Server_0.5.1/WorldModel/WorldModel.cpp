#include "WorldModel.h"
#include "Utilities/SwarmException.h"

WorldModel::WorldModel()
{
  m_curCycle = 0;
}

const Object &WorldModel::getObject( unsigned id )
{
  if( id == 0 || id > m_objects.size() )
    throw SwarmException( "(WorldModel::getObject) id is not found " );

  return m_objects[id-1];
}

Object &WorldModel::setObject( unsigned id )
{
  if( id == 0 || id > m_objects.size() )
    throw SwarmException( "(WorldModel::getObject) id is not found " );

  return m_objects[id-1];
}


unsigned WorldModel::getNumOfObjects() const
{
  return m_objects.size();
}

void WorldModel::createObject()
{
  m_objects.push_back(
      Object( m_objects.size() + 1,
      Vector3D( 0.0, 0.0 ),
      Vector3D( 0.0, 0.0 ) ) );
}

void WorldModel::addObject( Object obj )
{
  obj.setID( m_objects.size() + 1 );
  m_objects.push_back( obj );
}

int WorldModel::getCurCycle() const
{
  return m_curCycle;
}

void WorldModel::setCurCycle( int curCycle )
{
  m_curCycle = curCycle;
}

const Field &WorldModel::getField() const
{
  return m_field;
}

Field &WorldModel::setField()
{
  return m_field;
}

unsigned WorldModel::getTeamId( string teamName )
{
  return m_teamId[teamName];
}

map<string, unsigned> &WorldModel::setTeamIdMap()
{
  return m_teamId;
}

unsigned WorldModel::setupTeam( string teamName )
{
  if( m_teamId.find( teamName ) != m_teamId.end() )
    return 0;

  m_teamId[teamName] = m_teamId.size();
  return m_teamId[teamName];
}

