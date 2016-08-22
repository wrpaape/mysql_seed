#ifndef MYSQL_SEED_RANDOM_RANDOM_GENERATOR_H_
#define MYSQL_SEED_RANDOM_RANDOM_GENERATOR_H_

/* external dependencies
 * ────────────────────────────────────────────────────────────────────────── */
#include "random/random.h"	/* generator functions */


/* typedefs, struct declarations
 * ────────────────────────────────────────────────────────────────────────── */
/* unsigned integers */
struct UInt32Bounds {
	uint32_t limit;
	uint32_t length;
};

struct UInt64Bounds {
	uint64_t limit;
	uint64_t length;
};

union UIntBounds {
	struct UInt32Bounds uint32;
	struct UInt64Bounds uint64;
};

union UIntOffset {
	uint32_t uint32;
	uint64_t uint64;
};

struct UIntBoundsOffset {
	union UIntBounds bounds;
	union UIntOffset offset;
};


/* 0 ... UINT32|64_MAX */
typedef uintmax_t
UIntGenerator(void);

/* 0 ... upto */
typedef uintmax_t
UIntBoundGenerator(const union UIntBounds *const restrict params);

struct UIntBoundClosure {
	union UIntBounds params;
	UIntBoundGenerator *generate;
};

/* from ... UINT32|64_MAX, min ... max */
typedef uintmax_t
UIntBoundOffsetGenerator(const struct UIntBoundsOffset *const restrict params);

struct UIntBoundOffsetClosure {
	struct UIntBoundsOffset params;
	UIntBoundOffsetGenerator *generate;
};
