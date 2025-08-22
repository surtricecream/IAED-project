/**
 * @file main.c
 * @author Francisco Simões (ist1113780)
 * @brief Main function to manage the vaccination system.
 * 
 * This file contains the main function and supporting functions to manage
 * a vaccination system. It handles user commands to create vaccine batches,
 * apply doses, list inoculations, and manage users. The program supports
 * multilingual output and date manipulation for the system.
 */

#include "header.h"

/**
 * @brief Lists inoculations for all users or a specific user.
 * 
 * If the input is "u\n", it lists all inoculations for all users.
 * Otherwise, it lists inoculations for a specific user identified by their username.
 * 
 * @param sys Pointer to the system structure containing user and batch data.
 * @param input Input command specifying the operation and username (if applicable).
 */
static void list_inocs(Sys *sys, char *input) {
    char username[MAXUSERNAME + 2] = "";
    int i;
    int userexists = 0;

    // Check if the input is "u\n", which means listing all users' inoculations.
    if (strcmp(input, "u\n") == 0) {
        for (i = 0; i <= sys->cntusers - 1; i++) { /////////////////////////////////////////
            print_inoculation(&sys->dataI[i]);
        }
        return;
    }

    // Extract the username from the input, see if it is enclosed in quotes or not.
    if (input[2] == '"') {
        sscanf(input, "%*s \"%[^\"]\"", username);
    } else {
        sscanf(input, "%*s %s", username);
    }

    // Iterate through the list of users to find a match for the extracted username.
    for (i = 0; i <= sys->cntusers - 1; i++) { ////////////////////////////////////////////
        if (strcmp(sys->dataI[i].username, username) == 0) {
            print_inoculation(&sys->dataI[i]);
            userexists = 1;
        }
    }

    // In case no matching username is found.
    if (userexists != 1) {
        printf("%s: %s\n", username, sys->language ? ENONEXUSER_PT : ENONEXUSER);
    }
}

/**
 * @brief Main function to handle the vaccination system.
 * 
 * Initializes the system, processes user commands, and executes corresponding operations.
 * Supported commands:
 * - 'q': Quit the program and free allocated memory.
 * - 'c': Create a new vaccine batch.
 * - 'l': List vaccine batches.
 * - 'a': Apply a vaccine dose to a user.
 * - 'r': Remove a vaccine batch.
 * - 'd': Delete an application user.
 * - 'u': List inoculations.
 * - 't': Skip to a specific date.
 * 
 * @param argc Number of command-line arguments.
 * @param argv Array of command-line arguments.
 * @return int Returns 0 on successful execution.
 */
int main(int argc, char *argv[]) {
    char input[INPUTMAX];
    Sys sys;

    // Initialize the Sys structure to zero to avoid uninitialized values.
    memset(&sys, 0, sizeof(Sys));

    sys.cntusers = 0;
    sys.cntbatches = 0;

    // Set the initial system date to 1-1-2025.
    sys.date.d = 1;
    sys.date.m = 1;
    sys.date.y = 2025;

    // Check if the program was started with the "pt" argument to set the language.
    if (argc > 1 && strcmp(argv[1], "pt") == 0) {
        sys.language = 1; // Portuguese.
    } else {
        sys.language = 0; // English.
    }

    // Main loop to process user commands.
    while (fgets(input, INPUTMAX, stdin)) {
        switch (input[0]) {
            case 'q': free_memory(&sys); return 0;
            case 'c': create_vacbatch(&sys, input); break;
            case 'l': list_batches(&sys, input); break;
            case 'a': apply_dose(&sys, input); break;
            case 'r': remove_batch(&sys, input); break;
            case 'd': delete_app_user(&sys, input); break;
            case 'u': list_inocs(&sys, input); break;
            case 't': skip_date(&sys, input); break;
            case 'm': m(&sys, input); break;
            default: break;
        }
    }
    return 0;
}