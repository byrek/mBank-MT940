#include "mt940.h"
#include "ui_mt940.h"
#include "QFile"
#include "QMessageBox"
#include "QDebug"
#include "QDateTime"
#include "QRegularExpression"

MT940::MT940(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MT940)
{

    ui->setupUi(this);

    this->load_report();
    if (this->parse()!=1) this->close();
    if (this->regex()!=1) this->close();
    this->translate();
    this->save();

}

MT940::~MT940()
{
    delete ui;
}


int MT940::load_report(void)
{
    QFile raport("raport.csv");
    if (!raport.open(QIODevice::ReadOnly)) { QMessageBox::information(0,"Error",raport.errorString()); return -1; }
    else
        {
        qint16 row_cnt=0;
        qint16 col_cnt=0;
        qint16 col=0;
        ui->tLista->setRowCount(row_cnt);
        ui->tLista->setColumnCount(col_cnt);


        while (!raport.atEnd())
            {
            ui->tLista->setRowCount(row_cnt+1);
            QString linia = QString::fromUtf8(raport.readLine());
            QStringList pars=linia.split(';');
            if (ui->tLista->columnCount()<pars.count()+1) ui->tLista->setColumnCount(pars.count()+1);

            for (int i=0;i<pars.count();i++)
                {
                    if (ui->tLista->columnCount()<col+1) { col_cnt=col+1; ui->tLista->setColumnCount(col_cnt);}
                    pars[i]=pars[i].trimmed(); pars[i]=pars[i].simplified();
                    if (pars[i]=="") pars[i]=QString("GUNWO");
                    if (pars[i]!="") ui->tLista->setItem(row_cnt,i,new QTableWidgetItem(pars[i]));
                }
            row_cnt++;
            }
        }
    return 0;
}

int MT940::parse(void)
{
 //   QRegularExpression liczba("-?\\d*\\,\\d+");
    QRegularExpression spacje("\\s+");
/*
    //Szukamy salda pooczątkowego
    search=ui->tLista->findItems(QString::fromUtf8("Saldo początkowe"), Qt::MatchContains);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono salda początkowego\n"; return -1; }
    else
    {
        this->saldo_poczatkowe.row= search.first()->row();
        this->saldo_poczatkowe.col=search.first()->column();
        qDebug()<<"Saldo początkowe"<<this->saldo_poczatkowe.row<<this->saldo_poczatkowe.col;
        QString saldo=ui->tLista->item(this->saldo_poczatkowe.row, this->saldo_poczatkowe.col)->text();
        saldo.replace(spacje,"");
        QRegExp re("[^0-9\,]");
        saldo=saldo.remove(re);
        qDebug()<<saldo;
    }
*/

    //Szukamy Daty operacji
    QList <QTableWidgetItem *> search=ui->tLista->findItems("#Data operacji", Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono kolumny z datą operacji\n"; return -1; }
    else
    {
        this->data_operacji.row= search.first()->row();
        this->data_operacji.col=search.first()->column();
        qDebug()<<"Data operacji"<<this->data_operacji.row<<this->data_operacji.col;
    }
    //Szukamy Opisu operacji
    search=ui->tLista->findItems("#Opis operacji", Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono kolumny z opisem operacji\n"; return -1; }
    else
    {
        this->opis_operacji.row= search.first()->row();
        this->opis_operacji.col=search.first()->column();
        qDebug()<<"Opis operacji"<<this->opis_operacji.row<<this->opis_operacji.col;
    }    //Szukamy #Rachunek
    search=ui->tLista->findItems("#Rachunek", Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono kolumny z danymi rachunku\n"; return -1; }
    else
    {
        this->rachunek.row= search.first()->row();
        this->rachunek.col=search.first()->column();
        qDebug()<<"Rachunek"<<this->rachunek.row<<this->rachunek.col;
    }

    //Szukamy #Kategoria
    search=ui->tLista->findItems("#Kategoria", Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono kolumny z opisem kategorii\n"; return -1; }
    else
    {
        this->kategoria.row= search.first()->row();
        this->kategoria.col=search.first()->column();
        qDebug()<<"Kategoria:"<<this->kategoria.row<<this->kategoria.col;
    }
    //Szukamy #Kwota
    search=ui->tLista->findItems("#Kwota", Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono kolumny z kwotą transakcji\n"; return -1; }
    else
    {
        this->kwota.row= search.first()->row();
        this->kwota.col=search.first()->column();
        qDebug()<<"Kwota:"<<this->kwota.row<<this->kwota.col;
    }
    //Szukamy #Saldo po operacji
    search=ui->tLista->findItems("#Saldo po operacji", Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono kolumny z saldem po operacji\n"; return -1; }
    else
    {
        this->saldo.row= search.first()->row();
        this->saldo.col=search.first()->column();
        qDebug()<<"Saldo:"<<this->saldo.row<<this->saldo.col;
    }

    //Szukamy #dla rachunków
    search=ui->tLista->findItems(QString::fromUtf8("#dla rachunków:"), Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono listy rachunków\n"; return -1; }
    else
    {
        this->lista_rachunkow.row= search.first()->row();
        this->lista_rachunkow.col=search.first()->column();
        qDebug()<<"Lista rachunków"<<this->lista_rachunkow.row<<this->lista_rachunkow.col;
    }


    //Szukamy #Waluta
    search=ui->tLista->findItems(QString::fromUtf8("#Waluta"), Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono waluty rachunków\n"; return -1; }
    else
    {
        this->waluta.row= search.first()->row();
        this->waluta.col=search.first()->column();
        qDebug()<<"Waluta"<<this->waluta.row<<this->waluta.col;
    }
    //Szukamy #za okres
    search=ui->tLista->findItems(QString::fromUtf8("#Za okres:"), Qt::MatchExactly);
    if (search.isEmpty()) { qDebug()<<"Nie znaleziono zakresu dat\n"; return -1; }
    else
    {
        this->za_okres.row= search.first()->row();
        this->za_okres.col=search.first()->column();
        qDebug()<<"Waluta"<<this->za_okres.row<<this->za_okres.col;
    }
    return 1;
}

int MT940::regex(void)
{
    QRegExp cyfry("[^0-9]");
    QRegExp liczby("[^0-9,+-]");
    //konwertujemy numery rachunków wyrzucając tekst i pozostawiając sam numer rachunku
    int i=1;
    while (!ui->tLista->item(this->lista_rachunkow.row+i,this->lista_rachunkow.col)->text().startsWith("GUNWO"))
    {
    QString rachunek=ui->tLista->item(this->lista_rachunkow.row+i, this->lista_rachunkow.col)->text();

    rachunek.remove(cyfry);
    ui->tLista->item(this->lista_rachunkow.row+i,this->lista_rachunkow.col)->setText(rachunek);
    //konwertujemy na pierwsze cztery i ostatnie cztery
    QString tmp=rachunek.left(4).append(" ... ").append(rachunek.right(4));
    //i zamieniamy na liście w tabeli
    QList <QTableWidgetItem *> search=ui->tLista->findItems(tmp, Qt::MatchContains);
    if (!search.isEmpty())
    {
    for (int j=0;j<search.count();j++)
        {
        ui->tLista->item(search[j]->row(), search[j]->column())->setText(rachunek);
        qDebug()<<"podmieniam pod"<<search[j]->row()<<search[j]->column();
        }
    }
    i++;
    qDebug()<<rachunek<<tmp;
    }


    i=1;
    while (ui->tLista->item(this->rachunek.row+i, this->rachunek.col)!=NULL)
    {
           i++;
           qDebug()<<i;
    }

    QString waluta=ui->tLista->item(this->waluta.row+1, this->waluta.col)->text();
    qDebug()<<waluta;

    //sprawdzamy czy pole kwota zawiera kod waluty
    QString kod_waluty=ui->tLista->item(this->waluta.row+1, this->waluta.col)->text();
    i=this->kwota.row+1;
    while (ui->tLista->item(i,this->kwota.col)!=NULL)
        {
        if (ui->tLista->item(i,this->kwota.col)->text().contains(kod_waluty))
        {
          QString tmp=ui->tLista->item(i,this->kwota.col)->text();
          tmp.remove(liczby);
          ui->tLista->item(i,this->kwota.col)->setText(tmp);
        }
        i++;
        }
    //sprawdzamy czy pole saldo zawiera kod waluty
    i=this->saldo.row+1;
    while (ui->tLista->item(i,this->saldo.col)!=NULL)
        {
        if (ui->tLista->item(i,this->saldo.col)->text().contains(kod_waluty))
        {
          QString tmp=ui->tLista->item(i,this->saldo.col)->text();
          tmp.remove(liczby);
          ui->tLista->item(i,this->saldo.col)->setText(tmp);
        }
        i++;
        }
    return 1;
}
int MT940::translate(void)
{
qint16 row_cnt=0;
ui->tWynik->setColumnCount(8);
ui->tWynik->setRowCount(row_cnt);

//Tworzymy unikalny numer:
qint64 timestamp=QDateTime::currentDateTime().toSecsSinceEpoch();

int i=this->data_operacji.row+1;
qDebug()<<"Generowanie translacji";
//Header
ui->tWynik->setRowCount(row_cnt+1);
ui->tWynik->setItem(row_cnt,0,new QTableWidgetItem("20"));
ui->tWynik->setItem(row_cnt,1,new QTableWidgetItem(QString::number(timestamp+i).append("313374")));
ui->tWynik->setItem(row_cnt,2,new QTableWidgetItem("25"));
ui->tWynik->setItem(row_cnt,3,new QTableWidgetItem(QString("PL").append(ui->tLista->item(i,2)->text())));
ui->tWynik->setItem(row_cnt,4,new QTableWidgetItem("28C"));
ui->tWynik->setItem(row_cnt,5,new QTableWidgetItem("1/1"));
ui->tWynik->setItem(row_cnt,6,new QTableWidgetItem("60F"));
//Data początkowa
QDate start=QDate::fromString(ui->tLista->item(this->za_okres.row+1, this->za_okres.col)->text(),"dd.MM.yyyy");
if (!start.isValid()) { qDebug()<<"Błąd czytania daty startu"; return -1; }

//Otwarcie
QString otwarcie="C";
otwarcie.append(start.toString("yyMMdd"));
otwarcie.append(ui->tLista->item(this->waluta.row+1, this->waluta.col)->text());
//Wyliczamy saldo początkowe
i=this->saldo.row+1;
while (ui->tLista->item(i,this->saldo.col)!=NULL) i++;
QString pierwsze_saldo=ui->tLista->item(i-1, this->saldo.col)->text();
pierwsze_saldo.replace(",",".");
qDebug()<<"Pierwsze saldo"<<pierwsze_saldo;
QString pierwsza_operacja=ui->tLista->item(i-1,this->kwota.col)->text();
pierwsza_operacja.replace(",",".");
qDebug()<<"Pierwsza operacja"<<pierwsza_operacja;
float saldo_otwarcia=pierwsze_saldo.toFloat()-pierwsza_operacja.toFloat();
qDebug()<<"Saldo otwarcia"<<saldo_otwarcia;
QString saldo_otwarcia_str=QString::number(saldo_otwarcia,'f',2);
saldo_otwarcia_str.replace(".",",");

otwarcie.append(saldo_otwarcia_str);

ui->tWynik->setItem(row_cnt,7,new QTableWidgetItem(otwarcie));
row_cnt++;
i=this->data_operacji.row+1;
qDebug()<<"I wynosi"<<i;

while (!ui->tLista->item(i,0)->text().contains("GUNWO"))
{
    ui->tWynik->setRowCount(row_cnt+1);
    ui->tWynik->setItem(row_cnt,0,new QTableWidgetItem("61"));

    QDate data_operacji=QDate::fromString(ui->tLista->item(i, this->data_operacji.col)->text(),"yyyy-MM-dd");
    if (!data_operacji.isValid()) { qDebug()<<"Błąd czytania daty operacji"; return -1; }

    //Otwarcie
    QString statement;
    statement.append(data_operacji.toString("yyMMddMMdd"));
    QString tmp_txt=ui->tLista->item(i,this->kwota.col)->text();
    tmp_txt.replace(",",".");
    float tmp=tmp_txt.toFloat();
    if (tmp>=0) statement.append("C"); else statement.append("D");
    tmp_txt=QString::number(qAbs(tmp));
    tmp_txt.replace(".",",");

    statement.append(tmp_txt);
    //teraz pytanie czy SWIFT czy nie:
    statement.append("N"); //non-swift

    QString cat=ui->tLista->item(i,this->kategoria.col)->text();
    if (cat.contains("Wpływy - inne")) statement.append("TRF");
    else if (cat.contains("Opłaty i odsetki")) statement.append("TRN");//albo CHG lub COM?
    else if (cat.contains("Bez kategorii"))statement.append("MSC");
    else if (cat.contains("Ubezpieczenia"))statement.append("TRF");
    else if (cat.contains("Usługi księgowe i doradcze")) statement.append("TRF");
    else if (cat.contains("Podatki - inne")) statement.append("TRF");
    else { qDebug()<<"Brak kategorii"; return -1;}

    //potem jest jakis nonref, HGW co to jest
    statement.append("NONREF");
    ui->tWynik->setItem(row_cnt,1,new QTableWidgetItem(statement));
    row_cnt++;
    ui->tWynik->setRowCount(row_cnt+1);
    ui->tWynik->setItem(row_cnt,0,new QTableWidgetItem("86"));
    ui->tWynik->setItem(row_cnt,1,new QTableWidgetItem(ui->tLista->item(i,this->opis_operacji.col)->text()));
       i++;
       row_cnt++;
       qDebug()<<i;
}
    ui->tWynik->setRowCount(row_cnt+1);
    ui->tWynik->setItem(row_cnt,0, new QTableWidgetItem("62F"));

    QDate data_operacji=QDate::fromString(ui->tLista->item(this->za_okres.row+1,this->za_okres.col+1)->text(),"dd.MM.yyyy");
    if (!data_operacji.isValid()) { qDebug()<<"Błąd czytania daty operacji"; return -1; }
    QString saldo_koncowe="C";
    saldo_koncowe.append(data_operacji.toString("yyMMdd"));
    saldo_koncowe.append(ui->tLista->item(this->saldo.row+1,this->saldo.col)->text());
    ui->tWynik->setItem(row_cnt,1, new QTableWidgetItem(saldo_koncowe));




return 1;
}

int MT940::save(void)
{
    QString filename = "MT940.txt";
    QFile file(filename);
    if (!file.open(QIODevice::WriteOnly)) { QMessageBox::information(0,"Error",file.errorString()); return -1; }
    QTextStream out(&file);

    out<<":"<<ui->tWynik->item(0,0)->text()<<":"<<ui->tWynik->item(0,1)->text()<<"\n";
    out<<":"<<ui->tWynik->item(0,2)->text()<<":"<<ui->tWynik->item(0,3)->text()<<"\n";
    out<<":"<<ui->tWynik->item(0,4)->text()<<":"<<ui->tWynik->item(0,5)->text()<<"\n";
    out<<":"<<ui->tWynik->item(0,6)->text()<<":"<<ui->tWynik->item(0,7)->text()<<"\n";
    int i=1;
    while (ui->tWynik->item(i,0)!=NULL)

    {
        out<<":"<<ui->tWynik->item(i,0)->text()<<":"<<ui->tWynik->item(i,1)->text()<<"\n";
        i++;
    }
    file.close();
}
