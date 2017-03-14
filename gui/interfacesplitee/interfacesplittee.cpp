#include <QtWidgets>
#include <QtCore>

int main(int argv, char **args){
	
	// déclarations
	QApplication app(argv, args);

	// éléments
    QVBoxLayout *wlay = new QVBoxLayout;
    QSplitter *splithorizontal = new QSplitter(Qt::Vertical);
    QSplitter *splitvertical = new QSplitter;
    QWidget *haut = new QWidget;
    QHBoxLayout *layhaut = new QHBoxLayout;
	QTextEdit *hautgauche = new QTextEdit;
    QTextEdit *hautdroite = new QTextEdit;
    QTextEdit *basmilieu = new QTextEdit;

    layhaut->addWidget(splitvertical);
    
    splitvertical->addWidget(hautgauche);
    splitvertical->addWidget(hautdroite);

    haut->setLayout(layhaut);
    
    splithorizontal->addWidget(haut);
	splithorizontal->addWidget(basmilieu);
    
    wlay->addWidget(splithorizontal);

	// fenêtre
	QWidget *w = new QWidget();
	w->resize(800, 600);
	w->setWindowTitle("Guinix");
	w->setLayout(wlay);
	w->show();
	
	return app.exec();
}
