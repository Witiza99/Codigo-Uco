/*********************************************************************************/
/* misTipos.h: definiciones de tipos de variables para practicas con LPC2378     */
/* Sistemas Empotrados Universidad de Cordoba                                    */
/*********************************************************************************/

#ifndef __misTipos_H
#define __misTipos_H

/* Byte */
#define UINT8 	unsigned char
#define INT8 		char 
	
/* 16 bits */
#define UINT16 	unsigned short int
#define INT16 	short int
	
/* 32 bits WORD para el LPC2378 */
#define UINT32 	unsigned int
#define INT32 	int
	
/* Tipos para control */
#define STATUS	UINT32

/* Booleanas */
#define BOOL		UINT32
#define FALSE		(unsigned int)0x000000000
#define TRUE		(unsigned int)0x000000001
	
/* flags */
#define FLAG 		BOOL

#endif
