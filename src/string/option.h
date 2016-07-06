#ifndef MYSQL_SEED_STRING_OPTION_H_
#define MYSQL_SEED_STRING_OPTION_H_

/* external dependencies
 *─────────────────────────────────────────────────────────────────────────── */
#include "string/string_utils.h"	/* string utils, macros, ascii utils */

/* typedefs, struct declarations
 *─────────────────────────────────────────────────────────────────────────── */

enum OptionType {
	OPTION_STRING_LIMITED,
	OPTION_STRING_UNLIMITED,
	OPTION_CHARACTER,
	OPTION_STRING_ASCII_LIMITED,
	OPTION_STRING_ASCII_UNLIMITED,
	OPTION_CHARACTER_ASCII,
	OPTION_STRING_UTF8_LIMITED,
	OPTION_STRING_UTF8_UNLIMITED,
	OPTION_CHARACTER_UTF8,
	OPTION_INTEGER_SIGNED,
	OPTION_INTEGER_UNSIGNED
};


/* jump functions */
typedef void
OptionStringJump(void *state,
		 char *parsed)
__attribute__((noreturn));

typedef void
OptionCharacterJump(void *state,
		    char parsed)
__attribute__((noreturn));

typedef void
OptionStringASCIIJump(void *state,
		      ascii_t *parsed)
__attribute__((noreturn));

typedef void
OptionCharacterASCIIJump(void *state,
			 ascii_t parsed)
__attribute__((noreturn));

typedef void
OptionStringUTF8Jump(void *state,
		     char *parsed)
__attribute__((noreturn));

typedef void
OptionCharacterUTF8Jump(void *state,
			struct UTF8Char parsed)
__attribute__((noreturn));

typedef void
OptionIntegerSignedJump(void *state,
			intmax_t parsed)
__attribute__((noreturn));

typedef void
OptionIntegerUnsignedJump(void *state,
			  uintmax_t parsed)
__attribute__((noreturn));

/* option specifications */
struct OptionStringLimitedSpec {
	size_t max_length;
	OptionStringJump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionStringUnLimitedSpec {
	OptionStringJump		*jump_valid;
};

struct OptionCharacterSpec {
	OptionCharacterJump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionStringASCIILimitedSpec {
	size_t max_length;
	OptionStringASCIIJump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionStringASCIIUnLimitedSpec {
	OptionStringASCIIJump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionCharacterASCIISpec {
	OptionCharacterASCIIJump	*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionStringUTF8LimitedSpec {
	size_t max_length;
	OptionStringUTF8Jump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionStringUTF8UnLimitedSpec {
	OptionStringUTF8Jump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

struct OptionCharacterUTF8Spec {
	OptionCharacterUTF8Jump		*jump_valid;
	OptionStringJump		*jump_invalid;
};

union OptionSpec {
	struct OptionStringLimitedSpec		string_limited;
	struct OptionStringUnlimitedSpec	string_unlimited;
	struct OptionCharacterSpec		character;
	struct OptionStringASCIILimitedSpec	string_ascii_limited;
	struct OptionStringASCIIUnlimitedSpec	string_ascii_unlimited;
	struct OptionCharacterASCIISpec		character_ascii;
	struct OptionStringUTF8LimitedSpec	string_utf8_limited;
	struct OptionStringUTF8UnlimitedSpec	string_utf8_unlimited;
	struct OptionCharacterUTF8Spec		character_utf8;
	struct OptionIntegerSignedSpec		integer_signed;
	struct OptionIntegerUnsignedSpec	integer_unsigned;
};

struct Option {
	char flag;
	const char *rem_alias;
	enum OptionType type;
	union OptionSpec spec;
};

struct OptionNode {
	struct Option *flag_map[U];
};

#endif /* ifndef MYSQL_SEED_STRING_OPTION_H_ */
