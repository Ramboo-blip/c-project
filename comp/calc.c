#include <stdio.h>
#include <math.h> // For fmod, pow, NAN

// Forward declarations
double division(double a, double b);
double modulus(double a, double b);
void print_menu(void);
void prompt_for_choice(void);
int get_numbers(double *first, double *second);

/**
 * @brief Defines the available calculator operations.
 */
typedef enum {
    ADD = 1,
    SUBTRACT,
    MULTIPLY,
    DIVIDE,
    MODULUS_OP, // MODULUS is a C keyword, so MODULUS_OP is used
    POWER,
    EXIT
} MenuChoice;

/**
 * @brief Main function for the calculator program.
 *
 * Initializes the calculator, displays the menu, and processes user input
 * for arithmetic operations until the user chooses to exit.
 * @return 0 on successful execution.
 */
int main(void) {
    MenuChoice Choice; // Variable to store the user's menu selection
    double first, second, result; // Variables for operands and result

    print_menu(); // Display the main menu once at the beginning
    prompt_for_choice(); // Prompt the user for their initial choice

    // Main program loop: continues until the user chooses to exit
    while (1) {
        // Read user's menu choice
        if (scanf("%d", (int*)&Choice) != 1) {
            // Handle non-numeric input for menu choice
            fprintf(stderr, "Invalid input. Please enter a valid menu option.\n");
            // Consume the rest of the invalid input line
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            print_menu(); // Reprint the menu as the screen might be garbled
            prompt_for_choice(); // Re-prompt the user
            continue; // Restart the loop to get fresh input
        }

        // Check if the user chose to exit
        if (Choice == EXIT) {
            printf("Exiting calculator. Goodbye!\n");
            break; // Exit the main loop
        }

        // Validate if the numeric choice is within the valid menu range
        if (Choice < ADD || Choice > EXIT) {
            fprintf(stderr, "Invalid Menu Choice. Please enter a number between %d and %d.\n", ADD, EXIT);
            // Consume the rest of the invalid input line (likely just a newline)
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            prompt_for_choice(); // Re-prompt the user without reprinting the whole menu
            continue; // Restart the loop
        }

        // Get the two numbers for the operation
        if (get_numbers(&first, &second) != 0) {
            // get_numbers handles its own error message and input consumption
            prompt_for_choice(); // Re-prompt for menu choice if number input failed
            continue; // Restart the loop
        }

        // Perform the selected operation using a switch statement
        switch (Choice) {
            case ADD:
                result = first + second;
                break;
            case SUBTRACT:
                result = first - second;
                break;
            case MULTIPLY:
                result = first * second;
                break;
            case DIVIDE:
                result = division(first, second);
                break;
            case MODULUS_OP:
                result = modulus(first, second);
                break;
            case POWER:
                result = pow(first, second); // from <math.h>
                break;
            default:
                // This case should ideally not be reached due to prior validation
                fprintf(stderr, "Error: Unhandled menu choice in switch!\n");
                result = NAN;
                break;
        }

        // Display the result if the operation was successful (not NAN)
        if (!isnan(result)) {
            printf("\nResult of operation is: %.2f\n", result);
        }

        // Prompt for the next menu choice for the subsequent iteration
        prompt_for_choice();
    }

    return 0; // Indicate successful program termination
}

/**
 * @brief Performs division of two double-precision numbers.
 * @param a The dividend.
 * @param b The divisor.
 * @return The result of a / b. If b is 0, prints an error and returns NAN.
 */
double division(double a, double b) {
    // Check for division by zero
    if (b == 0.0) {
        fprintf(stderr, "Error: Cannot divide by zero.\n");
        return NAN; // Not a Number, from <math.h>
    } else {
        return a / b;
    }
}

/**
 * @brief Calculates the modulus of two double-precision numbers.
 * @param a The dividend.
 * @param b The divisor.
 * @return The result of a mod b using fmod(). If b is 0, prints an error and returns NAN.
 */
double modulus(double a, double b) {
    // Check for division by zero (modulus is undefined)
    if (b == 0.0)  {
        fprintf(stderr, "Error: Division by zero in modulus operation.\n");
        return NAN; // Not a Number, from <math.h>
    } else {
        return fmod(a, b); // fmod() from <math.h> for double modulus
    }
}

/**
 * @brief Prompts the user to enter two numbers (operands).
 *
 * Includes input validation to ensure valid double-precision numbers are entered.
 * @param first Pointer to a double where the first number will be stored.
 * @param second Pointer to a double where the second number will be stored.
 * @return 0 on successful input of both numbers, 1 if input fails for either number.
 */
int get_numbers(double *first, double *second) {
    printf("\nPlease enter the first number: ");
    // Read and validate the first number
    if (scanf("%lf", first) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number for the first operand.\n");
        // Consume the rest of the invalid input line
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1; // Indicate failure
    }

    printf("Now enter the second number: ");
    // Read and validate the second number
    if (scanf("%lf", second) != 1) {
        fprintf(stderr, "Invalid input. Please enter a number for the second operand.\n");
        // Consume the rest of the invalid input line
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        return 1; // Indicate failure
    }
    return 0; // Indicate success
}

/**
 * @brief Displays the main menu of the calculator.
 */
void print_menu(void) {
    printf("\n\n------------------------------\n");
    printf("Welcome to Simple Calculator\n");
    printf("------------------------------\n");
    printf("Choose one of the following Options:\n");
    printf("%d. Add\n", ADD);
    printf("%d. Subtract\n", SUBTRACT); // Corrected "Substract" to "Subtract"
    printf("%d. Multiply\n", MULTIPLY);
    printf("%d. Divide\n", DIVIDE);
    printf("%d. Modulus\n", MODULUS_OP);
    printf("%d. Power\n", POWER);
    printf("%d. Exit\n", EXIT);
    printf("------------------------------\n");
}

/**
 * @brief Displays the prompt for the user to enter their menu choice.
 */
void prompt_for_choice(void) {
    printf("\nNow Enter your Choice: ");
}
