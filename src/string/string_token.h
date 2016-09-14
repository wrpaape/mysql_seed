#ifndef MYSQL_SEED_STRING_STRING_TOKEN_H_
#define MYSQL_SEED_STRING_STRING_TOKEN_H_


/*			- token.h -
 * macros for printing multi-byte characters to char pointer 'PTR'
 */

#undef  PUT_CHAR
#define PUT_CHAR(PTR, BYTE)	\
do {				\
	*(PTR) = BYTE;		\
	++(PTR);		\
} while (0)

#undef  PUT_SPACE
#define PUT_SPACE(PTR) PUT_CHAR(PTR, ' ')


/* ANSI ESCAPE SEQUENCES
 ******************************************************************************/
#define _OPEN_ANSI(PTR)		\
do {				\
	PUT_CHAR(PTR, 27);	\
	PUT_CHAR(PTR, 91);	\
} while (0)

#define _CLOSE_ANSI(PTR) PUT_CHAR(PTR, 109)


#define _SML_ANSI(PTR, B2)	\
do {				\
	_OPEN_ANSI(PTR);	\
	PUT_CHAR(PTR, B2);	\
	_CLOSE_ANSI(PTR);	\
} while (0)


#define _BIG_ANSI(PTR, B2, B3)	\
do {				\
	_OPEN_ANSI(PTR);	\
	PUT_CHAR(PTR, B2);	\
	PUT_CHAR(PTR, B3);	\
	_CLOSE_ANSI(PTR);	\
} while (0)

#define _ANSI_OFF(PTR, B3)	_BIG_ANSI(PTR, 50, B3)
#define _ANSI_COLOR(PTR, B3)	_BIG_ANSI(PTR, 51, B3)
#define _ANSI_BG(PTR, B3)	_BIG_ANSI(PTR, 52, B3)

/* 4 bytes */
#define ANSI_FAINT			"\e[2m"
#define ANSI_UNDERLINE			"\e[4m"
#define ANSI_BRIGHT			"\e[1m"
#define ANSI_RESET			"\e[0m"
#define ANSI_CLEAR			"\e[2J"
#define ANSI_CLEAR_LINE			"\e[2K"
#define ANSI_BLINK			"\e[5m"
#define ANSI_INVERSE			"\e[7m"
#define ANSI_REVERSE			ANSI_INVERSE
#define ANSI_FAINT_NN_WIDTH		4
#define ANSI_UNDERLINE_NN_WIDTH		4
#define ANSI_BRIGHT_NN_WIDTH		4
#define ANSI_RESET_NN_WIDTH		4
#define ANSI_CLEAR_NN_WIDTH		4
#define ANSI_CLEAR_LINE_NN_WIDTH	4
#define ANSI_BLINK_NN_WIDTH		4
#define ANSI_INVERSE_NN_WIDTH		4
#define ANSI_REVERSE_NN_WIDTH		4
#define ANSI_FAINT_WIDTH		5
#define ANSI_UNDERLINE_WIDTH		5
#define ANSI_BRIGHT_WIDTH		5
#define ANSI_RESET_WIDTH		5
#define ANSI_CLEAR_WIDTH		5
#define ANSI_CLEAR_LINE_WIDTH		5
#define ANSI_BLINK_WIDTH		5
#define ANSI_INVERSE_WIDTH		5
#define ANSI_REVERSE_WIDTH		5

#define PUT_ANSI_RESET(PTR)	_SML_ANSI(PTR, 48)
#define PUT_ANSI_BRIGHT(PTR)	_SML_ANSI(PTR, 49)
#define PUT_ANSI_FAINT(PTR)	_SML_ANSI(PTR, 50)
#define PUT_ANSI_UNDERLINE(PTR) _SML_ANSI(PTR, 52)
#define PUT_ANSI_BLINK(PTR)	_SML_ANSI(PTR, 53)
#define PUT_ANSI_INVERSE(PTR)	_SML_ANSI(PTR, 55)
#define PUT_ANSI_REVERSE(PTR)	PUT_ANSI_REVERSE(PTR)

/* 5 bytes */
#define ANSI_NORMAL			"\e[22m"
#define ANSI_BLINK_OFF			"\e[25m"
#define ANSI_NO_UNDERLINE		"\e[24m"
#define ANSI_NORMAL_NN_WIDTH		5
#define ANSI_BLINK_OFF_NN_WIDTH		5
#define ANSI_NO_UNDERLINE_NN_WIDTH	5
#define ANSI_NORMAL_WIDTH		6
#define ANSI_BLINK_OFF_WIDTH		6
#define ANSI_NO_UNDERLINE_WIDTH		6

#define ANSI_BLACK_BG			"\e[40m"
#define ANSI_RED_BG			"\e[41m"
#define ANSI_GREEN_BG			"\e[42m"
#define ANSI_YELLOW_BG			"\e[43m"
#define ANSI_BLUE_BG			"\e[44m"
#define ANSI_MAGENTA_BG			"\e[45m"
#define ANSI_CYAN_BG			"\e[46m"
#define ANSI_WHITE_BG			"\e[47m"
#define ANSI_WHITE			"\e[37m"
#define ANSI_BLUE			"\e[34m"
#define ANSI_CYAN			"\e[36m"
#define ANSI_GREEN			"\e[32m"
#define ANSI_YELLOW			"\e[33m"
#define ANSI_RED			"\e[31m"
#define ANSI_MAGENTA			"\e[35m"
#define ANSI_BLACK			"\e[30m"
#define ANSI_BLACK_BG_NN_WIDTH		5
#define ANSI_RED_BG_NN_WIDTH		5
#define ANSI_GREEN_BG_NN_WIDTH		5
#define ANSI_YELLOW_BG_NN_WIDTH		5
#define ANSI_BLUE_BG_NN_WIDTH		5
#define ANSI_MAGENTA_BG_NN_WIDTH	5
#define ANSI_CYAN_BG_NN_WIDTH		5
#define ANSI_WHITE_BG_NN_WIDTH		5
#define ANSI_WHITE_NN_WIDTH		5
#define ANSI_BLUE_NN_WIDTH		5
#define ANSI_CYAN_NN_WIDTH		5
#define ANSI_GREEN_NN_WIDTH		5
#define ANSI_YELLOW_NN_WIDTH		5
#define ANSI_RED_NN_WIDTH		5
#define ANSI_MAGENTA_NN_WIDTH		5
#define ANSI_BLACK_NN_WIDTH		5
#define ANSI_BLACK_BG_WIDTH		6
#define ANSI_RED_BG_WIDTH		6
#define ANSI_GREEN_BG_WIDTH		6
#define ANSI_YELLOW_BG_WIDTH		6
#define ANSI_BLUE_BG_WIDTH		6
#define ANSI_MAGENTA_BG_WIDTH		6
#define ANSI_CYAN_BG_WIDTH		6
#define ANSI_WHITE_BG_WIDTH		6
#define ANSI_WHITE_WIDTH		6
#define ANSI_BLUE_WIDTH			6
#define ANSI_CYAN_WIDTH			6
#define ANSI_GREEN_WIDTH		6
#define ANSI_YELLOW_WIDTH		6
#define ANSI_RED_WIDTH			6
#define ANSI_MAGENTA_WIDTH		6
#define ANSI_BLACK_WIDTH		6

#define PUT_ANSI_NORMAL(PTR)		_ANSI_OFF(PTR, 50)
#define PUT_ANSI_NO_UNDERLINE(PTR)	_ANSI_OFF(PTR, 52)
#define PUT_ANSI_BLINK_OFF(PTR)		_ANSI_OFF(PTR, 53)
#define PUT_ANSI_CLEAR(PTR)		_ANSI_OFF(PTR, 74)

#define PUT_ANSI_BLACK(PTR)		_ANSI_COLOR(PTR, 48)
#define PUT_ANSI_RED(PTR)		_ANSI_COLOR(PTR, 49)
#define PUT_ANSI_GREEN(PTR)		_ANSI_COLOR(PTR, 50)
#define PUT_ANSI_YELLOW(PTR)		_ANSI_COLOR(PTR, 51)
#define PUT_ANSI_BLUE(PTR)		_ANSI_COLOR(PTR, 52)
#define PUT_ANSI_MAGENTA(PTR)		_ANSI_COLOR(PTR, 53)
#define PUT_ANSI_CYAN(PTR)		_ANSI_COLOR(PTR, 54)
#define PUT_ANSI_WHITE(PTR)		_ANSI_COLOR(PTR, 55)

#define PUT_ANSI_BLACK_BG(PTR)		_ANSI_BG(PTR, 48)
#define PUT_ANSI_RED_BG(PTR)		_ANSI_BG(PTR, 49)
#define PUT_ANSI_GREEN_BG(PTR)		_ANSI_BG(PTR, 50)
#define PUT_ANSI_YELLOW_BG(PTR)		_ANSI_BG(PTR, 51)
#define PUT_ANSI_BLUE_BG(PTR)		_ANSI_BG(PTR, 52)
#define PUT_ANSI_MAGENTA_BG(PTR)	_ANSI_BG(PTR, 53)
#define PUT_ANSI_CYAN_BG(PTR)		_ANSI_BG(PTR, 54)
#define PUT_ANSI_WHITE_BG(PTR)		_ANSI_BG(PTR, 55)



/* BOX DRAWING CHARACTERS
 ******************************************************************************/
#define BOX_CHAR_SIZE 3lu

#define _OPEN_BOX_CHAR(PTR) PUT_CHAR(PTR, 226)

#define _SGL_BOX_CHAR(PTR, BYTE)	\
do {					\
	_OPEN_BOX_CHAR(PTR);		\
	PUT_CHAR(PTR, 148);		\
	PUT_CHAR(PTR, BYTE);		\
} while (0)

#define _DBL_BOX_CHAR(PTR, BYTE)	\
do {					\
	_OPEN_BOX_CHAR(PTR);		\
	PUT_CHAR(PTR, 149);		\
	PUT_CHAR(PTR, BYTE);		\
} while (0)

/* light */
#define PUT_BOX_CHAR_LIGHT_NW_CORNER(PTR) _SGL_BOX_CHAR(PTR, 140) /* ┌ */
#define PUT_BOX_CHAR_LIGHT_NE_CORNER(PTR) _SGL_BOX_CHAR(PTR, 144) /* ┐ */
#define PUT_BOX_CHAR_LIGHT_SW_CORNER(PTR) _SGL_BOX_CHAR(PTR, 148) /* └ */
#define PUT_BOX_CHAR_LIGHT_SE_CORNER(PTR) _SGL_BOX_CHAR(PTR, 152) /* ┘ */
#define PUT_BOX_CHAR_LIGHT_N_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 172) /* ┬ */
#define PUT_BOX_CHAR_LIGHT_S_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 180) /* ┴ */
#define PUT_BOX_CHAR_LIGHT_W_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 156) /* ├ */
#define PUT_BOX_CHAR_LIGHT_E_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 164) /* ┤ */
#define PUT_BOX_CHAR_LIGHT_H_LINE(PTR)	  _SGL_BOX_CHAR(PTR, 128) /* ─ */
#define PUT_BOX_CHAR_LIGHT_V_LINE(PTR)	  _SGL_BOX_CHAR(PTR, 130) /* │ */
#define PUT_BOX_CHAR_LIGHT_CROSS(PTR)	  _SGL_BOX_CHAR(PTR, 188) /* ┼ */

/* heavy */
#define PUT_BOX_CHAR_HEAVY_NW_CORNER(PTR) _SGL_BOX_CHAR(PTR, 143) /* ┏ */
#define PUT_BOX_CHAR_HEAVY_NE_CORNER(PTR) _SGL_BOX_CHAR(PTR, 147) /* ┓ */
#define PUT_BOX_CHAR_HEAVY_SW_CORNER(PTR) _SGL_BOX_CHAR(PTR, 151) /* ┗ */
#define PUT_BOX_CHAR_HEAVY_SE_CORNER(PTR) _SGL_BOX_CHAR(PTR, 155) /* ┛ */
#define PUT_BOX_CHAR_HEAVY_N_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 179) /* ┳ */
#define PUT_BOX_CHAR_HEAVY_S_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 187) /* ┻ */
#define PUT_BOX_CHAR_HEAVY_W_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 163) /* ┣ */
#define PUT_BOX_CHAR_HEAVY_E_JOIN(PTR)	  _SGL_BOX_CHAR(PTR, 171) /* ┫ */
#define PUT_BOX_CHAR_HEAVY_H_LINE(PTR)	  _SGL_BOX_CHAR(PTR, 129) /* ━ */
#define PUT_BOX_CHAR_HEAVY_V_LINE(PTR)	  _SGL_BOX_CHAR(PTR, 131) /* ┃ */
#define PUT_BOX_CHAR_HEAVY_CROSS(PTR)	  _SGL_BOX_CHAR(PTR, 139) /* ╋ */

/* double */
#define PUT_BOX_CHAR_DOUBLE_NW_CORNER(PTR) _DBL_BOX_CHAR(PTR, 148) /* ╔ */
#define PUT_BOX_CHAR_DOUBLE_NE_CORNER(PTR) _DBL_BOX_CHAR(PTR, 151) /* ╗ */
#define PUT_BOX_CHAR_DOUBLE_SW_CORNER(PTR) _DBL_BOX_CHAR(PTR, 154) /* ╚ */
#define PUT_BOX_CHAR_DOUBLE_SE_CORNER(PTR) _DBL_BOX_CHAR(PTR, 157) /* ╝ */
#define PUT_BOX_CHAR_DOUBLE_N_JOIN(PTR)	   _DBL_BOX_CHAR(PTR, 166) /* ╦ */
#define PUT_BOX_CHAR_DOUBLE_S_JOIN(PTR)	   _DBL_BOX_CHAR(PTR, 169) /* ╩ */
#define PUT_BOX_CHAR_DOUBLE_W_JOIN(PTR)	   _DBL_BOX_CHAR(PTR, 160) /* ╠ */
#define PUT_BOX_CHAR_DOUBLE_E_JOIN(PTR)	   _DBL_BOX_CHAR(PTR, 163) /* ╣ */
#define PUT_BOX_CHAR_DOUBLE_H_LINE(PTR)	   _DBL_BOX_CHAR(PTR, 144) /* ═ */
#define PUT_BOX_CHAR_DOUBLE_V_LINE(PTR)	   _DBL_BOX_CHAR(PTR, 145) /* ║ */
#define PUT_BOX_CHAR_DOUBLE_CROSS(PTR)	   _DBL_BOX_CHAR(PTR, 172) /* ╬ */




/* BLOCK ELEMENTS
 ******************************************************************************/
#define BLOCK_CHAR_SIZE 3lu

#define FILL_BLOCK_CHAR(PTR, BYTE)	\
do {					\
	PUT_CHAR(PTR, 226);		\
	PUT_CHAR(PTR, 150);		\
	PUT_CHAR(PTR, BYTE);		\
} while (0)

/* filled from bottom:
 * ▁ ▂ ▃ ▄ ▅ ▆ ▇ █
 * 1 2 3 4 5 6 7 8 */
#define PUT_BLOCK_CHAR_BASE_FILL(PTR, FILL) FILL_BLOCK_CHAR(PTR, 128 + (FILL))

/* filled from left:
 * ▏ ▎ ▍ ▌ ▋ ▊ ▉ █
 * 1 2 3 4 5 6 7 8 */
#define PUT_BLOCK_CHAR_LEFT_FILL(PTR, FILL) FILL_BLOCK_CHAR(PTR, 128 + (FILL))



/* GEOMETRIC SHAPES
 ******************************************************************************/
#define _GEO_CIRC(PTR, BYTE)	\
do {				\
	PUT_CHAR(PTR, 226);	\
	PUT_CHAR(PTR, 151);	\
	PUT_CHAR(PTR, BYTE);	\
} while (0)

/* ◉ */
#define PUT_FISHEYE(PTR)	_GEO_CIRC(PTR, 137)

/* ◯ */
#define PUT_LARGE_CIRCLE(PTR)	_GEO_CIRC(PTR, 175)

#endif /* ifndef MYSQL_SEED_STRING_STRING_TOKEN_H_ */
