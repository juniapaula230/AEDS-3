#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

/*Implemente, usando arquivos para simular as fitas de entrada e saída, o método de ordenação externa
Intercalação Balanceada de Vários Caminhos.*/

using namespace std;
//MÉTODO DE ORDENAÇÃO BUBBLE SORT
void bubbleSort(vector<char> &bloco) {
    int n = bloco.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (bloco[j] > bloco[j + 1]) {
                //TROCA OS ELEMENTOS SE ESTIVEREM FORA DE ORDEM
                char temp = bloco[j];
                bloco[j] = bloco[j + 1];
                bloco[j + 1] = temp;
            }
        }
    }
}

//DIVIDI E ORDENA OS BLOCOS DE CARACTERES
void dividirOrdenarBlocos(const string &arquivoEntrada, const string &arquivoSaida, const string &arquivoSaida01, const string &arquivoSaida02) {
//ABERTURA DOS ARQUIVOS DE ENTRADA E SAIDA
    ifstream arquivo(arquivoEntrada);  
    ofstream saida(arquivoSaida);      
    ofstream saida01(arquivoSaida01);
    ofstream saida02(arquivoSaida02);

    string palavra;

    //LOOP QUE LER CADA LINHA DO ARQUIVO DE ENTRADA (PALAVRA POR PALAVRA) 
    while (getline(arquivo, palavra)) {
        vector<char> Fita, Fita01, Fita02;  //ARMAZENA OS BLOCOS DE CARACTERES

        //PREEENCHE OS VETORES FITAS COM OS PRIMEIROS 3 CARACTERES, 3 SEGUINTES E RESPECTIVAMENTE
        for (int i = 0; i < 3 && i < palavra.length(); i++) {
            Fita.push_back(palavra[i]);
        }

        for (int i = 3; i < 6 && i < palavra.length(); i++) {
            Fita01.push_back(palavra[i]);
        }

        for (int i = 6; i < 9 && i < palavra.length(); i++) {
            Fita02.push_back(palavra[i]);
        }

        //ORDENA OS BLOCOS DE CARACTERES  
        bubbleSort(Fita);
        bubbleSort(Fita01);
        bubbleSort(Fita02);

        //ESCREVE OS RESULTADOS NOS ARQUIVOS DE SAIDA
        for (char c : Fita) {
            saida << c; //ESCREVE OS CARACTERES DA FITA01 NO ARQUIVO DE SAIDA01
        }
        saida01 << endl; //PULA PRA PRÓXIMA LINHA NO ARQUIVO DE SAIDA01

        for (char c : Fita01) {
            saida01 << c; //ESCREVE OS CARACTERES DA FITA01 NO ARQUIVO DE SAIDA02
        }
        saida02 << endl; //PULA PRA PRÓXIMA LINHA NO ARQUIVO DE SAIDA02

        for (char c : Fita02) {
            saida02 << c; //ESCREVE OS CARACTERES DA FITA01 NO ARQUIVO DE SAIDA02 (NOVAMENTE)
        }
        saida02 << endl; //PULA PRA PRÓXIMA LINHA NO ARQUIVO DE SAIDA02
    }

    //FECHAMENTO DOS ARQUIVOS
    arquivo.close();
    saida.close();
    saida01.close();
    saida02.close();
}

int main() {
    const string arquivoEntrada = "Entrada.txt";
    const string arquivoSaida = "Fita.txt";
    const string arquivoSaida01 = "Fita01.txt";
    const string arquivoSaida02 = "Fita02.txt";

    //CHAMA A FUNÇÃO PARA DIVIDIR E ORDENAR OS BLOCOS
    dividirOrdenarBlocos(arquivoEntrada, arquivoSaida, arquivoSaida01, arquivoSaida02);

    return 0; 
}
