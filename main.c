#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#ifdef _WIN32
#include <windows.h>
#include <mmsystem.h>
#pragma comment(lib, "winmm.lib")
#define sleep_ms(ms) Sleep(ms)
#define beep() Beep(1000, 300)
#define play_final_sound() MessageBeep(MB_OK)
#else
#include <unistd.h>
#define sleep_ms(ms) usleep((ms) * 1000)
#define beep() printf("\a"); fflush(stdout)
#define play_final_sound() do { printf("\a"); fflush(stdout); } while(0)
#endif

void wait_seconds(int seconds) {
    for (int i = 0; i < seconds; ++i) {
        sleep_ms(1000);
    }
}

void log_event(const char* message, FILE* log_file) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    fprintf(log_file, "[%02d:%02d:%02d] %s\n", t->tm_hour, t->tm_min, t->tm_sec, message);
    fflush(log_file);
}

void log_date(FILE* log_file) {
    time_t now = time(NULL);
    struct tm* t = localtime(&now);
    fprintf(log_file, "\n======== Study Log: %04d-%02d-%02d ========\n",
            t->tm_year + 1900, t->tm_mon + 1, t->tm_mday);
    fflush(log_file);
}

int main() {
    int study_min, rest_min;
    float total_hr;
    char subject[256];

    printf("Enter what you are studying today: ");
    getchar(); // flush newline
    fgets(subject, sizeof(subject), stdin);
    subject[strcspn(subject, "\n")] = 0;

    printf("Enter study time in minutes: ");
    if (scanf("%d", &study_min) != 1 || study_min <= 0) {
        printf("Invalid input for study time.\n");
        return 1;
    }

    printf("Enter rest time in minutes: ");
    if (scanf("%d", &rest_min) != 1 || rest_min <= 0) {
        printf("Invalid input for rest time.\n");
        return 1;
    }

    printf("Enter total session time in hours: ");
    if (scanf("%f", &total_hr) != 1 || total_hr <= 0) {
        printf("Invalid input for total time.\n");
        return 1;
    }

    int study_sec = study_min * 60;
    int rest_sec = rest_min * 60;
    int total_sec = (int)(total_hr * 3600);
    int elapsed_sec = 0;
    int cycle = 1;

    FILE* log_file = fopen("log/study_log.txt", "a");
    if (!log_file) {
        printf("Unable to open log file.\n");
        return 1;
    }

    log_date(log_file);
    fprintf(log_file, "Studying: %s\n", subject);
    log_event("Study session started.", log_file);

    while (elapsed_sec < total_sec) {
        char message[100];
        sprintf(message, "Cycle %d: Study started for %d minutes.", cycle, study_min);
        log_event(message, log_file);
        printf("\nCycle %d - Study (%d min)...\n", cycle, study_min);
        wait_seconds(study_sec);
        elapsed_sec += study_sec;
        beep();

        if (elapsed_sec >= total_sec)
            break;

        sprintf(message, "Cycle %d: Rest started for %d minutes.", cycle, rest_min);
        log_event(message, log_file);
        printf("Cycle %d - Rest (%d min)...\n", cycle, rest_min);
        wait_seconds(rest_sec);
        elapsed_sec += rest_sec;
        beep();

        cycle++;
    }

    log_event("Study session completed.", log_file);
    fclose(log_file);

    printf("\nStudy session complete! Log saved to 'study_log.txt'\n");
    play_final_sound();  // Plays default system sound

    return 0;
}
