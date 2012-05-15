#ifndef __OBJECT_PARAMETERS_H
#define __OBJECT_PARAMETERS_H

#include <map>
#include <string>

#define Options std::map<std::string, double>

class ObjectParameters
{
  public:
  static void initParameters();

  static std::map<std::string, Options> *groundEffect;
  static std::map<std::string, Options> *wheatherEffect;
  static std::map<std::string, Options> *solActEffect;
};

#endif

