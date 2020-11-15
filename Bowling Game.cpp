#include <stdio.h>
#include <stdlib.h>
#include <cstdlib> 
#include <time.h> 
#include <conio.h>

typedef struct Puntuacio{
	struct Puntuacio *next;
	struct Puntuacio *prev;
	int puntos;
}Puntuacion;

typedef struct Jugador{
	struct Puntuacio *head;
	struct Puntuacio *tail;
	int size;
	int totalPuntos;
}Jugador;

Jugador* crearJugador(int qtd);
void insertePuntuacion(Jugador *jugador, int puntos, int x);
void imprimir(Jugador *jugador, int qtd);
void calcularPuntuacionFinal(Jugador *jugador, int qtd);
int qtdJugadores();
void iniciarJuego(Jugador *jugador, int qtd);
void freeMemory(Jugador *jugador, int qtd);
void imprimirJugadores(Jugador *jugador, int qtd);

main(){
	int op=0;
	Jugador *jugador;
	
	while(op==0){
        
		printf("\n\t*****BIENVENIDO AL BOWLING GAME*****\n\n\n");
        printf("1 = Jugar\n");
        printf("2 = Salir\n");

       
        
        int qtd;
        scanf("%d",&op);
        switch (op){
            case 1: qtd= 1;
					jugador= crearJugador(1);
					iniciarJuego(jugador, 1);
					imprimir(jugador, qtd);
					calcularPuntuacionFinal(jugador, qtd);
					imprimirJugadores(jugador, qtd);
					printf("\n\n\n");
					system("pause");
                    break; 
			case 2: break;
               
            default:op=0;
                    break;
        }
    }	
}

Jugador* crearJugador(int qtd)
{
    Jugador *jugador= (Jugador*)malloc(qtd * sizeof(Jugador));
    for(int i=0; i<qtd; i++){
    	jugador[i].head=NULL;
    	jugador[i].tail=NULL;
		jugador[i].size=0;
		jugador[i].totalPuntos=0;
	}
	return jugador;
}

void insertePuntuacion(Jugador *jugador, int puntos, int x){
	Puntuacion *play= jugador[x].tail;
	Puntuacion *nueva_Puntuacion= (Puntuacion*)malloc(sizeof(Puntuacion));
	nueva_Puntuacion->puntos=puntos;
    
	if(jugador[x].size==0){
        jugador[x].head=nueva_Puntuacion;
        jugador[x].head->prev=NULL;
        jugador[x].head->next=NULL;
        jugador[x].tail=nueva_Puntuacion;
    }else{
        nueva_Puntuacion->next=play->next;
        nueva_Puntuacion->prev=play;

        if(play->next==NULL){
            jugador[x].tail= nueva_Puntuacion;
        }else{
            play->next->prev=nueva_Puntuacion;
        }
        play->next=nueva_Puntuacion;
    }
    jugador[x].size++;
}

void imprimir(Jugador *jugador, int qtd){
	Puntuacion *aux;
	for(int i=0; i<qtd; i++){
		aux= jugador[i].head;
		printf("\nJugador %d: ", i+1);
		while(aux!=NULL){
			printf("%d ", aux->puntos);
			aux= aux->next;
		}
		printf("\n");
	}	
}

void calcularPuntuacionFinal(Jugador *jugador, int qtd){
	int suma=0;
	Puntuacion *aux;
	
	for(int i=0; i<qtd; i++){
		aux=jugador[i].head;
		while(aux!=NULL){
			suma+=aux->puntos;
			aux= aux->next;
		}
		jugador[i].totalPuntos=suma;
		suma=0;
	}
}

void iniciarJuego(Jugador *jugador, int qtd){
	system("clear||cls");
	int totalPinos=10;
	int pinos;
	int suma=0;
	srand(time(NULL));
	
	for(int i=0; i<10; i++){
		printf("\n\n\t Round %d\n", i+1);
	
		for(int x=0; x<qtd; x++){
			
			if(i<9){
				printf("\nJugador %d\n", x+1);
				for(int y=0; y<2; y++){
					pinos=rand() % (totalPinos+1);
					printf("Intento %d, %d pinos derrubados.\n",y+1,pinos);
					totalPinos-=pinos;
					suma+=pinos;
					
					if(totalPinos==0 && y==0){
						totalPinos=10;
						insertePuntuacion(jugador, 15, x);
						break;
					}else if(y==1)
					{
						insertePuntuacion(jugador, suma, x);
					}
				}
				totalPinos=10;
				suma=0;
				
			}else
			{
				printf("\nJugador %d\n", x+1);
				for(int y=0; y<3; y++){
					pinos=rand() % (totalPinos+1);
					printf("Intento %d, %d pinos derrubados.\n",y+1,pinos);
					totalPinos-=pinos;
					if(totalPinos==0){
						totalPinos=10;
					}
					if(pinos==10){
						suma+=15;
					}else{
						suma+=pinos;
					}
				}
				insertePuntuacion(jugador, suma, x);
				totalPinos=10;
				suma=0;
			}
			
		}
	}
}

void imprimirJugadores(Jugador *jugador, int qtd){
	int i, j, aux, vet[qtd];
	
	for(i=0; i<qtd; i++){
		vet[i]=jugador[i].totalPuntos;
	}

 	for(i=0; i<qtd; i++){
 		aux= vet[i];
 		for(j=i; (j>0) && (aux < vet[j-1]); j--)
 			vet[j]= vet[j-1];
 		vet[j]= aux;
	}
	
	for(i=qtd-1; i>=0; i--){
		for(j=0; j<qtd; j++){
			if(vet[i]==jugador[j].totalPuntos){
				
				if(jugador[j].totalPuntos==vet[qtd-1]){
					printf("\n\nJugador %d: %d puntos \n", j+1, vet[i]);
				}else{
					printf("Jugador %d: %d pontos\n", j+1, vet[i]);
				}
				jugador[j].totalPuntos=-1;
				break;
			}
		}
	}
}



