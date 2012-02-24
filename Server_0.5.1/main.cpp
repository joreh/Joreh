#include <QtCore/QCoreApplication>
#include <iostream>

#include "Utilities/SwarmException.h"
#include "Kernel/Kernel.h"

using namespace std;

int main( int argc, char *argv[] )
{
  QCoreApplication app(argc, argv);

  Kernel kernel;
  

  return app.exec();
}


