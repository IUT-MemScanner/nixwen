#ifndef FENETRE_H
#define FENETRE_H

#include <QDialog>

class QTextEdit;
class QHBoxLayout;
class QSplitter;
class QVBoxLayout;

class Fenetre : public QDialog
{
    Q_OBJECT

    public:
        Fenetre();

    private:
        void creerHautGauche(QSplitter *splitvertical);
        void creerHautDroite(QSplitter *splitvertical);
        void creerBas(QSplitter *splithorizontal);

        QVBoxLayout *wlay;
        QSplitter *splithorizontal;
        QSplitter *splitvertical;
        QWidget *haut;
        QHBoxLayout *layhaut;
        QTextEdit *hautgauche;
        QTextEdit *hautdroite;
        QTextEdit *basmilieu;
        QWidget *w;

        QPushButton *bouton; //TEST

    private slots:
        void on_bouton_clicked();
};

#endif // FENETRE_H
