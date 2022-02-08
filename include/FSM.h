/**
 * @file       FSM.h
 * @author     Horak, Jurena
 * @date       2019.6
 * @brief      Header file defining functions for functions.c file
 * ******************************************
 * @par       COPYRIGHT NOTICE (c) 2019 TBU in Zlin. All rights reserved.
 */

#ifndef _FSM_H_
#define _FSM_H_

/*Private includes: ---------------------------------------------------------*/
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*Private defines: ----------------------------------------------------------*/
/*!
 * \brief Mealys state machine - reads input per single character and transition
 * to the new state based on the value of the character. Using this approach it
 * removes comments in the C sources.
 *
 * \param[in] input   Pointer to input stream. The stream shall be opened for
 * reading.
 * \param[in] output  Pointer to the output stream. It is expected that
 * the file is opened for writting.
 */
void FSM_RemoveNotes(FILE* input, FILE* output);

#endif
