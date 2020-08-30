#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <vector>
using namespace std;

int quantum = 30;

int contadorFila = 9; // Contagem de processos na fila.
int prioridadeFila = 10;

int frenteFila = 0; // Primeira posição da fila

struct processo
{
    int prioridadeOriginal = 0;
    int prioridadeDinamica = 0;
    int tempo = 0;
    int status = 1;
};
struct processo p[10];

int inicializa()
{
    int pri[] = {3, 2, 5, 8, 3, 1, 1, 4, 6, 1};
    int temp[] = {300, 250, 100, 200, 250, 150, 100, 200, 300, 200};

    for (int x = 0; x < 10; x++)
    {

        p[x].prioridadeOriginal = pri[x];
        p[x].prioridadeDinamica = pri[x];
        p[x].tempo = temp[x];
    }
    return 0;
}

void round_robbin()
{
    inicializa();
    // int contadorFila = 9; // Contagem de processos na fila.
    int frenteFila = 0; // Primeira posição da fila
    while (contadorFila != 0)
    {
        while (&p[frenteFila] <= 0)
        { // Tira processos que acabaram da primeira posição ( EM TESTE ).
            frenteFila++;
            if (frenteFila >= 9)
            { // Faz a rotação
                frenteFila = 0;
            }
        }
        if (p[frenteFila].tempo > 0 && p[frenteFila].status == 1)
        {
            printf("\n\nO processo %d vai para o comeco da fila com %d ms", frenteFila, p[frenteFila].tempo);
            printf("\nExecuta ate %d ms", quantum);
            p[frenteFila].tempo = p[frenteFila].tempo - quantum; // Calculo de quantos ms se passaram e quantos ficaram.
            if (p[frenteFila].tempo <= 0)
            {
                p[frenteFila].status = 2;
                printf("\nE sai da fila.\n");
                contadorFila--;
            }
            else
            {
                printf("\nE vai pro final da fila com %d ms restantes.\n\n", p[frenteFila].tempo);
            }
            system("pause");
        }
        frenteFila++; //Atualiza a primeira posição da fila.
        if (frenteFila > 9)
        { //Faz a rotação
            frenteFila = 0;
        }
    }
    cout << "\n\n :::: Fim :::: \n";
}

void processa()
{

    printf("\n\nO processo %d vai para o comeco da fila com %d ms", frenteFila, p[frenteFila].tempo);
    printf("\nExecuta ate %d ms", quantum);
    p[frenteFila].tempo = p[frenteFila].tempo - quantum; // Calculo de quantos ms se passaram e quantos ficaram.
    if (p[frenteFila].tempo <= 0)
    {
        p[frenteFila].status = 2;
        printf("\nE sai da fila.\n");
        contadorFila--;
    }
    else
    {
        printf("\nE vai pro final da fila com %d ms restantes.\n\n", p[frenteFila].tempo);
    }
}
void priord()
{
    inicializa();
    while (contadorFila != 0)
    { //enquanto houver processo na fila
        while (&p[frenteFila] <= 0)
        { // Tira processos que acabaram da primeira posição.
            frenteFila++;
            if (frenteFila >= 9)
            { // Faz a rotação
                frenteFila = 0;
            }
        }
        if (p[frenteFila].tempo > 0 && p[frenteFila].status == 1) // se esse processo ainda tem coisa para processar
        {

            if (p[frenteFila].prioridadeDinamica == 10)
            {
                processa();
                p[frenteFila].prioridadeDinamica = p[frenteFila].prioridadeOriginal;
            }
            else
            {

                p[frenteFila].prioridadeDinamica++;

                printf("\n\nO processo %d", frenteFila);

                printf("\nProcesso ignorado, aumentado sua prioridade para: %d\n\n", p[frenteFila].prioridadeDinamica);

                //frenteFila++; //Atualiza a primeira posição da fila.
                if (frenteFila > 9)
                { //Faz a rotação
                    frenteFila = 0;
                }
            }
            system("pause");
        }
        frenteFila++; //Atualiza a primeira posição da fila.
        if (frenteFila > 9)
        { //Faz a rotação
            frenteFila = 0;
        }
    }
    cout << "\n\n :::: Fim :::: \n";
}

int main()
{
    int opc = 3;

    while (opc != 0)
    {
        opc = 0;
        cout << ":::: Escolha o Metodo de Escalonamento         ::::\n";
        cout << ":::: Ha 10 processos!                          ::::\n";
        cout << ":::: 1 - Escalonamento Round-Robbin            ::::\n";
        cout << ":::: 2 - Escalonamento de Prioridade Dinamica  ::::\n";
        cout << ":::: 0 - Sair                                  ::::\n";
        cout << "\n:::: ESCOLHA O ESCALONAMENTO = ";

        cin >> opc;

        switch (opc)
        {
        case 1:
            cout << "\nEscalonamento Round-Robbin";
            round_robbin();
            break;
        case 2:
            cout << "\nEscalonamento de Prioridade Dinamica";
            priord();
            break;
        case 0:
            break;
        }
    }

    return 0;
}