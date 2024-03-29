#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <ctime>
#include <thread>

unsigned t0, t1;

using namespace std;

class ListArray{
    int size;
    int *arr;
public:
    ListArray() : size(0){};
    ListArray(int _size,int *_arr){size = _size;arr = _arr;}
    ~ListArray(){delete[] arr;}

    int get_size(){return size;}

    void insert(int,int);
    void in_order(int);
    void remove(int);
    void print();

    //busqueda...
    bool linear_search(int);
    bool binary_search(int);

    //ordenamiento...
    void insertsort();

    void quicksort(int,int);//indices del array inicio y fin (0,size-1)
    int divide(int,int);
    void swap(int*,int*);

    void mergesort(int,int);//indices inicio y fin
    void merge(int,int,int);
};

void ListArray::insert(int pos,int dato){
    int *temp = new int[++size];

    for (int i=0, j=0; i<size; i++){
        if (i == pos){
            *(temp+i) = dato;
        } else {
            *(temp+i) = *(arr+(j++));
        }
    }
    delete[] arr;
    arr = temp;
}

void ListArray::in_order(int dato){
    int *temp = new int[++size];
    int aux = 0;

    while (dato > *(arr+aux)){
        *(temp+aux) = *(arr+aux);
        aux++;
    }
    *(temp+aux) = dato;
    for (int j=aux++, i=aux; i<size; i++, j++){
        *(temp+i) = *(arr+j);
    }
    delete[] arr;
    arr = temp;
}

void ListArray::remove(int pos){
    int *temp = new int[--size];

    for (int i=0, j=0; i<size; i++, j++){
        if (i == pos){ j++; }
        *(temp+i) = *(arr+j);
    }
    delete[] arr;
    arr = temp;
}

void ListArray::print(){
    for (int i=0; i<size; i++){
        cout<<*(arr+i)<<" ";
    }
    cout<<"\n";
}

bool ListArray::linear_search(int dato){
    for (int i=0; i<size; i++){
        if (dato == *(arr+i)){
            cout<<"El dato esta en la posicion "<<i<<endl;
            return 1;
        }
    }
    cout<<"El dato no se encuentra en el arreglo"<<endl;
    return 0;
}

bool ListArray::binary_search(int dato){
    int ini=0,fin=size, mitad=(ini+fin)/2;
    while (mitad <= fin){
        if (dato == *(arr+mitad)){
            cout<<"El dato se encuentra en la posicion "<<mitad<<endl;
            return 1;
        }
        if (dato < *(arr+mitad)){
            fin = mitad;
        } else {
            ini = mitad;
        }
        mitad = (ini+fin)/2;
    }
    cout<<"El dato no se encuentra en el arreglo"<<endl;
    return 0;
}

void ListArray::insertsort(){
    for (int i=0; i<size; i++){
        for (int j=i; j>=0; j--){
            if (*(arr+j) > *(arr+j+1)){
                int aux = *(arr+j);
                *(arr+j) = *(arr+j);
                *(arr+j) = aux;
            }
        }
    }
}

void ListArray::swap(int* a, int* b){
    int c = *a;
    *a = *b;
    *b = c;
}

int ListArray::divide(int izq, int der){
    int pivot = arr[der];
    int i = (izq - 1);

    for (int j=izq; j <= der-1; j++){
        if (arr[j] < pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i+1], &arr[der]);
    return (i + 1);
}

void ListArray::quicksort(int izq, int der){
    if (izq < der){
        int pi = divide(izq, der);
        quicksort(izq, pi - 1);
        quicksort(pi + 1, der);
    }
}

void ListArray::merge(int izq,int m,int der){
    int i,j,k;
    int n1 = m - izq + 1;
    int n2 = der - m;
    int L[n1], R[n2];

    for (i=0; i<n1; i++){
        L[i] = *(arr+izq+i);
    }
    for (j=0; j<n2; j++){
        R[j] = *(arr+m+j+1);
    }

    i = 0; j = 0; k = izq;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            *(arr+k) = L[i];
            i++;
        } else {
            *(arr+k) = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        *(arr+k) = L[i];
        i++; k++;
    }
    while (j < n2){
        *(arr+k) = R[j];
        j++; k++;
    }
}

void ListArray::mergesort(int izq,int der){
    if (izq < der){
        int medio = (der + izq)/2;
        mergesort(izq,medio);
        mergesort(medio+1,der);
        merge(izq,medio,der);
    }
}


void Merge(int *A,int izq,int m,int der){
    int i,j,k;
    int n1 = m - izq + 1;
    int n2 = der - m;
    int L[n1], R[n2];

    for (i=0; i<n1; i++){
        L[i] = A[izq+i];
    }
    for (j=0; j<n2; j++){
        R[j] = A[m+j+1];
    }

    i = 0; j = 0; k = izq;
    while (i < n1 && j < n2){
        if (L[i] <= R[j]){
            A[k] = L[i];
            i++;
        } else {
            A[k] = R[j];
            j++;
        }
        k++;
    }
    while (i < n1){
        A[k] = L[i];
        i++; k++;
    }
    while (j < n2){
        A[k] = R[j];
        j++; k++;
    }
}

void MergeSort(int *A,int izq,int der){

    if (izq < der){
        int medio = (der + izq)/2;
        MergeSort(A,izq,medio);
        MergeSort(A,medio+1,der);
        Merge(A,izq,medio,der);
    }
    this_thread::sleep_for(chrono::milliseconds(1000));
}

int main()
{

    int n = 1000000;
    int *nums = new int[n];
    srand(time(NULL));
    for (int i=1; i<=n; i++){
        *(nums+i-1) = 1+rand()%(n-1);
    }
    ListArray *L1 = new ListArray(n,nums);
    //L1->print();
    t0 = clock();
    //L1->quicksort(0,n-1);
    thread th(MergeSort,nums,0,n-1);
    //th.join();
    t1 = clock();


    double time = (double(t1-t0)/CLOCKS_PER_SEC);
    cout<< time <<endl;

    /*int opc, pos, dato;
    cout<<"Elija una opcion: "<<endl;
    do {
        cout<<"1.Insertar"<<endl;
        cout<<"2.Insertar (en orden)"<<endl;
        cout<<"3.Eliminar"<<endl;
        cout<<"4.Buscar"<<endl;
        cout<<"5.Imprimir"<<endl;
        cout<<"6.Ordenar"<<endl;
        cout<<"7.Salir"<<endl;
        cin>>opc;
        switch (opc){
        case 1:
            cout<<"Posicion: "; cin>>pos;
            cout<<"Numero: "; cin>>dato;
            L1->insert(pos,dato); break;
        case 2:
            cout<<"Numero: "; cin>>dato;
            L1->in_order(dato); break;
        case 3:
            cout<<"Posicion: "; cin>>pos;
            L1->remove(pos); break;
        case 4:
            cout<<"Numero: "; cin>>dato;
            L1->binary_search(dato); break;
        case 5:
            L1->print(); break;
        case 6:
            pos = L1->get_size();
            L1->mergesort(0,pos); break;
        default: break;
        }
    } while (opc != 7);*/

    delete[] nums;
    delete L1;
}
