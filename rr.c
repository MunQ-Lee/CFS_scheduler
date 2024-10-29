#include "simul.h"

// 마지막으로 실행된 작업을 추적하는 변수
int last_executed_job = -1;

// 현재 실행할 Job과 수행 시간을 결정하는 스케줄러 함수
int round_robin_scheduler(Job jobs[], int n, int current_time, int *time_slice) {
    int selected_job = -1;
    
    // 마지막으로 실행된 작업의 다음 작업부터 순환 탐색
    for (int i = (last_executed_job + 1) % n; i != last_executed_job; i = (i + 1) % n) {
        if (jobs[i].arrival_time <= current_time && jobs[i].remaining_time > 0) {
            selected_job = i;
            *time_slice = (jobs[i].remaining_time > TIME_QUANTUM) ? TIME_QUANTUM : jobs[i].remaining_time;
            last_executed_job = i;  // 마지막 실행 작업 업데이트
            break;
        }
    }

    return selected_job;
}
