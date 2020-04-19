/**
*  @file  quiensabe.h
*  @brief Esta es una Red de petri automaticamente sintetizada.
*
*  @author Julio César Gambandé
*  @date 
*  @version v0.0.2
*
*/

#ifndef __QUIENSABE_H
#define __QUIENSABE_H

//Lugares:
//    "P0"
//    "P1"
//    "P2"
//    "P3"

//Transisiones:
enum t_quiensabe{
    T0,
    T1,
    T2
}

/**
* @brief Resetea todos los estados y establece el marcado inicial.
*/
void quiensabe_Reset();

/**
* @brief Hace evolucionar la maquina de estados.
* Debe ser llamado una vez por ciclo.
*/
void quiensabe_Step();

/**
* @brief Obtiene el estado de un lugar.
* @param nombre del lugar cuyo estado se desea consultar.
* @return 1 si el lugar se encuentra actualmente marcado o 0 en caso contrario, si esta desmarcado.
*/
unsigned char quiensabe_strGetOput(char* nombre);

/**
* @brief entrada de los valores logicos de las transiciones.
* @param arreglo de valores logicos, su tamaño debe ser igual al numero total de las transiciones y
* y debe estar igualmente indexado.
*/
void quiensabe_SetInput(unsigned char* arry);

#endif // __QUIENSABE_H

