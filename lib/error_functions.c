#include <stdarg.h>
#include "error_functions.h"
#include "tlpi_hdr.h"
#include "ename.c.inc" /* Defines ename and MAX_ENAME */

#ifndef __GNUC__
__attribute__((__noreturn__))
#endif //__GNUC__

static void
terminate(bool useExit3)
{
    char *s;

    /* Dump core if EF_DUMPCORE environment variable is defined and is a nonempty string; otherwise call exit(3) or _exit(2), depending on the value of 'useExit3'. */

    s = getenv("EF_DUMPCORE");

    if (s != NULL && *s != '\0')
        abort();
    else if (useExit3)
        exit(EXIT_FAILURE);
    else
        _exit(EXIT_FAILURE);
}

static void outputError(bool useErr, int err, bool flushStdout, const char *format, va_list ap)
{
#define BUF_SIZE 500

    char buf[BUF_SIZE], useMsg[BUF_SIZE], errText[BUF_SIZE];

    vsnprintf(useMsg, BUF_SIZE, format, ap);

    if (useErr)
        snprintf(errText, BUF_SIZE, "[%s %s]", (err > 0 && err <= MAX_ENAME) ? ename[err] : "?UNKNOWN?", strerror(err));
    else
        snprintf(errText, BUF_SIZE, ": ");

    snprintf(buf, BUF_SIZE, "ERROR%s %s\n", errText, useMsg);

    if (flushStdout)
        fflush(stdout); /* Flush any pending stdout */
    fputs(buf, stderr);
    fflush(stderr); /* In case stderr is not line-buffered */
}

void errMsg(const char *format, ...)
{
    va_list argList;
    int savedErrno;

    savedErrno = errno; /* In case we change it here */

    va_start(argList, format);
    outputError(true, errno, true, format, argList);
    va_end(argList);

    errno = savedErrno;
}

void errExit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(true, errno, true, format, argList);
    va_end(argList);

    terminate(true);
}

void err_exit(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(true, errno, false, format, argList);
    va_end(argList);

    terminate(false);
}

void errExitEN(int errnum, const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(true, errnum, true, format, argList);
    va_end(argList);

    terminate(true);
}

void fatal(const char *format, ...)
{
    va_list argList;

    va_start(argList, format);
    outputError(false, 0, true, format, argList);
    va_end(argList);

    terminate(true);
}

void usageErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout); /* Flush any pending stdout */

    fprintf(stderr, "Usage: ");
    va_start(argList, format);
    vprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr); /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}

void cmdLineErr(const char *format, ...)
{
    va_list argList;

    fflush(stdout); /* Flush any pending stdout */
    va_start(argList, format);
    vfprintf(stderr, format, argList);
    va_end(argList);

    fflush(stderr); /* In case stderr is not line-buffered */
    exit(EXIT_FAILURE);
}
