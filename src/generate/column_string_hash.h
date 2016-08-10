#ifndef MYSQL_SEED_COLUMN_STRING_HASH_H_
#define MYSQL_SEED_COLUMN_STRING_HASH_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "bitwise/bitwise_utils.h"	/* for shuffling hash state */
#include "generate/generator.h"		/* string/thread utils */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
union HashStateBufferPointer {
	word_t *restrict word;
	uint8_t *restrict octet;
};

/* macro constants
 * ────────────────────────────────────────────────────────────────────────── */
#define HASH_LENGTH_MAX	       255lu	/* arbitrary upper limit on length */
#define HASH_LENGTH_MAX_STRING "255"

struct HashState {
	word_t *restrict words;
	uint8_t *restrict octets;
	uint8_t *restrict upto;
	unsigned int rotate;
};

inline void
hash_state_init(struct HashState *const restrict state,
		void *const restrict buffer,
		const void *const restrict until)
{
	union HashStateBufferPointer buffer_ptr;

	buffer_ptr.word = (word_t *restrict) buffer;

	state->words  = buffer_ptr.word;
	state->octets = buffer_ptr.octet + (OCTET_WORD - 1l);
	state->upto   = ((uint8_t *restrict) until) - OCTET_WORD;
	state->rotate = (uintptr_t) until;

	*(buffer_ptr.word) = (uintptr_t) buffer_ptr.word;
	++(buffer_ptr.octet);

	while (buffer_ptr.octet <= state->upto) {
		*(buffer_ptr.word) ^= (uintptr_t) buffer_ptr.word;
		++(buffer_ptr.octet);
	}
}


inline void
hash_state_shuffle(struct HashState *const restrict state)
{
	union HashStateBufferPointer buffer_ptr;

	buffer_ptr.word = state->words;

	do {
		++(state->rotate);

		*(buffer_ptr.word) = word_rotate_right(*(buffer_ptr.word),
						       state->rotate);

		++(buffer_ptr.octet);
	} while (buffer_ptr.octet <= state->upto);
}


inline void
set_last_hash_nibble(char *const restrict buffer,
		     const unsigned int last)
{
	switch (last & 0xf) {
	case 0x0: SET_STRING_WIDTH(buffer, "0", 2); return;
	case 0x1: SET_STRING_WIDTH(buffer, "1", 2); return;
	case 0x2: SET_STRING_WIDTH(buffer, "2", 2); return;
	case 0x3: SET_STRING_WIDTH(buffer, "3", 2); return;
	case 0x4: SET_STRING_WIDTH(buffer, "4", 2); return;
	case 0x5: SET_STRING_WIDTH(buffer, "5", 2); return;
	case 0x6: SET_STRING_WIDTH(buffer, "6", 2); return;
	case 0x7: SET_STRING_WIDTH(buffer, "7", 2); return;
	case 0x8: SET_STRING_WIDTH(buffer, "8", 2); return;
	case 0x9: SET_STRING_WIDTH(buffer, "9", 2); return;
	case 0xa: SET_STRING_WIDTH(buffer, "a", 2); return;
	case 0xb: SET_STRING_WIDTH(buffer, "b", 2); return;
	case 0xc: SET_STRING_WIDTH(buffer, "c", 2); return;
	case 0xd: SET_STRING_WIDTH(buffer, "d", 2); return;
	case 0xe: SET_STRING_WIDTH(buffer, "e", 2); return;
	default:  SET_STRING_WIDTH(buffer, "f", 2);
	}
}

inline char *
put_last_hash_nibble(char *const restrict buffer,
		     const unsigned int last)
{
	switch (last & 0xf) {
	case 0x0: SET_STRING_WIDTH(buffer, "0", 2); return buffer + 2l;
	case 0x1: SET_STRING_WIDTH(buffer, "1", 2); return buffer + 2l;
	case 0x2: SET_STRING_WIDTH(buffer, "2", 2); return buffer + 2l;
	case 0x3: SET_STRING_WIDTH(buffer, "3", 2); return buffer + 2l;
	case 0x4: SET_STRING_WIDTH(buffer, "4", 2); return buffer + 2l;
	case 0x5: SET_STRING_WIDTH(buffer, "5", 2); return buffer + 2l;
	case 0x6: SET_STRING_WIDTH(buffer, "6", 2); return buffer + 2l;
	case 0x7: SET_STRING_WIDTH(buffer, "7", 2); return buffer + 2l;
	case 0x8: SET_STRING_WIDTH(buffer, "8", 2); return buffer + 2l;
	case 0x9: SET_STRING_WIDTH(buffer, "9", 2); return buffer + 2l;
	case 0xa: SET_STRING_WIDTH(buffer, "a", 2); return buffer + 2l;
	case 0xb: SET_STRING_WIDTH(buffer, "b", 2); return buffer + 2l;
	case 0xc: SET_STRING_WIDTH(buffer, "c", 2); return buffer + 2l;
	case 0xd: SET_STRING_WIDTH(buffer, "d", 2); return buffer + 2l;
	case 0xe: SET_STRING_WIDTH(buffer, "e", 2); return buffer + 2l;
	default:  SET_STRING_WIDTH(buffer, "f", 2); return buffer + 2l;
	}
}

inline char *
put_hash_state_odd(char *restrict ptr,
		   struct HashState *const restrict state)
{
	const uint8_t *restrict octet;

	hash_state_shuffle(state);

	octet = state->octets;

	while (octet < state->upto) {
		ptr = put_octet_hex_lower(ptr,
					  *octet);
		++octet;
	}

	return put_last_hash_nibble(ptr,
				    *((const unsigned int *restrict) octet));
}

inline char *
put_hash_state_even(char *restrict ptr,
		    struct HashState *const restrict state)
{
	const uint8_t *restrict octet;

	hash_state_shuffle(state);

	octet = state->octets;

	while (1) {
		ptr = put_octet_hex_lower(ptr,
					  *octet);
		if (octet == state->upto) {
			*ptr = '\0';
			return ptr + 1l;
		}
		++octet;
	}
}

inline void
set_hash_state_odd(char *restrict ptr,
		   struct HashState *const restrict state)
{
	const uint8_t *restrict octet;

	hash_state_shuffle(state);

	octet = state->octets;

	while (octet < state->upto) {
		ptr = put_octet_hex_lower(ptr,
					  *octet);
		++octet;
	}

	set_last_hash_nibble(ptr,
			     *((const unsigned int *restrict) octet));
}

inline void
set_hash_state_even(char *restrict ptr,
		    struct HashState *const restrict state)
{
	const uint8_t *restrict octet;

	hash_state_shuffle(state);

	octet = state->octets;

	while (1) {
		ptr = put_octet_hex_lower(ptr,
					  *octet);
		if (octet == state->upto) {
			*ptr = '\0';
			return;
		}
		++octet;
	}
}


void
build_column_string_hash(void *arg);


#endif /* ifndef MYSQL_SEED_COLUMN_STRING_HASH_H_ */
