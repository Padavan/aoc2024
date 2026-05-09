#ifndef DAY_19_H__
#define DAY_19_H__

#include <stddef.h>
typedef struct {
	char chars[100];
	int size;
} Pattern;

typedef struct {
	Pattern items[1000];
	int size;
} List;

typedef struct {
	Pattern* keys;
	size_t* values;
	size_t size;
}  Cache;


void set_cache(Cache* cache, Pattern pattern, size_t value);
int get_cached_idx(Cache* cache, Pattern pattern);
void print_cache(Cache* cache);
size_t check_design(Pattern design, List* pattern_list,  Cache* cache);

int run_day19();

#endif /*  DAY_19_H__  */
