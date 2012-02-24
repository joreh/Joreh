#ifndef __WORLDMODEL_H
#define __WORLDMODEL_H

#include "Object.h"
#include "Field.h"
#include <vector>

class WorldModel
{
public:
  WorldModel();

  const Object &getObject( unsigned id );
  Object &setObject( unsigned id );

  unsigned getNumOfObjects() const;

  void createObject();
  void addObject( Object obj );

  int getCurCycle() const;
  void setCurCycle( int curCycle );

  const Field &getField() const;
  Field &setField();

private:
  std::vector<Object> m_objects;
  Field m_field;

  int m_curCycle;

};

#endif
