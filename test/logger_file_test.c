#include "logger.h"
#include <stdio.h>
#include "nanounit.h"

static const char kOutputFilename[] = "file.log";

static void setup(void)
{
    remove(kOutputFilename);
}

static void cleanup(void)
{
    remove(kOutputFilename);
}

static int test_fileLogger(void)
{
    const char message[] = "message";
    int result;
    FILE* fp;
    char line[256];
    int count = 0;

    /* when: initialize file logger */
    result = logger_initFileLogger(kOutputFilename, 0, 0);

    /* then: ok */
    nu_assert_eq_int(1, result);

    /* when: output to the file */
    LOG_TRACE(message);
    LOG_DEBUG(message);
    LOG_INFO(message);

    /* then: write only one line */
    if ((fp = fopen(kOutputFilename, "r")) == NULL) {
        nu_fail();
    }
    while (fgets(line, sizeof(line), fp) != NULL) {
        line[strlen(line) - 1] = '\0'; /* remove LF */
        nu_assert_eq_int('I', line[0]);
        nu_assert_eq_str(message, &line[strlen(line) - strlen(message)]);
        count++;
    }
    nu_assert_eq_int(1, count);

    /* cleanup: close resources */
    fclose(fp);
    return 0;
}

int main(int argc, char* argv[])
{
    setup();
    nu_run_test(test_fileLogger);
    cleanup();
    nu_report();
}