#ifndef JANELAPRINCIPAL_H
#define JANELAPRINCIPAL_H
#include <QMainWindow>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <QMessageBox>
#include "scimm_cor.h"
namespace Ui {
class JanelaPrincipal;
}

class JanelaPrincipal : public QMainWindow
{
    Q_OBJECT

public:
    explicit JanelaPrincipal(QWidget *parent = 0);
    ~JanelaPrincipal();

    void CameraIndisponivel();
    QMessageBox::StandardButton SCIMM_ALERT();


    // -----------  Variaveis Publicas Calibração Manual
    int INDICE_CALIBRACAO;
    bool FINALIZADA=false, CALIBRAR=false,EXTRAIR=false;

    // -----------  Variaveis Publicas Calibração Automatica
    int INDICE_COR = 0    , INDICE_OBJETO = 0;
    bool SALVAR, INICIAR;



public slots:

    //----------- Slots Calibração Automatica


    void AbrirDocumento();

    QImage ConverterFrame(cv::Mat frame);
    void ComboCorChanged(int index);
    void SetImage(cv::Mat frame);

private:
    Ui::JanelaPrincipal *ui;
    // -----------  Variaveis Publicas Calibração Manual
    int INDEX;
    int* H,*S, *V;


};

#endif // JANELAPRINCIPAL_H
