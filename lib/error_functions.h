#ifndef ERROR_FUNCTIONS_H
#define ERROR_FUNCTIONS_H

void errMsg(const char *format, ...);

#ifndef __GNUC__

/* This macro stops 'gcc -Wall' complaining that "control reaches end of non-void functions" if we use the following functions to terminate main() or some other non-void functions. */

#define NORETURN __attribute__((__noreturn__))
#else
#define NORETURN
#endif // __GNUC__

void errExit(const char *format, ...) NORETURN;

void err_exit(const char *format, ...) NORETURN;

void errExitEN(int errnum, const char *format, ...) NORETURN;

void fatal(const char *format, ...) NORETURN;

void usageErr(const char *format, ...) NORETURN;

void cmdLineErr(const char *format, ...) NORETURN;

#endif // ERROR_FUNCTIONS_H
