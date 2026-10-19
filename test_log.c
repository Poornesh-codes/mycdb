#include "pebble_log.h"
#include <stdio.h>

int main(void)
{
    FILE *log = log_open("pebble.log");

    if (log == NULL) {
        printf("Failed to open log\n");
        return 1;
    }

    printf("Log opened successfully\n");

    if (log_append_put(log, "cat", 3, "meow", 4)) {
        printf("Record written successfully\n");
    } else {
        printf("Failed to write record\n");
    }

    log_close(log);
    printf("Log closed successfully\n");

    return 0;
}