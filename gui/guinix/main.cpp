#include <QApplication>
#include "fenetre.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    Fenetre *f = new Fenetre();
    return app.exec();
}
