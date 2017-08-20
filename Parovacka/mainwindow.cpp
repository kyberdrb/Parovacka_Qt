#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    srand(time(NULL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_2_clicked()
{
    // Prida polozku na koniec zoznamu
    QString meno = "meno";
    QString poradie = QString::number(ui->listWidget->count());
    QListWidgetItem *item = new QListWidgetItem(meno + poradie);
    item->setFlags(item->flags () | Qt::ItemIsEditable);
    item->setTextAlignment(Qt::AlignRight);
    ui->listWidget->addItem(item);
}

void MainWindow::on_pushButton_clicked()
{
    int riadky = ui->listWidget->count();
    int zoznam2[riadky];                // pole uz vybranych indexov mien
    bool vybranyZPovodnehoZoznamu[riadky];     // pole uz vybranych indexov mien

    int randomNum;

    // Prevencia proti zacykleniu, ked tam mame iba jeden prvok (meno)
    if(riadky <= 1) return;

    // Inicializacia nahodne vybranych prvkov
    inicializujVybrane(zoznam2, vybranyZPovodnehoZoznamu, riadky);

    // Ak sa cislo nenachadza v zozname vybranych cisel (mien),
    // vyber unikatne nahodne cislo z rozsahu od 0 do (pocetRiadkov-1)
    // a pridaj ho do pola uz vybranych cisel (mien)

    for(int i = 0; i < riadky; i++)
    {
        // vzdy vyber ine cislo ako je index i
        while(1)
        {
//            vypisVybraneCisla(zoznam2, vybranyZPovodnehoZoznamu, riadky);
            randomNum = rand() % riadky;
            qDebug() << i << "  ....  " << randomNum
                     << " (" << vybranyZPovodnehoZoznamu[randomNum] << ")"
                     << "     "
                     << vsetkoOstatneJeObsadene(vybranyZPovodnehoZoznamu, riadky-1);
            if(vybranyZPovodnehoZoznamu[randomNum] == true)
            {
                // kontrola proti zacykleniu
                // 1 da 2, 2 da 1, ale 3 nemoze dat 3 (samemu sebe)
                if(i == riadky-1
                        && vsetkoOstatneJeObsadene(vybranyZPovodnehoZoznamu, riadky-1))
                {
                    // zresetuj vsetko, nastav i = 0 a chod odznova
                    qDebug() << "Zacyklil som sa";
                    i = 0;
                    inicializujVybrane(zoznam2, vybranyZPovodnehoZoznamu, riadky);
                }
                continue;
            }
            if(randomNum != i) break;
        }

        zoznam2[i] = randomNum;
        vybranyZPovodnehoZoznamu[randomNum] = true;
    }

    // Vycisti druhy zoznam
    ui->listWidget_2->clear();

    // Vloz do druheho zoznamu rozhadzane mena
    QString polozka;
    for(int i = 0; i < riadky; i++)
    {
        polozka = ui->listWidget->item(zoznam2[i])->text();
        qDebug() << polozka;
        ui->listWidget_2->addItem(polozka);
    }

    vypisVybraneCisla(zoznam2, vybranyZPovodnehoZoznamu, riadky);
    qDebug() << "****";
}

// Vypis vybrane cisla
void MainWindow::vypisVybraneCisla(int *paZoznam, bool *paBoolZoznam,
                                   int paVelkostZoznamu)
{
    for(int i = 0; i < paVelkostZoznamu; i++)
    {
        qDebug() << i << " : " << paZoznam[i] << "               " << paBoolZoznam[i];
    }
    qDebug() << "----";
}

// Inicializuj zoznam nahodne vybranych cisel
void MainWindow::inicializujVybrane(int *paZoznam, bool *paBoolZoznam,
                                    int paVelkostZoznamu)
{
    for(int i = 0; i < paVelkostZoznamu; i++)
    {
        paZoznam[i] = INT_MAX;
        paBoolZoznam[i] = false;
    }
}

// Funkcia zabranujuca zacykleniu programu
bool MainWindow::vsetkoOstatneJeObsadene(bool *paBoolZoznam, int poPredposledny)
{
    for(int i = 0; i < poPredposledny; i++)
    {
        if(paBoolZoznam[i] == false)
            return false;
    }
    return true;
}
