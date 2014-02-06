#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "matcher.h"

/**
 * Implementation of your matcher function, which
 * will be called by the main program.
 *
 * You may assume that both line and pattern point
 * to reasonably short, null-terminated strings.
 */

int match_bracket(char *line, char *pattern) {
	int m, n, count = 0;
	char c = *(pattern-1);
	char *idx = strchr(pattern, ',');
	*idx = '\0';
	m = atoi(pattern+1);
	pattern = idx+1;
	idx = strchr(pattern, '}');
	*idx = '\0';
	n = atoi(pattern);
	while(*line == c)
		count++;
	// only m available
	if (count >= m && n == 0)
		return 1;
	// both m and n available
	if (count >= m && count <= n)
		return 1;
	return 0;
}

int rgrep_matches(char *line, char *pattern) {
  for (;*pattern != '\0'; pattern++) {
  	switch (*pattern) {
  		case '.':
  			line++;
  			break;
  		case '{':
  			if (match_bracket(line, pattern))
  				break;
  			else
  				return 0;
  			break;
  	}
  }
  return 1;
}
