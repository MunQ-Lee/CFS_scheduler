#include "simul.h"

int nice[40] = {-20, -19, -18, -17, -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

int weight[40] = {88761, 71755, 56483, 46273, 36291, 29154, 23254, 18705, 14949, 11916, 9548, 7620, 6100, 4904, 3906, 3121, 2501, 1991, 1586, 1277, 1024, 820, 655, 526, 423, 335, 272, 215, 172, 137, 110, 87, 70, 56, 45, 36, 29, 23, 18, 15};

// 시뮬레이터 함수
void run_simulation() {

    for (int iter = 0; iter < ITERATIONS; iter++) {
        // int num_jobs = rand() % MAX_JOBS + 1; // 랜덤 Job 개수
        int num_jobs = MAX_JOBS;
        Job jobs[num_jobs];
        printf("number of jobs: %d\n", num_jobs);

        // 랜덤 Arrival Time과 Burst Time 생성
        for (int i = 0; i < num_jobs; i++) {
            jobs[i].id = i + 1;
            jobs[i].arrival_time = rand() % MAX_ARRIVAL_TIME;
            jobs[i].burst_time = rand() % MAX_BURST_TIME + 1;
            jobs[i].remaining_time = jobs[i].burst_time;
            int weight_idx = rand() % 40;
            jobs[i].nice = nice[weight_idx]; // 각 프로세스에 -20에서 19 사이의 가중치 할당
            jobs[i].weight = weight[weight_idx];
            jobs[i].virtual_runtime = 0.0;   // 초기 가상 실행 시간은 0
            jobs[i].start_time = -1;
            jobs[i].completed = 0;
        }

        int current_time = 0;
        int completed_jobs = 0;

        while (completed_jobs < num_jobs) {
            int time_slice = 0;
            int selected_job = round_robin_scheduler(jobs, num_jobs, current_time, &time_slice);

            if (selected_job == -1) {
                current_time++; // 다음 시점을 기다림
                continue;
            }

            Job *job = &jobs[selected_job];

            // 첫 실행 시 Response Time 설정
            if (job->start_time == -1) {
                job->start_time = current_time;
                job->completed = 1;
            }

            // Job 수행
            current_time += time_slice;
            job->remaining_time -= time_slice;
            printf("%d job execute, %d nice value, %f vruntime, %d time slice\n", selected_job, job->nice, job->virtual_runtime, time_slice);

            // Job 완료 시
            if (job->remaining_time == 0) {
                printf("%d job complete, %d nice value\n", selected_job, job->nice);
                completed_jobs++;
            }
        }
    }
}

int main() {
    srand(time(NULL));  // 랜덤 시드 설정
    run_simulation();   // 시뮬레이션 실행
    return 0;
}

