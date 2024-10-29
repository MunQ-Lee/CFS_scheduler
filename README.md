# CFS Scheduler Simulation

## Project Overview

In this project, a CFS scheduler assigns CPU time based on each process's weight, where processes with higher weights are granted more frequent access to the CPU. Each process has an associated `vruntime` (virtual runtime) which tracks its CPU usage relative to other processes.

The scheduler aims to:
- Simulate a fair allocation of CPU time across randomly generated processes.
- Calculate key metrics such as average **waiting time**, **turnaround time**, and **response time** for the simulated processes.

## Features

- Simulates **CFS scheduling** using virtual runtime tracking for fairness.
- Configurable parameters for:
  - Maximum job count
  - Maximum burst time
  - Maximum arrival time
  - Number of iterations for averaging results
- Computes average waiting time, turnaround time, and response time for each iteration of the simulation.

## Code Structure

The main components of the code are:
- `Job` structure: Defines process attributes, including arrival time, burst time, weight, and virtual runtime.
- `round_robin_scheduler` function: Implements the round robin scheduling logic by preempting job.
- `fair_scheduler` function: Implements the CFS scheduling logic by selecting the job with the lowest virtual runtime.
- `run_simulation` function: Manages the setup, execution, and statistics collection for the simulation.

## Compilation and Usage

To compile and run the program:

```bash
make
./simulator
```
