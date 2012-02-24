#include <QtGui/QApplication>
#include "GUI/MainWindow.h"
#include "Logger/Logger.h"

#include "WorldModel/WorldModel.h"
#include <fstream>

using namespace std;

int main(int argc, char *argv[])
{

  QApplication app(argc, argv);
  MainWindow window;
  window.show();

  return app.exec();
}
