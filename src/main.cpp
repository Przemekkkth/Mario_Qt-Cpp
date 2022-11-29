#include <QApplication>
#include <QIcon>
#include "view.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);

    View v;
    v.setWindowTitle("Mario Qt/C++ World 1-1");
    v.show();

    return a.exec();
}
