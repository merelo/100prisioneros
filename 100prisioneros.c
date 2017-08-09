#include <stdio.h>
#include <stdlib.h>
#include<time.h>

#define NRECLUSOS 100 //Numero de reclusos (Número par)
#define NPRUEBAS 1000000 //Numero de muestras


//Variable que contiene a las cajas, almacenan en su posición un número del 1 a NRECLUSOS
int cajas[NRECLUSOS];


int ejecucion(FILE *salida);
void asignaCajas();
int nRepetido(int num);
int compruebaJugador(int jugador);
int compruebaCaja(int *visitada,int sigCaja);


int main(){
  float intento=0;  //contiene el número de muestra en el que estamos
  float nCorrectos=0; //Número de pruebas correctas
  float nFallos=0; //Número de pruebas fallidas
  int resultado=0; //Variable de control
  
  //Fichero en el que se desglosa cada uno de los intentos que realizaremos
  FILE *salida;
  salida=fopen("fich.txt","w");
    
  srand(time(NULL)); //Para generar posiciones aleatorias
  
  for(int i=0;i<NPRUEBAS;i++){
	//Ejecutamos la prueba, nos devuelve 1 si se "salvan" los presos, 0 en caso contrario
    resultado=ejecucion(salida);
    intento++;

	//Escribimos en el fichero de salida el resultado de la prueba
    fprintf(salida,"Intento: %f\nResultado: ",intento);
    if(resultado){
      nCorrectos++;
      fprintf(salida,"Correcto\n\n----------------------\n");
    }else{
      nFallos++;
      fprintf(salida,"Fallido\n\n----------------------\n");
    }
  }
  
  //Resultados finales
  fprintf(salida,"Resultado:\n");
  fprintf(salida,"nIntentos: %f nAciertos: %f nFallos: %f\n",intento,nCorrectos,nFallos);
  fprintf(salida,"Prob Acierto: %f\n",nCorrectos/intento);
  printf("Porcentaje acierto: %f\n",nCorrectos/intento);
    
  
  fclose(salida);

  return 0;
}


/*
	Función que recibe como parámetro el fichero en el que queremos escribir el resultado
	Esta función ejecuta una prueba
	Devuelve 0 si un prisionero falla
	Devuelve 1 si los prisioneros se salvan
*/
int ejecucion(FILE *salida){
  int fallo=1; //0 si falla, 1 si correcto
  int i=0;
  int jugador=0;
  
  //Creamos un nuevo escenario (generamos los números contenidos en las cajas)
  asignaCajas();

  //Imprimo en el fichero las cajas y su contenido
  fprintf(salida,"Cajas\n");
  for(;i<NRECLUSOS;i++)
    fprintf(salida,"%d ",cajas[i]);
  fprintf(salida,"\nPosicion\n");
  for(i=0;i<NRECLUSOS;i++)
    fprintf(salida,"%d ",i);
  fprintf(salida,"\n\n");
  
  //Vamos prisionero a prisionero comprobando que todos tengan éxito, si uno falla, se deja de buscar
  while(jugador<NRECLUSOS&&fallo==1){
    fallo=compruebaJugador(jugador);
    fprintf(salida,"Jugador %d Resultado: %d \n",jugador,fallo);
    jugador++;
  }
  
  return fallo;
}


/*
	Función que comprueba si el prisionero encuentra su número en el número de intentos correspondiente
	Devuelve 0 si el prisionero no encuentra su número
	Devuelve 1 si el prisionero encuentra su número
*/
int compruebaJugador(int jugador){
  //devuelve 0 si hay fallo, 1 si correcto
  int cuenta=NRECLUSOS/2;
  int sigCaja=jugador;
  int visitada[NRECLUSOS/2]; //Variable que almacena las cajas que ya ha abierto el prisionero
  int i=0;
  
  //Bucle para posteriormente detectar que cajas ha abierto
  for(i=0;i<NRECLUSOS/2-1;i++){
    visitada[i]=-1;
  }

  //Bucle hasta que encuentre su número o llegue al máximo de intentos
  for(;cuenta>0;cuenta--){
    if(cajas[sigCaja]==jugador) //Si encuentra su número finaliza
      return 1;
    else{
      visitada[NRECLUSOS/2-cuenta]=jugador;
	  //Función para evitar que el prisionero entre en un bucle
      sigCaja=compruebaCaja(visitada,cajas[sigCaja]); 
    }    
  }

  if(cuenta==0)
    return 0;
  else
    return 1;
}

/*
	Función que comprueba si sigCaja ya ha sido visitada previamente
	Devuelve la caja siguiente a la que debe acceder el preso
*/
int compruebaCaja(int *visitada,int sigCaja){
  int repe=1;
  int salBucle=0;
  //devuelve sigCaja si no esta en visitada

  while(repe==1){
    for(int i=0;salBucle==0&&i<NRECLUSOS/2-1&&visitada[i]!=-1;i++){
      if(visitada[i]==sigCaja){
	salBucle=1;
	sigCaja++;
	if(sigCaja>NRECLUSOS-1)
	  sigCaja=0;
      }
    }
    if(salBucle==0)
      repe=0;
  }
  
  return sigCaja;
}


/*
	Función que introduce los números en las cajas
*/
void asignaCajas(){
  int repetido=1;
  int num=0;

  
  for(int i=0;i<NRECLUSOS;i++)
    cajas[i]=-1;

  for(int i=0;i<(NRECLUSOS);i++){
    while(repetido){
      num=rand()%(NRECLUSOS); //Generamos número aleatorio entre 0 y NRECLUSOS-1
      repetido=nRepetido(num); //Comprobamos que no exista ese número en otra caja
    }
    repetido=1;
    cajas[i]=num;
  }
}

/*
	Función que toma un número y comprueba su existencia en la variable cajas[]
*/
int nRepetido(int num){
  int repetido=0;
  for(int i=0;i<NRECLUSOS&&repetido==0;i++){
    if(cajas[i]==num)
      repetido=1;
    else
      repetido=0;
  }

  return repetido;
}