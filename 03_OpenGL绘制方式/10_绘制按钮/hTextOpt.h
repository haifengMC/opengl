#pragma once

#include "vmacro.h"

#define TEXTOPT_DELC_F(n, nm) const char* nm = NULL
#define TEXTOPT_DELC_V_F(n, nm) int COMB(nm, V) = NULL
#define TEXTOPT_CASE_F(n, nm)  case 'nm': nm=p;break
#define TEXTOPT_CASE_F(n, nm)  case 'nm': nm=p;break

//ÎÄ±¾²Ù×÷·û
#define TEXTOPT(cls, opt, ...) \
	constexpr cls operator""opt(const char* col, size_t n)\
	{\
	const char* end = col + n;\
	REPEAT_SEP(TEXTOPT_DELC_F, SEM_M, ##__VA_ARGS__);\
	REPEAT_SEP(TEXTOPT_DELC_V_F, SEM_M, ##__VA_ARGS__);
	for (const char* p = col; p != end; ++p)\
	{\
		switch (*p){REPEAT_SEP(TEXTOPT_DELC_V_F, SEM_M, ##__VA_ARGS__);)\
	}
	

/*
	{
		{
		case 'x': x = p; break;
		case 'y': y = p; break;
		case 'w': w = p; break;
		case 'h': h = p; break;
		default: break;
		}
	}

	if (x) xV = atoi(x + 1);
	if (y) yV = atoi(y + 1);
	if (w) wV = atoi(w + 1);
	if (h) hV = atoi(h + 1);
	return hRect(xV, yV, wV, hV);
	}
*/