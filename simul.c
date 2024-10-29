#include "simul.h"

// 시뮬레이터 함수
void run_simulation() {
    int total_waiting_time = 0;
    int total_turnaround_time = 0;
    int total_response_time = 0;

    for (int iter = 0; iter < ITERATIONS; iter++) {
        int num_jobs = rand() % MAX_JOBS + 1; // 랜덤 Job 개수
        Job jobs[num_jobs];

        // 랜덤 Arrival Time과 Burst Time 생성
        for (int i = 0; i < num_jobs; i++) {
            jobs[i].id = i + 1;
            jobs[i].arrival_time = rand() % MAX_ARRIVAL_TIME;
            jobs[i].burst_time = rand() % MAX_BURST_TIME + 1;
            jobs[i].remaining_time = jobs[i].burst_time;
            jobs[i].weight = rand() % 20 + 1; // 각 프로세스에 1에서 20 사이의 가중치 할당
            jobs[i].virtual_runtime = 0.0;   // 초기 가상 실행 시간은 0
            jobs[i].start_time = -1;
            jobs[i].completed = 0;
        }

        int current_time = 0;
        int completed_jobs = 0;

        while (completed_jobs < num_jobs) {
            int time_slice = 0;
            int selected_job = fair_scheduler(jobs, num_jobs, current_time, &time_slice);

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

            // Job 완료 시 Turnaround Time과 Waiting Time 계산
            if (job->remaining_time == 0) {
                int turnaround_time = current_time - job->arrival_time;
                int waiting_time = turnaround_time - job->burst_time;
                int response_time = job->start_time - job->arrival_time;

                total_turnaround_time += turnaround_time;
                total_waiting_time += waiting_time;
                total_response_time += response_time;

                completed_jobs++;
            }
        }
        total_turnaround_time = total_turnaround_time / num_jobs;
        total_waiting_time = total_waiting_time / num_jobs;
        total_response_time = total_response_time / num_jobs;
    }

    // 평균 계산
    double avg_waiting_time = (double)total_waiting_time / ITERATIONS;
    double avg_turnaround_time = (double)total_turnaround_time / ITERATIONS;
    double avg_response_time = (double)total_response_time / ITERATIONS;

    // 결과 출력
    printf("Average Waiting Time: %.2f\n", avg_waiting_time);
    printf("Average Turnaround Time: %.2f\n", avg_turnaround_time);
    printf("Average Response Time: %.2f\n", avg_response_time);
}

int main() {
    srand(time(NULL));  // 랜덤 시드 설정
    run_simulation();   // 시뮬레이션 실행
    return 0;
}

