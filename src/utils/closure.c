#include "utils/closure.h"

/* RoutineClosure operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
routine_closure_init(struct RoutineClosure *const restrict routine_cl,
		     Routine *const fun,
		     void *arg);

extern inline void *
routine_closure_call(struct RoutineClosure *const restrict routine_cl);

/* ProcedureClosure operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
procedure_closure_init(struct ProcedureClosure *const restrict procedure_cl,
		       Procedure *const fun,
		       void *arg);

extern inline void
procedure_closure_call(struct RoutineClosure *const restrict procedure_cl);

/* HandlerClosure operations
 *─────────────────────────────────────────────────────────────────────────── */
extern inline void
handler_closure_init(struct HandlerClosure *const restrict handler_cl,
		     Handler *const handle,
		     void *arg);
extern inline void
handler_closure_call(struct HandlerClosure *const restrict handler_cl,
		     const char *const restrict failure);
