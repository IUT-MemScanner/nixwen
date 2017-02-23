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
