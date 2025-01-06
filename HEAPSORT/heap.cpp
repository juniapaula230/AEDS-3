#include <iostream>
#include <vector>

/*Implemente o método de ordenação interna HeapSort.*/

using namespace std;

//FUNÇÃO PARA CONSTRUIR A HEAP 
void constroi(vector<int> &arr, int n, int i) {
    int maior = i;
    int esq = 2 * i + 1;
    int dir = 2 * i + 2;

    //ENCONTRE ÍNDICE DO MAIOR ELEMENTO ENTRE PAI E OS FILHOS 
    if (esq < n && arr[esq] > arr[maior])
        maior = esq;

    if (dir < n && arr[dir] > arr[maior])
        maior = dir;

    //SE MAIOR ELEMENTO NÃO FOR O PAI, TROCA E CONTINUA A CONSTRUÇÃO 
    if (maior != i) {
        swap(arr[i], arr[maior]);
        constroi(arr, n, maior);
    }
}

//FUNÇÃO PARA REFAZER A HEAP DE CIMA PARA BAIXO
void refazDeCimaParaBaixo(vector<int> &arr, int n) {
    //CONSTRUÇÃO COMEÇA A PARTIR DO ÚLTIMO PAI 
    for (int i = n / 2 - 1; i >= 0; i--)
        constroi(arr, n, i);
}

//REFAZ A HEAP DE BAIXO PARA CIMA APÓS INCERSÃO
void refazDeBaixoParaCima(vector<int> &arr, int i) {
    while (i > 0 && arr[(i - 1) / 2] < arr[i]) {
        swap(arr[i], arr[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

//FUNÇÃO PARA REMOVER O ELEMENTO MÁXIMO DA HEAP
void remove(vector<int> &arr, int &n) {
    if (n <= 0)
        return;

    //TROCA O ELEMENTO MÁXIMO COM O ÚLTIMO ELEMENTO 
    swap(arr[0], arr[n - 1]);
    n--;

    //RECONSTRÓI A HEAP APÓS A REMOÇÃO 
    constroi(arr, n, 0);
}

//FUNÇÃO HEAP SORT
void heapSort(vector<int> &arr) {
    int n = arr.size();

    //CONSTRÓI A HEAP INICIAL 
    refazDeCimaParaBaixo(arr, n);

    //EXTRAI ELEMENTOS UM POR UM E RECONSTRÓI A HEAP 
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        constroi(arr, i, 0);
    }
}

int main() {
    vector<int> arr = {12, 11, 13, 5, 6, 7};
    int n = arr.size();

    cout << "Vetor original: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    //APLICA A FUNÇÃO REFAZDECIMAPARABAIXO PARA CONSTRUIR A HEAP 
    refazDeCimaParaBaixo(arr, n);

    cout << "Vetor apos refazDeCimaParaBaixo: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    //INSERE UM NOVO ELEMENTO E RECONSTRÓI A HEAP DE BAIXO PARA CIMA 
    arr.push_back(15);
    n++;
    refazDeBaixoParaCima(arr, n - 1);

    cout << "Vetor apos refazDeBaixoParaCima: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    //REMOVE O ELEMENTO MÁXIMO (RAIZ DA HEAP) 
    remove(arr, n);

    cout << "Vetor apos remocao: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    //APLICA O ALGORITMO HEAP SORT PARA ORDENAÇÃO 
    heapSort(arr);

    cout << "Vetor ordenado: ";
    for (int i = 0; i < n; i++)
        cout << arr[i] << " ";
    cout << endl;

    return 0;
}
