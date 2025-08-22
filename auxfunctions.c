/**
 * @file auxfunctions.c
 * @author Francisco Simões (ist1113780)
 * @brief Implementation of auxiliary functions for the vaccination system.
 * 
 * This file includes the auxiliary functions used in the project.
 */

#include "header.h"

/**
 * @brief Checks if a given year is a leap year.
 * 
 * @param year The year to check.
 * @return int 1 if the year is a leap year, 0 otherwise.
 */
int is_leap_year(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

/**
 * @brief Gets the number of days in a given month of a specific year.
 * 
 * @param month The month (1-12).
 * @param year The year.
 * @return int The number of days in the month.
 */
int days_in_month(int month, int year) {
    if (month == 2) {
        return is_leap_year(year) ? 29 : 28;
    }
    if (month == 4 || month == 6 || month == 9 || month == 11) {
        return 30;
    }
    return 31;
}

/**
 * @brief Verifies if a given date is valid and not earlier than the current date.
 * 
 * @param d Day of the date.
 * @param m Month of the date.
 * @param y Year of the date.
 * @param cdate Current date.
 * @return int 1 if the date is valid, 0 otherwise.
 */
int verify_date(int d, int m, int y, Date cdate) {
    // Check if year is valid and compares it to current system's date.
    if (y < cdate.y || (y == cdate.y && (m < cdate.m || (m == cdate.m && d < cdate.d)))) {
        return 0;
    }
    if (m < 1 || m > 12) { // Check if month is valid.
        return 0;
    }
    if (d < 1 || d > days_in_month(m, y)) { // Check if day is valid.
        return 0;
    }
    return 1;
}

/**
 * @brief Checks if a batch name is valid.
 * 
 * @param sys Pointer to the system structure.
 * @param batch The batch name to validate.
 * @return int 1 if the batch name is valid, 0 otherwise.
 */
int is_valid_batch_name(Sys *sys, const char *batch) {
    if (strlen(batch) > MAXBATCHNAME) { // If batch name length is valid.
        puts(sys->language ? EINVBATCH_PT : EINVBATCH); // Error handler.
        return 0;
    }
    for (int i = 0; batch[i] != '\0'; i++) {
        if (!(((batch[i] >= '0') && (batch[i] <= '9')) || ((batch[i] >= 'A') && (batch[i] <= 'F')))) { // Check hexadecimal digits.
            puts(sys->language ? EINVBATCH_PT : EINVBATCH); // Error handler.
            return 0;
        }
    }
    return 1;
}

/**
 * @brief Checks if a batch is a duplicate.
 * 
 * @param sys Pointer to the system structure.
 * @param batch The batch name to check.
 * @return int 1 if the batch is a duplicate, 0 otherwise.
 */
int is_dup_batch(Sys *sys, const char *batch) {
    for (int i = 0; i < sys->cntbatches; i++) {
        if (strcmp(batch, sys->data[i].batch) == 0) { // Check if there already exists a batch with the same name in the system.
            puts(sys->language ? EBATCHDUPLIC_PT : EBATCHDUPLIC); // Error handler.
            return 1;
        }
    }
    return 0;
}

/**
 * @brief Checks if a user is already vaccinated with a specific batch on the current date.
 * 
 * @param sys Pointer to the system structure.
 * @param username The username of the user.
 * @param name The name of the batch.
 * @return int 1 if the user is vaccinated, 0 otherwise.
 */
int is_user_vaccinated(Sys *sys, const char *username, const char *name) {
    for (int i = 0; i < sys->cntusers; i++) {
        // Check if the user and vaccine name exist in the system and if it date is the same as the current system's date.
        if (strcmp(sys->dataI[i].username, username) == 0 && 
            strcmp(sys->dataI[i].batch.name, name) == 0 &&
            sys->dataI[i].usagedate.d == sys->date.d &&
            sys->dataI[i].usagedate.m == sys->date.m &&
            sys->dataI[i].usagedate.y == sys->date.y) {
            return 1; // User is already vaccinated.
        }
    }
    return 0; // User is not vaccinated.
}

/**
 * @brief Verifies if a given date is valid and not later than the current date.
 * 
 * @param d Day of the date.
 * @param m Month of the date.
 * @param y Year of the date.
 * @param cdate Current date.
 * @return int 1 if the date is valid, 0 otherwise.
 */
int verify_date_d(int d, int m, int y, Date cdate) {
    // Check if year is valid and compares it to current system's date.
    if (y > cdate.y || (y == cdate.y && (m > cdate.m || (m == cdate.m && d > cdate.d)))) {
        return 0;
    }
    if (m < 1 || m > 12) { // Check if month is valid.
        return 0;
    }
    if (d < 1 || d > days_in_month(m, y)) { // Check if day is valid.
        return 0;
    }
    return 1;
}

/**
 * @brief Checks if a user deletion request is valid.
 * 
 * @param sys Pointer to the system structure.
 * @param i Index of the user in the system.
 * @param arg Number of arguments provided.
 * @param d Day of the date.
 * @param m Month of the date.
 * @param y Year of the date.
 * @param batch The batch name to validate.
 * @return int 1 if the deletion is valid, 0 otherwise.
 */
int is_valid_user_deletion(Sys *sys, int i, int arg, int d, int m, int y, const char *batch) {
    if (arg >= 4 && !verify_date_d(d, m, y, sys->date)) {
        puts(sys->language ? EINVDATE_PT : EINVDATE); // Error handler.
        return 0; // Invalid date.
    }

    if (arg == 5 && strcmp(sys->dataI[i].batch.batch, batch) != 0) {
        printf("%s: %s\n", batch, sys->language ? ENONEXBATCH_PT : ENONEXBATCH); // Error handler.
        return 0; // Batch mismatch.
    }

    return 1; // Valid for deletion.
}

/**
 * @brief Adds a new vaccination batch to the system.
 * 
 * @param sys Pointer to the system structure.
 * @param name The name of the vaccine.
 * @param batch The batch name.
 * @param d Expiration day.
 * @param m Expiration month.
 * @param y Expiration year.
 * @param doses Number of doses in the batch.
 */
void add_vacbatch(Sys *sys, const char *name, const char *batch, int d, int m, int y, int doses) {
    sys->data[sys->cntbatches].name = malloc(strlen(name) + 1);
    strcpy(sys->data[sys->cntbatches].name, name);
    sys->data[sys->cntbatches].batch = malloc(strlen(batch) + 1);
    strcpy(sys->data[sys->cntbatches].batch, batch);
    sys->data[sys->cntbatches].expiredate.d = d;
    sys->data[sys->cntbatches].expiredate.m = m;
    sys->data[sys->cntbatches].expiredate.y = y;
    sys->data[sys->cntbatches].doses = doses;
    sys->data[sys->cntbatches].usages = 0;
    sys->cntbatches++;
}

/**
 * @brief Registers an inoculation for a user with a specific batch.
 * 
 * @param sys Pointer to the system structure.
 * @param username The username of the user.
 * @param batch_index The index of the batch in the system.
 */
void register_inoculation(Sys *sys, const char *username, int batch_index) {
    sys->dataI[sys->cntusers].username = malloc(strlen(username) + 1);
    strcpy(sys->dataI[sys->cntusers].username, username);
    sys->dataI[sys->cntusers].usagedate = sys->date;
    sys->dataI[sys->cntusers].batch = sys->data[batch_index];
    sys->cntusers++;
    sys->data[batch_index].usages++;
    sys->data[batch_index].doses--;
}

/**
 * @brief Prints the details of an inoculation.
 * 
 * @param inoc Pointer to the inoculation structure.
 */
void print_inoculation(const Inoc *inoc) {
    printf("%s %s %02d-%02d-%04d\n", 
           inoc->username, 
           inoc->batch.batch, 
           inoc->usagedate.d, 
           inoc->usagedate.m, 
           inoc->usagedate.y);
}

/**
 * @brief Removes a user from the system.
 * 
 * @param sys Pointer to the system structure.
 * @param index The index of the user to remove.
 */
void remove_user(Sys *sys, int index) {
    free(sys->dataI[index].username); // Free the memory allocated for the username of the user being removed.
    for (int j = index; j < sys->cntusers - 1; j++) { // Shift all users after the removed user one position to the left.
        sys->dataI[j] = sys->dataI[j + 1];
    }
    sys->cntusers--;
}

/**
 * @brief Compares two vaccination batches based on their expiration dates and names.
 * 
 * @param a Pointer to the first batch.
 * @param b Pointer to the second batch.
 * @return int Negative if the first batch is earlier, positive if later, 0 if equal.
 */
int compare_batches(const void *a, const void *b) {
    VacBatch *batchA = (VacBatch *)a;
    VacBatch *batchB = (VacBatch *)b;

    if (batchA->expiredate.y != batchB->expiredate.y) // Compare the expiration years of the two batches.
        return batchA->expiredate.y - batchB->expiredate.y;
    if (batchA->expiredate.m != batchB->expiredate.m) // Compare the expiration months of the two batches.
        return batchA->expiredate.m - batchB->expiredate.m;
    if (batchA->expiredate.d != batchB->expiredate.d) // Compare the expiration days of the two batches.
        return batchA->expiredate.d - batchB->expiredate.d;

    return strcmp(batchA->batch, batchB->batch); // Compare the two batches names.
}

/**
 * @brief Sorts the vaccination batches in the system by expiration date and name.
 * 
 * @param sys Pointer to the system structure.
 * @return int Always returns 0.
 */
int sort_batches(Sys *sys) {
    int i, j;
    VacBatch temp;

    for (i = 0; i < sys->cntbatches - 1; i++) {
        for (j = 0; j < sys->cntbatches - i - 1; j++) {
            if (compare_batches(&sys->data[j], &sys->data[j + 1]) > 0) { // Compare two adjacent batches.
                temp = sys->data[j];
                sys->data[j] = sys->data[j + 1]; // Swap the first batch with the second.
                sys->data[j + 1] = temp;
            }
        }
    }
    return 0;
}

/**
 * @brief Searches for a vaccine by name in the system.
 * 
 * @param sys Pointer to the system structure.
 * @param name The name of the vaccine to search for.
 * @return int The index of the vaccine if found, -1 otherwise.
 */
int search_vacc(Sys *sys, const char *name) {
    int i;

    for (i = 0; i < sys->cntbatches; i++) {
        if (strcmp(name, sys->data[i].name) == 0) { // Compare the given name with the name of the current batch.
            return i; // If a match is found, return the index of the batch.
        }
    }
    return -1;
}

/**
 * @brief Finds the first available batch of a vaccine with remaining doses.
 * 
 * @param sys Pointer to the system structure.
 * @param name The name of the vaccine to search for.
 * @return int The index of the available batch if found, -1 otherwise.
 */
int find_available_batch(Sys *sys, const char *name) {
    int j;

    sort_batches(sys);
    j = search_vacc(sys, name); // Search for the first batch with the given vaccine name.

    while (j != -1 && sys->data[j].doses == 0) { // Loop while the batch exists and has no remaining doses.
        j++;
        if (j >= sys->cntbatches || strcmp(sys->data[j].name, name) != 0) { // Check if the index is out of bounds or the batch name no longer matches.
            j = -1;
        }
    }

    return j; // Return the index of the first available batch, or -1 if none is found.
}