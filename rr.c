#include "simul.h"

// 현재 실행할 Job과 수행 시간을 결정하는 스케줄러 함수
int round_robin_scheduler(Job jobs[], int n, int current_time, int *time_slice) {
    int selected_job = -1;
    for (int i = 0; i < n; i++) {
        if (jobs[i].arrival_time <= current_time && jobs[i].remaining_time > 0) {
            selected_job = i;
            *time_slice = (jobs[i].remaining_time > TIME_QUANTUM) ? TIME_QUANTUM : jobs[i].remaining_time;
            break;
        }
    }
    return selected_job;
}