#ifndef CALIBRACAO_H
#define CALIBRACAO_H
#include "calibracao.h"
#include "janelaprincipal.h"
#include <fstream>
#include "scimm_cor.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <unistd.h>
using namespace cv;


#define LARANJA 4
#define AMARELO 0
#define AZUL 1
#define VERMELHO 3
#define VERDE 2
#define ROSA 5
#define ROXO 6

class Calibracao
{
public:
   Calibracao();
    void ConfigurarCamera();
    void Calibrar();
    void Iniciar(JanelaPrincipal *janela, int c);
    void ReconhecerFundoExtrairObjetos();
    void Exibir();
    void Calcular();
    void Fechar();
    void SalvarArquivo();
    void AutoFoco();
private:

    bool FIM;
    Mat  HSV;
    Mat frame, frameAtual;
    int thresh = 60;
    int CAMERA;
    int brilho = 0, contraste = 50;
    std::vector<Rect> boundRect;
    std::vector<Rect> EliminarExcessos();
    void DetectarObjetos(int, void *);
    double ObterPorcentagem(int valor, int porcentagem);
    JanelaPrincipal* JANELA;
    int FOCO = 0;
};

#endif // CALIBRACAO_H
