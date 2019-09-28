#ifndef min
#define min(a, b) (((a) < (b)) ? (a) : (b))
#endif

#ifndef max
#define max(a, b) (((a) > (b)) ? (a) : (b))
#endif

#define swap(x, y, T) \
	do                \
	{                 \
		T swap = x;   \
		x = y;        \
		y = swap;     \
	} while (0)