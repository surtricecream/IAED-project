#ifndef constants
#define constants

/**
 * @file constants.h
 * @author Francisco Simões (ist1113780)
 * @brief Constants used throughout the program.
 *
 * This file defines constants for various limits and error messages
 * used in the program. It includes both English and Portuguese versions
 * of error messages.
*/

#define INPUTMAX        65536   /** @brief Maximum size for input line. */
#define MAXVACNAME      50      /** @brief Maximum length for vaccine names. */
#define MAXBATCHNAME    20      /** @brief Maximum length for batch names. */
#define MAXUSERNAME     200     /** @brief Maximum length for user names. */
#define MAXBATCH        1000    /** @brief Maximum number of batches allowed. */
#define MAXINOC         13000   /** @brief Maximum number of inoculations allowed */

/** @name English Error Messages
 *  @brief Error messages displayed to the user in English.
 *  @{
 */
#define EMANYVACCINES       "too many vaccines"         /** @brief Exceeded vaccine limit. */
#define EBATCHDUPLIC        "duplicate batch number"    /** @brief Batch number already exists. */
#define EINVBATCH           "invalid batch"             /** @brief Batch does not meet requirements. */
#define EINVNAME            "invalid name"              /** @brief Name format is invalid. */
#define EINVDATE            "invalid date"              /** @brief Date format is invalid. */
#define EINVQUANT           "invalid quantity"          /** @brief Quantity is not valid. */
#define ENONEXVAC           "no such vaccine"           /** @brief Vaccine does not exist. */
#define ENONEXBATCH         "no such batch"             /** @brief Batch does not exist. */
#define ENONEXUSER          "no such user"              /** @brief User does not exist. */
#define ENOSTOCK            "no stock"                  /** @brief Stock is depleted. */
#define EVACCINATED         "already vaccinated"        /** @brief User is already vaccinated. */
#define ENOMEMORY           "no memory"                 /** @brief Memory allocation failed. */
/** @} */

/** @name Portuguese Error Messages
 *  @brief Error messages displayed to the user in Portuguese.
 *  @{
 */
#define EMANYVACCINES_PT    "demasiadas vacinas"        /** @brief Excedido o limite de vacinas. */
#define EBATCHDUPLIC_PT     "número de lote duplicado"  /** @brief Número de lote já existe. */
#define EINVBATCH_PT        "lote inválido"             /** @brief Lote não cumpre os requisitos. */
#define EINVNAME_PT         "nome inválido"             /** @brief Formato do nome inválido. */
#define EINVDATE_PT         "data inválida"             /** @brief Formato da data inválido. */
#define EINVQUANT_PT        "quantidade inválida"       /** @brief Quantidade não é válida. */
#define ENONEXVAC_PT        "vacina inexistente"        /** @brief Vacina não existe. */
#define ENONEXBATCH_PT      "lote inexistente"          /** @brief Lote não existe. */
#define ENONEXUSER_PT       "utente inexistente"        /** @brief Utente não existe. */
#define ENOSTOCK_PT         "esgotado"                  /** @brief Stock esgotado. */
#define EVACCINATED_PT      "já vacinado"               /** @brief Utente já vacinado. */
#define ENOMEMORY_PT        "sem memória"               /** @brief Falha na alocação de memória. */
/** @} */

#endif