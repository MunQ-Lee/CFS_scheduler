#ifndef _SIMUL_H_
#define _SIMUL_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <limits.h>

#define MAX_JOBS 100         // 최대 Job 개수
#define MAX_BURST_TIME 100   // 최대 Burst Time
#define MAX_ARRIVAL_TIME 100 // 최대 Arrival Time
#define ITERATIONS 1     // 시뮬레이션 반복 횟수
#define TIME_QUANTUM 4      // Time Quantum for Round Robin
#define BASE_WEIGHT 1024    // 기본 가중치 값 (참조 가중치)

// Job 구조체 정의
typedef struct {
    int id;
    int arrival_time;
    int burst_time;
    int remaining_time;
    int weight;               // 프로세스 가중치
    double virtual_runtime;   // 가상 실행 시간
    int start_time;
    int completed;
} Job;

int round_robin_scheduler(Job jobs[], int n, int current_time, int *time_slice);
int fair_scheduler(Job jobs[], int n, int current_time, int *time_slice);

#endif