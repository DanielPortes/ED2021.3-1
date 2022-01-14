#pragma once

#include <iostream>
#include "Leitura.h"
#include"Parametros.h"
#include <cassert>
#define A 1000000
#include "arvoreVP.h"

void inicializaVetorAleatorioArvore(vector<elementoArvore> &elemento, int size)
{
    fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
    if (!arquivoBinario.is_open())
    {
        cerr << "ERRO: arquivo nao pode ser aberto na funcao inicializaVetor()";
        assert(false);
    }
    int aux=0;
    Review aux2;
    for (int j = 0; j < size; j++)
    {
        elemento.resize(size);
        aux=retonaNumeroAleatorio(0, reviews_totais);
        aux2 =retornaReviewEspecifica(aux, arquivoBinario);
        elemento[j].id = aux2.review_id;
        elemento[j].posicaoBinario=j;
    }
}
void imprimeResultadoArvoreVP(int comparacoesMedias,int comparacoesMediasBusca,double tempoMedioInsercao,double tempoMedioBusca,int mediaAchados){
   
    ofstream arquivotxt("saida.txt",ios::app);
    arquivotxt << "***********************************************************************"  << endl;
    arquivotxt << "**********************   Arvore Vermelho - Preto  *********************" << endl;
    arquivotxt << "***********************************************************************" <<  endl;
    arquivotxt << "Numero de comparações médias para inserção de 1.000.000 elementos:" << comparacoesMedias <<  endl;
    arquivotxt << "Tempo médio para inserção de 1.000.000 elementos:" << tempoMedioInsercao <<"s"<<  endl;
    arquivotxt << "Numero de comparações médias para busca de 100 elementos:" << comparacoesMediasBusca <<  endl;
    arquivotxt << "Tempo médios para busca de 100 elementos:" << tempoMedioBusca <<"s"<<   endl;
    arquivotxt << "Numero médio de reviews encontradas na busca para busca de 100 elementos:" << mediaAchados <<  endl;
    arquivotxt << "***********************************************************************"  << endl;
    arquivotxt.close();

    

}


void benchmarkArvoreVP(){
    int comparacoes=0;
    int comparacoesBusca=0;
    int entrada=0;
    int achados=0;
    bool conseguiu=false;
    elementoArvore aux;
    vector <elementoArvore> elementosBusca;
    string id;
    arvoreVP arvore;
    vector<elementoArvore> elementos;
    clock_t h;        // Criando variaveis de tempo
    h = clock();      // Iniciando o tempo 
    cout << "inicializando insercao..." <<endl;
    for(int i=0;i<3;i++){   //rodando 3 vezes para tirar media
        cout << "insercao dos 1.000.000 elementos,teste numero " <<i+1<<" de 3"<<endl;
        inicializaVetorAleatorioArvore(elementos,A); //inicializando vetor de elementos
        for (int i = 0; i <A;i++){  //inserção
            arvore.inserir(&elementos[i],&comparacoes);
        }
    }
    h = clock() - h;  // Finalizando o tempo
    h=h/3;
    double auxTempoInsere = ((double)h)/((CLOCKS_PER_SEC)); 
    comparacoes=comparacoes/3;

    //-------busca--------
    
    cout << "Realizando testes de busca..." <<endl;
    h = clock();      // Iniciando o tempo 
    for(int i = 0; i < 3;i++){
        cout << "busca dos 100 elementos,teste numero " <<i+1<<" de 3"<<endl;
        inicializaVetorAleatorioArvore(elementosBusca,100); 
        for(int j = 0; j < 100 ;j++){
           conseguiu=false;
            aux=arvore.buscar(elementosBusca[j].id,&comparacoesBusca,&conseguiu);
            if(conseguiu==true){
                achados++;
            }
        }
    }
    h = clock() - h;  // Finalizando o tempo
    h=h/3;
    double auxTempoBusca = ((double)h)/((CLOCKS_PER_SEC)); 
    achados=achados/3;
    cout << "Realizando impressao..." <<endl;
    imprimeResultadoArvoreVP(comparacoes,comparacoesBusca,auxTempoInsere,auxTempoBusca,achados);
    cout << "benchmark concluido com sucesso" <<endl;
    
    
}
void testArvoreVP(){
    int comparacoes=0;
    int comparacoesBusca=0;
    int entrada=0;
    int achados=0;
    bool conseguiu=false;
    elementoArvore aux;
    vector <elementoArvore> elementosBusca;
    string id;
    arvoreVP arvore;
    vector<elementoArvore> elementos;
    cout << "inicializando insercao..." <<endl;
 
    inicializaVetorAleatorioArvore(elementos,A); //inicializando vetor de elementos
    for (int i = 0; i <A;i++){  //inserção
        if(i==0){
            cout<<"dica,a id a seguir foi inserida na arvore"<<endl<<elementos[i].id<<endl;
        }
        arvore.inserir(&elementos[i],&comparacoes);
    }
    //--------------TESTE MANUAL DE BUSCA--------------------------------------------------
    while(true){ //busca 
        cout<<"deseja procurar uma id?  1-sim || 2-nao"<<endl;
        cin>>entrada;
        if(entrada==1){
            comparacoesBusca=0;
            cout<<"digite a id desejada"<<endl;
            cin>>id;
            aux=arvore.buscar(id,&comparacoesBusca,&conseguiu);
            if(conseguiu){
                cout<<endl<<"elemento presente na arvore,realizando acesso a disco para recuperar todas as informacoes:"<<endl;
                fstream arquivoBinario("./saidaBinaria.bin", ios::in | ios::binary);
                if (!arquivoBinario.is_open())
                {
                    cerr << "ERRO: arquivo nao pode ser aberto na funcao inicializaVetor()";
                    assert(false);
                }
                cout<<endl<<"elemento encontrado com numero de comparacoes igual a :"<<comparacoesBusca<<endl;
                imprimeReviewEspecifica(aux.posicaoBinario,arquivoBinario);
            }
            else{
                cout<<"id nao encontrada com numero de comparacoes igual a:";
                cout<<comparacoesBusca<<endl;
            }
        }
        else{
            return;
        }
    }
}
