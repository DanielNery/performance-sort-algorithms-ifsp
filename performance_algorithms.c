/*
    BIBLIOTECAS USADAS
*/

#include <stdio.h>
#include <sys/time.h>
#include <string.h>
#include <locale.h>

/*
    ENCONTRA O SISTEMA OPERACIONAL USADO
    UNIX = Linux/Mac
    WIN = Windowns
*/
#ifdef __unix__
    #include <unistd.h>
    #include <stdlib.h>

#elif defined(_WIN32) || defined(WIN32)

   #define OS_Windows

   #include <windows.h>

#endif


/*
    ESTRUTURA USADA PARA GUARDAR OS DADOS DE TESTE
*/

typedef struct {
    char name[100];
    double unsorted;
    double sorted;

} Algorithm;

/*
    FUNÇÕES USADAS
*/

// Escolhe as opções de execução
void ChooseOptions(int title, Algorithm *algorithms);
// Faz a seleção do tamanho do vetor
int ChooseSize();
// Aloca memória para os vetores usados
int *AllocateMemory(int n);
// Preenche os vetores com valores aleatórios
void FillVector(int *vet, int n);
// Faz a limpeza do terminal de acordo com o sistema operacional
void CleanConsole();
// Printa relatório de desempenho
void print_report(Algorithm *algorithms);

// Funções de Ordenação
void BubbleSort(int *vetor, int n);
void SelectionSort(int *vetor, int n);
void InsertionSort(int *vetor, int n);
void HeapSort(int *vet, int N);
void QuickSort(int *vet, int start, int end);
void RadixSort(int *vetor, int tamanho);
void MergeSort(int *V, int inicio, int fim);

// Auxilia HeapSort
void criaHeap(int *vet, int i, int f);
// Auxilia o MergeSort
void merge(int *V, int inicio, int meio, int fim);

/*
    FUNÇÃO PRINCIPAL DE DEFINIÇÕES
*/

int main(){
    /*
        LIMPANDO CONSOLE E OBTENDO
        VARIÁVEIS IMPORTANTES
    */
    setlocale(LC_ALL, "Portuguese");
    CleanConsole();
    int title = 1;
    Algorithm algorithms[7];
    ChooseOptions(title, &algorithms);

    return 0;
}

/*
    FUNÇÕES AUXILIARES
*/

void CleanConsole(){
    #ifdef OS_Windows
     /* Codigo Windows */
        system("cls");
    #else
     /* Codigo GNU/Linux */
        system("clear");
    #endif
}

void criaHeap(int *vet, int i, int f){
    int aux = vet[i];
    int j = i * 2 + 1;
    while (j <= f){
        if(j < f){
            if(vet[j] < vet[j + 1]){
                j = j + 1;
            }
        }
        if(aux < vet[j]){
            vet[i] = vet[j];
            i = j;
            j = 2 * i + 1;
        }else{
            j = f + 1;
        }
    }
    vet[i] = aux;
}

void merge(int *V, int inicio, int meio, int fim){
    int *temp, p1, p2, tamanho, i, j, k;
    int fim1 = 0, fim2 = 0;
    tamanho = fim-inicio+1;
    p1 = inicio;
    p2 = meio+1;
    temp = (int *) malloc(tamanho*sizeof(int));
    if(temp != NULL){
        for(i=0; i<tamanho; i++){
            if(!fim1 && !fim2){
                if(V[p1] < V[p2])
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];

                if(p1>meio) fim1=1;
                if(p2>fim) fim2=1;
            }else{
                if(!fim1)
                    temp[i]=V[p1++];
                else
                    temp[i]=V[p2++];
            }
        }
        for(j=0, k=inicio; j<tamanho; j++, k++)
            V[k]=temp[j];
    }
    free(temp);
}

int *AllocateMemory(int n){

    printf("\n\nAlocando memória, aguarde um momento...");
    sleep(2);
    int *vet = (int *) malloc(n * sizeof(int));

    if (vet == NULL){
        CleanConsole();
        printf("Erro na alocação de memória");
        exit(1);
    }

    CleanConsole();
    return vet;

}

void FillVector(int *vet, int n){
    printf("\n\nPreenchendo vetor, aguarde um momento...");
    sleep(2);
    int i;
    for (i = 0; i < n; i++){
        vet[i] = rand() % n;
    }
    CleanConsole();
}

void print_report(Algorithm *algorithms){
    int i;

    printf("\n\n==================================");
    printf("\nRelatorio de Desempenho");
    printf("\n==================================");

    for (i = 0; i < 7; i++){
        printf("\nAlgoritmo %s", algorithms[i].name);
        printf("\nUnsorted time %f", algorithms[i].unsorted);
        printf("\nSorted time %f", algorithms[i].sorted);
        printf("\n==============================");
    }
}


/*
    FUNÇÕES DE ORDENAÇÃO
*/


void MergeSort(int *V, int inicio, int fim){
    int meio;
    if(inicio < fim){
        meio = floor((inicio+fim)/2);
        MergeSort(V,inicio,meio);
        MergeSort(V,meio+1,fim);
        merge(V,inicio,meio,fim);
    }

}

void RadixSort(int *vetor, int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;

    b = (int *)calloc(tamanho, sizeof(int));

    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }

    while (maior/exp > 0) {
        int bucket[10] = { 0 };
    	for (i = 0; i < tamanho; i++)
    	    bucket[(vetor[i] / exp) % 10]++;
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
    	for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
    	exp *= 10;
    }

    free(b);
}

void QuickSort(int *vet, int start, int end){

   int pivo, aux, i, j, m, a;

   i = start;
   j = end;

   m = ((i + j) / 2); //definindo o meio do vetor
   pivo = vet[m]; //valor no meio do vetor sendo atribuido como pivo


   do{
       //comparação dos valores da esquerda com o pivo:
      while (vet[i] < pivo) //enquanto o valor da esquerda for menor que o pivo avance uma posição
         i = i + 1;

       //comparação dos valores da direita com o pivo
      while (vet[j] > pivo) //enquanto o valor da direita for maior que o pivo recue uma posição
         j = j - 1;
      //trocar de posição (valor maior a direita com valor menor da esquerda)
      if(i <= j){
         aux = vet[i];
         vet[i] = vet[j];
         vet[j] = aux;
         i = i + 1;
         j = j - 1;
      }



   }while(j > i); //o lopping continua enquanto o valor de j for maior que o de i

   if(start < j) QuickSort(vet, start, j);
   if(i < end) QuickSort(vet, i, end);

}

void HeapSort(int *vet, int N) {
    int i, aux;
    for(i=(N-1)/2; i >= 0; i--){
        criaHeap(vet, i, N-1);
    }
    for (i = N-1; i >= 1; i--){
        aux = vet[0];
        vet[0] = vet[i];
        vet[i] = aux;
        criaHeap(vet, 0, i - 1);
    }

}

void InsertionSort(int *vetor, int n){
     int i, j, aux;
    for (i = 1; i < n; i++) {
        aux = vetor[i];
        for (j = i; (j > 0) && (aux < vetor[j-1]); j--){
            vetor[j] = vetor[j-1];
        }
        vetor[j] = aux;
    }

}

void SelectionSort(int *vetor, int n){
    int i, j, menor, troca;

    for (i = 0; i < n - 1; i++) {
        menor = i;
        for (j = i + 1; j < n; j++){
            if (vetor[j] < vetor[menor]) {
                menor = j;
            }
        }
        if (i != menor) {
            troca = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = troca;
        }
    }


}

void BubbleSort(int *vetor, int n){
    int i, continua, aux;
    int fim = n;

    // Ordenação por bolha
    do {
        continua = 0;
        for (i = 0; i < fim-1; i++) {
            if (vetor[i] > vetor[i+1]){
                aux = vetor[i];
                vetor[i] = vetor[i+1];
                vetor[i+1] = aux;
                continua = i;
            }
        }

        fim --;
    } while (continua != 0 );

}

/*
    FUNÇÕES DE ESCOLHA E MEDIÇÃO
*/

int ChooseSize(){
    //CleanConsole();
    printf("\n\n==================================");
    printf("\nANALISE DE ALGORITMOS DE ORDENACAO");
    printf("\n==================================");
    printf("\nEscolha o tamanho do vetor");

    printf("\n 1 - 1.000");
    printf("\n 2 - 5.000");
    printf("\n 3 - 10.000");
    printf("\n 4 - 20.000");
    printf("\n 5 - 50.000");
    printf("\n 6 - 100.000\n");



    int option;
    printf("\n\nQual tamanho deseja usar?\n");
    scanf("%d", &option);

    switch(option) {
        case 1:
            printf("\n\nEscolhido 1000 elementos ");
            return 1000;
        break;
        case 2:
            printf("\n\nEscolhido 5000 elementos");
            return 5000;
        break;
        case 3:
            printf("\n\nEscolhido 10000 elementos");
            return 10000;
        break;
        case 4:
            printf("\n\nEscolhido 20000 elementos");
            return 20000;
        break;
        case 5:
            printf("\n\nEscolhido 50000 elementos");
            return 50000;
        break;
        case 6:
            printf("\n\nEscolhido 100000 elementos");
            return 100000;
        break;
        default :
            printf("\nOpcao invalida.");
            sleep(5);
            ChooseSize();
        break;
    }
    exit(1);
}

void ChooseOptions(int title, Algorithm *algorithms){
    int *vet, size, option;
    struct timeval Tempo_antes, Tempo_depois;
    double deltaT;



    if (title){
        printf("\n\n==================================");
        printf("\nANALISE DE ALGORITMOS DE ORDENACAO");
        printf("\n==================================");

        printf("\n 1 - BubbleSort");
        printf("\n 2 - InsertionSort");
        printf("\n 3 - SelectionSort");
        printf("\n 4 - RadixSort");
        printf("\n 5 - MergeSort");
        printf("\n 6 - QuickSort");
        printf("\n 7 - HeapSort\n");
        printf("\n 8 - Relatorio de Desempenho\n");

    }

    printf("\n\nQual algoritmo deseja executar?\n");
    scanf("%d", &option);

    switch(option) {
        case 1:
            printf("\n\nOpcao 1");
            algorithms[0].name[30] = 'Teste';
            size = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);

            // Teste desordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            BubbleSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            algorithms[0].unsorted = deltaT;
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", algorithms[0].unsorted);

            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            BubbleSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            algorithms[0].sorted = deltaT;
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", algorithms[0].sorted);

            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 2:
            printf("\n\nOpcao 2");
            size = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);

            // Teste desordenado

            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            InsertionSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", deltaT);
            algorithms[1].unsorted = deltaT;

            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            InsertionSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", deltaT);
            algorithms[1].sorted = deltaT;


            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 3:
            printf("\n\nOpcao 3");
            size = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);


            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            SelectionSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", deltaT);
            algorithms[2].unsorted = deltaT;

            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            SelectionSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", deltaT);
            algorithms[2].sorted = deltaT;


            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 4:
            printf("\n\nOpcao 4");
            size = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);

            // Teste desordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            RadixSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", deltaT);
            algorithms[3].unsorted = deltaT;

            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            RadixSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", deltaT);
            algorithms[3].sorted = deltaT;


            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 5:
            printf("\n\nOpcao 5");
            size = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);

            // Teste desordenado
            printf("\nIniciando teste de desempenho em");
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            MergeSort(vet, 0, size-1);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", deltaT);
            algorithms[4].unsorted = deltaT;

            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            MergeSort(vet, 0, size-1);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", deltaT);
            algorithms[4].sorted = deltaT;


            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 6:
            printf("\n\nOpcao 6");
            size = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);

            // Teste desordenado
            printf("\nIniciando teste de desempenho em");
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            QuickSort(vet, 0, size-1);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", deltaT);
            algorithms[5].unsorted = deltaT;


            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            QuickSort(vet, 0, size-1);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", deltaT);
            algorithms[5].sorted = deltaT;

            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 7:
            printf("\n\nOpcao 7");
            vet = ChooseSize();
            vet = AllocateMemory(size);
            FillVector(vet, size);

            // Teste desordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            HeapSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("\nTempo para execucao do algoritmo desordenado: %f segundos\n", deltaT);
            algorithms[6].unsorted = deltaT;

            // Teste ordenado
            gettimeofday(&Tempo_antes, NULL); // Tempo Inicial
            HeapSort(vet, size);
            gettimeofday(&Tempo_depois, NULL); // Tempo final
            deltaT = (Tempo_depois.tv_sec + Tempo_depois.tv_usec/1000000.0) - (Tempo_antes.tv_sec + Tempo_antes.tv_usec/1000000.0);
            printf("Tempo para execucao do algoritmo ordenado: %f segundos\n", deltaT);
            algorithms[6].sorted = deltaT;


            free(vet);
            ChooseOptions(1, algorithms);
        break;
        case 8:
            CleanConsole();
            printf("\nMontando o relatorio, aguarde um momento...");
            sleep(5);
            return print_report(algorithms);

        default:
            printf("\nOpcao invalida.");
            sleep(5);
            ChooseOptions(1, algorithms);
        break;
    }

    exit(1);
}
