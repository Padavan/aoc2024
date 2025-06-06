#include "../include/day17.h"

#include <assert.h>
#include <check.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "../include/utils.h"

// struct Register {
// 	int A;
// 	int B;
// 	int C;
// };

long long int
combo_operand(struct Register state, long long int operand)
{
    if (operand == 4) {
        return state.A;
    } else if (operand == 5) {
        return state.B;
    } else if (operand == 6) {
        return state.C;
    } else {
        return operand;
    }
}

// void print_register(struct Register state) {
// 	printf("A: %d, B: %d, C: %d\n", state.A, state.B, state.C);
// }

void print_output_array(struct OutputArray output)
{
    if (output.size <= 0) {
        return;
    }

    for (int i = 0; i < output.size; i++) {
        printf("%lld", output.arr[i]);
        if (i != (output.size - 1)) {
            printf(",");
        }
    }
}

// --- INSTRUCTIONS ---
struct Register
adv(struct Register state, long long int operand)
{
    long long int numerator = state.A;
    long long int denumerator = power(2, combo_operand(state, operand));
    long long int result = numerator / denumerator;
    // todo truncated to integer
    struct Register new_state = { result, state.B, state.C };
    return new_state;
}
struct Register
bxl(struct Register state, long long int operand)
{
    long long int result = state.B ^ operand;
    struct Register new_state = { state.A, result, state.C };
    return new_state;
}
struct Register
bst(struct Register state, long long int operand)
{
    long long int result = combo_operand(state, operand) % 8;
    struct Register new_state = { state.A, result, state.C };
    return new_state;
}
int jnz(struct Register state, long long operand)
{
    if (state.A == 0) {
        return -1;
    } else {
        return operand;
    }
}
struct Register
bxc(struct Register state)
{
    long long result = state.B ^ state.C;
    struct Register new_state = { state.A, result, state.C };
    return new_state;
}
void out(struct Register state, long long int operand, struct OutputArray* output)
{
    long long int result = combo_operand(state, operand) % 8;
    output->arr[output->size] = result;
    output->size = output->size + 1;
    return;
}
struct Register
bdv(struct Register state, long long int operand)
{
    long long int numerator = state.A;
    long long int denumerator = power(2, combo_operand(state, operand));
    long long int result = numerator / denumerator;
    // todo truncated to integer
    struct Register new_state = { state.A, result, state.C };
    return new_state;
}
struct Register
cdv(struct Register state, long long int operand)
{
    long long int numerator = state.A;
    long long int denumerator = power(2, combo_operand(state, operand));
    long long int result = numerator / denumerator;
    // todo truncated to integer
    struct Register new_state = { state.A, state.B, result };
    return new_state;
}

struct Register
run_opcode(long long int opcode,
    long long int operand,
    struct Register state,
    int* cursor,
    struct OutputArray* output)
{
    // printf("\topcode: %d, operand %d \n", opcode, operand);
    switch (opcode) {
    case 0: {
        struct Register next_state = adv(state, operand);
        *cursor = *cursor + 2;
        return next_state;
    }
    case 1: {
        struct Register next_state = bxl(state, operand);
        *cursor = *cursor + 2;
        return next_state;
    }
    case 2: {
        struct Register next_state = bst(state, operand);
        *cursor = *cursor + 2;
        return next_state;
    }
    case 3: {
        int inst_ptr = jnz(state, operand);
        if (inst_ptr == -1) {
            *cursor = *cursor + 2;
        } else {
            *cursor = inst_ptr;
        }
        return state;
    }
    case 4: {
        struct Register next_state = bxc(state);
        *cursor = *cursor + 2;
        return next_state;
    }
    case 5: {
        out(state, operand, output);
        *cursor = *cursor + 2;
        return state;
    }
    case 6: {
        struct Register new_state = bdv(state, operand);
        *cursor = *cursor + 2;
        return new_state;
    }
    case 7: {
        struct Register new_state = cdv(state, operand);
        *cursor = *cursor + 2;
        return new_state;
    }
    }

    return state;
}

///////////////////////////////////// PART1
/////////////////////////////////////////////////
struct OutputArray
run_program(struct Register initialState, struct OutputArray program)
{
    int program_cursor = 0;
    struct Register state = initialState;
    struct OutputArray output = { { 0 }, 0 };

    while (program_cursor < program.size) {
        state = run_opcode(program.arr[program_cursor],
            program.arr[program_cursor + 1],
            state,
            &program_cursor,
            &output);
    }

    return output;
}

////////////////////////////////////// PART 2
///////////////////////////////////////////////////////

struct OutputArray
run_program_with_limit(struct Register initialState, struct OutputArray program)
{
    int program_cursor = 0;
    struct Register state = initialState;
    struct OutputArray output = { { 0 }, 0 };

    while (program_cursor < program.size) {
        bool check = program.arr[program_cursor] == 5;
        state = run_opcode(program.arr[program_cursor],
            program.arr[program_cursor + 1],
            state,
            &program_cursor,
            &output);

        if (check) {
            for (int i = 0; i < output.size; i++) {
                if (output.arr[i] != program.arr[i]) {
                    return output;
                }
            }
        }
    }

    return output;
}

bool is_outputs_equal(struct OutputArray a, struct OutputArray b)
{
    if (a.size != b.size) {
        return false;
    }

    for (int i = 0; i < a.size; i++) {
        if (a.arr[i] != b.arr[i]) {
            return false;
        }
    }

    return true;
}

long long int
run_day17_part2(struct OutputArray program)
{
    struct Register new_initial_state = { 0, 0, 0 };
    struct OutputArray candidate_output = run_program(new_initial_state, program);

    // last two digits changes while sort through one digit register
    // and we doing additional loop for last two- numbers
    for (long long int place = program.size - 1; place > 0; place--) {
        while (program.size != candidate_output.size || program.arr[place] != candidate_output.arr[place]) {
            new_initial_state.A = new_initial_state.A + llpower(8, place);
            candidate_output = run_program(new_initial_state, program);
        }
    }

    while (!is_outputs_equal(program, candidate_output)) {
        new_initial_state.A = new_initial_state.A + 1;
        candidate_output = run_program(new_initial_state, program);
    }

    return new_initial_state.A;
}

int run_day17()
{
    printf("Day 17: Chronospatial Computer\n");
    // char inputpath[] = "./input/day17-test.txt";
    char inputpath[] = "./input/day17.txt";

    size_t line_num = 0;
    char* line = NULL;
    size_t len = 0;
    ssize_t read;

    FILE* fp;
    fp = fopen(inputpath, "r");

    struct Register state = { 0 };
    // int program[100] = {};
    // size_t program_length = 0;
    struct OutputArray program = { { 0 }, 0 };

    while ((read = getline(&line, &len, fp)) != -1) {
        if (line_num == 0) {
            char* a = get_substring(12, read, line);
            state.A = atoll(a);
            free(a);
        } else if (line_num == 1) {
            char* b = get_substring(12, read, line);
            state.B = atoll(b);
            free(b);
        } else if (line_num == 2) {
            char* c = get_substring(12, read, line);
            state.C = atoll(c);
            free(c);
        } else if (line_num == 4) {
            int index = 9;
            while (line[index] != '\0' && index < read - 1) {
                if (line[index] != ',') {
                    program.arr[program.size] = atoll(&line[index]);
                    program.size++;
                }
                index++;
            }
        }
        line_num++;
    }

    free(line);
    fclose(fp);

    struct OutputArray output_part1 = run_program(state, program);

    printf("\tPart 1: ");
    print_output_array(output_part1);
    printf("\n");
    printf("\tPart 2: %lld\n", run_day17_part2(program));

    return 0;
}
