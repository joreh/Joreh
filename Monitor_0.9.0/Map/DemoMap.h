#ifndef DEMOMAP_H
#define DEMOMAP_H

#include <QColor>

namespace Demo
{
enum LandType {grass,river,land,swamp,camp,tree,tundra,lake,rocky};

int** GetHeight();

int** GetRamp();

QColor GetColor( LandType lanType ,int height,int x,int y);

LandType** GetLandType();
}

#endif // DEMOMAP_H
