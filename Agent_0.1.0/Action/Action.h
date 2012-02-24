#ifndef __ACTION_H
#define __ACTION_H

#include <string>

class Action
{
public:
  virtual std::string toString() const = 0;
};
class StandupAction : public Action
{
public:
    StandupAction();
};
class WalkAction : public Action
{
public:
    WalkAction();
    WalkAction(double,double);
    void setX(double);
    void setY(double);
    std::string toString() const;
private:
    double posX;
    double posY;

};

class RunAction : public Action
{
public:
    RunAction();
};
class FleeAction : public Action
{
public:
    FleeAction();
};
class WarmupAction : public Action
{
public:
    WarmupAction();
};
class LieAction : public Action
{
public:
    LieAction();
};

class InitAction : public Action
{
public:
  InitAction( std::string teamName = "", std::string modelName = "" );

  void setTeamName( std::string teamName );
  std::string getTeamName() const;

  void setModelName( std::string modelName );
  std::string getModelName() const;

  std::string toString() const;

private:
  std::string m_teamName;
  std::string m_modelName;
};

class MoveAction : public Action
{
public:
  MoveAction( double velX, double velY );

  void setVelX( double velX );
  double getVelX() const;

  void setVelY( double velY );
  double getVelY() const;

  std::string toString() const;

private:
  double m_velX;
  double m_velY;
};


#endif

