#include "random/random_generator.h"


/* generators
 * ────────────────────────────────────────────────────────────────────────── */
/* UGenerators */
uintmax_t
generate_u_32(void)
{
	return (uintmax_t) random_uint32();
}

uintmax_t
generate_u_64(void)
{
	return (uintmax_t) random_uint64();
}

/* IGenerators */
intmax_t
generate_i_32(void)
{
	return (intmax_t) (int32_t) random_uint32();
}

intmax_t
generate_i_64(void)
{
	return (intmax_t) (int64_t) random_uint64();
}


/* BoundUGenerators */
uintmax_t
generate_u_bound_32(const union Bound *const restrict params)
{
	return (uintmax_t) random_uint32_bound(params->uint32.threshold,
					       params->uint32.span);
}

uintmax_t
generate_u_bound_64(const union Bound *const restrict params)
{
	return (uintmax_t) random_uint64_bound(params->uint64.threshold,
					       params->uint64.span);
}

/* BoundIGenerators */
intmax_t
generate_i_bound_32_offset_32_min(const union Bound *const restrict params)
{
	return (intmax_t)
	       random_int32_bound_32_offset_32(params->uint32.threshold,
					       params->uint32.span,
					       INT32_MIN);
}

intmax_t
generate_i_bound_32_offset_64_min(const union Bound *const restrict params)
{
	return (intmax_t)
	       random_int64_bound_32_offset_64(params->uint32.threshold,
					       params->uint32.span,
					       INT64_MIN);
}

intmax_t
generate_i_bound_64_offset_32_min(const union Bound *const restrict params)
{
	return (intmax_t)
	       random_int64_bound_64_offset_32(params->uint64.threshold,
					       params->uint64.span,
					       INT32_MIN);
}

intmax_t
generate_i_bound_64_offset_64_min(const union Bound *const restrict params)
{
	return (intmax_t)
	       random_int64_bound_64_offset_64(params->uint64.threshold,
					       params->uint64.span,
					       INT64_MIN);
}



/* BoundOffsetUGenerators */
uintmax_t
generate_u_bound_32_offset_32(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t)
	       random_uint32_bound_32_offset_32(params->bound.uint32.threshold,
						params->bound.uint32.span,
						params->offset.uint32);
}

uintmax_t
generate_u_bound_32_offset_64(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t)
	       random_uint64_bound_32_offset_64(params->bound.uint32.threshold,
						params->bound.uint32.span,
						params->offset.uint64);
}

uintmax_t
generate_u_bound_64_offset_32(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t)
	       random_uint64_bound_64_offset_32(params->bound.uint64.threshold,
						params->bound.uint64.span,
						params->offset.uint32);
}

uintmax_t
generate_u_bound_64_offset_64(const struct BoundOffsetU *const restrict params)
{
	return (uintmax_t)
	       random_uint64_bound_64_offset_64(params->bound.uint64.threshold,
						params->bound.uint64.span,
						params->offset.uint64);
}


/* BoundOffsetIGenerators */
intmax_t
generate_i_bound_32_offset_32(const struct BoundOffsetI *const restrict params)
{
	return (intmax_t)
	       random_int32_bound_32_offset_32(params->bound.uint32.threshold,
					       params->bound.uint32.span,
					       params->offset.int32);
}

intmax_t
generate_i_bound_32_offset_64(const struct BoundOffsetI *const restrict params)
{
	return (intmax_t)
	       random_int64_bound_32_offset_64(params->bound.uint32.threshold,
					       params->bound.uint32.span,
					       params->offset.int64);
}

intmax_t
generate_i_bound_64_offset_32(const struct BoundOffsetI *const restrict params)
{
	return (intmax_t)
	       random_int64_bound_64_offset_32(params->bound.uint64.threshold,
					       params->bound.uint64.span,
					       params->offset.int32);
}

intmax_t
generate_i_bound_64_offset_64(const struct BoundOffsetI *const restrict params)
{
	return (intmax_t)
	       random_int64_bound_64_offset_64(params->bound.uint64.threshold,
					       params->bound.uint64.span,
					       params->offset.int64);
}
