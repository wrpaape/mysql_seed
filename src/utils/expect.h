#ifndef MYSQL_SEED_UTILS_EXPECT_H_
#define MYSQL_SEED_UTILS_EXPECT_H_

/* helper macros
 * ────────────────────────────────────────────────────────────────────────── */
#define LIKELY(BOOL)   __builtin_expect(BOOL, 1)
#define UNLIKELY(BOOL) __builtin_expect(BOOL, 0)

#endif /* ifndef MYSQL_SEED_UTILS_EXPECT_H_ */
