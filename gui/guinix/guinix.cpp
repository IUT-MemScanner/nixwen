#include <QtWidgets/QApplication>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtWidgets/QLabel>

using namespace std;

int main(int argv, char **args){
	
	// déclarations
	int hp1 = 42;
	QApplication app(argv, args);

	// éléments
	QLabel *l1 = new QLabel(QString::number(hp1));
	
	QPushButton *bfermer = new QPushButton("heal 33");

	// linkage des handlers (SIGNAL -> SLOTS)
	QObject::connect(bfermer, SIGNAL(clicked()), qApp, SLOT(quit()));
	//QObject::connect(b1_plus_33, &QPushButton::clicked, [&hp1, &l1]{hp1 += 33; l1->setText(QString::number(hp1));});

	
	// fenêtre
	QWidget w;
	w.resize(300, 70);
	w.setWindowTitle("Nixwen's favorite dummy");
	w.setLayout(lay);
	w.show();
	
	return app.exec();
}
