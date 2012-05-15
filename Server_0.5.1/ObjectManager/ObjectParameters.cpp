#include "ObjectParameters.h"

using namespace std;

map<string, Options> *ObjectParameters::wheatherEffect = new map<string, Options>();
map<string, Options> *ObjectParameters::groundEffect = new map<string, Options>();
map<string, Options> *ObjectParameters::solActEffect = new map<string, Options>();


void ObjectParameters::initParameters()
{
  (*wheatherEffect)["sunny"]["soldier"] = 1.0;
  (*wheatherEffect)["morning"]["soldier"] = 1.0;  
  (*wheatherEffect)["night"]["soldier"] = 0.9;  
  (*wheatherEffect)["rainy"]["soldier"] = 0.8;
  (*wheatherEffect)["snowy"]["soldier"] = 0.7;
  (*wheatherEffect)["storm"]["soldier"] = 0.6;
  (*wheatherEffect)["fog"]["soldier"] = 0.5;

  (*groundEffect)["road"]["soldier"] = 1.0;
  (*groundEffect)["soil"]["soldier"] = 1.0;  
  (*groundEffect)["sand"]["soldier"] = 1.0;  
  (*groundEffect)["lake"]["soldier"] = 1.0;  
  (*groundEffect)["jungle"]["soldier"] = 0.5;  
  (*groundEffect)["rocky"]["soldier"] = 1.0;
  (*groundEffect)["mud"]["soldier"] = 1.0; 
  (*groundEffect)["river"]["soldier"] = 1.0;
  (*groundEffect)["mountain"]["soldier"] = 1.0;
  (*groundEffect)["swamp"]["soldier"] = 0.8;  
  (*groundEffect)["mine"]["soldier"] = 0.0;


  (*solActEffect)["stand"]["firePower"] = 1.0;
  (*solActEffect)["stand"]["fireAccr"] = 1.0;
  (*solActEffect)["stand"]["speed"] = 0.0;
  (*solActEffect)["stand"]["moveNoise"] = 0.0;
  (*solActEffect)["stand"]["fireNoise"] = 1.0;
  (*solActEffect)["stand"]["weaponRange"] = 1.0;
  (*solActEffect)["stand"]["dataRange"] = 1.0;
  (*solActEffect)["stand"]["coldArmRange"] = 1.0;
  (*solActEffect)["stand"]["beingSeen"] = 0.9;
  (*solActEffect)["stand"]["maxVision"] = 1.0;
  (*solActEffect)["stand"]["spirit_decay"] = 0.0;
  (*solActEffect)["stand"]["tiredness_decay"] = -0.001;
  (*solActEffect)["stand"]["wellness_decay"] = 0.0;
  (*solActEffect)["stand"]["stress_decay"] = 0.0;

  (*solActEffect)["lie"]["firePower"] = 1.0;
  (*solActEffect)["lie"]["fireAccr"] = 1.0;
  (*solActEffect)["lie"]["speed"] = 0.0;
  (*solActEffect)["lie"]["moveNoise"] = 0.0;
  (*solActEffect)["lie"]["fireNoise"] = 1.0;
  (*solActEffect)["lie"]["weaponRange"] = 1.0;
  (*solActEffect)["lie"]["dataRange"] = 1.0;
  (*solActEffect)["lie"]["coldArmRange"] = 1.0;
  (*solActEffect)["lie"]["beingSeen"] = 0.5;
  (*solActEffect)["lie"]["maxVision"] = 0.8;
  (*solActEffect)["lie"]["spirit_decay"] = 0.0;
  (*solActEffect)["lie"]["tiredness_decay"] = -0.002;
  (*solActEffect)["lie"]["wellness_decay"] = 0.0;
  (*solActEffect)["lie"]["stress_decay"] = 0.0;

  (*solActEffect)["walk"]["firePower"] = 1.0;
  (*solActEffect)["walk"]["fireAccr"] = 0.8;
  (*solActEffect)["walk"]["speed"] = 0.4;
  (*solActEffect)["walk"]["moveNoise"] = 0.0;
  (*solActEffect)["walk"]["fireNoise"] = 1.0;
  (*solActEffect)["walk"]["weaponRange"] = 1.0;
  (*solActEffect)["walk"]["dataRange"] = 1.0;
  (*solActEffect)["walk"]["coldArmRange"] = 1.0;
  (*solActEffect)["walk"]["beingSeen"] = 1.0;
  (*solActEffect)["walk"]["maxVision"] = 1.0;
  (*solActEffect)["walk"]["spirit_decay"] = 0.0;
  (*solActEffect)["walk"]["tiredness_decay"] = 0.0002;
  (*solActEffect)["walk"]["wellness_decay"] = 0.0;
  (*solActEffect)["walk"]["stress_decay"] = 0.0;

  (*solActEffect)["rest"]["firePower"] = 0.0;
  (*solActEffect)["rest"]["fireAccr"] = 0.0;
  (*solActEffect)["rest"]["speed"] = 0.0;
  (*solActEffect)["rest"]["moveNoise"] = 0.0;
  (*solActEffect)["rest"]["fireNoise"] = 1.0;
  (*solActEffect)["rest"]["weaponRange"] = 1.0;
  (*solActEffect)["rest"]["dataRange"] = 1.0;
  (*solActEffect)["rest"]["coldArmRange"] = 1.0;
  (*solActEffect)["rest"]["beingSeen"] = 0.4;
  (*solActEffect)["rest"]["maxVision"] = 0.8;
  (*solActEffect)["rest"]["spirit_decay"] = 0.002;
  (*solActEffect)["rest"]["tiredness_decay"] = -0.002;
  (*solActEffect)["rest"]["wellness_decay"] = 0.0001;
  (*solActEffect)["rest"]["stress_decay"] = -0.002;

  (*solActEffect)["run"]["firePower"] = 1.0;
  (*solActEffect)["run"]["fireAccr"] = 0.7;
  (*solActEffect)["run"]["speed"] = 1.0;
  (*solActEffect)["run"]["moveNoise"] = 1.0;
  (*solActEffect)["run"]["fireNoise"] = 1.0;
  (*solActEffect)["run"]["weaponRange"] = 1.0;
  (*solActEffect)["run"]["dataRange"] = 1.0;
  (*solActEffect)["run"]["coldArmRange"] = 1.0;
  (*solActEffect)["run"]["beingSeen"] = 1.0;
  (*solActEffect)["run"]["maxVision"] = 0.9;
  (*solActEffect)["run"]["spirit_decay"] = 0.0;
  (*solActEffect)["run"]["tiredness_decay"] = 0.0005;
  (*solActEffect)["run"]["wellness_decay"] = 0.0;
  (*solActEffect)["run"]["stress_decay"] = 0.0;

  (*solActEffect)["evade"]["firePower"] = 1.0;
  (*solActEffect)["evade"]["fireAccr"] = 0.6;
  (*solActEffect)["evade"]["speed"] = 0.7;
  (*solActEffect)["evade"]["moveNoise"] = 1.0;
  (*solActEffect)["evade"]["fireNoise"] = 1.0;
  (*solActEffect)["evade"]["weaponRange"] = 1.0;
  (*solActEffect)["evade"]["dataRange"] = 1.0;
  (*solActEffect)["evade"]["coldArmRange"] = 1.0;
  (*solActEffect)["evade"]["beingSeen"] = 1.0;
  (*solActEffect)["evade"]["maxVision"] = 0.8;
  (*solActEffect)["evade"]["spirit_decay"] = -0.004;
  (*solActEffect)["evade"]["tiredness_decay"] = 0.002;
  (*solActEffect)["evade"]["wellness_decay"] = 0.0;
  (*solActEffect)["evade"]["stress_decay"] = 0.01;

  (*solActEffect)["ready"]["firePower"] = 1.0;
  (*solActEffect)["ready"]["fireAccr"] = 0.9;
  (*solActEffect)["ready"]["speed"] = 0.0;
  (*solActEffect)["ready"]["moveNoise"] = 0.0;
  (*solActEffect)["ready"]["fireNoise"] = 1.0;
  (*solActEffect)["ready"]["weaponRange"] = 1.0;
  (*solActEffect)["ready"]["dataRange"] = 1.0;
  (*solActEffect)["ready"]["coldArmRange"] = 1.0;
  (*solActEffect)["ready"]["beingSeen"] = 0.9;
  (*solActEffect)["ready"]["maxVision"] = 1.0;
  (*solActEffect)["ready"]["spirit_decay"] = 0.0;
  (*solActEffect)["ready"]["tiredness_decay"] = 0.0;
  (*solActEffect)["ready"]["wellness_decay"] = 0.0;
  (*solActEffect)["ready"]["stress_decay"] = 0.0;

}

