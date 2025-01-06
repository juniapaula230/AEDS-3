#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class Grafo {
private:
    int tamanhoVertice = 0;
    int tamanhoAresta = 0;
    vector<vector<int>> matrizVertices;
    vector<vector<int>> matrizArestas;

public:
    //MÉTODO PARA IMPORTAR UM GRAFO DE UM ARQUIVO 
    void importarGrafo(const string& nomeArquivo) {
        ifstream arquivo(nomeArquivo);
        string line;

        //LÊ O TIPO DE GRAFO (DIRECIONADO OU NÃO) 
        getline(arquivo, line);
        bool direcionado = (line == "1");

        if (direcionado) {
        cout << "Grafo direcionado importado." << endl;
    } else {
        cout << "Grafo não direcionado importado." << endl;
    }

        //LÊ O NÚMERO DE VÉRTICES 
        getline(arquivo, line); //lê a primeira linha do arquivo, contém o número de vértices do grafo
        tamanhoVertice = stoi(line); //converte a linha lida em um número inteiro e armazena esse número na variável
        matrizVertices.resize(2, vector<int>(tamanhoVertice, 0)); //cria uma matriz de tamanho tamanhoVertice x2, cada linha da matriz representa um vértice do grafo

        for (int i = 0; i < tamanhoVertice; i++) { //inicializam a matriz com zeros, para evitar valores inválidos na matriz
            matrizVertices[0][i] = 0;
            matrizVertices[1][i] = 0;
        }

        int a, b, c;
        for (int i = 0; i < tamanhoVertice; i++) { //lêem as coordenadas de cada vértice do arquivo 
            getline(arquivo, line);
            a = 0;
            b = 0;
            c = 0;
            sscanf(line.c_str(), "%d %d %d", &a, &b, &c); //lê as três coordenadas de cada vértice, são armazenadas nas variáveis a, b e c
            matrizVertices[0][i] = b; //as coordenadas são armazenadas na matriz matrizVertices.
            matrizVertices[1][i] = c;
        }

        //LÊ O NÚMERO DE ARESTAS 
        getline(arquivo, line); //lê a primeira linha do arquivo, contém o número de arestas do grafo
        tamanhoAresta = stoi(line); //converte a linha lida em um número inteiro e armazena esse número na variável
        matrizArestas.resize(tamanhoVertice, vector<int>(tamanhoVertice, 0)); //cria uma matriz de tamanho tamanhoVertice x tamanhoVertice. Cada elemento da matriz representa o peso da aresta entre os vértices correspondentes

        for (int i = 0; i < tamanhoAresta; i++) { //
            getline(arquivo, line); //lê a próxima linha do arquivo.
            a = 0;
            b = 0;
            c = 0;
            sscanf(line.c_str(), "%d %d %d", &a, &b, &c); //lê os dois vértices de cada aresta, bem como o peso da aresta


            matrizArestas[a][b] = c; //as informações são armazenadas aqui

            if (!direcionado) {
                matrizArestas[b][a] = c;
            }
        }
        cout << "Arquivo importado com sucesso!" << endl;
    }

    //MÉTODO PARA CRIAR UM GRAFO VAZIO COM UM NÚMERO  ESPECIFICADO DE VÉRTICES 
    void criarGrafoVazio(int numVertices) { 
        tamanhoVertice = numVertices; //define o número de vértices
        matrizVertices.resize(2, vector<int>(numVertices, 0)); //cria uma matriz para armazenar as coordenadas dos vértices
        matrizArestas.resize(numVertices, vector<int>(numVertices, 0)); //cria uma matriz para armazenar as informações das arestas
        cout << "Grafo vazio criado com " << numVertices << " vertices." << endl; //imprime uma mensagem de confirmação
    }

    //MÉTODO PARA EXIBIR A MATRIZ DE ADJACÊNCIAS 
    void exibirMatrizAdjacencias() { 
        cout << "Matriz de Adjacencias: " << endl; //imprime um cabeçalho para a matriz
        for (int i = 0; i < tamanhoVertice; i++) { //imprime os elementos da matriz por linha
            for (int j = 0; j < tamanhoVertice; j++) { //imprime os elementos da matriz por coluna
                cout << matrizArestas[i][j] << " ";
            }
            cout << endl;
        }
    }

    //MÉTODO PARA VERIFICAR SE UM VÉRTICE É ADJACENTE A OUTRO 
    void verificarAdjacencia(int vertice1, int vertice2) {
        if (matrizArestas[vertice1][vertice2] != 0) { //verifica se o valor da matriz de adjacências na posição (vertice1, vertice2) é diferente de zero
            cout << "Os vertices " << vertice1 << " e " << vertice2 << " sao adjacentes." << endl;
        } else {
            cout << "Os vertices " << vertice1 << " e " << vertice2 << " nao sao adjacentes." << endl;
        }
    }

    //MÉTODO PARA INSRRIR UMA NOVA ARESTA ENTRE DOIS VERTICES 
    void inserirAresta(int vertice1, int vertice2, int peso) { 
        if (vertice1 >= 0 && vertice1 < tamanhoVertice && vertice2 >= 0 && vertice2 < tamanhoVertice) { //verifica se os vertices são validos
            matrizArestas[vertice1][vertice2] = peso; //insere a aresta na matriz de adjacências
            matrizArestas[vertice2][vertice1] = peso;  //para grafos não direcionados
            cout << "Aresta adicionada entre os vertices " << vertice1 << " e " << vertice2 << " com peso " << peso << "." << endl;
        } else {
            cout << "INVALIDOS" << endl; //mensagem de erro
        }
    }

    //MÉTODO PARA REMOVER UMA ARESTA ENTRE DOIS VÉRTICES 
    void removerAresta(int vertice1, int vertice2) { 
        if (vertice1 >= 0 && vertice1 < tamanhoVertice && vertice2 >= 0 && vertice2 < tamanhoVertice) { //verifica se os dois vertices são válidos
            if (matrizArestas[vertice1][vertice2] != 0) { //verifica se existe a aresta
                matrizArestas[vertice1][vertice2] = 0;
                matrizArestas[vertice2][vertice1] = 0;  //para grafos não direcionados
                cout << "Aresta removida entre os vertices " << vertice1 << " e " << vertice2 << "." << endl;
            } else {
                cout << "Nao existe aresta entre os vertices " << vertice1 << " e " << vertice2 << "." << endl;
            }
        } else {
            cout << "INVALIDOS" << endl;
        }
    }

    //MÉTODO PARA EDITAR AS COORDENADAS DE UM VÉRTICE 
    void editarCoordenadasVertice(int vertice, int x, int y) {
        if (vertice >= 0 && vertice < tamanhoVertice) { //verifica se o vertice é válido
            matrizVertices[0][vertice] = x; //muda as coordenadas dos vertices
            matrizVertices[1][vertice] = y; //muda as coordenadas dos vertices
            cout << "Coordenadas do vertice " << vertice << " editadas para (" << x << ", " << y << ")." << endl;
        } else {
            cout << "INVALIDOS" << endl;
        }
    }

    //MÉTODO PARA CONSULTAR O PRIMEIRO O PREIMEIRO VÉRTICE ADJACENTE A UM VÉRTICE 
    int consultarPrimeiroAdjacente(int vertice) {
        for (int i = 0; i < tamanhoVertice; i++) {
            if (matrizArestas[vertice][i] != 0) { //verifica se o vertice adjacente existe
                return i;
            }
        }
        return -1;  //se não houver vértices adjacentes
    }

    //MÉTODO PARA CONSULTAR O PRÓXIMO VÉRTICE ADJACENTE A PARTIR DE UM VÉRTICE ADJACENTE INFORMADO
    int consultarProximoAdjacente(int vertice, int adjacenteAtual) {
        for (int i = adjacenteAtual + 1; i < tamanhoVertice; i++) {
            if (matrizArestas[vertice][i] != 0) {
                return i;
            }
        }
        return -1;  //se não houver vértices adjacentes
    }

    //MÉTODO PARA CONSULTAR A LISTA COMPLETA DE VÉRTICES ADJACENTES A UM VÉRTICE 
    void consultarListaAdjacentes(int vertice) {
        cout << "Vertices adjacentes a " << vertice << ": "; //imprime a mensagem de inicio 
        for (int i = 0; i < tamanhoVertice; i++) {
            if (matrizArestas[vertice][i] != 0) { //verifica se o vértice adjacente ainda existe 
                cout << i << " "; //imprime o vértice adjacente
            }
        }
        cout << endl;
    }

    //MÉTODO PARA EXPORTAR O GRAFO PARA UM ARQUIVO DE TEXTO 
    void exportarGrafo(const string& nomeArquivo) {
        ofstream arquivo(nomeArquivo); //cria objeto de arquivo

        //ESCREVE O TIPO DE GRAFO (NÃO DIRECIONADO) 
        arquivo << "0" << endl;

        //ESCREVE O NÚMERO DE VÉRTICES  
        arquivo << tamanhoVertice << endl;

        //ESCREVE AS COORDENADAS DOS VÉRTICES
        for (int i = 0; i < tamanhoVertice; i++) {
            arquivo << i << " " << matrizVertices[0][i] << " " << matrizVertices[1][i] << endl;
        }

        //ESCREVE O NÚMERO DE ARESTAS
        arquivo << tamanhoAresta << endl;

        //ESCREVE AS ARESTAS E PESOS 
        for (int i = 0; i < tamanhoVertice; i++) {
            for (int j = i + 1; j < tamanhoVertice; j++) {
                if (matrizArestas[i][j] != 0) {
                    arquivo << i << " " << j << " " << matrizArestas[i][j] << endl;
                }
            }
        }

        cout << "Grafo exportado com sucesso para " << nomeArquivo << "." << endl;
    }

};

int main() {
    Grafo grafo; //cria a instância de um objeto
    int opcao = 0; //será usada para armazenar a opção selecionada pelo usuário
    string nomeArquivo;

    do {
        cout << "    Informe a opcao desejada: " << endl;
        cout << " 1. Importar grafo de arquivo " << endl;
        cout << " 2. Criar grafo vazio " << endl;
        cout << " 3. Exibir matriz de adjacencias " << endl;
        cout << " 4. Verificar adjacencia entre vertices " << endl;
        cout << " 5. Inserir nova aresta " << endl;
        cout << " 6. Remover aresta " << endl;
        cout << " 7. Editar coordenadas de vertice " << endl;
        cout << " 8. Consultar primeiro adjacente " << endl;
        cout << " 9. Consultar proximo adjacente " << endl;
        cout << " 10. Consultar lista de adjacentes " << endl;
        cout << " 11. Exportar grafo para arquivo " << endl;
        cout << " 12. SAIR " << endl;
        cin >> opcao;

        switch (opcao) { //será usada para executar a opção selecionada pelo usuário
            case 1: {
                cout << "Digite o nome do arquivo a ser importado: ";
                cin >> nomeArquivo;
                grafo.importarGrafo(nomeArquivo);
                break;
            }
            case 2: {
                int numVertices;
                cout << "Digite o numero de vertices para criar o grafo vazio: ";
                cin >> numVertices;
                grafo.criarGrafoVazio(numVertices);
                break;
            }
            case 3: {
                grafo.exibirMatrizAdjacencias();
                break;
            }
            case 4: {
                int vertice1, vertice2;
                cout << "Digite os vertices para verificar adjacencia (Vertice1 Vertice2): ";
                cin >> vertice1 >> vertice2;
                grafo.verificarAdjacencia(vertice1, vertice2);
                break;
            }
            case 5: {
                int vertice1, vertice2, peso;
                cout << "Digite os vertices e o peso da nova aresta (Vertice1 Vertice2 Peso): ";
                cin >> vertice1 >> vertice2 >> peso;
                grafo.inserirAresta(vertice1, vertice2, peso);
                break;
            }
            case 6: {
                int vertice1, vertice2;
                cout << "Digite os vertices da aresta a ser removida (Vertice1 Vertice2): ";
                cin >> vertice1 >> vertice2;
                grafo.removerAresta(vertice1, vertice2);
                break;
            }
            case 7: {
                int vertice, x, y;
                cout << "Digite o vertice e as novas coordenadas (Vertice X Y): ";
                cin >> vertice >> x >> y;
                grafo.editarCoordenadasVertice(vertice, x, y);
                break;
            }
            case 8: {
                int vertice;
                cout << "Digite o vertice para consultar o primeiro adjacente: ";
                cin >> vertice;
                int adjacente = grafo.consultarPrimeiroAdjacente(vertice);
                if (adjacente != -1) {
                    cout << "O primeiro adjacente a " << vertice << " e o vertice " << adjacente << "." << endl;
                } else {
                    cout << "Nao ha vertices adjacentes a " << vertice << "." << endl;
                }
                break;
            }
            case 9: {
                int vertice, adjacenteAtual;
                cout << "Digite o vertice e o adjacente atual para consultar o proximo adjacente: ";
                cin >> vertice >> adjacenteAtual;
                int adjacente = grafo.consultarProximoAdjacente(vertice, adjacenteAtual);
                if (adjacente != -1) {
                    cout << "O proximo adjacente a " << vertice << " apos " << adjacenteAtual << " e o vertice " << adjacente << "." << endl;
                } else {
                    cout << "Nao ha vertices adjacentes a " << vertice << " apos " << adjacenteAtual << "." << endl;
                }
                break;
            }
            case 10: {
                int vertice;
                cout << "Digite o vertice para consultar a lista de adjacentes: ";
                cin >> vertice;
                grafo.consultarListaAdjacentes(vertice);
                break;
            }
            case 11: {
                cout << "Digite o nome do arquivo para exportar o grafo: ";
                cin >> nomeArquivo;
                grafo.exportarGrafo(nomeArquivo);
                break;
            }
            case 12: {
                cout << "SAINDO..." << endl;
                break;
            }
            default: {
                cout << "OPCAO INVALIDA! Por favor, escolha uma opcao valida." << endl;
                break;
            }
        }
    } while (opcao != 12);

    return 0;
}
