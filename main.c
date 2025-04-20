#include <stdio.h>
#include <time.h>
#include <string.h>

void get_timestamp(char *buffer, size_t size) {
    time_t now = time(NULL);
    struct tm *t = localtime(&now);
    strftime(buffer, size, "<%Y-%m-%d %a %H:%M>", t);
}

int main() {
    char activity[256], type;
    char timestamp[64];
    FILE *file;

    printf("What are you doing? ");
    fgets(activity, sizeof(activity), stdin);
    activity[strcspn(activity, "\n")] = 0; // remove newline

    printf("Creation (c) or Consumption (C)? ");
    scanf(" %c", &type);

    get_timestamp(timestamp, sizeof(timestamp));

    file = fopen("focuslog.org", "a");
    if (!file) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "* %s %s\n  - Type: %s\n",
            timestamp,
            activity,
            (type == 'c' || type == 'C') ? ((type == 'c') ? "Creation" : "Consumption") : "Unknown");

    fclose(file);
    printf("Logged to focuslog.org\n");

    return 0;
}
