#include <QtWidgets/QApplication>
#include <QtWidgets/QSizePolicy>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QGridLayout>
#include <QtCore/QObject>
#include <QtCore/QString>
#include <QtWidgets/QLabel>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
using namespace std;



int test(const char * lol) {
	if(lol){
		return 1;
	}else{
		return 0;
	}
}

int main(int argv, char **args){

	// déclarations
	long hp0 = 42;
  int hp1 = 42;
  short hp2 = 42;
  char hp3 = 42;

	QApplication app(argv, args);

	const char * heal33 = "heal 33";
	const char * heal3 = "heal 3";
	const char * heal1 = "heal 1";
	const char * hit1 = "hit 1";
	const char * hit3 = "hit 3";
	const char * hit33 = "hit 33";

	test(heal1);
	test(heal3);
	test(heal33);
	test(hit1);
	test(hit3);
	test(hit33);


	// éléments
	QLabel *l0 = new QLabel(QString::number(hp0));
	l0->setAlignment(Qt::AlignCenter);
	QPushButton *b0_plus_33 = new QPushButton(heal33);
	QPushButton *b0_plus_3 = new QPushButton(heal3);
	QPushButton *b0_plus_1 = new QPushButton(heal1);
	QPushButton *b0_moins_1 = new QPushButton(hit1);
	QPushButton *b0_moins_3 = new QPushButton(hit3);
	QPushButton *b0_moins_33 = new QPushButton(hit33);

	// éléments
	QLabel *l1 = new QLabel(QString::number(hp1));
	l1->setAlignment(Qt::AlignCenter);
	QPushButton *b1_plus_33 = new QPushButton(heal33);
	QPushButton *b1_plus_3 = new QPushButton(heal3);
	QPushButton *b1_plus_1 = new QPushButton(heal1);
	QPushButton *b1_moins_1 = new QPushButton(hit1);
	QPushButton *b1_moins_3 = new QPushButton(hit3);
	QPushButton *b1_moins_33 = new QPushButton(hit33);

    // éléments
	QLabel *l2 = new QLabel(QString::number(hp2));
	l2->setAlignment(Qt::AlignCenter);
	QPushButton *b2_plus_33 = new QPushButton(heal33);
	QPushButton *b2_plus_3 = new QPushButton(heal3);
	QPushButton *b2_plus_1 = new QPushButton(heal1);
	QPushButton *b2_moins_1 = new QPushButton(hit1);
	QPushButton *b2_moins_3 = new QPushButton(hit3);
	QPushButton *b2_moins_33 = new QPushButton(hit33);


	// éléments
	QLabel *l3 = new QLabel(QString::number(hp3));
	l3->setAlignment(Qt::AlignCenter);
	QPushButton *b3_plus_33 = new QPushButton(heal33);
	QPushButton *b3_plus_3 = new QPushButton(heal3);
	QPushButton *b3_plus_1 = new QPushButton(heal1);
	QPushButton *b3_moins_1 = new QPushButton(hit1);
	QPushButton *b3_moins_3 = new QPushButton(hit3);
	QPushButton *b3_moins_33 = new QPushButton(hit33);


	// handlers
	QObject::connect(b0_plus_33, &QPushButton::clicked, [&hp0, &l0]{hp0 += 33; l0->setText(QString::number(hp0));});
	QObject::connect(b0_plus_3, &QPushButton::clicked, [&hp0, &l0]{hp0 += 3; l0->setText(QString::number(hp0));});
	QObject::connect(b0_plus_1, &QPushButton::clicked, [&hp0, &l0]{hp0++; l0->setText(QString::number(hp0));});
	QObject::connect(b0_moins_1, &QPushButton::clicked, [&hp0, &l0]{hp0--; l0->setText(QString::number(hp0));});
	QObject::connect(b0_moins_3, &QPushButton::clicked, [&hp0, &l0]{hp0 -= 3; l0->setText(QString::number(hp0));});
	QObject::connect(b0_moins_33, &QPushButton::clicked, [&hp0, &l0]{hp0 -= 33; l0->setText(QString::number(hp0));});

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

	QObject::connect(b3_plus_33, &QPushButton::clicked, [&hp3, &l3]{hp3 += 33; l3->setText(QString::number(hp3));});
	QObject::connect(b3_plus_3, &QPushButton::clicked, [&hp3, &l3]{hp3 += 3; l3->setText(QString::number(hp3));});
	QObject::connect(b3_plus_1, &QPushButton::clicked, [&hp3, &l3]{hp3++; l3->setText(QString::number(hp3));});
	QObject::connect(b3_moins_1, &QPushButton::clicked, [&hp3, &l3]{hp3--; l3->setText(QString::number(hp3));});
	QObject::connect(b3_moins_3, &QPushButton::clicked, [&hp3, &l3]{hp3 -= 3; l3->setText(QString::number(hp3));});
	QObject::connect(b3_moins_33, &QPushButton::clicked, [&hp3, &l3]{hp3 -= 33; l3->setText(QString::number(hp3));});


	// layout
	QGridLayout *lay = new QGridLayout;
	lay->setSpacing(0);
	lay->setMargin(0);

  lay->addWidget(l0, 0, 0, 1, 1);
	lay->addWidget(b0_plus_33, 1, 0, 1, 1);
	lay->addWidget(b0_plus_3, 2, 0, 1, 1);
	lay->addWidget(b0_plus_1, 3, 0, 1, 1);
	lay->addWidget(b0_moins_1, 4, 0, 1, 1);
	lay->addWidget(b0_moins_3, 5, 0, 1, 1);
	lay->addWidget(b0_moins_33, 6, 0, 1, 1);

	lay->addWidget(l1, 0, 1, 1, 1);
	lay->addWidget(b1_plus_33, 1, 1, 1, 1);
	lay->addWidget(b1_plus_3, 2, 1, 1, 1);
	lay->addWidget(b1_plus_1, 3, 1, 1, 1);
	lay->addWidget(b1_moins_1, 4, 1, 1, 1);
	lay->addWidget(b1_moins_3, 5, 1, 1, 1);
	lay->addWidget(b1_moins_33, 6, 1, 1, 1);

	lay->addWidget(l2, 0, 2, 1, 1);
	lay->addWidget(b2_plus_33, 1, 2, 1, 1);
	lay->addWidget(b2_plus_3, 2, 2, 1, 1);
	lay->addWidget(b2_plus_1, 3, 2, 1, 1);
	lay->addWidget(b2_moins_1, 4, 2, 1, 1);
	lay->addWidget(b2_moins_3, 5, 2, 1, 1);
	lay->addWidget(b2_moins_33, 6, 2, 1, 1);

    lay->addWidget(l3, 0, 3, 1, 1);
	lay->addWidget(b3_plus_33, 1, 3, 1, 1);
	lay->addWidget(b3_plus_3, 2, 3, 1, 1);
	lay->addWidget(b3_plus_1, 3, 3, 1, 1);
	lay->addWidget(b3_moins_1, 4, 3, 1, 1);
	lay->addWidget(b3_moins_3, 5, 3, 1, 1);
	lay->addWidget(b3_moins_33, 6, 3, 1, 1);


	// fenêtre
	QWidget w;
	w.resize(500, 70);
	w.setWindowTitle("Nixwen's favorite dummy");
	w.setLayout(lay);
	w.show();

	return app.exec();
}
