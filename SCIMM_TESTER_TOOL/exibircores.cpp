#include "exibircores.h"
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

ExibirCores::ExibirCores(){

}

void ExibirCores::CarregarArquivo(string nome){
     memset(CORES, 0, sizeof(CORES));
    FILE* arquivo = fopen(nome.c_str(), "r");
    if (arquivo == NULL)
        //return false;

        int numerosLidos[8] = { 0 };
    int contador = 0;
    char c;
    int i=0;
    int linha = -1;
    int aux[3];
    while (!feof(arquivo)) {
        fscanf(arquivo, "%c", &c);

        if(linha < 13) {
            if(c == '\n'){
                linha++;
                aux[contador] = i;
                contador=0;
                if(linha%2==0) {
                    CORES[(linha/2)].SetMin(aux);
                } else {
                    CORES[(linha/2)].SetMax(aux);
                }


                i=0;
            } else  if(c == '.'){
                aux[contador] = i;
                contador++;
                i=0;
            }
            else {
                //std::cout << c;
                i = (i*10)+(c- '0');

            }
        }}
    fclose(arquivo);

 std::cout << "Cabo CarregarArquivo"   <<std::endl;
}


void ExibirCores::MostrarCor(int numero, JanelaPrincipal* JANELA){
    std::cout << "começou MostrarCor"   <<std::endl;

            cv::VideoCapture camera;
            camera.open(numero);

                    Mat Threshold;
   while(true){
                            Mat final;
                            camera >> frame;

                            dilate(frame, frame, Mat(), Point(-1, -1), 2, 1, 1);
                            cv::cvtColor(frame,HSV,cv::COLOR_BGR2HSV);
                            cv::inRange(
                                        HSV,
                                        cv::Scalar(CORES[JANELA->INDICE_OBJETO].S_H[0],
                                    CORES[JANELA->INDICE_OBJETO].S_S[0],
                                    CORES[JANELA->INDICE_OBJETO].S_V[0]),
                                    cv::Scalar( CORES[JANELA->INDICE_OBJETO].S_H[1] ,
                                    CORES[JANELA->INDICE_OBJETO].S_S[1] ,
                                    CORES[JANELA->INDICE_OBJETO].S_V[1] ),Threshold);
                            bitwise_and(frame, frame, final, Threshold );

                            JANELA->SetImage( final);
                            imshow("cor", final);
                            if (cv::waitKey(30)>= 0) break;

                        }
                        camera.release();
                }



