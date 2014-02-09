#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matcher.h"


int bracket_match(char last, char *tmp_line, char *tmp_pattern) {
	int m, n, i, j, no_problem;
	char *tmp;
	tmp = strchr(tmp_pattern, ',');
	*tmp = '\0';
	m = atoi(tmp_pattern + 1);
	*tmp = ',';
	tmp_pattern = tmp;
	tmp = strchr(tmp_pattern, '}');
	*tmp = '\0';
	n = atoi(tmp_pattern + 1);
	*tmp = '}';
	tmp_pattern = tmp + 1;
	for (i = m; i <= m + n; i++) {
		// try if c appears i times in line
		no_problem = 1;
		for (j = 0; j < i; j++)
			if (*(tmp_line + j) != last) {
				no_problem = 0;
				break;
			}
			if (no_problem)
				no_problem = rgrep_matches(tmp_line, tmp_pattern);
		if (no_problem) return 1;
	}
	return 0;
}

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */
int rgrep_matches(char *line, char *pattern) {
		char *tmp_line, *tmp_pattern, last;
		int no_problem;
		for (; *(line+1) != '\0'; line++) {
			// iterate to try different entries
			tmp_line = line;
			// if no problem found when pattern ends, return true
			no_problem = 1;
			tmp_pattern = pattern;
			while(*tmp_pattern != '\0') {
				//printf("next pattern: %c(%d)\n", *tmp_pattern, *tmp_pattern);
				if (*tmp_line == '\0') {
					no_problem = 0;
					break;
				}
				switch (*tmp_pattern) {
					case '.':
						last = *tmp_pattern;
						tmp_line++;
						break;
					case '{':
						no_problem = bracket_match(last, tmp_line, tmp_pattern);
						break;
					case '\\':
						tmp_pattern++;
						// do not break
					default:
						//printf("%c %c\n", *tmp_line, *tmp_pattern);
						if (*tmp_line != *tmp_pattern)
							no_problem = 0;
						last = *tmp_pattern;
						tmp_line++;
				}
				// if problem found, quit the loop
				if (!no_problem) break;
				tmp_pattern++;
			}
			// if no problem found, return true
			if (no_problem) {
				printf("Success!\n");
				return 1;
			}
		}
    return 0;
}
