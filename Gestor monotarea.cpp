//Proyecto 1 Sistemas operativos: Simulador de Gestor monotarea de monoproceso y multiproceso
//Alumno Eduardo Martell Hernandez Hernandez
//Profesor Josue Perez Lucero

#include <stdio.h>
#include <iostream>
#include <string>
using namespace std;

////Los datos de las tareas son PID,T.lle,T.exe y prioridad
//class Tarea{
//	//Atributos
//	public:
//		Tarea *sig;
//		string pid;
//	//Constructor vacio
//	Tarea()	{
//		sig=NULL;
//		pid="";
//	}
//	//Contructor con argumentos
//	Tarea(string nom){
//		pid=nom;
//		sig=NULL;
//	}
//};

class Gestor{
	//Atributos
	private:
		int *listaP;
		int pid[],tll[],texe[],prio[];
		int listaD[][3];
		int tDExe;
		int tEsp;
		int fil,col;
		int cantT;
		int mayorLleg;
	public:
		//Constructor vacio
		Gestor(){
			listaP=NULL;
			tDExe=tEsp=cantT=mayorLleg=0;
		}
		
		void leerDatos(char name[]){
			FILE *fp;
			int c,v;
			int i,j;
			char ch;
			fp=fopen(name,"r");
			
			cout<<"Leyendo datos...\n";
			cantT=0;
			while((ch=getc(fp))!=EOF){	//Encontramos la cantidad de tareas que son
				if(ch=='\n') cantT++;
			}
			cout<<"Tareas: "<<cantT<<endl;
			fclose(fp);
			
			fp=fopen(name,"r");
			for(i=0; i<cantT; i++){//Se copian los datos tal cual como vienen
				fscanf(fp,"%d %d %d %d\n",&pid[i],&tll[i],&texe[i],&prio[i]); 
			
				printf("%d %d %d %d",pid[i],tll[i],texe[i],prio[i]); 
				cout<<endl;
			}
			fclose(fp);
			
			mayorLleg=0;
			for(i=0; i<cantT; i++){ //Se busca el que tiene la llegada mas tardada
				if(i>0 && tll[i] > tll[i-1]) mayorLleg=tll[i];
				cout<<mayorLleg;
			}
			cout<<"Mayor timpo de llegada: "<<mayorLleg<<endl;
			
		}
		
		void mostrarDatos(){
			int i;
			cout<<"PID\tT.Lleg\tT.Exe\tPrioridad\n";
			for(i=0; i<cantT; i++){
				printf("T%i\t%i\t%i\t%i\n",&pid[i],tll[i],texe[i],prio[i]);
			}
			
		}
		
		void salida(){
			char el;
			int el2, aux;
			int n, t, ex, p; //Nombre ,Tiempo(llegada), execucion, y prioridad
			n=t=ex=0;
			
			cout<<"Monoproceso o multiproceso? (Mo | Mu) ";
			scanf("M%c",&el);
			tolower(el);
			
			if(el=='o') el2=1;
			else el2=2;
			switch(el2){
//	case 1 monoproceso
				case 1: 
					cout<<"Tiempo de ejecucion Lijero o pesado? (L | P) ";
					cin>>el;
					toupper(el);
					if(el=='L'){//Tiempo ejecucion Ligero
						cout<<"Prioridad Alta o baja? (a,b) ";
						cin>>el;
						tolower(el);
						if(el=='a'){//Prioridad Alta
							cout<<"Ordenar los nombres Ascendente o Descendente? (a | d) ";
							cin>>el;
							if(el=='a'){//PID Adcendente
//								for(t=0; t<cantT; t++){ //Vamos a ir avanzando hasta que ya no llegue ninguna tarea
									
								
							}
							else{ //PID Descendente
								
							}
						}
						else{ //Prioridad baja
							cout<<"Ordenar los nombres Ascendente o Descendente? (a | d) ";
							cin>>el;
							if(el=='a'){//PID Adcendente
								
							}
							else{//PID Descendente
								
							}
						}
					}
					else{ //Tiempo ejecucion pesado
						
					}
					
					break;
//	case 2 Multiproceso
				case 2: 
					break;
			}
		}
		
};

int main(){
	Gestor g1;
	int e;
	cout<<"\t\t\t\t Planificador Monotarea\n"
		<<"1.-Leer Datos de archivo\n"
		<<"2.- Mostrar Datos\n"
		<<"3.- Mostrar linea de procesos\n"
		<<"4.- Limpiar pantalla\n"
		<<"5 o mas para salir\n\n";
	do{
		cout<<"Opcion: ";
		cin>>e;
		switch(e){
			case 1:
				g1.leerDatos("tareas2.txt");
				break;
			case 2:
				g1.mostrarDatos();
				break;
			case 3:
				g1.salida();
				break;
			case 4:
				break;
			default:
				cout<<"Hasta luego\n";
				exit(0);
				break;
		}
	}while(e<5);
}
