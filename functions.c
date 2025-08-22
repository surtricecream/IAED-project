/**
 * @file functions.c
 * @author Francisco Simões (ist1113780)
 * @brief Implementation of command functions for the vaccination system.
 * 
 * This file includes the command functions used in the project.
 */

#include "header.h"

/**
 * @brief Frees all allocated memory in the system.
 * 
 * @param sys Pointer to the system structure.
 */
void free_memory(Sys *sys) {
    // Iterate through all vaccine batches in the system.
    for (int i = 0; i < sys->cntbatches; i++) {
        // Free the memory allocated for the vaccine and batch name. 
        free(sys->data[i].name);
        free(sys->data[i].batch);
    }
    // Iterate through all users in the system.
    for (int i = 0; i < sys->cntusers; i++) {
        // Free the memory allocated for the username.
        free(sys->dataI[i].username);
    }
}

/**
 * @brief Creates a new vaccine batch.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing batch details.
 */
void create_vacbatch(Sys *sys, char *input) {
    char name[MAXVACNAME + 2];
    char batch[MAXBATCHNAME + 2];
    int doses, d, m, y;

    sscanf(input, "%*s %21s %d-%d-%d %d %51s[^\n]", batch, &d, &m, &y, &doses, name);

    if (!is_valid_batch_name(sys, batch)) { // Check if the batch name is valid.
        return;
    }
    if (is_dup_batch(sys, batch)) { // Check if the batch name is a duplicate.
        return;
    }
    if (!verify_date(d, m, y, sys->date)) { // Verify if the expiration date is valid.
        puts(sys->language ? EINVDATE_PT : EINVDATE); // Error handler.
        return;
    }
    if (doses < 0) { // Check if the number of doses is negative.
        puts(sys->language ? EINVQUANT_PT : EINVQUANT); // Error handler.
        return;
    }  
    if (strlen(name) > MAXVACNAME) { // Check if the vaccine name exceeds the maximum allowed length.
        puts(sys->language ? EINVNAME_PT : EINVNAME); // Error handler.
        return;
    }


    if (sys->cntbatches >= MAXBATCH) { // Check if the system has reached the maximum number of batches.
        puts(sys->language ? EMANYVACCINES_PT : EMANYVACCINES); // Error handler.
        return;
    }

    add_vacbatch(sys, name, batch, d, m, y, doses); // Add the new vaccine batch to the system.
    printf("%s\n", sys->data[sys->cntbatches - 1].batch);
}

/**
 * @brief Lists all vaccine batches or batches of a specific vaccine.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing the command.
 */
void list_batches(Sys *sys, char *input) {
    char name[MAXVACNAME + 2];
    char *token;
    int i, j;

    if (strcmp(input, "l\n") == 0) { // Check if the input is the command to list all batches.
        sort_batches(sys);
        for (i = 0; i < sys->cntbatches; i++) {
            printf("%s %s %02d-%02d-%04d %d %d\n", sys->data[i].name, sys->data[i].batch,
                sys->data[i].expiredate.d, sys->data[i].expiredate.m, sys->data[i].expiredate.y, 
                sys->data[i].doses, sys->data[i].usages);
        }
    }

    token = strtok(input + 2, " \n"); // Tokenize the input to extract vaccine names.
    while (token != NULL) {
        strncpy(name, token, MAXVACNAME + 1);
        j = search_vacc(sys, name); // Search for the vaccine in the system.
        if (j != -1) { // If the vaccine is found, print its batch details.
            printf("%s %s %02d-%02d-%04d %d %d\n", sys->data[j].name, sys->data[j].batch,
                sys->data[j].expiredate.d, sys->data[j].expiredate.m, sys->data[j].expiredate.y, 
                sys->data[j].doses, sys->data[j].usages);
        } else { // If the vaccine is not found, print an error message.
            printf("%s: %s\n", name, sys->language ? ENONEXVAC_PT : ENONEXVAC);
        }

        // Get the next token from the input.
        token = strtok(NULL, " \n");
    }
}

/**
 * @brief Applies a vaccine dose to a user.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing user and vaccine details.
 */
void apply_dose(Sys *sys, char *input) {
    char username[INPUTMAX + 2];
    char name[MAXVACNAME + 2];
    int j;

    if (input[2] == '"') {
        sscanf(input, "%*s \"%[^\"]\" %s", username, name); // If the username is enclosed in quotes, use this format.
    } else {
        sscanf(input, "%*s %s %s", username, name);
    }

    if (is_user_vaccinated(sys, username, name)) { // Check if the user is already vaccinated with the specified vaccine.
        puts(sys->language ? EVACCINATED_PT : EVACCINATED); // Error handler.
        return;
    }

    j = find_available_batch(sys, name); // Find an available batch of the specified vaccine.

    if (j == -1) { // If no batch is available
        puts(sys->language ? ENOSTOCK_PT : ENOSTOCK); // Error handler.
        return;
    }

    printf("%s\n", sys->data[j].batch);
    register_inoculation(sys, username, j); // Register the inoculation for the user.
}

/**
 * @brief Removes a vaccine batch from the system.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing batch details.
 */
void remove_batch(Sys *sys, char *input) {
    char batch[MAXBATCHNAME + 1];
    int i, j;
    int batchexists = 0;
    
    sscanf(input, "%*s %s", batch);

    for (i = 0; i < sys->cntbatches; i++) { // Iterate through all batches in the system.
        if (strcmp(sys->data[i].batch, batch) == 0) { // Check if the current batch matches the input batch name.
            printf("%d\n", sys->data[i].usages);
            batchexists = 1;
            
            if (sys->data[i].usages == 0) { // If the batch has no usages, remove it.
                free(sys->data[i].batch);
                free(sys->data[i].name);

                for (j = i; j < sys->cntbatches - 1; j++) { // Shift the remaining batches to fill the gap.
                    sys->data[j] = sys->data[j + 1];
                }

                sys->cntbatches--;
            } else {
                sys->data[i].doses = 0;
            }
            break;
        }
    }

    if (batchexists != 1) { // If the batch does not exist.
        printf("%s: %s\n", batch, sys->language ? ENONEXBATCH_PT : ENONEXBATCH); // Error handler.
    }
}

/**
 * @brief Deletes a user from the system.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing user details.
 */
void delete_app_user(Sys *sys, char *input) {
    char username[INPUTMAX + 1];
    char batch[MAXBATCHNAME + 1];
    int d, m, y, i, cnt = 0, arg = 0, userexists = 0;
    
    arg = sscanf(input, "%*s %s %d-%d-%d %s", username, &d, &m, &y, batch);

    for (i = 0; i < sys->cntusers; i++) { // Iterate through all users in the system.
        if (strcmp(sys->dataI[i].username, username) == 0) { // Check if the current user's username matches the input username.
            userexists = 1;

            if (!is_valid_user_deletion(sys, i, arg, d, m, y, batch)) { // Check if the user can be deleted based on the input arguments.
                return;
            }

            // If only the username is provided or the date matches, delete the user.
            if (arg == 1 || 
                (arg >= 4 && sys->dataI[i].usagedate.d == d && sys->dataI[i].usagedate.m == m && sys->dataI[i].usagedate.y == y)) {
                remove_user(sys, i);
                cnt++;
                i--;
            }
        }
    }

    if (userexists == 0) { // If the user does not exist, print an error message.
        printf("%s: %s\n", username, sys->language ? ENONEXUSER_PT : ENONEXUSER);  // Error handler.
        return; 
    }

    printf("%d\n", cnt);
}

/**
 * @brief Skips or sets the system date.
 * 
 * @param sys Pointer to the system structure.
 * @param input Input string containing the new date.
 */
void skip_date(Sys *sys, char *input) {
    int d, m, y;

    if (strcmp(input, "t\n") == 0) { // Check if the input is the command to display the current date.
        printf("%02d-%02d-%04d\n", sys->date.d, sys->date.m, sys->date.y);
        return;
    } 

    if (sscanf(input, "%*s %d-%d-%d", &d, &m, &y) != 3) { // If the input format is invalid, print an error message.
        puts(sys->language ? EINVDATE_PT : EINVDATE); // Error handler.
        return;
    }

    if (!verify_date(d, m, y, sys->date)) { // If the date is invalid, print an error message.
        puts(sys->language ? EINVDATE_PT : EINVDATE); // Error handler.
        return;
    }
    
    // Update the system date to the new date.
    sys->date.d = d;
    sys->date.m = m;
    sys->date.y = y;
    printf("%02d-%02d-%04d\n", sys->date.d, sys->date.m, sys->date.y);
}
