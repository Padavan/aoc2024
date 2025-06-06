#include "day8.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "matrix_utils.h"
#include "utils.h"

char nodes_characters[62] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
    'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
    's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A',
    'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
    'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', '0', '1',
    '2', '3', '4', '5', '6', '7', '8', '9' };

// PART 1
int day8_part1(char** matrix, size_t width, size_t height)
{
    char** antinodes_matrix = malloc(sizeof(char*) * width);
    for (size_t row = 0; row < height; row++) {
        antinodes_matrix[row] = malloc(sizeof(char) * width);
    }

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            antinodes_matrix[row][col] = '.';
        }
    }

    for (int i = 0; i < 62; i++) {
        char target = nodes_characters[i];

        size_t nodes[100][2] = { 0 };
        int finded_nodes = 0;

        for (size_t row = 0; row < height; row++) {
            for (size_t col = 0; col < width; col++) {
                if (matrix[col][row] == target) {
                    nodes[finded_nodes][0] = col;
                    nodes[finded_nodes][1] = row;
                    finded_nodes++;
                }
            }
        }

        for (int i = 0; i < finded_nodes; i++) {
            for (int j = 0; j < finded_nodes; j++) {
                if (i == j) {
                    continue;
                } else {
                    int diff_col = nodes[j][0] - nodes[i][0];
                    int diff_row = nodes[j][1] - nodes[i][1];
                    size_t increase_a[2] = { diff_col, diff_row };
                    size_t increate_b[2] = { -diff_col, -diff_row };

                    size_t* antinode_a = move_point(nodes[j], increase_a);
                    size_t* antinode_b = move_point(nodes[i], increate_b);

                    if (is_inbound(antinode_a, width, height)) {
                        antinodes_matrix[antinode_a[0]][antinode_a[1]] = '#';
                    }

                    if (is_inbound(antinode_b, width, height)) {
                        antinodes_matrix[antinode_b[0]][antinode_b[1]] = '#';
                    }
                    free(antinode_a);
                    free(antinode_b);
                }
            }
        }
    };

    // print_char_matrix(width, height, antinodes_matrix);

    int count_anitnodes = 0;
    for (size_t col = 0; col < height; col++) {
        for (size_t row = 0; row < width; row++) {
            if (antinodes_matrix[col][row] == '#') {
                count_anitnodes++;
            }
        }
    }

    for (size_t i = 0; i < height; ++i) {
        free(antinodes_matrix[i]);
    }
    free(antinodes_matrix);

    return count_anitnodes;
};

// PART 2
int day8_part2(char** matrix, size_t width, size_t height)
{
    char** antinodes_matrix = malloc(sizeof(char*) * width);
    for (size_t row = 0; row < height; row++) {
        antinodes_matrix[row] = malloc(sizeof(char) * width);
    }

    for (size_t row = 0; row < height; row++) {
        for (size_t col = 0; col < width; col++) {
            antinodes_matrix[row][col] = '.';
        }
    }

    for (int i = 0; i < 62; i++) {
        char target = nodes_characters[i];

        size_t nodes[100][2] = { 0 };
        int finded_nodes = 0;

        for (size_t row = 0; row < height; row++) {
            for (size_t col = 0; col < width; col++) {
                if (matrix[col][row] == target) {
                    nodes[finded_nodes][0] = col;
                    nodes[finded_nodes][1] = row;
                    finded_nodes++;
                }
            }
        }

        for (int i = 0; i < finded_nodes; i++) {
            for (int j = 0; j < finded_nodes; j++) {
                if (i == j) {
                    continue;
                } else {
                    int diff_col = nodes[j][0] - nodes[i][0];
                    int diff_row = nodes[j][1] - nodes[i][1];

                    // SIDE A
                    int multiplier_a = 0;

                    size_t increase_a[2] = { diff_col * multiplier_a,
                        diff_row * multiplier_a };
                    size_t* antinode_a = move_point(nodes[j], increase_a);

                    while (is_inbound(antinode_a, width, height)) {
                        antinodes_matrix[antinode_a[0]][antinode_a[1]] = '#';
                        multiplier_a++;
                        size_t increase_a[2] = { diff_col * multiplier_a,
                            diff_row * multiplier_a };
                        size_t* next_antinode_a = move_point(nodes[j], increase_a);
                        antinode_a[0] = next_antinode_a[0];
                        antinode_a[1] = next_antinode_a[1];
                        free(next_antinode_a);
                    }
                    free(antinode_a);

                    // SIDE B
                    int multiplier_b = 0;

                    size_t increate_b[2] = { -diff_col * multiplier_b,
                        -diff_row * multiplier_b };
                    size_t* antinode_b = move_point(nodes[i], increate_b);

                    while (is_inbound(antinode_b, width, height)) {
                        antinodes_matrix[antinode_b[0]][antinode_b[1]] = '#';
                        multiplier_b++;
                        size_t increate_b[2] = { -diff_col * multiplier_b,
                            -diff_row * multiplier_b };
                        size_t* next_antinode_b = move_point(nodes[i], increate_b);
                        antinode_b[0] = next_antinode_b[0];
                        antinode_b[1] = next_antinode_b[1];
                        free(next_antinode_b);
                    }
                    free(antinode_b);
                }
            }
        }
    };

    // print_char_matrix(width, height, antinodes_matrix);

    int count_anitnodes = 0;
    for (size_t col = 0; col < height; col++) {
        for (size_t row = 0; row < width; row++) {
            if (antinodes_matrix[col][row] == '#') {
                count_anitnodes++;
            }
        }
    }

    for (size_t i = 0; i < height; ++i) {
        free(antinodes_matrix[i]);
    }
    free(antinodes_matrix);

    return count_anitnodes;
};

int run_day8()
{
    printf("Day 8: Resonant Collinearity\n");
    // char inputpath[] = "./input/day8-test.txt";
    char inputpath[] = "./input/day8.txt";

    FILE* fp;
    fp = fopen(inputpath, "r");
    char ch;

    char content[10000] = { 0 };

    size_t char_count = 0;
    size_t matrix_size = 0;
    size_t line = 0;
    do {
        ch = fgetc(fp);
        if (ch == '\n') {
            if (line == 0) {
                matrix_size = char_count;
            }
            line++;
        } else {
            content[char_count] = ch;
        }
        char_count++;
    } while (ch != EOF);
    fclose(fp);

    if (matrix_size < 2) {
        perror("Matrix dimensions are wrong");
        return 1;
    }

    char** matrix = malloc(sizeof(char*) * matrix_size);
    for (size_t row = 0; row < matrix_size; row++) {
        matrix[row] = malloc(sizeof(char) * matrix_size);
    }

    size_t col = 0;
    size_t row = 0;

    size_t index = 0;
    while (index <= char_count) {
        char current = content[index];

        index++;
        if (current == '.' || find_character_index(nodes_characters, current) >= 0) {
            matrix[row][col] = current;
            if (col == (matrix_size - 1)) {
                row++;
                col = 0;
            } else {
                col++;
            }
        }
    }

    // print_char_matrix(matrix_size, matrix_height, matrix);

    printf("\tPart 1: %d\n", day8_part1(matrix, matrix_size, matrix_size));
    printf("\tPart 2: %d\n", day8_part2(matrix, matrix_size, matrix_size));

    for (size_t i = 0; i < matrix_size; ++i)
        free(matrix[i]);
    free(matrix);

    return 0;
}
