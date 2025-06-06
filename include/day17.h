 
#ifndef DAY_17_H__
#define DAY_17_H__

struct Register {
	long long int A;
	long long int B;
	long long int C;
};

struct OutputArray {
	long long int arr[50];
	int size;
};

struct OutputArray run_program(struct Register initialState, struct OutputArray program);

struct Register run_opcode(long long int opcode, long long int operand, struct Register state, int *cursor, struct OutputArray* output);

int run_day17();

#endif /*  DAY_17_H__  */
