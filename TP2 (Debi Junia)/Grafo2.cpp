#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>
#include <cstdio>
#include <fstream>
#include <iomanip>
#define MAX_VERTICES 100 // o número máximo de vértices do grafo

using namespace std;

// ESTRUTURA VERTICE E PROFUNDIDADE
struct Vertice_Profundidade
{
    int visitado;
    int tempo_inicial;
    int tempo_final;
    int antecessor;
};

// ESTRUTURA VERTICE E LARGURA
struct Vertice_Largura
{
    int cor;
    int distancia;
    int antecessor;
};

// ESTRUTURA ARESTA MENOR CAMINHO
struct Aresta_MC
{
    int origem;
    int destino;
    int peso;
};

// ESTRUTURA VERTICE
struct Vertice
{
    string nome;
};

vector<string> nomesVertices;
vector<vector<int>> matrizAdjacencias;

class Grafo
{
private:
    int tamanhoAresta = 0;
    vector<vector<int>> matrizVertices;
    vector<vector<int>> matrizArestas;
    vector<vector<int>> matrizPesosArestas;
    vector<Vertice_Largura> coordenadas_vertice;
    vector<vector<int>> matriz_adjacencias;
    vector<Vertice> coordenadasVertice;

public:
    int tamanhoVertice;
    vector<Vertice> vertices;

    // ESTRUTURA DE DADOS MAIS EFICIENTES
    vector<vector<int>> matrizAdjacenciasEficiente;
    vector<Vertice> coordenadasVerticesEficientes;

    // MÉTODO PARA IMPORTAR UM GRAFO DE UM ARQUIVO
    void importarGrafo(const string &nomeArquivo)
    {
        ifstream arquivo(nomeArquivo);
        string line;

        // LÊ O TIPO DE GRAFO (DIRECIONADO OU NÃO)
        getline(arquivo, line);
        bool direcionado = (line == "1");

        if (direcionado)
        {
            cout << "Grafo direcionado importado." << endl;
        }
        else
        {
            cout << "Grafo nao direcionado importado." << endl;
        }

        // LÊ O NÚMERO DE VÉRTICES
        getline(arquivo, line);                                   // lê a primeira linha do arquivo, contém o número de vértices do grafo
        tamanhoVertice = stoi(line);                              // converte a linha lida em um número inteiro e armazena esse número na variável
        matrizVertices.resize(2, vector<int>(tamanhoVertice, 0)); // cria uma matriz de tamanho tamanhoVertice x2, cada linha da matriz representa um vértice do grafo

        for (int i = 0; i < tamanhoVertice; i++)
        { // inicializam a matriz com zeros, para evitar valores inválidos na matriz
            matrizVertices[0][i] = 0;
            matrizVertices[1][i] = 0;
        }

        int a, b, c;
        for (int i = 0; i < tamanhoVertice; i++)
        { // lêem as coordenadas de cada vértice do arquivo
            getline(arquivo, line);
            a = 0;
            b = 0;
            c = 0;
            sscanf(line.c_str(), "%d %d %d", &a, &b, &c); // lê as três coordenadas de cada vértice, são armazenadas nas variáveis a, b e c
            matrizVertices[0][i] = b;                     // as coordenadas são armazenadas na matriz matrizVertices.
            matrizVertices[1][i] = c;
        }

        // LÊ O NÚMERO DE ARESTAS
        getline(arquivo, line);                                               // lê a primeira linha do arquivo, contém o número de arestas do grafo
        tamanhoAresta = stoi(line);                                           // converte a linha lida em um número inteiro e armazena esse número na variável
        matrizArestas.resize(tamanhoVertice, vector<int>(tamanhoVertice, 0)); // cria uma matriz de tamanho tamanhoVertice x tamanhoVertice. Cada elemento da matriz representa o peso da aresta entre os vértices correspondentes

        for (int i = 0; i < tamanhoAresta; i++)
        {                           //
            getline(arquivo, line); // lê a próxima linha do arquivo.
            a = 0;
            b = 0;
            c = 0;
            sscanf(line.c_str(), "%d %d %d", &a, &b, &c); // lê os dois vértices de cada aresta, bem como o peso da aresta

            matrizArestas[a][b] = c; // as informações são armazenadas aqui

            if (!direcionado)
            {
                matrizArestas[b][a] = c;
            }
        }
        cout << "Arquivo importado com sucesso!" << endl;
    }

    // MÉTODO PARA EDITAR O NOME DE UM VÉRTICE
    void editarNomeVertice(int vertice, const string &novoNome)
    {
        if (vertice >= 0 && vertice < tamanhoVertice && tamanhoVertice > 0)
        {
            nomesVertices[vertice] = novoNome;
            cout << "Nome do vertice " << vertice << " editado para " << novoNome << "." << endl;

            for (int i = 0; i < tamanhoVertice; i++)
            { // atualiza os nomes nas arestas
                if (matrizArestas[vertice][i] != 0)
                {
                    matrizArestas[vertice][i] = matrizArestas[i][vertice] = stoi(novoNome);
                }
            }
        }
        else
        {
            cout << "Vertice invalido." << endl;
        }
    }

    // MÉTODO PARA CRIAR UM GRAFO VAZIO COM UM NÚMERO  ESPECIFICADO DE VÉRTICES
    void criarGrafoVazio(int numVertices)
    {
        if (tamanhoVertice == 0 && numVertices <= MAX_VERTICES)
        {                                 // verifica se o grafo já foi criado e se o número de vértices é válido
            tamanhoVertice = numVertices; // define o número de vértices
            matrizVertices.resize(numVertices, vector<int>(2, 0));
            nomesVertices.resize(numVertices);                                        // cria uma matriz para armazenar as coordenadas dos vértices
            matrizArestas.resize(numVertices, vector<int>(numVertices, 0));           // cria uma matriz para armazenar as informações das arestas
            cout << "Grafo vazio criado com " << numVertices << " vertices." << endl; // imprime uma mensagem de confirmação
        }
        else if (tamanhoVertice > 0)
        {
            cout << "O grafo ja foi criado." << endl; // imprime uma mensagem de erro
        }
        else
        {
            cout << "O numero de vertices deve ser menor ou igual a " << MAX_VERTICES << "." << endl; // imprime uma mensagem de erro
        }
    }

    // MÉTODO PARA EXIBIR A MATRIZ DE ADJACÊNCIAS
    void exibirMatrizAdjacencias()
    {
        cout << "Matriz de Adjacencias: " << endl; // imprime um cabeçalho para a matriz
        for (int i = 0; i < tamanhoVertice; i++)
        { // imprime os elementos da matriz por linha
            for (int j = 0; j < tamanhoVertice; j++)
            { // imprime os elementos da matriz por coluna
                cout << setw(2) << to_string(matrizArestas[i][j]) << " ";
            }
            cout << endl;
        }
    }

    // MÉTODO PARA VERIFICAR SE UM VÉRTICE É ADJACENTE A OUTRO
    void verificarAdjacencia(int vertice1, int vertice2)
    {
        if (matrizArestas[vertice1][vertice2] == 1)
        { // verifica se o valor da matriz de adjacências na posição (vertice1, vertice2) é igual a 1
            cout << "Os vertices " << vertice1 << " e " << vertice2 << " sao adjacentes." << endl;
        }
        else
        {
            cout << "Os vertices " << vertice1 << " e " << vertice2 << " nao sao adjacentes." << endl;
        }
    }

    // MÉTODO PARA INSRRIR UMA NOVA ARESTA ENTRE DOIS VERTICES
    void inserirAresta(int vertice1, int vertice2, int peso)
    {
        if (vertice1 >= 0 && vertice1 < tamanhoVertice && vertice2 >= 0 && vertice2 < tamanhoVertice)
        {                                             // verifica se os vertices são validos
            matrizArestas[vertice1][vertice2] = peso; // insere a aresta na matriz de adjacências
            matrizArestas[vertice2][vertice1] = peso; // para grafos não direcionados
            tamanhoAresta++;
            cout << "Aresta adicionada entre os vertices " << vertice1 << " e " << vertice2 << " com peso " << peso << "." << endl;
        }
        else
        {
            cout << "INVALIDOS" << endl; // mensagem de erro
        }
    }

    // MÉTODO PARA REMOVER UMA ARESTA ENTRE DOIS VÉRTICES
    void removerAresta(int vertice1, int vertice2)
    {
        if (vertice1 >= 0 && vertice1 < tamanhoVertice && vertice2 >= 0 && vertice2 < tamanhoVertice)
        { // verifica se os dois vertices são válidos
            if (matrizArestas[vertice1][vertice2] != 0)
            { // verifica se existe a aresta
                matrizArestas[vertice1][vertice2] = 0;
                matrizArestas[vertice2][vertice1] = 0; // para grafos não direcionados
                tamanhoAresta--;
                cout << "Aresta removida entre os vertices " << vertice1 << " e " << vertice2 << "." << endl;
            }
            else
            {
                cout << "Nao existe aresta entre os vertices " << vertice1 << " e " << vertice2 << "." << endl;
            }
        }
        else
        {
            cout << "INVALIDOS" << endl;
        }
    }

    // MÉTODO PARA EDITAR AS COORDENADAS DE UM VÉRTICE
    void editarCoordenadasVertice(int vertice, int x, int y)
    {
        if (vertice >= 0 && vertice < tamanhoVertice && tamanhoVertice > 0)
        {                                   // verifica se o vertice é válido
            matrizVertices[0][vertice] = x; // muda as coordenadas dos vertices
            matrizVertices[1][vertice] = y; // muda as coordenadas dos vertices
            cout << "Coordenadas do vertice " << vertice << " editadas para (" << x << ", " << y << ")." << endl;
        }
        else
        {
            cout << "INVALIDOS" << endl;
        }
    }

    // MÉTODO PARA CONSULTAR O PRIMEIRO O PRIMEIRO VÉRTICE ADJACENTE A UM VÉRTICE
    int consultarPrimeiroAdjacente(int vertice)
    {
        for (int i = 0; i < tamanhoVertice; i++)
        {
            if (matrizArestas[vertice][i] != 0)
            { // verifica se o vertice adjacente existe
                return i;
            }
        }
        return -1; // se não houver vértices adjacentes
    }

    // MÉTODO PARA CONSULTAR O PRÓXIMO VÉRTICE ADJACENTE A PARTIR DE UM VÉRTICE ADJACENTE INFORMADO
    int consultarProximoAdjacente(int vertice, int adjacenteAtual)
    {
        for (int i = adjacenteAtual + 1; i < tamanhoVertice; i++)
        {
            if (matrizArestas[vertice][i] != 0)
            {
                return i;
            }
        }
        return -1; // se não houver vértices adjacentes
    }

    // MÉTODO PARA CONSULTAR A LISTA COMPLETA DE VÉRTICES ADJACENTES A UM VÉRTICE
    void consultarListaAdjacentes(int vertice)
    {
        cout << "Vertices adjacentes a " << vertice << ": "; // imprime a mensagem de inicio
        for (int i = 0; i < tamanhoVertice; i++)
        {
            if (matrizArestas[vertice][i] != 0)
            {                     // verifica se o vértice adjacente ainda existe
                cout << i << " "; // imprime o vértice adjacente
            }
        }
        cout << endl;
    }

    // MÉTODO PARA EXPORTAR O GRAFO PARA UM ARQUIVO DE TEXTO
    void exportarGrafo(const string &nomeArquivo)
    {
        ofstream arquivo(nomeArquivo); // cria objeto de arquivo

        arquivo << "NAO DIRECIONADO" << endl;

        arquivo << tamanhoVertice << endl; // escreve o número de vértices

        for (int i = 0; i < tamanhoVertice; i++)
        { // escreve as coordenadas dos vértices
            arquivo << i << " " << matrizVertices[0][i] << " " << matrizVertices[1][i] << endl;
        }

        arquivo << tamanhoAresta << endl; // escreve o número de arestas

        for (int i = 0; i < tamanhoVertice; i++)
        { // escreve as arestas e pesos
            for (int j = i + 1; j < tamanhoVertice; j++)
            {
                if (matrizArestas[i][j] != 0)
                {
                    arquivo << i << " " << j << " " << matrizArestas[i][j] << endl;
                }
            }
        }

        cout << "Grafo exportado com sucesso para " << nomeArquivo << "." << endl;
    }

    // FUNÇÃO DE BUSCA EM PROFUNDIDADE
    void dfs(int vertice, int &tempo, Vertice_Profundidade *buscaP)
    {
        tempo = 0;

        buscaP[vertice].visitado = 1; // marca o vértice como visitado
        buscaP[vertice].tempo_inicial = tempo++;

        cout << vertice << " "
             << "DESCOBERTO" << endl;

        for (int i = 0; i < tamanhoVertice; i++)
        { // percorre os vértices adjacentes ao vértice atual
            if (matrizArestas[vertice][i] != 0 && buscaP[i].visitado == -1)
            {                                   // verifica se o vértice adjacente não foi visitado
                buscaP[i].antecessor = vertice; // marca o vértice adjacente como visitado
                dfs(i, tempo, buscaP);
            }
        }

        buscaP[vertice].visitado = 2; // marca o vértice como terminado
        buscaP[vertice].tempo_final = tempo++;

        cout << vertice << " "
             << "Terminado no tempo: " << buscaP[vertice].tempo_final << endl;
    }
    // FUNÇÃO DE BUSCA EM PROFUNDIDADE
    int buscaEmProfundidade(int verticeOrigem)
    {
        if (verticeOrigem < 0 || verticeOrigem >= tamanhoVertice)
        { // verifica se o vértice inicial existe
            cout << "O vertice inicial nao existe" << endl;
            return -1;
        }

        Vertice_Profundidade buscaP[tamanhoVertice]; // marca o vértice inicial como visitado
        for (int i = 0; i < tamanhoVertice; i++)
        {
            buscaP[i].visitado = -1;
        }

        buscaP[verticeOrigem].visitado = 1;

        dfs(verticeOrigem, buscaP[verticeOrigem].tempo_inicial, buscaP); // chama a função recursivamente para o vértice inicial

        return verticeOrigem;
    }
    // MÉTODO BUSCA EM LARGURA
    void buscaEmLargura(int verticeInicial)
    {
        if (verticeInicial < 0 || verticeInicial >= tamanhoVertice)
        { // verifica se o vértice inicial existe
            cout << "O vertice inicial nao existe" << endl;
            return;
        }

        vector<bool> visitados(tamanhoVertice, false); // cria um vetor de bool para armazenar as informações sobre cada vértice
        visitados[verticeInicial] = true;              // marca o vértice inicial como visitado
        queue<int> fila;                               // cria uma fila para armazenar os vértices a serem visitados
        fila.push(verticeInicial);

        for (int verticeAtual = fila.front(); !fila.empty(); verticeAtual = fila.front())
        { // percorre a fila até que ela esteja vazia
            fila.pop();
            cout << "Visitando vertice: " << vertices[verticeAtual].nome << endl; // imprime o vértice atual
            cout << vertices[verticeAtual].nome << endl;
            for (int i = 0; i < tamanhoVertice; i++)
            { // percorre os vértices adjacentes ao vértice atual
                if (matrizArestas[verticeAtual][i] != 0 && !visitados[i])
                {                        // verifica se o vértice adjacente não foi visitado
                    visitados[i] = true; // marca o vértice adjacente como visitado
                    fila.push(i);
                }
            }
        }
    }

    int buscaVerticePorNome(string nomeDoVerticeInicial)
    {
        if (nomeDoVerticeInicial.empty())
        { // verifica se o nome do vértice é válido
            cout << "O nome do vertice inicial e invalido" << endl;
            return -1;
        }
        for (int i = 0; i < tamanhoVertice; i++)
        { // percorre todos os vértices
            if (vertices[i].nome == nomeDoVerticeInicial)
            {             // se o nome do vértice atual for igual ao nome fornecido
                return i; // retorna o índice do vértice
            }
        }
        return -1; // o vértice não foi encontrado
    }

    // MÉTODO PARA ENCONTRAR A ARESTA DE MENOR PESO EM UM CONJUNTO DE ARESTAS
    size_t encontrarMenorAresta(const vector<int> &chave, const vector<bool> &mstSet)
    {
        size_t minimoIndex = -1; // armazena o vértice com a menor chave
        int minimo = INT_MAX;

        for (size_t i = 0; i < chave.size(); i++)
        {
            if (!mstSet[i] && chave[i] <= minimo)
            {
                minimo = chave[i];
                minimoIndex = i;
            }
        }
        return minimoIndex;
    }

    // ALGORITMO DE PRIM PARA ENCONTRAR A ÁRVORE GERADORA MÍNIMA
    void primAGM(int raiz)
    {
        vector<bool> visitado(tamanhoVertice, false); //inicializa o vértice inicial
        visitado[raiz] = true;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> filaP; //cria uma fila de prioridades para armazenar as arestas que ainda não foram adicionadas à árvore

        for (int i = 0; i < tamanhoVertice; i++)
        { // adiciona as arestas que saem do vértice inicial à fila de prioridades
            if (matrizArestas[raiz][i] != 0)
            {
                filaP.push({matrizArestas[raiz][i], i});
            }
        }

        while (!filaP.empty())
        {                                     // percorre a fila de prioridades, adicionando as arestas à árvore
            pair<int, int> aux = filaP.top(); // remove a aresta com o menor custo da fila de prioridades
            filaP.pop();

            if (!visitado[aux.second])
            {                                // verifica se o vértice adjacente à aresta removida ainda não foi visitado
                visitado[aux.second] = true; // marca o vértice adjacente como visitado
                raiz = aux.second;           // atualiza o vértice inicial para o vértice adjacente

                for (int i = 0; i < tamanhoVertice; i++)
                { // adiciona as arestas que saem do vértice adjacente à fila de prioridades
                    if (matrizArestas[raiz][i] != 0 && !visitado[i])
                    {
                        filaP.push({matrizArestas[raiz][i], i});
                    }
                }
            }
        }
    }
    // MÉTODO PARA ENCONTRAR O VÉRTICE COM A DISTÂNCIA MÍNIMA ENTRE OS VÉRTICES NÃO INCLUÍDOS NA ÁRVORE DE CAMINHO MÍNIMO
    int encontrarVerticeMinimo(int tamanhoVertice, const vector<int> &distancia, const vector<bool> &incluido)
    {
        int minimo = INT_MAX, minimoIndex = -1; // armazena o vértice com a menor distância

        for (int i = 0; i < tamanhoVertice; i++)
        { // percorre todos os vértices
            if (!incluido[i] && distancia[i] < minimo)
            { // verifica se o vértice não está na árvore de caminhos mínimos //verifica se o vértice tem a menor distância
                // atualiza o vértice com a menor distância
                minimo = distancia[i];
                minimoIndex = i;
            }
        }

        return minimoIndex; // retorna o índice do vértice com a menor distância*
    }

    // METODO PARA BUSCAR NOME
    int buscaNome()
    {
        string nome; // armazena o nome do vértice
        cout << "Informe o nome de um vertice: ";

        cin.clear();               // limpa o fluxo de entrada
        cin.ignore(INT_MAX, '\n'); // ignora todos os caracteres até encontrar um '\n'
        getline(cin, nome);        // lê o nome do vértice

        for (int i = 0; i < tamanhoVertice; i++)
        { // percorre todos os vértices
            cout << "Comparando nomes:" << nomesVertices[i] << ":" << nome << ".." << endl;

            if (nomesVertices[i] == nome)
            { // verifica se o nome do vértice foi encontrado
                cout << "O vertice " << nomesVertices[i] << " foi encontrado." << endl;
                return i; // retorna o índice do vértice
            }
        }
        cout << "O vertice " << nome << " nao foi encontrado." << endl;
        return -1; // retorna -1 se o vértice não foi encontrado
    }

    // FUNÇÃO DIJKSTRA
    void Dijkstra(int origem, int destino){
        vector<int> distancia(tamanhoVertice, INT_MAX); // vetor para armazenar as distâncias mínimas
        vector<bool> visitado(tamanhoVertice, false);   // vetor para rastrear os vértices visitados

        distancia[origem] = 0; // a distância da origem para ela mesma é zero

        for (int i = 0; i < tamanhoVertice - 1; ++i)
        {
            int u = -1;

            for (int j = 0; j < tamanhoVertice; ++j)
            { // encontrar o vértice não visitado com a menor distância
                if (!visitado[j] && (u == -1 || distancia[j] < distancia[u]))
                {
                    u = j;
                }
            }

            visitado[u] = true; // marcar o vértice como visitado

            for (int v = 0; v < tamanhoVertice; ++v){ // relaxamento das arestas adjacentes ao vértice escolhido
                int peso = matrizAdjacencias[u][v];
                if (peso != -1 && distancia[u] != INT_MAX && distancia[u] + peso < distancia[v])
                {
                    distancia[v] = distancia[u] + peso;
                }
            }
        }

        cout << "Distancias minimas a partir do vertice " << origem << ":" << endl;
        for (int i = 0; i < tamanhoVertice; ++i)
        {
            cout << "Para o vertice " << i << ": " << distancia[i] << endl;
        }
    }
};

int main()
{
    Grafo grafo;
    int opcao = 0;
    string nomeArquivo, nomeVerticeOrigem, nomeVerticeDestino;

    do
    {
        cout << "Informe a opcao desejada: " << endl;
        cout << "1. Importar grafo de arquivo" << endl;
        cout << "2. Criar grafo vazio" << endl;
        cout << "3. Exibir matriz de adjacencias" << endl;
        cout << "4. Verificar adjacencia entre vertices" << endl;
        cout << "5. Inserir nova aresta" << endl;
        cout << "6. Remover aresta" << endl;
        cout << "7. Editar coordenadas de vertice" << endl;
        cout << "8. Consultar primeiro adjacente" << endl;
        cout << "9. Consultar proximo adjacente" << endl;
        cout << "10. Consultar lista de adjacentes" << endl;
        cout << "11. Exportar grafo para arquivo" << endl;
        cout << "12. Editar nome de vertice" << endl;
        cout << "13. Busca em profundidade" << endl;
        cout << "14. Busca em largura" << endl;
        cout << "15. Executar Prim" << endl;
        cout << "16. Dijkstra" << endl;
        cout << "17. SAIR" << endl;

        cin >> opcao;

        switch (opcao)
        {
        case 1:
        {
            cout << "Digite o nome do arquivo a ser importado: ";
            cin >> nomeArquivo;
            grafo.importarGrafo(nomeArquivo);
            break;
        }
        case 2:
        {
            int numVertices;
            cout << "Digite o numero de vertices para criar o grafo vazio: ";
            cin >> numVertices;
            grafo.criarGrafoVazio(numVertices);
            break;
        }
        case 3:
        {
            grafo.exibirMatrizAdjacencias();
            break;
        }
        case 4:
        {
            int vertice1, vertice2;
            cout << "Digite os vertices para verificar adjacencia (Vertice1 Vertice2): ";
            cin >> vertice1 >> vertice2;
            grafo.verificarAdjacencia(vertice1, vertice2);
            break;
        }
        case 5:
        {
            int vertice1, vertice2, peso;
            cout << "Digite os vertices e o peso da nova aresta (Vertice1 Vertice2 Peso): ";
            cin >> vertice1 >> vertice2 >> peso;
            grafo.inserirAresta(vertice1, vertice2, peso);
            break;
        }
        case 6:
        {
            int vertice1, vertice2;
            cout << "Digite os vertices da aresta a ser removida (Vertice1 Vertice2): ";
            cin >> vertice1 >> vertice2;
            grafo.removerAresta(vertice1, vertice2);
            break;
        }
        case 7:
        {
            int vertice, x, y;
            cout << "Digite o vertice e as novas coordenadas (Vertice X Y): ";
            cin >> vertice >> x >> y;
            grafo.editarCoordenadasVertice(vertice, x, y);
            break;
        }
        case 8:
        {
            int vertice;
            cout << "Digite o vertice para consultar o primeiro adjacente: ";
            cin >> vertice;
            int adjacente = grafo.consultarPrimeiroAdjacente(vertice);
            if (adjacente != -1)
            {
                cout << "O primeiro adjacente a " << vertice << " e o vertice " << adjacente << "." << endl;
            }
            else
            {
                cout << "Nao ha vertices adjacentes a " << vertice << "." << endl;
            }
            break;
        }
        case 9:
        {
            int vertice, adjacenteAtual;
            cout << "Digite o vertice e o adjacente atual para consultar o proximo adjacente: ";
            cin >> vertice >> adjacenteAtual;
            int adjacente = grafo.consultarProximoAdjacente(vertice, adjacenteAtual);
            if (adjacente != -1)
            {
                cout << "O proximo adjacente a " << vertice << " apos " << adjacenteAtual << " e o vertice " << adjacente << "." << endl;
            }
            else
            {
                cout << "Nao ha vertices adjacentes a " << vertice << " apos " << adjacenteAtual << "." << endl;
            }
            break;
        }
        case 10:
        {
            int vertice;
            cout << "Digite o vertice para consultar a lista de adjacentes: ";
            cin >> vertice;
            grafo.consultarListaAdjacentes(vertice);
            break;
        }
        case 11:
        {
            cout << "Digite o nome do arquivo para exportar o grafo: ";
            cin >> nomeArquivo;
            grafo.exportarGrafo(nomeArquivo);
            break;
        }
        case 12:
        {
            int vertice;
            cout << "Digite o vertice para editar o nome: ";
            cin >> vertice;
            string novoNome;
            cout << "Digite o novo nome: ";
            cin >> novoNome;
            grafo.editarNomeVertice(vertice, novoNome);
            break;
        }
        case 13:
        {
            cout << "Digite o vertice de origem para a busca em profundidade: ";
            int verticeOrigem;
            cin >> verticeOrigem;
            int verticeRetornado = grafo.buscaEmProfundidade(verticeOrigem); // passa o vértice de origem para a função
            cout << "O vertice de origem retornado pela funcao e: " << verticeRetornado << endl;
            break;
        }
        case 14:
        {
            cout << "Digite o nome do vertice de origem para a busca em largura: ";
            string nomeVerticeOrigem;
            cin >> nomeVerticeOrigem;
            int verticeOrigem = grafo.buscaVerticePorNome(nomeVerticeOrigem); // busca o vértice de origem na matriz de vértices
            grafo.buscaEmLargura(verticeOrigem);                              // chama a função
            break;
        }
        case 15:
        {
            grafo.primAGM(0); // inicializa o vértice inicial
            break;
        }
        case 16:
        {
            int origem = grafo.buscaVerticePorNome(nomeVerticeOrigem); // inicializa o vértice de origem
            int destino = grafo.buscaVerticePorNome(nomeVerticeDestino);
            grafo.Dijkstra(origem, destino);
            break;
        }
        case 17:
        {
            cout << "SAINDO..." << endl;
            break;
        }
        default:
        {
            cout << "Opcao invalida. Tente novamente." << endl;
            break;
        }
        }
    } while (opcao != 17);

    return 0;
}