#include <iostream>
#include <fstream>
#include <string>

using namespace std;

//clase que contiene los atributos de todas las tareas
class Tarea {
 
	protected:
	//atributos de las tareas
	int id, tll, texe, prioridad;
	//atributo para saber si la tarea está conectada o no al canal
	bool conectado;
	//atributo para saber si está conectado a la c.llegada o no
	bool conectadoll;
	// abajo e inicial son atributos para formar una lista ligada de todas las tareas jaladas por el archivo
	Tarea *abajo;
	Tarea *inicial; 
	Tarea *final;
	// atributos lista ligada para cola de llegada
	Tarea *inicioll;
	Tarea *abajoll;
	Tarea *finll;
	// atributos lista ligada para cola de ejecución
	Tarea *inicioexe;
	Tarea *abajoexe;
	// atributos lista ligada para cola de prioridad
	Tarea *inicioprio;
	Tarea *abajoprio;
	// atributos de lista ligada para cola de PID
	Tarea *iniciopid;
	Tarea *abajopid;

public:

	Tarea() {

		//conectorCanal = NULL;
		conectadoll=conectado = false;
		id = tll = texe = prioridad = 0;
		abajo = inicial = NULL;
			final = NULL;
		inicioll = abajoll=finll = NULL;
		inicioexe = abajoexe = NULL;
		inicioprio = abajoprio = NULL; 
		iniciopid = abajopid = NULL;
	}
	friend class Canal;
};

//clase que indica las unidades de tiempo de cada proceso
class Proceso {

public:
	Proceso *sig;
	Tarea *conectorTarea;
	bool visitado;
	int unidadTiempo;

public:

	Proceso() {
		sig = NULL;
		conectorTarea = NULL;
		visitado = false;
		unidadTiempo = 0;

	}

};
//clase que ayuda a formar los canales y la que ocnitene operaciones

class Canal : public Tarea {

private:
	Proceso *INICIO;
	Proceso *FINAL;
	bool ocupado;
public:
	Canal() {
		INICIO = NULL;
		FINAL = NULL;
		ocupado = false;
	}

	/* método que sirve para crear las tareas con sus respectivos atributos, jalandolos desde un archivo*/
	void lectura(ifstream &archivo) {

		cout<<"Tarea leida.\n";
		while (!archivo.eof())
		{
			int Id, Tll, Texe, Prioridad;
			archivo >> Id >> Tll >> Texe >> Prioridad;

			if (archivo.fail()) { return; } // Checa alguna falla en el archivo

			Tarea *nodo = new Tarea();
			nodo->id = Id;
			nodo->tll = Tll;
			nodo->texe = Texe;
			nodo->prioridad = Prioridad;

			if (inicial == NULL && final==NULL)
			{
				inicial = nodo;
				final = nodo;
			}
			else {
				Tarea *aux = inicial;

				while (aux->abajo != NULL)
				{
					aux = aux->abajo;
				}
				aux->abajo = nodo;
				final = nodo;
			cout<<"Tarea leida.\n";
			}
			
		}
		
	}

	/*Verifica que todas las tareas estén ya conectadas al canal, de lo contrario nos lanzará un FALSE */
	bool VerificarConexion(Tarea *aux) {
		aux = inicial;

		while (aux != NULL)
		{
			if (aux->conectado == true)
			{
				aux = aux->abajo;
			}
			else
			{
				return false;
				break;
			}
		}
		return true;
	}
	// SECCIÓN DE MÉTODOS DE ORDENAMIENTO
	//OrdenarTll() sirve para ordenar tll pero en la lista de carga
	void OrdenarTll() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = inicial; //se inicializa en el primer nodo
		while (actual->abajo != NULL) { // aqui verifica si esta vacia, obviamente jamas lo estara, asi que siempre entrara al ciclo
			sig = actual->abajo; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->tll > sig->tll) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
											//si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajo; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajo;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajo;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}

	//OrdenarTexeLigero() sirve para ordenar texe pero en la lista de exe
	void OrdenarTexeLigero() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = inicioexe; //se inicializa en el primer nodo
		while (actual->abajoexe != NULL) { // aqui verifica si esta vacia, obviamente jamas lo estara, asi que siempre entrara al ciclo
			sig = actual->abajoexe; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->texe > sig->texe) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
											  //si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajoexe; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajoexe;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajoexe;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}
	//OrdenarTexePesado() sirve para ordenar texe pero en la lista de exe
	void OrdenarTexePesado() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = inicioexe; //se inicializa en el primer nodo
		while (actual->abajoexe != NULL) { // aqui verifica si esta vacia, obviamente jamas lo estara, asi que siempre entrara al ciclo
			sig = actual->abajoexe; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->texe < sig->texe) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
											  //si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajoexe; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajoexe;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajoexe;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}
	//OrdenarPrioAlta() sirve para ordenar prioridad pero en la lista de prioridad
	void OrdenarPrioAlta() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = inicioprio; //se inicializa en el primer nodo
		while (actual->abajoprio != NULL) { // aqui verifica si esta vacia, obviamente jamas lo estara, asi que siempre entrara al ciclo
			sig = actual->abajoprio; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->prioridad > sig->prioridad){
				//if (actual->prioridad < sig->prioridad) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
												//si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajoprio; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajoprio;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajoprio;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}//OrdenarPrioBaja() sirve para ordenar prioridad pero en la lista de prioridad
	void OrdenarPrioBaja() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = inicioprio; //se inicializa en el primer nodo
		while (actual->abajoprio != NULL) { // aqui verifica si esta vacia, obviamente jamas lo estara, asi que siempre entrara al ciclo
			sig = actual->abajoprio; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->prioridad < sig->prioridad){
				//if (actual->prioridad < sig->prioridad) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
												//si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajoprio; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajoprio;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajoprio;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}
	//OrdenarPidAsc() sirve para ordenar id pero en la lista de pid
	void OrdenarPidAsc() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = iniciopid; //se inicializa en el primer nodo
		while (actual->abajopid != NULL) { // aqui verifica si esta vacia, obviamente jamas lo estara, asi que siempre entrara al ciclo
			sig = actual->abajopid; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->id > sig->id) {
				//if (actual->id < sig->id) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
												//si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajopid; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajopid;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajopid;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}
	//OrdenarPidDes() sirve para ordenar id pero en la lista de pid
	void OrdenarPidDes() {

		Tarea *actual;
		Tarea *sig; // pensaba incluirle a Tarea un apuntador sig 
		int p, ll, ex, prio;

		actual = iniciopid; //se inicializa en el primer nodo
		while (actual->abajopid != NULL) { // aqui verifica si esta vacia asi que siempre entrara al ciclo
			sig = actual->abajopid; // en la variable sig se guarda el actual valor con su apuntador 
			while (sig != NULL) {
				if (actual->id < sig->id) {
				//if (actual->id < sig->id) { //Si el metodo estabien, lo unico que cambiaria en el metodo de PID menor es el signo de menor
												//si cumple la condicion, todo lo guaradaremos en la nuevas variables, se puede decir que se recorren
					p = sig->id;
					ll = sig->tll;
					ex = sig->texe;
					prio = sig->prioridad;

					// en este punto, los siguientes valores se vuelven los actuales valores
					sig->id = actual->id;
					sig->tll = actual->tll;
					sig->texe = actual->texe;
					sig->prioridad = actual->prioridad;

					//y el actual valor se guarda en las variables nuevas   
					actual->id = p;
					actual->tll = ll;
					actual->texe = ex;
					actual->prioridad = prio;
				}
				sig = sig->abajopid; // ahora el siguiente va apuntar al siguiente valor
			}
			actual = actual->abajopid;   // el actual valor, apuntaria al siguiente valor, se recorre por decirlo de una forma
			sig = actual->abajopid;     //y la var sig, guardaria el actual con su respectivo apuntador, se actualiza
		}
	}
	//BANDERAS
	// método que checa si hay mas de una tarea con el mismo tiempo de llegada  pero en la c.llegada
	//(devuelve true cuando hay mas de una tarea con el mismo tiempo de llegada)

	int banderaTll(){
		Tarea *aux = inicioll;
		int j = 0;

		if (aux == NULL)
		{
			return j;
		}
		else
		{
			while (aux != NULL)
			{
				j = j + 1;
				aux = aux->abajoll;
			}
		}

		return j;
	}

	// bandera ejecución
	bool banderaexe(){
		Tarea *aux = inicioexe;
		Tarea *aux1 = aux->abajoexe;
		int j = 1;

		while (aux != NULL && aux1 != NULL)
		{
			if (aux->texe == aux1->texe)
			{
				j += 1;
				aux = aux->abajoexe;
				aux1 = aux1->abajoexe;
			}
			else
			{
				break;
			}

		}

		if (j > 1) {
			return true;
		}
		else {
			return false;
		}
	}


	// bandera prioridad
	bool banderaprio() {
		Tarea *aux = inicioprio;
		Tarea *aux1 = aux->abajoprio;
		int j = 1;

		while (aux != NULL && aux1 != NULL)
		{
			if (aux->prioridad == aux1->prioridad)
			{
				j = j + 1;
				aux = aux->abajoprio;
				aux1 = aux1->abajoprio;
			}
			else
			{
				break;
			}

		}

		if (j > 1) {
			return true;
		}
		else {
			return false;
		}
	}


	//éste metodo ayuda al método colaLlegada(Tarea *aux) a insertar en c.llegada
	void insertarColaLlegada(Tarea *nodo) {

		if (inicioll == NULL && finll==NULL) {
			inicioll = nodo;
			finll = nodo;
		}
		else
		{

			Tarea *aux = inicioll;

			while (aux->abajoll != NULL)
			{
				aux = aux->abajoll;
			}
			aux->abajoll = nodo;
			finll = nodo;
		}
	}

	// la cola llegada como tal
	void colaLlegada() {	
		Tarea *aux = inicial;
		//
		while ( aux != final && aux->conectadoll==true  )
		{
			aux = aux->abajo;
		}


			int x = aux->tll;

			while ( aux != final && aux->tll == x   )
			{

				Tarea * dato = new Tarea();
				dato->id = aux->id;
				dato->tll = aux->tll;
				dato->texe = aux->texe;
				dato->prioridad = aux->prioridad;
				dato->conectadoll = true;
				aux->conectadoll = true;
				insertarColaLlegada(dato);

				aux = aux->abajo;
			}



			if (aux == final && aux->conectadoll == false && aux->tll == x)
			{
				Tarea * dato = new Tarea();
				dato->id = aux->id;
				dato->tll = aux->tll;
				dato->texe = aux->texe;
				dato->prioridad = aux->prioridad;
				dato->conectadoll = true;
				aux->conectadoll = true;
				insertarColaLlegada(dato);
			}
		


	}


	//ayuda a insertar a colaEjecucion()
	void insertarColaEjecucion(Tarea *nodo) {
	
		if (inicioexe == NULL) {
			inicioexe = nodo;
		}
		else
		{
			Tarea *aux = inicioexe;

			while (aux->abajoexe != NULL)
			{
				aux = aux->abajoexe;
			}
			aux->abajoexe = nodo;
		}
	}
	//cola de exe como tal
	void colaEjecucion() {
		Tarea *aux = inicioll;
		while ( aux!=NULL)
		{
			Tarea *dato = new Tarea();

			dato->id = aux->id;
			dato->tll = aux->tll;
			dato->texe = aux->texe;
			dato->prioridad = aux->prioridad;
			dato->conectadoll = true;
			insertarColaEjecucion(dato);
			aux = aux->abajoll;
		}

	}

	//ayuda a insertar a colaPrioridad()
	void insertarColaPrioridad(Tarea *nodo) {

		if (inicioprio == NULL) {
			inicioprio = nodo;
		}
		else
		{
			/*nodo->abajoprio = inicioprio;
			inicioprio = nodo;*/
        	Tarea *aux = inicioprio;

			while (aux->abajoprio != NULL)
			{
				aux = aux->abajoprio;
			}
			aux->abajoprio = nodo;
		}
	}

	//cola de prio como tal
	void colaPrioridad() {
		Tarea *aux = inicioexe;
		int x = aux->texe;
		while (aux!=NULL && aux->texe==x)
		{
			Tarea *dato = new Tarea();
			dato->id = aux->id;
			dato->tll = aux->tll;
			dato->texe = aux->texe;
			dato->prioridad = aux->prioridad;
			dato->conectadoll = true;
			insertarColaPrioridad(dato);

			aux = aux->abajoexe;
		}

	}
	//ayuda a insertar a colaPid()
	void insertarColaPid(Tarea *nodo) {

		if (iniciopid == NULL) {
			iniciopid = nodo;
		}
		else
		{
			Tarea *aux = iniciopid;

			while (aux->abajopid != NULL)
			{
				aux = aux->abajopid;
			}
			aux->abajopid = nodo;
		}
	}

	//cola de pid como tal
	void colaPid() {
		Tarea *aux = inicioprio;
		int x = aux->prioridad;

		while (aux!=NULL && aux->prioridad==x)
		{
			Tarea *dato = new Tarea();

			dato->id = aux->id;
			dato->tll = aux->tll;
			dato->texe = aux->texe;
			dato->prioridad = aux->prioridad;
			dato->conectadoll = true;
			insertarColaPid(dato);
			aux = aux->abajoprio;
		}

	}
	//incrementa en una unidad los procesos del canal 
	void UincrementarCanal() {
		int j;
		Proceso *unidad = new Proceso();

			if (INICIO==NULL && FINAL==NULL) {
				j = 0;
				unidad->unidadTiempo = j;
				INICIO = unidad;
				FINAL = unidad;
			}
			else {
		
				Proceso *aux = INICIO;

				while (aux->sig!=NULL)
				{

					aux = aux->sig;
				}

				j = aux->unidadTiempo + 1;
				aux->sig = unidad;
				unidad->unidadTiempo = j;
				FINAL = unidad;
			}
	}

	//incrementa en una unidad los procesos del canal 
	void EincrementarCanal(int j) {
		int x;
		for (int i = 0; i < j; i++)
		{
			Proceso *unidad = new Proceso();
			if (INICIO == NULL && FINAL == NULL) {
				x = 0;
				unidad->unidadTiempo = x;
				INICIO = unidad;
				FINAL = unidad;
			}
			else {

				Proceso *aux = INICIO;

				while (aux->sig != NULL)
				{

					aux = aux->sig;
				}

				x = aux->unidadTiempo + 1;
				aux->sig = unidad;
				unidad->unidadTiempo = x;
				FINAL = unidad;
			}
		}
	}
	//retorna Tareas de cola de carga
	Tarea *RetornarTarea(int i) {
		Tarea *aux = inicial;

		while (aux!=NULL)
		{
			if (aux->id == i) {

				return aux;
				break;
			}
			aux = aux->abajo;
		}


	}
	//método para checar si ya hay una tarea conectada al CANAL
	bool checarEspacio() {
		Proceso *aux = INICIO;
		while (aux!=NULL)
		{
			if (aux->conectorTarea!=NULL) {
				return true;
				break;
			}
			aux = aux->sig;
		}
		return false;
	}

	//método que inserta las tareas en el canal
	void insertarCanal(Tarea *ref) {
		ocupado = checarEspacio();
		Proceso *Utiempo=INICIO;
		bool flag=false;

		while (Utiempo!=NULL) {
			if (Utiempo->unidadTiempo==ref->tll)
			{
				flag = true;
				break;
			}
			Utiempo = Utiempo->sig;
		}

		if (flag==false){
			EincrementarCanal(ref->tll);
		}

		EincrementarCanal(ref->texe);
		Proceso *aux = INICIO;

			if (ocupado == false){

				while (aux != NULL && aux->unidadTiempo != ref->tll)
				{
					aux->visitado=true;
					aux = aux->sig;
				}
				aux->conectorTarea = ref;

				for (int i = 0; i < ref->texe; i++)
				{
					aux->visitado = true;
					aux = aux->sig;
					
				}
				
			//	aux->visitado = true;
			}

			else {
				while (aux->visitado==true)
				{
					aux = aux->sig;
				}
				aux->conectorTarea = ref;

				for (int i = 0; i < ref->texe; i++)
				{
					aux->visitado = true;
					aux = aux->sig;

				}
			}
	}

	//elimina la tarea en la c.llegada una vez conectada en el canal

	void eliminarTareall(int datoAE) {
		Tarea *ant, *act;
		ant = act = inicioll;

		if (inicioll == NULL && finll == NULL) {
			return;
		}
		 //
		if (inicioll->id== datoAE && inicioll->abajoll != NULL) {
			inicioll = inicioll->abajoll;
		}

		if (inicioll->id == datoAE && inicioll->abajoll == NULL) {
			inicioll = NULL;
			finll = NULL;
		}

		while (act != NULL && act->id != datoAE) {
			ant = act;
			act = act->abajoll;
		}

		if (act != NULL) {
			ant->abajoll = act->abajoll;
		}

		/*if (act->abajoll == NULL && act->id==datoAE) {

			ant->abajoll = NULL;

		}*/
		if (act == finll) {

			finll = ant;

		}
	}

	//elimina el primer elemento de c.pid
	void desencolarPid() {
		if (iniciopid==NULL)
		{
			return;
		}
		if(iniciopid->abajopid==NULL){
			iniciopid = NULL;
		}
		else
		{
			iniciopid = iniciopid->abajopid;
		}
	}

	//elimina el primer elemento de c.prioridad
	void desencolarPrio() {
		if (inicioprio == NULL)
		{
			return;
		}
		if (inicioprio->abajoprio == NULL) {
			inicioprio = NULL;
		}
		else
		{
			inicioprio = inicioprio->abajoprio;
		}
		
	}

	//elimina el primer elemento de c.exe
	void desencolarExe() {
		if (inicioexe == NULL)
		{
			return;
		}
		if (inicioexe->abajoexe == NULL) {
			inicioexe = NULL;
		}
		else
		{
			inicioexe = inicioexe->abajoexe;
		}
	}
	//elimina por completo la c.prioridad

	void eliminarCPrio() {

		if (inicioprio == NULL)
		{
			return;
		}
		while (inicioprio!=NULL)
		{
			desencolarPrio();
			//inicioprio = inicioprio->abajoprio;
		}
		desencolarPrio();
	}
	//elimina por completo la c.exe

	void eliminarCExe() {

		if (inicioexe == NULL)
		{
			return;
		}
		while (inicioexe != NULL)
		{
			desencolarExe();
			//nicioexe = inicioexe->abajoexe;
		}
		desencolarExe();
	}
	/*método que nos permite operar mediante las llamadas de métodos de ordenamiento, entre otros métodos
	(esa es la idea hasta ahora)
	*/
	void metodoGeneral() {
		char res1,res2,res3;
		OrdenarTll();// ordenamos las llegadas en una lista de carga (es una lista ligada)
		Tarea *aux1 = inicial;
		
		cout<<"Ordenar Tiempo de ejecucion Ligero o Pesado? (L | P) ";
		cin>>res1;
		toupper(res1);
		cout<<"Ordenar Prioridad Alta o Baja? (A | B) ";
		cin>>res2;
		toupper(res2);
		cout<<"Ordenar PID Ascendente o Descendente? (A | D) ";
		cin>>res3;
		toupper(res3);
	
			while (VerificarConexion(aux1) == false)///verificamos de manera general si hay tareas sin conectar en lista de carga
			{
				if (aux1->conectado == false) {//checamos si la tarea actual aún no está conectada, en caso contrario el else de éste if avanzará al siguiente nodo
					
					colaLlegada();//insertamos  las tareas ya ordenadas por t.ll
					OrdenarTll();
					
					UincrementarCanal();//incrementamos de a unidad el canal

					if (banderaTll() == 0) {
						UincrementarCanal();
					}
					else
					{
						if (banderaTll() > 1)
						{
							//encolar en cola de ejecución
							if(res1=='L'){
								colaEjecucion();
								OrdenarTexeLigero();
							}
							else{
								colaEjecucion();
								OrdenarTexePesado();
							}
							
							//checar si hay dos o mas tareas con el mismo tiempo de exe
							if (banderaexe()==true)
							{
								//llevamos las tareas de c. exe a c.prio
								if(res2=='A'){
									colaPrioridad();
									OrdenarPrioAlta();
								}
								else{
									colaPrioridad();
									OrdenarPrioBaja();
								}
								//checar si hay dos o mas tareas con la misma prioridad
								if (banderaprio()==true)
								{
									//llevamos las tareas de cprio a c.pid
									if(res3=='A'){
										colaPid();
										OrdenarPidAsc();
									}
									else{
										colaPid();
										OrdenarPidDes();
									}
									Tarea *auxPid = iniciopid;
										while (auxPid!=NULL)
										{
											//sacar todos los elementos de ésta cola y encolarlos
												Tarea *pcanal = RetornarTarea(auxPid->id);//apunta a la lista de carga
												pcanal->conectado = true;
												Tarea *dato=new Tarea();
												dato->id = pcanal->id;
												dato->tll = pcanal->tll;
												dato->texe = pcanal->texe;
												dato->prioridad = pcanal->prioridad;
												dato->conectadoll = true;
	
												insertarCanal(dato);
												//eliminar la tarea conectada de cola de llegada
												eliminarTareall(dato->id);
												auxPid = auxPid->abajopid;
												//sacar de c.pid el primer elemento
												desencolarPid();
												imprimirCanal();
												cout<<"-----------------------------\n";
												
										}

										//eliminar todas las tareas en c.exe,c.prio
										eliminarCPrio();
										eliminarCExe();
								}
								else
								{
									//sólo hay una tarea y ésta debe ser encolada al canal
									Tarea *auxprio = inicioprio;
									Tarea *pcanal = RetornarTarea(auxprio->id);//apunta a la lista de carga
									pcanal->conectado = true;
									Tarea *dato = new Tarea();
									dato->id = pcanal->id;
									dato->tll = pcanal->tll;
									dato->texe = pcanal->texe;
									dato->prioridad = pcanal->prioridad;
									dato->conectadoll = true;

									insertarCanal(dato);
									//eliminar la tarea conectada de cola de llegada 
									eliminarTareall(dato->id);
								//	desencolarPrio();	
									eliminarCPrio();
									//eliminar todas las tareas en c.exe,c.prio
									eliminarCExe();
									imprimirCanal();
									cout<<"-----------------------------\n";
								}
							}
							else
							{
								//sólo hay una tarea y ésta se debe encolar al canal 
								Tarea *auxexe = inicioexe;
								Tarea *pcanal = RetornarTarea(auxexe->id);//apunta a la lista de carga
								pcanal->conectado = true;
								Tarea *dato = new Tarea();
								dato->id = pcanal->id;
								dato->tll = pcanal->tll;
								dato->texe = pcanal->texe;
								dato->prioridad = pcanal->prioridad;
								dato->conectadoll = true;

								insertarCanal(dato);
								//eliminar la tarea conectada de cola de llegada 
								eliminarTareall(dato->id);
								//sacar de c.pid el primer elemento
								
								//eliminarCPrio();
								//eliminar todas las tareas en c.exe,c.prio
								eliminarCExe();
								imprimirCanal();
								cout<<"-----------------------------\n";
							}
						}
						else
						{
							//sólo hay una tarea en cola llegada
							//se debe conectar al canal
							Tarea *auxll = inicioll;
							Tarea *pcanal = RetornarTarea(auxll->id);//apunta a la lista de carga
							pcanal->conectado = true;
							Tarea *dato = new Tarea();
							dato->id = pcanal->id;
							dato->tll = pcanal->tll;
							dato->texe = pcanal->texe;
							dato->prioridad = pcanal->prioridad;
							dato->conectadoll = true;
							insertarCanal(dato);
							//eliminar la tarea conectada de cola de llegada 
							eliminarTareall(dato->id);
							//eliminarCPrio();
							//eliminarCExe();
							imprimirCanal();
							cout<<"-----------------------------\n";
						}
					}

				}
				else
				{
					aux1 = aux1->abajo;
				}
			}
	}

	void recortarCanal() {
		Proceso *p = INICIO;

		while (p->visitado == true)
		{
			p = p->sig;
		}
		FINAL = p;
		p->sig = NULL;

	}

	void imprimirCanal() {
		Proceso *aux = INICIO;
		while (aux != NULL) {

			cout << aux->unidadTiempo << "-|";
			if (aux->conectorTarea != NULL) {
				cout << "- T" << aux->conectorTarea->id << endl;
			}
			else
			{
				cout << endl;
			}
			aux = aux->sig;
		}
	}
};


int main() {
	int e;
	Canal c;
	ifstream archivo;
	archivo.open("tareas3.txt");//abrimos el archivo

	cout<<"\t\t\t\t Planificador Monotarea\n"
		<<"1.-Leer Datos de archivo\n"
		<<"2.- Mostrar linea de procesos\n"
		<<"3.- Limpiar pantalla\n"
		<<"4 o mas para salir\n\n";
	do{
		cout<<"Opcion: ";
		cin>>e;
		switch(e){
			case 1:
				c.lectura(archivo);
				break;
			case 2:
				c.metodoGeneral();
				c.recortarCanal();
				c.imprimirCanal();
				break;
			case 3:
				system("cls");
				cout<<"\t\t\t\t Planificador Monotarea\n"
					<<"1.-Leer Datos de archivo\n"
					<<"2.- Mostrar linea de procesos\n"
					<<"3.- Limpiar pantalla\n"
					<<"4 o mas para salir\n\n";
				break;
			default:
				cout<<"Hasta luego\n";
				exit(0);
				break;
		}
	}while(e<4);
}
