#include "WorldModel.h"
#include "SwarmException.h"

WorldModel::WorldModel()
{
  m_bFinished = false;
}

const Object &WorldModel::getObject( unsigned id )
{
  if( m_objects.find( id ) == m_objects.end() )
    throw SwarmException( "(WorldModel::getObject) id is not found " );

  return m_objects[id];
}

const Object &WorldModel::getObjectByIndex( unsigned indx )
{
  if( (int)indx >= m_objectsIndx.size() )
    throw SwarmException( "(WorldModel::getObjectByIndex) indx is out of"
                          " bound " );

  return m_objects[m_objectsIndx[indx]];
}

unsigned WorldModel::getNumOfObjects() const
{
  return m_objectsIndx.size();
}

Object &WorldModel::setObject( unsigned id )
{
  if( m_objects.find( id ) == m_objects.end() )
    throw SwarmException( "(WorldModel::setObject) id is not found " );

  return m_objects[id];
}

void WorldModel::createObject( unsigned id )
{
  if( m_objects.find( id ) != m_objects.end() )
    throw SwarmException( "(WorldModel::createObject) id exists " );

  m_objects[id] = Object( id,
      Vector3D( 0.0, 0.0 ),
      Vector3D( 0.0, 0.0 ) );


  m_objectsIndx.push_back( id );
}

void WorldModel::addObject( Object obj )
{
  if( m_objects.find( obj.getID() ) != m_objects.end() )
    throw SwarmException( "(WorldModel::createObject) id exists " );

  m_objects[obj.getID()] = obj;

  //cout << "add " << m_objectsIndx.size() << " " << obj.getID() << endl;
  m_objectsIndx.push_back( obj.getID() );
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

int WorldModel::getMonitorID() const
{
  return m_monitorID;
}

void WorldModel::setMonitorID( int id )
{
  m_monitorID = id;
}

void WorldModel::gameFinished()
{
  m_bFinished = false;
}

bool WorldModel::isGameFinished() const
{
  return m_bFinished;
}

