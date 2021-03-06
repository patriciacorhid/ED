/**
 * @file quienesquien.h
 * @brief Fichero cabecera del QuienEsQuien.
 *
 * Almacena el árbol de preguntas para jugar al ¿Quién es quién?.
 */

#ifndef _QUIENESQUIEN_H_
#define _QUIENESQUIEN_H_

#define DEBUG_QUIENESQUIEN 0

#include <string>
#include <iostream>
#include <map>
#include <vector>
#include <cassert>
#include <set>
#include <sstream>
#include <list>

#include "pregunta.h"
#include "bintree.h"

using namespace std;

/**
 * @brief T.D.A. QuienEsQuien
 *
 * Conjunto de personajes con sus atributos.
 *
 * @author Patricia Córdoba Hidalgo y David Cabezas Berrido
 * @date Diciembre 2017
 */
class QuienEsQuien{
private:
	/**
	  * @brief Almacena el nombre de los personajes. Su índice en
	  *        este vector corresponde con el índice de su
	  *        descripción en el tablero.
	  */
	vector<string> personajes;

	/**
	  * @brief Almacena los atributos.  Su ìndice en este vector
	  *        corresponde con el ìndice correspondiente de cada
	  *        vector del tablero.
	  */
	vector<string> atributos;

	/**
	  * @brief Matriz que almacena para cada personaje su valor para
	  *        cada atributo.
	  */
	vector<vector<bool>> tablero;

	/**
	  * @brief Arbol de preguntas para adivinar personajes.
	  */
	bintree<Pregunta> arbol;

	/**
	  * @brief Nodo del arbol de preguntas correspondiente a la jugada
	  *        actual.
	  */
	bintree<Pregunta>::node jugada_actual;

	/**
		* @brief Método que modifica el árbol de preguntas para que no haya
		*       preguntas redundantes.
		* @param n Nodo a partir del cual comprobamos si hay preguntas redundantes.
		* @pre La raíz no puede ser un nodo redundante.
		* @post El árbol de preguntas se modifica.
		*/
	void eliminar_nodos_redundantes(bintree<Pregunta>::node n);

	/**
		* @brief Elige como pregunta el próximo atributo y coloca los personajes a la
		*				izquierda o derecha de un nodo con dicha pregunta según si tienen el
		*				atrubuto o no
		* @param a Árbol de preguntas que estamos creando.
		* @param pers Índices de los personajes del vector de personajes
		* @param atrib Índices de los atributos del vector de atrbutos que quedan sin colocar
		* @post El árbol a se modifica
		* @post La lista atrib se modifica
		*/
	void elige_preguntas(bintree<Pregunta> &a, list<int> pers, list<int> atrib);

	/**
		* @brief Elige como pregunta el atributo óptimo y coloca los personajes a la
		*				izquierda o derecha de un nodo con dicha pregunta según si tienen el
		*				atrubuto o no
		* @param a Árbol de preguntas que estamos creando.
		* @param pers Índices de los personajes del vector de personajes
		* @param atrib Índices de los atributos del vector de atrbutos que quedan sin colocar
		* @post El árbol a se modifica
		* @post La lista atrib se modifica
		*/
	void elige_preguntas_mejorado(bintree<Pregunta> &a, list<int> pers, list<int> atrib);

	/**
		* @brief Devuelve la suma de las profundidades de los nodos hoja de árbol
		* @param n Nodo a partir del cuál se encuentran las hojas cuyas profundidades
		* 			 queremos calcular
		* @param prof_actual Profundidad del nodo n
		* @param suma_prof Suma de las profundidades de las hojas a partir del nodo n
		* @prec !n.null()
		* @prec Árbol ya creado
		*/
	void suma_profundidad_hojas(bintree<Pregunta>::node n, int prof_actual, int &suma_prof);

public:

	/**
	  * @brief Constructor básico de la clase
	  */
	QuienEsQuien();

	/**
	  * @brief Constructor de copia.
	  * @param quienEsQuien QuienEsQuien a copiar.
	  */
	QuienEsQuien(const QuienEsQuien &quienEsQuien);

	/**
	* @brief Destructor del pregunta.
	*/
	~QuienEsQuien();

	/**
	  * @brief Vacia todos los datos del QuienEsQuien receptor.
	  */
	void limpiar();

	/**
	* @brief Sobrecarga del operador de asignación.
	* @param quienEsQuien objeto a copiar.
	* @return Referencia al objeto copiado.
	*/
	QuienEsQuien& operator = (const QuienEsQuien &quienEsQuien);

	/**
	* @brief Operador de extracción de flujo.
	* @param is Stream de entrada
	* @param quienEsQuien Quien es quien a leer.
	* @return Referencia al stream de entrada.
	*
	* Lee de @e is un quien es quien y lo almacena en @e
	* quienEsQuien. El formato aceptado para la lectura es un TSV
	* (tab-separated values) en el que las columnas tienen cabecera y
	* son las preguntas. La última columna corresponde al nombre del
	* personaje. Tras la cabecera se especifica en cada línea un
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	* atributo de la columna. En la última columna se da el
	* nombre del personaje.
	*/
	friend istream& operator >> (istream& is, QuienEsQuien &quienEsQuien);

	/**
	* @brief Operador de inserción de flujo.
	* @param os Stream de salida
	* @param quienEsQuien Quien es quien a escribir.
	* @return Referencia al stream de salida.
	*
	* Escribe en @e is un quien es quien.
	* El formato usado para la escritura es un TSV
	* (tab-separated values) en el que las columnas tienen cabecera y
	* son las preguntas. La última columna corresponde al nombre del
	* personaje. Tras la cabecera se especifica en cada línea un
	* personaje, teniendo el valor 1 o 0 si tiene/no tiene el
	* atributo de la columna. En la última columna se da el
	* nombre del personaje.
	*/
	friend ostream& operator << (ostream& os, const QuienEsQuien &quienEsQuien);

	/**
	  * @brief Escribe en la salida estandar las estructuras atributos, personajes y tablero.
	  */
	void mostrar_estructuras_leidas();

	/**
		* @brief Crea el árbol de preguntas a partir de los datos del tablero
		* @post El árbol de preguntas se modifica
		*/
	bintree<Pregunta> crear_arbol();

	/**
		* @brief Crea el árbol de preguntas óptimo a partir de los datos del tablero
		* @post El árbol de preguntas se modifica
		*/
	bintree<Pregunta> crear_arbol_mejorado();

	/**
	  * @brief Sustituye el árbol actual por el árbol pasado por parámetro.
	  *
	  * @param arbol_nuevo Arbol de preguntas que sustituye al actual.
	  *
	  */
	void usar_arbol(bintree<Pregunta> arbol_nuevo);

	/**
	  * @brief Escribe el arbol generado en la salida estandard.
	  */
	void escribir_arbol_completo() const;

	/**
		* @brief Elimina el personaje con el nombre dado como argumento
		* @param nombre del personaje a eliminar
	  */
	void elimina_personaje(string nombre);

	/**
	 * @brief Inicializa el juego.
	 * @post  Si la partida anterior no había terminado se
	 *        pierde el progreso.
	 */
	void iniciar_juego();

	/**
	 * @brief Muestra por pantalla todas las preguntas formuladas hasta el momento
	 * 				en la partida y su correspondiente respuesta
	 * @param jugada hasta la que se ha avanzado con las preguntas formuladas
	 *
	 */
	void preguntas_formuladas(bintree<Pregunta>::node jugada);

	/**
	  * @brief Dado un estado del tablero devuelve los nombres de
	  *        los personajes que aún no han sido tumbados en el
	  *        tablero.
	  *
	  * @param jugada_actual Nodo del estado del tablero.
	  *
	  * @return Conjunto de personajes que no han sido tumbados en el tablero.
	  *
	  * @pre El arbol del QuienEsQuien receptor debe haber sido construido previamente.
	  * @pre El nodo indicado debe ser un nodo del arbol del QuienEsQuien receptor.
	  */
	set<string> informacion_jugada(bintree<Pregunta>::node jugada_actual);

	/**
	  * @brief Este método permite calcular la media de la profundidad de las hojas del árbol.
		*				Este valor representa el número (promedio) de preguntas necesarias para adivinar cada personaje.
		*			 	A menor profundidad promedio, mejor solución. Esta métrica es un indicador para evaluar la calidad
		*				de vuestra solución.
	  *
	  * @return Profundidad media de las hojas del arbol de preguntas.
	  *
	  * @pre El arbol de preguntas debe haber sido construido previamente.
	  */
	float profundidad_promedio_hojas();

	/**
		* @brief Método que modifica el árbol de preguntas para que no haya
		*       preguntas redundantes.
		* @post El árbol de preguntas se modifica.
		*/
	void eliminar_nodos_redundantes();

	/**
	  * @brief Rellena los datos del QuienEsQuien con un tablero calculado aleatoriamente.
	  *
	  * @param numero_de_personajes Número de personajes que tiene el tablero a crear.
	  */
	void tablero_aleatorio(int numero_de_personajes);

	/**
		* @brief Devuelve el número de personajes
		* @return Número de personajes
		*/
	int size_personajes() const;

	/**
		* @brief Devuelve el número de atributos
		* @return Número de atributos
		*/
	int size_atributos() const;

	/**
		* @brief Añade un personaje al árbol
		* @param nombre del nuevo personaje
		* @param caracteristicas del nuevo personaje
		*/
	void add_personaje(string nombre, vector<bool> caracteristicas);
};

#endif
