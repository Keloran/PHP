/* Generated by re2c 0.5 on Sat Nov 27 16:22:34 1999 */
#line 1 "../../../php4/ext/standard/url_scanner.re"
/*
   +----------------------------------------------------------------------+
   | PHP version 4.0                                                      |
   +----------------------------------------------------------------------+
   | Copyright (c) 1997, 1998, 1999, 2000 The PHP Group                   |
   +----------------------------------------------------------------------+
   | This source file is subject to version 2.02 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available at through the world-wide-web at                           |
   | http://www.php.net/license/2_02.txt.                                 |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
   | Author: Sascha Schumann <sascha@schumann.cx>                         |
   +----------------------------------------------------------------------+
 */
/* $Id$ */

#include "php.h"

#ifdef TRANS_SID

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#undef MIN
#define MIN(a,b) (a)<(b)?(a):(b)

#define YYCTYPE char
#define YYCURSOR state->crs
#define YYLIMIT state->end
#define YYMARKER state->ptr
#define YYFILL(n)

typedef enum {
	INITIAL,
	REF
} state;

typedef struct {
	state state;
	const char *crs;
	const char *end;
	const char *ptr;
	const char *start;
	char *target;
	size_t targetsize;
	const char *data;
} lexdata;

#define FINISH { catchup(state); goto finish; }

#define BEGIN(x) 						\
		switch(state->state) { 			\
			case INITIAL: 				\
				catchup(state); 		\
				break; 					\
			case REF: 					\
				screw_url(state); 		\
				break; 					\
		} 								\
		state->state = x; 				\
		state->start = state->crs; 		\
		goto nextiter

#define ATTACH(s, n) 										\
{ 															\
	size_t _newlen = state->targetsize + n; 				\
	state->target = realloc(state->target, _newlen + 1); 	\
	memcpy(state->target + state->targetsize, s, n); 		\
	state->targetsize = _newlen; 							\
	state->target[_newlen] = '\0'; 							\
}
	
#define URLLEN 512
	
static void screw_url(lexdata *state)
{
	int len;
	char buf[URLLEN];
	char url[URLLEN];
	const char *p, *q;
	char c;

	/* search outer limits for URI */
	for(p = state->start; p < state->crs && (c = *p); p++)
		if(c != '"' && c != ' ') break;

	/*  
	 *  we look at q-1, because q points to the character behind the last
	 *  character we are going to copy and the decision is based on that last
	 *  character 
	 */

	for(q = state->crs; q > state->start && (c = *(q-1)); q--)
		if(c != '"' && c != ' ') break;

	/* attach beginning */
	
	ATTACH(state->start, p-state->start);
	
	/* copy old URI */
	len = MIN(q - p, sizeof(buf) - 1);
	memcpy(url, p, len);
	url[len] = '\0';
	
	/* construct new URI */
	len = snprintf(buf, sizeof(buf), "%s%c%s", url,
			memchr(state->start, '?', len) ? '&' : '?',
			state->data);

	/* attach new URI */
	ATTACH(buf, len);
	
	/* attach rest */
	ATTACH(q, state->crs - q);
}

static void catchup(lexdata *state) 
{
	ATTACH(state->start, (state->crs - state->start));
}

#line 144


static void url_scanner(lexdata *state)
{
	while(state->crs < state->end) {
	
	switch(state->state) {
		case INITIAL: 
{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy0;
yy1:	++YYCURSOR;
yy0:
	if((YYLIMIT - YYCURSOR) < 7) YYFILL(7);
	yych = *YYCURSOR;
	switch(yych){
	case '\000':	goto yy7;
	case '<':	goto yy2;
	default:	goto yy4;
	}
yy2:	yych = *++YYCURSOR;
	switch(yych){
	case 'A':	case 'a':	goto yy9;
	case 'F':	case 'f':	goto yy10;
	default:	goto yy3;
	}
yy3:yy4:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy5:	switch(yych){
	case '\000':	case '<':	goto yy6;
	default:	goto yy4;
	}
yy6:
#line 157
	{ BEGIN(INITIAL); }
yy7:	yych = *++YYCURSOR;
yy8:
#line 158
	{ FINISH; }
yy9:	yych = *++YYCURSOR;
	switch(yych){
	case 'H':	case 'h':	goto yy3;
	case 'R':	case 'r':	goto yy41;
	default:	goto yy40;
	}
yy10:	yych = *++YYCURSOR;
	switch(yych){
	case 'O':	case 'o':	goto yy12;
	case 'R':	case 'r':	goto yy11;
	default:	goto yy3;
	}
yy11:	yych = *++YYCURSOR;
	switch(yych){
	case 'A':	case 'a':	goto yy27;
	default:	goto yy3;
	}
yy12:	yych = *++YYCURSOR;
	switch(yych){
	case 'R':	case 'r':	goto yy13;
	default:	goto yy3;
	}
yy13:	yych = *++YYCURSOR;
	switch(yych){
	case 'M':	case 'm':	goto yy14;
	default:	goto yy3;
	}
yy14:	yych = *++YYCURSOR;
	switch(yych){
	case 'A':	case 'a':	goto yy3;
	default:	goto yy16;
	}
yy15:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy16:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy15;
	case 'A':	case 'a':	goto yy17;
	default:	goto yy3;
	}
yy17:	yych = *++YYCURSOR;
	switch(yych){
	case 'C':	case 'c':	goto yy18;
	default:	goto yy3;
	}
yy18:	yych = *++YYCURSOR;
	switch(yych){
	case 'T':	case 't':	goto yy19;
	default:	goto yy3;
	}
yy19:	yych = *++YYCURSOR;
	switch(yych){
	case 'I':	case 'i':	goto yy20;
	default:	goto yy3;
	}
yy20:	yych = *++YYCURSOR;
	switch(yych){
	case 'O':	case 'o':	goto yy21;
	default:	goto yy3;
	}
yy21:	yych = *++YYCURSOR;
	switch(yych){
	case 'N':	case 'n':	goto yy22;
	default:	goto yy3;
	}
yy22:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy23:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy22;
	case '=':	goto yy24;
	default:	goto yy3;
	}
yy24:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy25:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy24;
	default:	goto yy26;
	}
yy26:
#line 155
	{ BEGIN(REF); }
yy27:	yych = *++YYCURSOR;
	switch(yych){
	case 'M':	case 'm':	goto yy28;
	default:	goto yy3;
	}
yy28:	yych = *++YYCURSOR;
	switch(yych){
	case 'E':	case 'e':	goto yy29;
	default:	goto yy3;
	}
yy29:	yych = *++YYCURSOR;
	switch(yych){
	case 'S':	case 's':	goto yy3;
	default:	goto yy31;
	}
yy30:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy31:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy30;
	case 'S':	case 's':	goto yy32;
	default:	goto yy3;
	}
yy32:	yych = *++YYCURSOR;
	switch(yych){
	case 'R':	case 'r':	goto yy33;
	default:	goto yy3;
	}
yy33:	yych = *++YYCURSOR;
	switch(yych){
	case 'C':	case 'c':	goto yy34;
	default:	goto yy3;
	}
yy34:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy35:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy34;
	case '=':	goto yy36;
	default:	goto yy3;
	}
yy36:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy37:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy36;
	default:	goto yy38;
	}
yy38:
#line 153
	{ BEGIN(REF); }
yy39:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy40:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy39;
	case 'H':	case 'h':	goto yy54;
	default:	goto yy3;
	}
yy41:	yych = *++YYCURSOR;
	switch(yych){
	case 'E':	case 'e':	goto yy42;
	default:	goto yy3;
	}
yy42:	yych = *++YYCURSOR;
	switch(yych){
	case 'A':	case 'a':	goto yy43;
	default:	goto yy3;
	}
yy43:	yych = *++YYCURSOR;
	switch(yych){
	case 'H':	case 'h':	goto yy3;
	default:	goto yy45;
	}
yy44:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy45:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy44;
	case 'H':	case 'h':	goto yy46;
	default:	goto yy3;
	}
yy46:	yych = *++YYCURSOR;
	switch(yych){
	case 'R':	case 'r':	goto yy47;
	default:	goto yy3;
	}
yy47:	yych = *++YYCURSOR;
	switch(yych){
	case 'E':	case 'e':	goto yy48;
	default:	goto yy3;
	}
yy48:	yych = *++YYCURSOR;
	switch(yych){
	case 'F':	case 'f':	goto yy49;
	default:	goto yy3;
	}
yy49:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy50:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy49;
	case '=':	goto yy51;
	default:	goto yy3;
	}
yy51:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy52:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy51;
	default:	goto yy53;
	}
yy53:
#line 156
	{ BEGIN(REF); }
yy54:	yych = *++YYCURSOR;
	switch(yych){
	case 'R':	case 'r':	goto yy55;
	default:	goto yy3;
	}
yy55:	yych = *++YYCURSOR;
	switch(yych){
	case 'E':	case 'e':	goto yy56;
	default:	goto yy3;
	}
yy56:	yych = *++YYCURSOR;
	switch(yych){
	case 'F':	case 'f':	goto yy57;
	default:	goto yy3;
	}
yy57:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy58:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy57;
	case '=':	goto yy59;
	default:	goto yy3;
	}
yy59:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy60:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy59;
	default:	goto yy61;
	}
yy61:
#line 154
	{ BEGIN(REF); }
}
#line 159

			break;
		case REF: 
{
	YYCTYPE yych;
	unsigned int yyaccept;
	goto yy62;
yy63:	++YYCURSOR;
yy62:
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
	switch(yych){
	case '\000':	case '>':	goto yy64;
	case '\t':	case '\v':
	case '\f':	case ' ':	case '"':	goto yy65;
	case '#':	goto yy69;
	case ':':	goto yy71;
	default:	goto yy67;
	}
yy64:
#line 163
	{ BEGIN(INITIAL); }
yy65:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy66:	switch(yych){
	case '\000':	case '>':	goto yy64;
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy65;
	case '"':	goto yy79;
	case '#':	goto yy69;
	case ':':	goto yy71;
	default:	goto yy67;
	}
yy67:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy68:	switch(yych){
	case '\000':	case '>':	goto yy64;
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy77;
	case '"':	goto yy79;
	case '#':	goto yy69;
	case ':':	goto yy71;
	default:	goto yy67;
	}
yy69:	yych = *++YYCURSOR;
yy70:	YYCURSOR -= 1;
#line 164
	{ BEGIN(INITIAL); }
yy71:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy72:	switch(yych){
	case '\000':	case '#':	case '>':	goto yy73;
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy74;
	case '"':	goto yy76;
	default:	goto yy71;
	}
yy73:
#line 165
	{ 
			/* don't modify absolute links */
			state->state = INITIAL; BEGIN(INITIAL); 
	}
yy74:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy75:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy74;
	case '"':	goto yy76;
	default:	goto yy73;
	}
yy76:	yych = *++YYCURSOR;
	goto yy73;
yy77:	++YYCURSOR;
	if(YYLIMIT == YYCURSOR) YYFILL(1);
	yych = *YYCURSOR;
yy78:	switch(yych){
	case '\t':	case '\v':
	case '\f':	case ' ':	goto yy77;
	case '"':	goto yy79;
	default:	goto yy64;
	}
yy79:	yych = *++YYCURSOR;
	goto yy64;
}
#line 169

  			break;
	}
nextiter:
	;
	}
finish:
	;
}

char *url_adapt(const char *src, size_t srclen, const char *data, size_t *newlen)
{
	lexdata state;

	state.state = INITIAL;
	state.start = state.crs = src;
	state.end = src + srclen;
	state.ptr = NULL;
	state.target = NULL;
	state.targetsize = 0;
	state.data = data;

	url_scanner(&state);

	if(newlen) *newlen = state.targetsize;

	return state.target;
}

#endif
