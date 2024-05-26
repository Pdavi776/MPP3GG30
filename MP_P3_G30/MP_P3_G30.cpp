/*********************
****** MP_P3_G30 *****
***********************/

#pragma warning(disable: 4996)
#pragma warning(disable: 6031)

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#define MAX_BUFFER 1024
#define V1len sizeof(V1) / sizeof(V1[0])
#define V2len sizeof(V2) / sizeof(V2[0])


int buscar_numero(int* vector, int pos, int len, int num);
void imprimir_vector(int* vector, int pos, int len);
long int prodVect(int* vector, int pos, int len);
void invertDigito(int* vector, int pos, int len);
int contarParesVector(int* vector, int pos, int len, int cont);
void combinarVectores(int* V1, int len1, int* V2, int len2, int* V3, int pos1, int pos2, int cont);
void Merge_Sort(int vector[], int inicio, int fin);
void merge(int vector[], int inicio, int medio, int fin);
void combinarOrdenar_ITER(int* V1, int* V2, int len1, int len2, int* V3);
void swap(int* num1, int* num2);
void array_arrange(int* vector, int len);
void RECUR_comb_y_ord_vect(int* V1, int* V2, int* V3,
    int pos1, int pos2,
    int len1, int len2,
    int cont);

int main()
{
    int V1[] = { 1, 12, 23, 28, 35 };
    int V2[] = { 15, 25, 32, 70, 91 };
    int V3[V1len + V2len] = {};
    int V3len = V1len + V2len;
    //hallo la longitud donde creo el array para evitar el decay

    //otras variables
    int opt = 0, numPares = 0;
    long int sol = 0;

    printf("MENU\n");
    printf("=========\n");
    printf("1. Producto de los Elementos del Vector v1\n");
    printf("2. Invertir digitos de un elemento del vector v1\n");
    printf("3. Contar Pares en el vector v1\n");
    printf("4. Combinar Vectores v1 y v2 (sin ordenar)\n");
    printf("5. Combinar Vectores v1 y v2 (ordenado ascendente) (version iterativa)\n");
    printf("6. Combinar Vectores v1 y v2 (ordenado ascendente) (version recursiva)\n");
    printf("0. Salir\n");
    printf("Elija opcion: ");
    scanf("%d", &opt);

    switch (opt) {
    case 1:
        sol = prodVect(V1, 0, V1len);
        printf("el resultado del producto de todos los elementos del array es: %d\n", sol);
        system("pause");
        break;
    case 2:
        invertDigito(V1, 0, V1len);
        break;
    case 3:
        numPares = contarParesVector(V1, 0, V1len, 0);
        printf("\n\n Nº de pares en el vector: %d\n", numPares);
        system("\n\n pause");
        break;
    case 4:
        system("cls");
        combinarVectores(V1, V1len, V2, V2len, V3, 0, 0, 0);
        printf("\n Vector 1: ");
        imprimir_vector(V1, 0, V1len);
        printf("\n Vector 2: ", V2);
        imprimir_vector(V2, 0, V2len);
        printf("\n Vector combinado resultante: ");
        imprimir_vector(V3, 0, V1len + V2len);
        system("\n pause");
        break;
    case 5:
        combinarOrdenar_ITER(V1, V2, V1len, V2len, V3);
        printf("vector combinado y ordenado: \n");
        imprimir_vector(V3, 0, V3len);
        system("pause");
        break;
    case 6:
        RECUR_comb_y_ord_vect(V1, V2, V3, 0, 0, V1len, V2len, 0);
        imprimir_vector(V3, 0, V1len + V2len);
        break;
    case 0:
        printf("Saliendo del programa...\n");
        return 0;
    default:
        printf("Opcion no valida. Intenta de nuevo.\n");
    }

    return 0;
}


int buscar_numero(int* vector, int pos, int len, int num) {
    //condición de parada que incluye el caso base
    if (pos == len) { return 0; }

    if (vector[pos] == num) {
        return 1;
    }
    else {
        return buscar_numero(vector, pos + 1, len, num);
    }
}


void imprimir_vector(int* vector, int pos, int len) {
    if (pos < len) {
        printf("%d ", vector[pos]);
        imprimir_vector(vector, pos + 1, len);
    }
    else {
        printf("\n");
        return;
    }
}


//f(V1) = 270.480
long int prodVect(int* V1, int pos, int len) {
    //caso general: vector de 1 elemento y el no vector
    if (len == 1) { return *V1; }
    if (len == 0) { return 0; }

    if (pos == len - 1) { return V1[pos]; }
    while (pos < len) {
        return V1[pos] * prodVect(V1, pos + 1, len);
    }
    return -1;
}


void invertir_string(char* entrada, char* salida, int pos, int len) {
    //caso paerticular: si final del string, lo devuelvo
    if (entrada[pos] == '\0') { return; }

    //caso general:
    else {
        salida[len - 1] = entrada[pos];
        return invertir_string(entrada, salida, pos + 1, len - 1);
    }
}


void invertDigito(int* vector, int pos, int len) {
    system("cls");
    imprimir_vector(vector, pos, len);
    int num = 0, invertido = 0, resto;
    char entrada[1024], salida[1024];
    memset(salida, '\0', sizeof(salida));

    printf("introduce el número que deseas invertir: ");
    scanf("%d", &num);
    if (buscar_numero(vector, pos, len, num)) {
        sprintf(entrada, "%d", num);//conversión de entero a string
        invertir_string(entrada, salida, 0, strlen(entrada));
        printf("el número invertido es: %s", salida);
    }
    else {
        printf("el numero no se encontró");
        system("pause");
    }
}//fin subpr


//el programa funciona de forma similar al del producto; 
// se llama con la siguiente posición del vector pero 
// en este caso la lógica es comprobar si es par (obviamente).
int contarParesVector(int* vector, int pos, int len, int cont) {
    //caso general: el no vector
    if (len == 0) { return 0; }

    if (pos == len - 1) { return cont; }
    while (pos < len) {
        if (vector[pos] % 2 == 0) { cont++; }
        return contarParesVector(vector, pos + 1, len, cont);
    }
    return -1;
}

void combinarVectores(int* V1, int len1, int* V2, int len2, int* V3, int pos1, int pos2, int cont) {

    if (len1 == 0) { V2; }
    if (len2 == 0) { V1; }
    if ((len1 == 0) && (len2 == 0)) { 0; }

    while (len1 <= pos1 - 1 || len2 <= pos1 - 1)
    {
        return;
    }
    if (pos1 <= len1)
    {
        V3[cont] = V1[pos1];
        cont++;
    }
    if (pos2 <= len1 - 1)
    {
        V3[cont] = V2[pos2];
        cont++;
    }
    combinarVectores(V1, len1, V2, len2, V3, pos1 + 1, pos2 + 1, cont);
}


//ordenacion recursiva

//MERGESORT

void Merge_Sort(int vector[], int inicio, int fin) {
    int largo = fin - inicio;
    if (largo < 2)
    {
        return;
    }
    int medio = (inicio + fin) / 2;
    Merge_Sort(vector, inicio, medio);
    Merge_Sort(vector, medio, fin);
    merge(vector, inicio, medio, fin);
}

void merge(int vector[], int inicio, int medio, int fin) {
    int pos1 = inicio;
    int pos2 = medio;
    int b = fin - inicio;
    int* aux = (int*)malloc(b * sizeof(int));
    int pos_a = 0;

    if ((inicio == fin) || (inicio == medio) || (medio == fin)) {
        return;
    }
    while ((pos1 < medio) && pos2 < fin) {
        if (vector[pos1] <= vector[pos2]) {
            aux[pos_a] = vector[pos1];
            pos_a++; pos1++;
        }
        else {
            aux[pos_a] = vector[pos2];
            pos_a++; pos2++;
        }
    }
    while (pos1 < medio) {
        aux[pos_a] = vector[pos1];
        pos_a++; pos1++;
    }
    while (pos2 < fin) {
        aux[pos_a] = vector[pos2];
        pos_a++; pos2++;
    }

    int a = 0; int i = inicio;
    while (i < fin)
    {
        vector[i] = aux[a];
        i++; a++;
    }
}


void combinarOrdenar_ITER(int* V1, int* V2, int len1, int len2, int* V3) {
    int i = 0, j = 0, k = 0;

    while (i < len1 && j < len2) {
        if (V1[i] <= V2[j])
        {
            V3[k] = V1[i];
            k++; i++;
        }
        else
        {
            V3[k] = V2[j];
            k++; j++;
        }
    }
    while (i < len1) {
        V3[k] = V1[i];
        k++; i++;
    }
    while (j < len2) {
        V3[k] = V2[j];
        k++; j++;
    }
}

void swap(int* num1, int* num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

void array_arrange(int* vector, int len) {
    int i = 0, j = 0;
    for (i = 0; i < len; i++) {
        for (j = 0; j < len - 1; j++) {
            if (vector[j] > vector[j + 1]) { swap(&vector[j], &vector[j + 1]); }
        }
        //printf("máximo valor de la %d iteración: %d\n", i, vector[j-i]);
    }
}

void RECUR_comb_y_ord_vect(int* V1, int* V2, int* V3,
    int pos1, int pos2,
    int len1, int len2,
    int cont) {
    //primero combino los vectores
    combinarVectores(V1, len1, V2, len2, V3, 0, 0, 0);
    array_arrange(V3, len1 + len2);
}