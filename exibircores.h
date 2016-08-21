#ifndef EXIBIRCORES_H
#define EXIBIRCORES_H
#include "scimm_cor.h"
#include "janelaprincipal.h"
using namespace std;
using namespace cv;

class ExibirCores
{
public:
    ExibirCores();
    void CarregarArquivo(string nome);
    void MostrarCor(int numero, JanelaPrincipal* JANELA);

    Mat frame, HSV;
    SCIMM_COR CORES[7];
};

#endif // EXIBIRCORES_H
