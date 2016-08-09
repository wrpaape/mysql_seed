#ifndef MYSQL_SEED_COLUMN_STRING_HASH_H_
#define MYSQL_SEED_COLUMN_STRING_HASH_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "generate/generator.h"	/* string/thread utils */
/* #include "time/time_utils.h"	/1* for seeding hash state *1/ */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
struct HashStateBufferPointer {
	word_t *restrict word;
	uint8_t *restrict octet;
};

struct HashState {
	word_t *restrict words;
	uint8_t *restrict octets;
	const uint8_t *restrict last;
	unsigned int rotate;
};

inline void
hash_state_init(struct HashState *const restrict state,
		void *const restrict buffer,
		const void *const restrict until)
{
	struct HashStateBufferPointer buffer_ptr;

	buffer_ptr.word = (word_t *restrict) buffer;

	state->words  = buffer_ptr.word;
	state->octets = buffer_ptr.octet + (OCTET_WORD - 1l);
	state->last   = ((uint8_t *restrict) until) - 1l;
	state->rotate = (uintptr_t) until;

	*(buffer_ptr.word) = (uintptr_t) buffer_ptr.word;
	++(buffer_ptr.octet);

	while (buffer_ptr.octet < (uint8_t *restrict) until) {
		*(buffer_ptr.word) ^= (uintptr_t) buffer_ptr.word;
		++(buffer_ptr.octet);
	}
}

inline void
set_last_hash_nibble(char *const restrict buffer,
		     const word_t last)
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
put_hash_state(char *const restrict ptr,
	       struct HashState *const restrict state)


void
build_column_string_hash(void *arg);


#endif /* ifndef MYSQL_SEED_COLUMN_STRING_HASH_H_ */
