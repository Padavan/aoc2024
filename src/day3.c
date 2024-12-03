#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "day3.h"

enum STATES {
  IDLE,
  M_CHAR,
  U_CHAR,
  L_CHAR,
  BRACE_LEFT,
  FIRST_DIGIT,
  COMMA,
  SECOND_DIGIT,
  END
}; 

enum STATES step_state(enum STATES state, char current) {
    enum STATES next_state = IDLE;
    switch(state) {
    case IDLE: {
        switch(current) {
        case 'm':
            next_state = M_CHAR;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    }
    case M_CHAR:
        switch(current) {
        case 'u':
            next_state = U_CHAR;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case U_CHAR:
        switch(current) {
        case 'l':
            next_state = L_CHAR;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case L_CHAR:
        switch(current) {
        case '(':
            next_state = BRACE_LEFT;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case BRACE_LEFT:
        switch(current) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            next_state = FIRST_DIGIT;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case FIRST_DIGIT:
        switch(current) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            next_state = FIRST_DIGIT;
            break;
        case ',':
            next_state = COMMA;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case COMMA:
        switch(current) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            next_state = SECOND_DIGIT;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case SECOND_DIGIT:
        switch(current) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            next_state = SECOND_DIGIT;
            break;
        case ')':
            next_state = END;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    case END: {
        switch(current) {
        case 'm':
            next_state = M_CHAR;
            break;
        default:
            next_state = IDLE;
            break;
        }
        break;
    }}

    return next_state;
}

enum D_STATE {
    START,
    D,
    O,
    DO_LEFT_BRACKET,
    DONT_LEFT_BRACKET,
    N,
    DONT_APOSTROPHE,
    T,
    SWITCH_TO_DO,
    SWITCH_TO_DONT
};

enum D_STATE build_switch(char checked_char, char match_char, enum D_STATE next_state) {
    if (checked_char == match_char) {
        return next_state;
    } else {
        return START;
    }
}

enum D_STATE d_step_state(enum D_STATE state, char current) {
    enum D_STATE next_state;
    switch (state) {
        case START:
        case SWITCH_TO_DO:
        case SWITCH_TO_DONT:
            next_state = build_switch(current, 'd', D);
            break;
        case D:
            next_state = build_switch(current, 'o', O);
            break;
        case O:
            switch (current) {
            case '(':
                next_state = DO_LEFT_BRACKET;
                break;
            case 'n':
                next_state = N;
                break;
            default:
                next_state = START;
                break;
            }
            break;
        case DO_LEFT_BRACKET:
            next_state = build_switch(current, ')', SWITCH_TO_DO);
            break;
        case N:
            next_state  = build_switch(current, '\'', DONT_APOSTROPHE);
            break;
        case DONT_APOSTROPHE:
            next_state = build_switch(current, 't', T);
            break;
        case T:
            next_state = build_switch(current, '(', DONT_LEFT_BRACKET);
            break;
        case DONT_LEFT_BRACKET:
            next_state = build_switch(current, ')', SWITCH_TO_DONT);
            break;
    }

    return next_state;
}

// PART 2
int day3part2(char inputpath[], int line_count) {
    int result = 0;
    int mul_count = 0;

    size_t line_num = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *fp;
    fp = fopen(inputpath, "r");
    int DO_OR_DO_NOT = 1;
    while ((read = getline(&line, &len, fp)) != -1) {
        int start_index = 0;
        int end_index = 0;
        enum STATES current_state = '\0';
        enum D_STATE current_d_state = START;

        for (int i = 0; i < strlen(line); i++) {
            current_state = step_state(current_state, line[i]);
            current_d_state = d_step_state(current_d_state, line[i]);

            if (current_d_state == SWITCH_TO_DO) {
                DO_OR_DO_NOT = 1;
            } else if (current_d_state == SWITCH_TO_DONT) {
                DO_OR_DO_NOT = 0;
            }
            if (current_state == M_CHAR) {
                start_index = i;
            }
            if (current_state == END) {
                end_index = i;
                // we are throwing away mul(...), and only leaving space for <number>,<number>
                char *multiplier_str = malloc(sizeof(char)*(end_index - start_index - 4));
                memcpy(multiplier_str, line + start_index + 4, end_index - start_index - 4);

                mul_count++;
                int comma_index = find_character_index(multiplier_str, ',');
                char *first_number_str = get_substring(0, comma_index, multiplier_str);
                int first_number = atoi(first_number_str);
                free(first_number_str);

                char *second_number_str = get_substring(comma_index + 1, strlen(multiplier_str), multiplier_str); 
                int second_number = atoi(second_number_str);
                free(second_number_str);
                result = (first_number * second_number * DO_OR_DO_NOT) + result;
                free(multiplier_str);

            }
        }
    }

    fclose(fp);
    free(line);

    return result;
}


// PART 1


int day3part1(char inputpath[], int line_count) {
    int result = 0;
    int mul_count = 0;

    size_t line_num = 0;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE *fp;
    fp = fopen(inputpath, "r");
    while ((read = getline(&line, &len, fp)) != -1) {
        int start_index = 0;
        int end_index = 0;
        enum STATES current_state = IDLE;        
        for (int i = 0; i < strlen(line); i++) {
            current_state = step_state(current_state, line[i]);
            if (current_state == M_CHAR) {
                start_index = i;
            }
            if (current_state == END) {
                end_index = i;
                // we are throwing away mul(...), and only leaving space for <number>,<number>
                char *multiplier_str = malloc(sizeof(char)*(end_index - start_index - 4));
                memcpy(multiplier_str, line + start_index + 4, end_index - start_index - 4);

                mul_count++;
                int comma_index = find_character_index(multiplier_str, ',');
                char *first_number_str = get_substring(0, comma_index, multiplier_str);
                int first_number = atoi(first_number_str);
                free(first_number_str);

                char *second_number_str = get_substring(comma_index + 1, strlen(multiplier_str), multiplier_str); 
                int second_number = atoi(second_number_str);
                free(second_number_str);
                result = (first_number * second_number) + result;
                free(multiplier_str);

            }
        }
    }

    fclose(fp);
    free(line);

    return result;
}

int run_day3() {
  int DAY = 3;
  char inputpath[] = "./input/day3.txt";

  int line_count = get_line_count(inputpath);
  if (line_count == 0) {
    perror("There is no lines in puzzle input");
    return 1;
  }

  printf("Day %d\n", DAY);
  printf("\tPart 1: %d\n", day3part1(inputpath, line_count));
  printf("\tPart 2: %d\n", day3part2(inputpath, line_count));

  return 0;
}
