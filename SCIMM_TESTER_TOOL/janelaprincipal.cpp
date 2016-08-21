#include "janelaprincipal.h"
#include "ui_janelaprincipal.h"


#include <iostream>
#include <unistd.h>
#include <string>
#include <qdebug.h>
#include <QCloseEvent>
#include <stdio.h>
#include <stdlib.h>
#include <QMessageBox>
#include "qfiledialog.h"
#include "exibircores.h"
using namespace cv;
QComboBox *op;
bool INDISPONIVEL;
int CAMERA =1;
int OS=0;
ExibirCores EXIBIR;
std::string slash = "/";
JanelaPrincipal::JanelaPrincipal(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::JanelaPrincipal)
{
    setWindowIcon(QIcon(":/icons/icone.png"));


    ui->setupUi(this);
    //Inicialização de Variaveis
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
    slash="\\";
    OS = 0;
#else
    slash="/";
    OS =1;
#endif


    //Ações Calibração Automatica
    connect(ui->BT_ARQUIVO, SIGNAL(clicked(bool)), SLOT(AbrirDocumento()));
    connect(ui->CB_CA_CORES, SIGNAL(currentIndexChanged(int)), SLOT(ComboCorChanged(int)));
    ui->BT_ARQUIVO->setIcon(QIcon(":icons/salvar.png"));

}


void JanelaPrincipal::CameraIndisponivel(){
    QMessageBox::warning(this, "SCIMM", "Camera Indisponivel");
    INDISPONIVEL = true;
}

QMessageBox::StandardButton JanelaPrincipal::SCIMM_ALERT(){
    QMessageBox::StandardButton reply;
    reply = QMessageBox::warning(this, "SCIMM", "Fundo Reconhecido, disponha os objetos no campo e clique em Ok para iniciar a Extração de Objetos.");
    return reply;
}

void JanelaPrincipal::SetImage(Mat frame){
    QImage img = ConverterFrame(frame);
    ui->IMAGEM->setPixmap(QPixmap::fromImage(img));
}

QImage JanelaPrincipal::ConverterFrame(Mat frame){
    switch ( frame.type() )
    {
    // 8-bit, 4 channel
    case CV_8UC4:
    {
        QImage image( frame.data,
                      frame.cols, frame.rows,
                      static_cast<int>(frame.step),
                      QImage::Format_ARGB32 );

        return image;
    }

        // 8-bit, 3 channel
    case CV_8UC3:
    {
        QImage image( frame.data,
                      frame.cols, frame.rows,
                      static_cast<int>(frame.step),
                      QImage::Format_RGB888 );

        return image.rgbSwapped();
    }

        // 8-bit, 1 channel
    case CV_8UC1:
    {
        static QVector<QRgb>  sColorTable( 256 );

        // only create our color table the first time
        if ( sColorTable.isEmpty() )
        {
            for ( int i = 0; i < 256; ++i )
            {
                sColorTable[i] = qRgb( i, i, i );
            }
        }

        QImage image( frame.data,
                      frame.cols, frame.rows,
                      static_cast<int>(frame.step),
                      QImage::Format_Indexed8 );

        image.setColorTable( sColorTable );

        return image;
    }

    default:
        qWarning() << "ASM::cvMatToQImage() - cv::Mat image type not handled in switch:" << frame.type();
        break;
    }
}

void JanelaPrincipal::AbrirDocumento(){
    QString dir = QFileDialog::getExistingDirectory(this, tr("Diretorio contendo o cores.arff"),
                                                       (OS==1?"C://":"/home"),
                                                       QFileDialog::ShowDirsOnly
                                                       | QFileDialog::DontResolveSymlinks);
    string arquivo = dir.toStdString()+"/cores.arff";
    EXIBIR.CarregarArquivo(arquivo);

    EXIBIR.MostrarCor(1, this);
}


void JanelaPrincipal::ComboCorChanged(int index){
    INDICE_OBJETO = index;

}

JanelaPrincipal::~JanelaPrincipal()
{
    delete ui;
}

