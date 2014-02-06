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

int equal(char c, char *pattern) {
	if (*(pattern-1) == '\\') {
		if (*pattern == c)
			return 1;
		else
			return 0;
	}
	switch(*pattern) {
		case '.':
			return 1;
		default:
			if (c == *pattern)
				return 1;
			else
				return 0;
	}
}

int match_bracket(char *line, char *pattern) {
	int m, n, count = 0;
	char *tmp = pattern;
	char *idx = strchr(pattern, ',');
	*idx = '\0';
	m = atoi(pattern+1);
	pattern = idx+1;
	idx = strchr(pattern, '}');
	*idx = '\0';
	n = atoi(pattern);
	while(equal(*line, tmp-1))
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
	char *end;
	for (;*line != '\0'; line++) {
		end = line;
	  for (;*pattern != '\0'; pattern++) {
	  	switch (*pattern) {
	  		case '.':
	  			end++;
	  			break;
	  		case '{':
	  			if (match_bracket(end, pattern))
	  				break;
	  			else
	  				continue;
	  			break;
	  		case '\\':
	  			pattern++;
	  			if (*end == *pattern)
	  				end++;
	  			else
	  				continue;
	  			break;
	  		default:
	  		 end++;
	  		 break;
	  	}
	  }
	}
  return 1;
}
