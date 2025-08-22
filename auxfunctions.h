#ifndef auxfunctions
#define auxfunctions

/**
 * @file auxfunctions.h
 * @author Francisco Simões (ist1113780)
 * @brief Header file containing auxiliary functions for the system.
 *
 * This file includes the auxiliary functions prototypes used in the project.
 */

#include "structs.h"

/**
 * @brief Checks if a given year is a leap year.
 * 
 * @param year The year to check.
 * @return 1 if the year is a leap year, 0 otherwise.
 */
int is_leap_year(int year);

/**
 * @brief Gets the number of days in a given month of a specific year.
 * 
 * @param month The month (1-12).
 * @param year The year.
 * @return The number of days in the month.
 */
int days_in_month(int month, int year);

/**
 * @brief Verifies if a given date is valid compared to a reference date.
 * 
 * @param d Day of the date.
 * @param m Month of the date.
 * @param y Year of the date.
 * @param cdate The reference date.
 * @return 1 if the date is valid, 0 otherwise.
 */
int verify_date(int d, int m, int y, Date cdate);

/**
 * @brief Checks if a batch name is valid in the system.
 * 
 * A valid batch name must not exceed the maximum length and must consist of 
 * alphanumeric characters (0-9, A-F).
 * 
 * @param sys Pointer to the system structure.
 * @param batch The batch name to check.
 * @return 1 if the batch name is valid, 0 otherwise.
 */
int is_valid_batch_name(Sys *sys, const char *batch);

/**
 * @brief Checks if a batch is a duplicate in the system.
 * 
 * @param sys Pointer to the system structure.
 * @param batch The batch name to check.
 * @return 1 if the batch is a duplicate, 0 otherwise.
 */
int is_dup_batch(Sys *sys, const char *batch);

/**
 * @brief Checks if a user is vaccinated with a specific vaccine.
 * 
 * A user is considered vaccinated if they have received a dose of the specified 
 * vaccine on the current system date.
 * 
 * @param sys Pointer to the system structure.
 * @param username The username of the user.
 * @param name The name of the vaccine.
 * @return 1 if the user is vaccinated, 0 otherwise.
 */
int is_user_vaccinated(Sys *sys, const char *username, const char *name);

/**
 * @brief Verifies if a given date is valid compared to a reference date.
 * 
 * This function checks if the given date is not in the future relative to the 
 * reference date.
 * 
 * @param d Day of the date.
 * @param m Month of the date.
 * @param y Year of the date.
 * @param cdate The reference date.
 * @return 1 if the date is valid, 0 otherwise.
 */
int verify_date_d(int d, int m, int y, Date cdate);

/**
 * @brief Validates if a user can be deleted from the system.
 * 
 * This function checks whether a user can be deleted based on the provided arguments,
 * such as date and batch. It ensures the date is valid and matches the system's 
 * constraints, and verifies the batch name if provided.
 * 
 * @param sys Pointer to the system structure.
 * @param i Index of the user in the system's data structure.
 * @param arg Number of arguments provided (used to determine the type of validation).
 * @param d Day of the date to validate.
 * @param m Month of the date to validate.
 * @param y Year of the date to validate.
 * @param batch The batch name to validate (if applicable).
 * @return 1 if the user deletion is valid, 0 otherwise.
 */
int is_valid_user_deletion(Sys *sys, int i, int arg, int d, int m, int y, const char *batch);

/**
 * @brief Adds a vaccine batch to the system.
 * 
 * This function creates a new vaccine batch with the specified details and adds 
 * it to the system.
 * 
 * @param sys Pointer to the system structure.
 * @param name The name of the vaccine.
 * @param batch The batch name.
 * @param d Day of the batch expiration date.
 * @param m Month of the batch expiration date.
 * @param y Year of the batch expiration date.
 * @param doses The number of doses in the batch.
 */
void add_vacbatch(Sys *sys, const char *name, const char *batch, int d, int m, int y, int doses);

/**
 * @brief Registers an inoculation for a user.
 * 
 * This function associates a user with a vaccine batch and updates the system 
 * to reflect the inoculation.
 * 
 * @param sys Pointer to the system structure.
 * @param username The username of the user.
 * @param batch_index The index of the batch used for inoculation.
 */
void register_inoculation(Sys *sys, const char *username, int batch_index);

/**
 * @brief Prints the details of an inoculation.
 * 
 * @param inoc Pointer to the inoculation structure.
 */
void print_inoculation(const Inoc *inoc);

/**
 * @brief Removes a user from the system.
 * 
 * This function deletes a user from the system's data structure at the specified index.
 * 
 * @param sys Pointer to the system structure.
 * @param index The index of the user to remove.
 */
void remove_user(Sys *sys, int index);

/**
 * @brief Compares two vaccine batches by expiration date and batch name.
 * 
 * This function is used for sorting vaccine batches. It compares two batches
 * first by expiration date (year, month, day) and then by batch name.
 * 
 * @param a Pointer to the first batch.
 * @param b Pointer to the second batch.
 * @return A negative value if a < b, 0 if a == b, and a positive value if a > b.
 */
int compare_batches(const void *a, const void *b);

/**
 * @brief Sorts the vaccine batches in the system.
 * 
 * This function sorts the vaccine batches in ascending order of expiration date
 * and batch name.
 * 
 * @param sys Pointer to the system structure.
 * @return 0 on success.
 */
int sort_batches(Sys *sys);

/**
 * @brief Searches for a vaccine in the system by name.
 * 
 * This function searches for a vaccine batch with the specified name in the system.
 * 
 * @param sys Pointer to the system structure.
 * @param name The name of the vaccine to search for.
 * @return The index of the vaccine batch if found, -1 otherwise.
 */
int search_vacc(Sys *sys, const char *name);

/**
 * @brief Finds an available batch for a specific vaccine.
 * 
 * This function searches for the first available batch of the specified vaccine
 * that has doses remaining.
 * 
 * @param sys Pointer to the system structure.
 * @param name The name of the vaccine.
 * @return The index of the available batch if found, -1 otherwise.
 */
int find_available_batch(Sys *sys, const char *name);

#endif