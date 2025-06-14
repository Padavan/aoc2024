#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

#include "../include/utils.h"
#include "../include/day19.h"

#define min(a,b)             \
({                           \
    __typeof__ (a) _a = (a); \
    __typeof__ (b) _b = (b); \
    _a < _b ? _a : _b;       \
})


int check_position(Pattern design, List pattern_list, int position, int skip_pattern, List* components) {
	if (design.lenght <= position) {
		return 1;
	}

	int found_patterns = 0;
	for (int i = 0; i < pattern_list.lenght; i++) {
		if (i == skip_pattern) {
			continue;
		}

		bool pattern_match = true;
		Pattern current_pattern = pattern_list.items[i];

		for (int j = 0; j < current_pattern.lenght; j++) {
			if (design.chars[position + j] != current_pattern.chars[j]) {
				pattern_match = false;
			}
		}

		if (pattern_match) {
			found_patterns = found_patterns + check_position(design, pattern_list, position + current_pattern.lenght, skip_pattern, components);
			if (found_patterns > 0) {
				components->items[components->lenght] = current_pattern;
				components->lenght++;
				return found_patterns;
			}
		}

	}

	return found_patterns;
}


List reverse_components(List* component) {
	List reversed = {{}, 0};

	for (int i = 0; i < component->lenght; i++) {
		reversed.items[reversed.lenght] = component->items[component->lenght - 1 - i];
		reversed.lenght++;
	}

	return reversed;
}

/////////////////// PART 2 ////////////////////////////
bool is_pattern_eq(Pattern a, Pattern b) {
	if (a.lenght != b.lenght) {
		return false;
	}

	for (int i = 0; i < a.lenght; i++) {
		if (a.chars[i] != b.chars[i]) {
			return false;
		}
	}

	return true;
}

Pattern combine_patterns(Pattern a, Pattern b) {
	Pattern result_pattern = {{}, 0};
	for (int i = 0; i < a.lenght; i++) {
		result_pattern.chars[result_pattern.lenght] = a.chars[i];
		result_pattern.lenght++;
	}

	for (int i = 0; i < b.lenght; i++) {
		result_pattern.chars[result_pattern.lenght] = b.chars[i];
		result_pattern.lenght++;
	}

	return result_pattern;
}

bool combined_pattern_exist(Pattern a, List* pattern_list) {
	for (int i = 0; i < pattern_list->lenght; i++) {
		if (is_pattern_eq(pattern_list->items[i], a)) {
			return true;
		}
	}

	return false;
}

// int count_recombination(List components, List* pattern_list, int index, int* counter) {
// 	// printf("index: %d/%d, counter: %d\n", index, components.lenght, *counter);

// 	if (components.lenght == index) {
// 		// printf("!!!ololo!!!");
// 		*counter = *counter + 1;
// 		return 0;
// 	}

// 	if (index > components.lenght) {
// 		printf("ERROR\n");
// 		return 0;
// 	}

// 	Pattern combined = components.items[index];
// 	int merge_count = 0;
// 	while (combined_pattern_exist(combined, pattern_list) && merge_count < (components.lenght - index)) {
// 		count_recombination(components, pattern_list, index + merge_count + 1, counter);

// 		merge_count++;
// 		combined = combine_patterns(combined, components.items[index + merge_count]);
// 	}

// 	// for (int comp_count = 0; comp_count < min(6, components.lenght - index); comp_count++) {
// 	// 	// printf("\tindex: %d | comp_count: %d \n", index, comp_count);
// 	// 	if (comp_count != 0) {
// 	// 		combined = combine_patterns(combined, components.items[index + comp_count]);
// 	// 	}

// 	// 	// printf("\tcombined pattern: %s, %d\n", combined.chars, combined.lenght);
// 	// 	if (combined_pattern_exist(combined, pattern_list)) {
// 	// 		// printf("\t\t pattern exist\n");
// 	// 		count_recombination(components, pattern_list, index + comp_count + 1, counter);
// 	// 	} else {
// 	// 		break;
// 	// 	}

// 	// }

// 	return 0;
// }



void recursive_count(struct ComponentList* mapping, int position, int* counter) {
	// printf("\t pos: %d/%d \n", position, mapping->size);
	if (position == mapping->size) {
		*counter = *counter + 1;
		printf("counter: %d\r", *counter);
		fflush(stdout);
	}

	if (position > mapping->size) {
		printf("ERROR\n");
	}

	struct Component current_component = mapping->items[position];
	for (int i = 0; i < current_component.size; i++) {
		// printf("\t\t skip: %d \n", current_component.items[i]);
		recursive_count(mapping, position + current_component.items[i] + 1, counter);
	}
}

long long get_multiplier(struct ComponentList* mapping, int start,  int end) {
	long long total = 1;
	for (int i = 0; i < start; i++) {
		total = total*mapping->items[i].size;
	}
	for (int i = end ; i < mapping->size; i++) {
		total = total*(long long) mapping->items[i].size;
	}
	return total;
}

long long count_combos(struct ComponentList* mapping) {
	printf("--------------------\n");
	long long total = (long long) 1;

	for (int position = 0; position < mapping->size; position++) {
		struct Component current_component = mapping->items[position];
		printf("total: %lld\n", total);
		total = total*(long long) current_component.size;
	}


	long long overlapping = 0;
	long long multiplicator = total;
	for (int position = 0; position < mapping->size; position++)  {
		struct Component current_component = mapping->items[position]; 
		// printf("\t current_component: %d\n", position);
		multiplicator = multiplicator / (long long) current_component.size;
		// int multiplicator = total / current_component.size;
		// int reducer = 0;
		for (int i = 1; i < current_component.size; i++) {
			int combination = current_component.items[i];
			// printf("\t\tcombination: %d\n", combination);

			int index = position + 1;
			while(index <= combination + position) {
				int mult =  get_multiplier(mapping, position - 1, index + 1);
				long long current_overlapping = ((long long)mapping->items[index].size - 1)*mult;
				// printf("\t\t\tcurrent_overlapping: %lld, index: %d, multiplicator: %d\n", current_overlapping, index, multiplicator);
				overlapping = overlapping + current_overlapping;
				index++;
			}

		}
		printf("\tposition: %d, overlapping: %lld\n", position, overlapping);
	}

	// TODO count compensation

	printf("\ttotal: %lld, overlapping: %lld\n", total, overlapping);

	assert(total > overlapping);
	assert(total > 0);

	return total - overlapping;
}


long long prepare_count_recombination(List components, List* pattern_list) {
	// PREPARATION
	struct ComponentList mapping = {{},components.lenght}; 

	for (int position = 0; position < components.lenght; position++) {
		Pattern combined = {{}, 0};
		for (int merge_count = 0; merge_count < min(8, components.lenght - position); merge_count++) {
			combined = combine_patterns(combined, components.items[position + merge_count]);
			// printf("\t combined: %s\n", combined.chars);
			if (combined_pattern_exist(combined, pattern_list)) {
				mapping.items[position].items[mapping.items[position].size] = merge_count; 
				mapping.items[position].size++;
			}			
		}
	}


	for (int i = 0; i < components.lenght; i++) {
		printf("[");
		for (int j = 0; j < mapping.items[i].size; j++) {
			printf("%d ", mapping.items[i].items[j]);
		}
		printf("]");
		// printf("\n");
	}
	printf("\n");

	int recursive_counter = 0;
	recursive_count(&mapping, 0, &recursive_counter);
	printf("recursive_counter: %d\n", recursive_counter);

	long long combos = count_combos(&mapping);
	printf("new combos: %lld\n", combos);
	return combos;
	 
}

long long count_combinations(List design_list, List pattern_list) {
	// filter patterns
	List filtered_pattern_list = {{}, 0};
	for (int i = 0; i < pattern_list.lenght; i++) {
		List dum = {{}, 0};
		bool is_not_unique = check_design(pattern_list.items[i], pattern_list, i, &dum);
		if (!is_not_unique) {
			filtered_pattern_list.items[filtered_pattern_list.lenght] = pattern_list.items[i];
			filtered_pattern_list.lenght++;
		}
	}

	long long recombination_count = 0;
	for (int i=0; i < design_list.lenght; i++) {
		// printf("checking design: %s \n", design_list.items[i].chars);
		List components = {{}, 0};
		bool is_design_possible = check_design(design_list.items[i], filtered_pattern_list, -1, &components);
		List reversed_components = reverse_components(&components);
		if (is_design_possible) {
			// printf("components: ");
			// for (int c = 0; c < reversed_components.lenght; c++) {
			// 	printf(" %s ", reversed_components.items[c].chars);
			// }
			// printf("\n");
			
			long long count = prepare_count_recombination(reversed_components, &pattern_list);
			recombination_count = count + recombination_count;
		}
		// printf("recombination_count: %d\n", recombination_count);
	}

	return recombination_count;
}



///////////////// PART 1 ////////////////////////////////////


bool check_design(Pattern design, List pattern_list, int skip_pattern, List* components) {
	return check_position(design, pattern_list, 0, skip_pattern, components) > 0;
}

int check_valid_patterns(List design_list, List pattern_list) {
	// filter patterns
	List filtered_pattern_list = {{}, 0};
	for (int i = 0; i < pattern_list.lenght; i++) {
		List components = {{}, 0};
		bool is_not_unique = check_design(pattern_list.items[i], pattern_list, i, &components);
		if (!is_not_unique) {
			filtered_pattern_list.items[filtered_pattern_list.lenght] = pattern_list.items[i];
			filtered_pattern_list.lenght++;
		}
	}

	int valid_design_count = 0;
	for (int i=0; i < design_list.lenght; i++) {
		List components = {{}, 0};
		bool is_design_possible = check_design(design_list.items[i], filtered_pattern_list, -1, &components);
		if (is_design_possible) {
			valid_design_count++;
		}
	}

	return valid_design_count;
}

int run_day19()
{
	printf("Day 19: Linen Layout\n");
	char inputpath[] = "./input/day19.txt";

	char* line = NULL;
	size_t len = 0;
	ssize_t read;

	FILE* fp;
	fp = fopen(inputpath, "r");

	int line_count = 0;

	List pattern_list = {{}, 0};
	List designs_list = {{}, 0};

	while ((read = getline(&line, &len, fp)) != -1) {
		if (line_count == 0) {

			Pattern new_pattern = {{}, 0};
			for (size_t i = 0; i < read; i++) {
				if (line[i] == ',') {
					new_pattern.chars[new_pattern.lenght] = '\0';
					pattern_list.items[pattern_list.lenght] = new_pattern;
					pattern_list.lenght++;
					new_pattern.chars[0] = '\0';
					new_pattern.lenght = 0;
				} else if (line[i] == '\n') {
					new_pattern.chars[new_pattern.lenght] = '\0';
					pattern_list.items[pattern_list.lenght] = new_pattern;
					pattern_list.lenght++;
				} else if (line[i] == ' ') {
					continue;
				} else {
					new_pattern.chars[new_pattern.lenght] = line[i];
					new_pattern.lenght++;
				}
			}

		}

		if (line_count > 1) {
			Pattern str = {{}, 0 };
			for (int i = 0; i < read - 1; i++) {
				str.chars[i] = line[i];
				str.lenght = i + 1;
			}
			designs_list.items[designs_list.lenght] = str;
			designs_list.lenght++;
		}
		line_count++;
	}

	free(line);
	fclose(fp);

	// printf("\tPart 1: %d\n", check_valid_patterns(designs_list, pattern_list));
	//322
	printf("\tPart 2: %lld\n", count_combinations(designs_list, pattern_list));

	// 941152423 too low
	// 10435200 too low
	// 89988689

	// second pattern: 74214, total: 
	// second pattern: 83328, total: 
	// 5904654

	return 0;
}
