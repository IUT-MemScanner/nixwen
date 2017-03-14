#include <QtWidgets>
#include "fenetre.h"

#include <QDebug>

Fenetre::Fenetre()
{
	QWidget *w = new QWidget();
	QVBoxLayout *wlay = new QVBoxLayout;
    QSplitter *splithorizontal = new QSplitter(Qt::Vertical);
    QWidget *haut = new QWidget;
	QSplitter *splitvertical = new QSplitter;
    QHBoxLayout *layhaut = new QHBoxLayout;

    layhaut->addWidget(splitvertical);

    creerHautGauche(splitvertical);
    creerHautDroite(splitvertical);
	haut->setLayout(layhaut);
	splithorizontal->addWidget(haut);
    creerBas(splithorizontal);
    wlay->addWidget(splithorizontal);

	w->resize(800, 600);
	w->setWindowTitle("Guinix");
	w->setLayout(wlay);
	w->show();
}

void Fenetre::creerHautGauche(QSplitter *splitvertical)
{
	QWidget *hautgauche = new QWidget;
	splitvertical->addWidget(hautgauche);
	QVBoxLayout *layhautgauche = new QVBoxLayout(); //TODO remplacer le VBoxLayout par un layout approprié
	hautgauche->setLayout(layhautgauche);

	//TODO partie en haut à gauche
}

void Fenetre::creerHautDroite(QSplitter *splitvertical)
{
	QWidget *hautdroite = new QWidget;
	splitvertical->addWidget(hautdroite);
	QVBoxLayout *layhautdroite = new QVBoxLayout(); //TODO remplacer le VBoxLayout par un layout approprié
	hautdroite->setLayout(layhautdroite);
	
	//TODO partie en haut à droite



	QHBoxLayout *secondlayhd = new QHBoxLayout();
	layhautdroite->addLayout(secondlayhd);

	QCheckBox *box = new QCheckBox("hex");
	secondlayhd->addWidget(box);

	QLineEdit *lineedit = new QLineEdit("");
	secondlayhd->addWidget(lineedit);

	QHBoxLayout *thirdlayhd = new QHBoxLayout();
	layhautdroite->addLayout(thirdlayhd);



	QComboBox *liste = new QComboBox();
	QLabel *l1 = new QLabel("Search : ");
	liste->addItem("valeur exacte");
	liste->addItem("supérieure à");
	thirdlayhd->addWidget(l1);
	thirdlayhd->addWidget(liste);


	QHBoxLayout *fourthlayhd = new QHBoxLayout();
	layhautdroite->addLayout(fourthlayhd);

	QComboBox *liste2 = new QComboBox();
	liste2->addItem("Int");
	liste2->addItem("String");
	fourthlayhd->addWidget(liste2);


	QHBoxLayout *fifthlayhd = new QHBoxLayout();
	layhautdroite->addLayout(fifthlayhd);

	QPushButton *b1 = new QPushButton("New search");
	fifthlayhd->addWidget(b1);
	b1->setFixedSize(100, 30);


	QPushButton *b2 = new QPushButton("Search");
	fifthlayhd->addWidget(b2);
	b2->setFixedSize(100, 30);



}

void Fenetre::creerBas(QSplitter *splithorizontal)	
{
	QWidget *basmilieu = new QWidget;
	splithorizontal->addWidget(basmilieu);
	QVBoxLayout *laybasmilieu = new QVBoxLayout(); //TODO remplacer le VBoxLayout par un layout approprié
	basmilieu->setLayout(laybasmilieu);

	//TEST
		QPushButton *bouton = new QPushButton("Ok");
		QObject::connect(bouton, SIGNAL(clicked()), this, SLOT(on_bouton_clicked())); // linkage du handler (SIGNAL -> SLOTS)
		laybasmilieu->addWidget(bouton);

	//TODO partie basse
}

void Fenetre::on_bouton_clicked()
{
	qWarning() << "heyyyy";
}
