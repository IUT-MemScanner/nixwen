#include <QApplication>
#include <QtWidgets>
#include "rsz.h"

int main(int argc, char *argv[]){
    QApplication app(argc, argv);
    
    // les widgets "parties de l'application" et leurs layouts
    ResizableFrame panelduhaut;
    ResizableFrame paneldubas;
	panelduhaut.setStyleSheet("background-color: red");
	paneldubas.setStyleSheet("background-color: blue");


	QBoxLayout *lay1 = new QVBoxLayout;
	QBoxLayout *lay2 = new QVBoxLayout;
	
	panelduhaut.setLayout(lay1);
    paneldubas.setLayout(lay2);

    // labels de test
    QLabel *l1 = new QLabel(QString::number(1111111111));
    QLabel *l2 = new QLabel(QString::number(2222222222));
    lay1->addWidget(l1);
	lay2->addWidget(l2);

    // le layout
    QGridLayout *lay = new QGridLayout;
	lay->setSpacing(0);
	lay->setMargin(0);
	lay->addWidget(&panelduhaut, 0, 0, 1, 1);
	lay->addWidget(&paneldubas, 1, 0, 1, 1);

	// le widget de plus haut niveau (fenêtre entière)
    QWidget w;
	w.resize(300, 70);
	w.setWindowTitle("Things in me are RESIZABLE ! :O");
	w.setLayout(lay);
	w.show();

	return app.exec();
}
