#ifndef MT940_H
#define MT940_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MT940; }
QT_END_NAMESPACE

class MT940 : public QMainWindow
{
    Q_OBJECT

public:
    MT940(QWidget *parent = nullptr);
    ~MT940();

private:
    Ui::MT940 *ui;

 //   int load_report (void);
    int parse (void);
    int regex(void);
    int translate(void);
    int save(QString);
    int load_report(QString);

 typedef   struct {
        int row;
        int col;
    } pole;

    //nagłówek:
    pole lista_rachunkow, waluta, za_okres;
    //tabelka:
    pole data_operacji, opis_operacji, rachunek, kategoria, kwota, saldo;

private slots:
    void menu(QAction *action);
};
#endif // MT940_H
