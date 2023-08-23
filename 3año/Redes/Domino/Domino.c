#include "Domino.h"

struct ficha *crear_ficha(int a, int b){//reserva memoria y se crea ficha
	//printf("Creando ficha nueva [%i|%i]\n", a,b);
	struct ficha *nueva=calloc(sizeof(struct ficha),1);//reservo memoria para la ficha
	nueva->valores[0] = a; //introduzco sus valores
	nueva->valores[1] = b;
	return nueva;
}

void revolver(struct ficha *monton){//función que revuelve todas las fichas

	struct ficha *aux=NULL;//creo puntero a vector de fichas auxiliar y reservo memoria para el
	aux=realloc(aux,sizeof(struct ficha *)*28);

	int *orden = NULL;
	int valor_aleatorio;
	int contador=0;
	int vector_fichas_no_repetidas[DOMINO];//creo vector de fichas que no se han repetido y lo inicializo a 0
	memset(&vector_fichas_no_repetidas,0,sizeof(int)*DOMINO);
	while(contador<DOMINO){//voy rellenando el vector orden con valores aleatorios que no se hayan repetido
		valor_aleatorio = rand() % 28;
		if(vector_fichas_no_repetidas[valor_aleatorio] == 0){
			orden[contador]=valor_aleatorio;
			contador++;
			vector_fichas_no_repetidas[valor_aleatorio] = 1;//cada vez que sale un valor este se pone a 1 para evitar que vuelva a salir 
		}
	}
	for(int i=0;i<DOMINO;i++){
		aux[i]=monton[orden[i]];
	}
	*monton=*aux;
}

struct mesa *reserva_memoria_mesa(){//función para reservar memoria para la estructura mesa
	struct mesa *temp = NULL;
	temp = calloc(1, sizeof(struct mesa));//reserva de memoria inicializada a 0 gracias a calloc
	return temp;
}

void agregar_ficha(struct ficha **jugador, struct ficha *f){//añadimos una ficha a un jugador
	//asignamos espacio para una nueva ficha
	jugador = realloc(jugador,sizeof(struct ficha *)*((sizeof(jugador)/sizeof(struct ficha))+1));
	//guardamos la ficha f en el espacio creado
	jugador[(sizeof(jugador)/sizeof(struct ficha))-1] = f;
}

void agregar_ficha_mesa(struct mesa *m, struct ficha *f){//añadimos una ficha a una mesa

	//asignamos espacio para una nueva ficha
	m->fichas = realloc(m->fichas,sizeof(struct ficha *) * (m->total+1));
	//guardamos la ficha f en el espacio creado
	m->fichas[m->total] = f;
	//incrementamos el contador de fichas de esta estructura en 1 y actualizamos primero y último
	m->total++;
	m->primero = m->fichas[0];
	m->ultimo = m->fichas[m->total-1];
}

void agregar_ficha_esquina(struct mesa *m, struct ficha *f, bool posicion){//agrego ficha en los extremos de la mesa, al principio o al final
	//si posicion es true es en el principio y si es false al final

	//asignamos espacio para una nueva ficha
	m->fichas = realloc(m->fichas,sizeof(struct ficha *) * (m->total+1));
	//guardamos la ficha f en el espacio creado
	if(posicion){
		int i = m->total;
		while(i > 0){//desplazo toda la mesa uno a la derecha para crear espacio para la nueva ficha 
			m->fichas[i] = m->fichas[i-1];
			i--;
		}
		m->fichas[0] = f;
	}else{
		m->fichas[m->total] = f;
	}
	//incrementamos el contador de fichas de esta estructura en 1 y actualizamos primero y último
	m->total++;
	m->primero = m->fichas[0];
	m->ultimo = m->fichas[m->total-1];
}

struct ficha *quitar_ficha_jugador(struct ficha **jugador, int lugar_ficha){//funcion para quitar ficha de un jugador en la posicion deseada
	struct ficha *temporal = NULL;
	temporal = jugador[lugar_ficha];//almaceno la ficha buscada para devolverla
	for(int i=lugar_ficha; i < (sizeof(jugador)/sizeof(struct ficha))-1; i++){//con este for reajusto todo el vector en caso de coger una ficha que no sea la última
		jugador[i] = jugador[i+1];
	}
	jugador[(sizeof(jugador)/sizeof(struct ficha))-1] = NULL; //la última ficha que va a estar vacía la pongo a null para borrarla en memoria
	jugador = realloc(jugador, sizeof(struct jugador *)*(sizeof(jugador)/sizeof(struct ficha))-1);//reajusto el vector
	return temporal;
}

char *imprimir_vector_fichas(struct ficha **jugador){//imprime una ficha
	char texto[250];
	char buffer[5];
	sprintf(texto, "FICHAS ");
	
	for(int i=0; i<(sizeof(jugador)/sizeof(struct ficha));i++){
		bzero(buffer,sizeof(buffer));
		sprintf(buffer, "|%i|%i|", jugador[i]->valores[0], jugador[i]->valores[1]);
		strcat(texto, buffer);
	}
	bzero(buffer,sizeof(buffer));
	sprintf(buffer, "\n");
	strcat(texto, buffer);
	return texto;
}

char *imprimir_mesa(struct mesa *m){//imprime una ficha
	char texto[250];
	char buffer[5];
	sprintf(texto, "FICHAS ");
	
	for(int i=0; i<m->total;i++){
		bzero(buffer,sizeof(buffer));
		sprintf(buffer, "|%i|%i|", m->fichas[i]->valores[0], m->fichas[i]->valores[1]);
		strcat(texto, buffer);
	}
	bzero(buffer,sizeof(buffer));
	sprintf(buffer, "\n");
	strcat(texto, buffer);
	return texto;
}

int buscar_valor_mesa(struct mesa *m, int valor){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < m->total){//recorremos todas la fichas hasta encontrar el valor pedido o no
		if(m->fichas[i]->valores[0] == valor || m->fichas[i]->valores[1] == valor){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}
int buscar_valor_jugador(struct ficha **jugador, int valor){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < (sizeof(jugador)/sizeof(struct ficha))){//recorremos todas la fichas hasta encontrar el valor pedido o no
		if(jugador[i]->valores[0] == valor || jugador[i]->valores[1] == valor){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

int buscar_doble(struct ficha **jugador, int valor){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < (sizeof(jugador)/sizeof(struct ficha))){//recorremos todas la fichas hasta encontrar la ficha doble o no
		if(jugador[i]->valores[0] == valor && jugador[i]->valores[1] == valor){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

int buscar_ficha_jugador(struct ficha **jugador, int valor0, int valor1){//busca una ficha con esos dos valores
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < (sizeof(jugador)/sizeof(struct ficha))){//recorremos todas la fichas hasta encontrar la ficha doble o no
		if((jugador[i]->valores[0] == valor0 && jugador[i]->valores[1] == valor1)||(jugador[i]->valores[0] == valor1 && jugador[i]->valores[1] == valor0)){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

int buscar_ficha_mesa(struct mesa *m, int valor0, int valor1){//busca la posicion donde se encuentra una ficha
	int v=-1;//se inicia a menos uno para saber si se ha encontrado o no. Si da -1 no lo ha encotrado y si es distinto es la posición
	bool encontrado = false;
	int i=0;
	while(!encontrado && i < m->total){//recorremos todas la fichas hasta encontrar la ficha doble o no
		if((m->fichas[i]->valores[0] == valor0 && m->fichas[i]->valores[1] == valor1)||(m->fichas[i]->valores[0] == valor1 && m->fichas[i]->valores[1] == valor0)){
			v=i;
			encontrado = true;
		}
		i++;
	}
	return v;
}

void rotar_ficha(struct ficha *f){ //rota la ficha, es decir, cambia los valores de posición
	int aux;
	aux = f->valores[0];//uso valor auxiliar para no machacar el valor de la ficha dada
	f->valores[0] = f->valores[1];
	f->valores[1] = aux;
}

struct ficha *consultar_valores(struct mesa *m){//devuelve los valores en los extremos de la mesa
	struct ficha *f = malloc(sizeof(struct ficha));
	f->valores[0] = m->primero->valores[0];//primer valor de la mesa
	f->valores[1] = m->ultimo->valores[1];//ultimo valor de la mesa
	return f;
}

void crear_monton(struct ficha *monton){
	//parte para crear las fichas
	struct ficha *temporal = NULL;
	int contador=0;
	for(int i=0;i<7;i++){//con estos bucles creo todas las fichas sin repetirme en algunas por ejemplo [1|0] y [0|1]
		for(int j=0;j<=i;j++){

			monton = realloc(monton,(contador+1)*sizeof(struct ficha));//reservamos memoria para monton donde se almacenaran todas las fichas
			temporal = crear_ficha(i,j);//esta variable guardara temporalmente la ficha
			memcpy(&monton[contador], temporal, sizeof(struct ficha));//copiamos esta variable en nuestro conjunto de fichas
			free(temporal);//liberamos la memoria de nuestra ficha temporal
			contador++;
		}
	}
	revolver(monton);//función que revuelve las fichas
}

void rellenar_jugadores(struct ficha **jugador1, struct ficha **jugador2, struct ficha *monton, int *i){
	while(*i < 7){
		agregar_ficha(jugador1, &monton[*i]);
		*i=*i+1;
	}
	while(*i < 14){
		agregar_ficha(jugador2, &monton[*i]);
		*i=*i+1;
	}
}

int empezar_turno(struct mesa *m, struct ficha **jugador1, struct ficha **jugador2){

	//procedemos ha dar turno al jugador con el mayor doble y si no poseen dobles al de número mayor
	struct ficha *temporal = NULL;
	int encontradoJ1 = -1;
	int encontradoJ2 = -1;
	int buscar = 6;

	while(encontradoJ1 == -1 && encontradoJ2 == -1 && buscar > 0){
		encontradoJ1 = buscar_doble(jugador1,buscar);
		encontradoJ2 = buscar_doble(jugador2,buscar);
		buscar--;
	}
	if(encontradoJ1 != -1){
		temporal = quitar_ficha_jugador(jugador1, encontradoJ1);//le quito la ficha para ponerla en la mesa
		agregar_ficha_mesa(m,temporal);
		return 2;

	}else if(encontradoJ2 != -1){
		temporal = quitar_ficha_jugador(jugador2, encontradoJ2);//le quito la ficha para ponerla en la mesa
		agregar_ficha_mesa(m,temporal);
		return 1;
	}else{
		buscar = 6;
		int buscar2;
		while(encontradoJ1 == -1 && encontradoJ2 == -1 && buscar > 0){
			buscar2 = 6;
			while(encontradoJ1 == -1 && encontradoJ2 == -1 && buscar2 > 0){
				encontradoJ1 = buscar_ficha_jugador(jugador1,buscar,buscar2);
				encontradoJ2 = buscar_ficha_jugador(jugador2,buscar,buscar2);
				buscar2--;
			}
			buscar--;
		}
		if(encontradoJ1 != -1){
			temporal = quitar_ficha_jugador(jugador1, encontradoJ1);//le quito la ficha para ponerla en la mesa
			agregar_ficha_mesa(m,temporal);
			return 2;
		}else if(encontradoJ2 != -1){
			temporal = quitar_ficha_jugador(jugador2, encontradoJ2);//le quito la ficha para ponerla en la mesa
			agregar_ficha_mesa(m,temporal);
			return 1;
		}else{
			return -1;
		}
	}
}

bool poner_ficha_jugador_a_mesa(struct mesa *m, struct ficha **jugador, struct ficha *ficha, bool posicion){
	int valor;
	if(posicion){//veo el valor donde quiere poner su ficha
		valor=m->primero->valores[0];
	}else{valor=m->ultimo->valores[1];}

	if((ficha->valores[0]!=valor)&&(ficha->valores[1]!=valor)){return false;}//compruebo que la ficha se puede poner

	int encontrado=buscar_ficha_jugador(jugador, ficha->valores[0], ficha->valores[1]);
	struct ficha *aux = NULL;
	free(aux);//liberamos la ficha auxiliar que consulto por si tuviera valores de haber llamado a la funcion antes
	aux = quitar_ficha_jugador(jugador, encontrado);

	if(posicion){
		if(m->primero->valores[0] != aux->valores[1]){//compruebo si es necesario girar en la primera posicion
			rotar_ficha(aux);
		}
	}else{
		if(m->ultimo->valores[1] != aux->valores[0]){//compruebo si es necesario girar en la ultima posicion
			rotar_ficha(aux);
		}
	}
	agregar_ficha_esquina(m, aux, posicion);

	return true;
}
bool pasar_turno(struct mesa *m, struct ficha **jugador){//comprobar si puede pasar turno
	int izq;
	int der;
	izq = m->primero->valores[0];
	der = m->ultimo->valores[1];

	if((buscar_valor_jugador(jugador, izq)==-1)&&(buscar_valor_jugador(jugador, der)==-1)){return true;}
	return false;
}
bool robar_ficha(struct mesa *m, struct ficha **jugador, struct ficha *monton, int *i){
	int izq, der;
	izq = m->primero->valores[0];
	der = m->ultimo->valores[1];
	if((*i==DOMINO)||((buscar_valor_jugador(jugador, izq)==-1)&&(buscar_valor_jugador(jugador, der)==-1))){return false;}//monton vacio y comprobar que el jugador no puede poner una ficha
	else{
		agregar_ficha(jugador, &monton[*i]);//agrego una ficha del monton a el jugador
		*i=*i+1;
		return true;
	}
}

int hay_ganador(struct mesa *m, struct ficha **jugador1, struct ficha **jugador2){

	if((sizeof(jugador1)/sizeof(struct ficha)) == 0){return 1;}//gana jugador 1
	if((sizeof(jugador2)/sizeof(struct ficha)) == 0){return 2;}//gana jugador 2	
		
	if(m->primero->valores[0]==m->ultimo->valores[1]){//compruebo valores de las esquinas
		int acumulador=0;
		for(int i=0;i<m->total;i++){
			if(buscar_valor_mesa(m, m->primero->valores[0])!=-1){
				acumulador++;//funciona rara
			}
		}	
		if(acumulador>=7){
			int suma1 = 0;
			int suma2 = 0;
			for(int i=0;i<(sizeof(jugador1)/sizeof(struct ficha));i++){
				suma1=suma1+jugador1[i]->valores[0]+jugador1[i]->valores[1];
			}
			for(int i=0;i<(sizeof(jugador2)/sizeof(struct ficha));i++){
				suma2=suma2+jugador2[i]->valores[0]+jugador2[i]->valores[1];
			}
			if(suma1>suma2){
				return 1;//gana jugador 1
			}else if(suma1<suma2){
				return 2;//gana jugador 2
			}else{
				return 3;//empate
			}
		}
	}
	return -1;//no gana nadie
}