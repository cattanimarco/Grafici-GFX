#ifndef GRAFICI_UTILS_H
#define GRAFICI_UTILS_H

#ifndef swap
#define swap(x, y, T) \
	do                \
	{                 \
		T swap = x;   \
		x = y;        \
		y = swap;     \
	} while (0)
#endif

#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#endif