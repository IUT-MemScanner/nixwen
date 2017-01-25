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
	int hp1 = 42, hp2 = 42;
	QApplication app(argv, args);

	// éléments
	QLabel *l1 = new QLabel(QString::number(hp1));
	l1->setAlignment(Qt::AlignCenter);
	QPushButton *b1_plus_33 = new QPushButton("heal 33");
	QPushButton *b1_plus_3 = new QPushButton("heal 3");
	QPushButton *b1_plus_1 = new QPushButton("heal 1");
	QPushButton *b1_moins_1 = new QPushButton("hit 1");
	QPushButton *b1_moins_3 = new QPushButton("hit 3");
	QPushButton *b1_moins_33 = new QPushButton("hit 33");
	
	QLabel *l2 = new QLabel(QString::number(hp2));
	l2->setAlignment(Qt::AlignCenter);
	QPushButton *b2_plus_33 = new QPushButton("heal 33");
	QPushButton *b2_plus_3 = new QPushButton("heal 3");
	QPushButton *b2_plus_1 = new QPushButton("heal 1");
	QPushButton *b2_moins_1 = new QPushButton("hit 1");
	QPushButton *b2_moins_3 = new QPushButton("hit 3");
	QPushButton *b2_moins_33 = new QPushButton("hit 33");

	// handlers
	QObject::connect(b1_plus_33, &QPushButton::clicked, [&hp1, &l1]{hp1 += 33; l1->setText(QString::number(hp1));});
	QObject::connect(b1_plus_3, &QPushButton::clicked, [&hp1, &l1]{hp1 += 3; l1->setText(QString::number(hp1));});
	QObject::connect(b1_plus_1, &QPushButton::clicked, [&hp1, &l1]{hp1++; l1->setText(QString::number(hp1));});
	QObject::connect(b1_moins_1, &QPushButton::clicked, [&hp1, &l1]{hp1--; l1->setText(QString::number(hp1));});
	QObject::connect(b1_moins_3, &QPushButton::clicked, [&hp1, &l1]{hp1 -= 3; l1->setText(QString::number(hp1));});
	QObject::connect(b1_moins_33, &QPushButton::clicked, [&hp1, &l1]{hp1 -= 33; l1->setText(QString::number(hp1));});

	QObject::connect(b2_plus_33, &QPushButton::clicked, [&hp2, &l2]{hp2 += 33; l2->setText(QString::number(hp2));});
	QObject::connect(b2_plus_3, &QPushButton::clicked, [&hp2, &l2]{hp2 += 3; l2->setText(QString::number(hp2));});
	QObject::connect(b2_plus_1, &QPushButton::clicked, [&hp2, &l2]{hp2++; l2->setText(QString::number(hp2));});
	QObject::connect(b2_moins_1, &QPushButton::clicked, [&hp2, &l2]{hp2--; l2->setText(QString::number(hp2));});
	QObject::connect(b2_moins_3, &QPushButton::clicked, [&hp2, &l2]{hp2 -= 3; l2->setText(QString::number(hp2));});
	QObject::connect(b2_moins_33, &QPushButton::clicked, [&hp2, &l2]{hp2 -= 33; l2->setText(QString::number(hp2));});
	
	// layout
	QGridLayout *lay = new QGridLayout;
	lay->setSpacing(0);
	lay->setMargin(0);
	
	lay->addWidget(l1, 0, 0, 1, 1);
	lay->addWidget(b1_plus_33, 1, 0, 1, 1);
	lay->addWidget(b1_plus_3, 2, 0, 1, 1);
	lay->addWidget(b1_plus_1, 3, 0, 1, 1);
	lay->addWidget(b1_moins_1, 4, 0, 1, 1);
	lay->addWidget(b1_moins_3, 5, 0, 1, 1);
	lay->addWidget(b1_moins_33, 6, 0, 1, 1);

	lay->addWidget(l2, 0, 1, 1, 1);
	lay->addWidget(b2_plus_33, 1, 1, 1, 1);
	lay->addWidget(b2_plus_3, 2, 1, 1, 1);
	lay->addWidget(b2_plus_1, 3, 1, 1, 1);
	lay->addWidget(b2_moins_1, 4, 1, 1, 1);
	lay->addWidget(b2_moins_3, 5, 1, 1, 1);
	lay->addWidget(b2_moins_33, 6, 1, 1, 1);

	// fenêtre
	QWidget w;
	w.resize(300, 70);
	w.setWindowTitle("Nixwen's favorite dummy");
	w.setLayout(lay);
	w.show();
	
	return app.exec();
}
