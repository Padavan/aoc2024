#ifndef DAY_19_H__
#define DAY_19_H__

typedef struct {
	char chars[100];
	int lenght;
} Pattern;

// typedef struct {
	// char* chars;
	// int lenght;
// } String;

typedef struct {
	Pattern items[500];
	int lenght;
} List;

struct Component {
	int items[500];
	int size;
};

struct ComponentList {
	struct Component items[500];
	int size;
};

long long count_combos(struct ComponentList* mapping);

bool check_design(Pattern design, List pattern_list, int skip_pattern, List* components);

Pattern combine_patterns(Pattern a, Pattern b);

int run_day19();

#endif /*  DAY_19_H__  */
