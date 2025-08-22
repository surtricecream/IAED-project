#ifndef functions
#define functions

/**
 * @file functions.h
 * @author Francisco Simões (ist1113780)
 * @brief Header file containing the command functions declarations for the project.
 * 
 * This file includes the command functions prototypes used in the project.
 */

#include "structs.h"

/**
 * @brief Frees all allocated memory in the system.
 * 
 * @param sys Pointer to the system structure.
 */
void free_memory(Sys *sys);

/**
 * @brief Creates a new vaccine batch.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing batch details.
 */
void create_vacbatch(Sys *sys, char *input);

/**
 * @brief Lists vaccine batches.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string for filtering or additional options.
 */
void list_batches(Sys *sys, char *input);

/**
 * @brief Applies a vaccine dose to a user.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing user and dose details.
 */
void apply_dose(Sys *sys, char *input);

/**
 * @brief Removes a vaccine batch from the system.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing batch details to remove.
 */
void remove_batch(Sys *sys, char *input);

/**
 * @brief Deletes an application user from the system.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing user details to delete.
 */
void delete_app_user(Sys *sys, char *input);

/**
 * @brief Skips the system's current date or gives the current system's date.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing the date skip details.
 */
void skip_date(Sys *sys, char *input);

#endif