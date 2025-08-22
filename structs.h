#ifndef structs
#define structs

/**
 * @file structs.h
 * @author Francisco Simões (ist1113780)
 * @brief Structs used throughout the program.
 * 
 * This file defines the main data structures used in the program, including
 * dates, vaccine batches, inoculations, and the system state.
*/

#include "constants.h"  /**< Contains project constants. */

/**
 * @struct Date
 * @brief Represents a date with day, month, and year.
*/
typedef struct {
    int d;                      /**< Day */
    int m;                      /**< Month */
    int y;                      /**< Year */
} Date;

/**
 * @struct VacBatch
 * @brief Represents a batch of vaccines.
*/
typedef struct {
    char *name;                 /**< Vaccine name */
    char *batch;                /**< Batch name*/
    Date expiredate;            /**< Expiration date */
    int doses;                  /**< Number of Doses */
    int usages;                 /**< Number of Usages */
} VacBatch;

/**
 * @struct Inoc
 * @brief Represents an inoculation record for a patient.
*/
typedef struct {
    char *username;             /**< Name of the Patient */
    Date usagedate;             /**< Date of the inoculation */
    VacBatch batch;             /**< Vaccine batch used for the inoculation */   
} Inoc;

/**
 * @struct Sys
 * @brief Represents the system state, including batches and inoculations.
*/
typedef struct {
    Date date;                  /**< Current date of the system */
    int cntbatches;             /**< Number of batches */
    int cntusers;               /**< Number of users */
    VacBatch data[MAXBATCH];    /**< Vaccine batch information */
    Inoc dataI[MAXINOC];        /**< Inoculation information */
    int language;               /**< System language setting */
} Sys;

#endif