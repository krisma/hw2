#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "matcher.h"

int try_entry(char *tmp_line, char *tmp_pattern);
int bracket_match(char *tmp_line, char *tmp_pattern);

int try_entry(char *tmp_line, char *tmp_pattern) {
	int no_problem = 1;
	// if no problem found when pattern ends, return true
	while(*tmp_pattern != '\0') {
		//printf("next pattern: %c(%d)\n", *tmp_pattern, *tmp_pattern);
		if (*tmp_line == '\0') return 0;
		switch (*tmp_pattern) {
			case '.':
				if (*(tmp_pattern + 1) == '{')
					break;
				tmp_line++;
				break;
			case '{':
				if (bracket_match(tmp_line, tmp_pattern)) return 1;
				break;
			case '\\':
				tmp_pattern++;
				// do not break
			default:
				if (*(tmp_pattern + 1) == '{')
					break;
				if (*tmp_line != *tmp_pattern)
					no_problem = 0;
				tmp_line++;
		}
		// if problem found, quit the loop
		if (!no_problem) return 0;
		tmp_pattern++;
	}
	return 1;
}

int bracket_match(char *tmp_line, char *tmp_pattern) {
	int m, n, i, j, no_problem, period_flag;
	char *tmp, *tmp2, pre, *next;
	// m
	tmp = strchr(tmp_pattern, ',');
	*tmp = '\0';
	m = atoi(tmp_pattern + 1);
	*tmp = ',';
	// n
	if (*(tmp + 1) == '}') {
		// minus one because of '\n'
		n = strlen(tmp_line) - m - 1;
	} else {
		tmp2 = strchr(tmp, '}');
		*tmp2 = '\0';
		n = atoi(tmp + 1);
		*tmp2 = '}';
	}
	// pre
	period_flag = 0;
	if (*(tmp_pattern - 2) == '\\')
		pre = *(tmp_pattern - 1);
	else {
		if (*(tmp_pattern - 1) == '.')
			period_flag = 1;
		pre = *(tmp_pattern - 1);
	}
	//printf("Ready to do bracket match: char: %c; m: %d; n : %d\nline is %s", pre, m, n, tmp_line);
	for (i = m; i <= m + n; i++) {
		// try if c appears i times in line
		no_problem = 1;
		if (!period_flag)
			// if pre is not a '.', do the check
			for (j = 0; j < i; j++) {
				if (*(tmp_line + j) != pre) {
					no_problem = 0;
					break;
				}
			}
		if (no_problem) {
			next = strchr(tmp_pattern, '}') + 1;
			no_problem = try_entry(tmp_line + i, next);
		}
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
	char *tmp_line, *tmp_pattern;
	if (*pattern == '\0') return 1;
	//printf("Ready to match:%swith pattern: %s\n", line, pattern);
	while (*line != '\0') {
		// iterate to try different entries
		tmp_line = line;
		tmp_pattern = pattern;
		// if no problem found, return true
		if (try_entry(tmp_line, tmp_pattern)) return 1;
		line++;
	}
  return 0;
}
