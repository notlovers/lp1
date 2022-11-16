/*
 * Practical 3: Write a program to simulate CPU Scheduling Algorithms: Priority (Non-Preemptive)
 * The Text Editor: VIM - Vi IMproved 9.0
 * The Compiler: Apple clang version 13.1.6 (clang-1316.0.21.2.3)
 * The Machine: MacBook Air M1 (Running ARM64 architecture)
 */

#include <iostream>
#include <algorithm>
#include <iomanip>
#include <string.h>

struct process {
    int pid;
    int arrival_time;
    int burst_time;
    int priority;
    int start_time;
    int completion_time;
    int turnaround_time;
    int waiting_time;
    int response_time;
};

int main() {
    int n;
    struct process p[100];
    float avg_turnaround_time;
    float avg_waiting_time;
    float avg_response_time;
    float cpu_utilisation;
    int total_turnaround_time = 0;
    int total_waiting_time = 0;
    int total_response_time = 0;
    int total_idle_time = 0;
    float throughput;
    int is_completed[100];
    memset(is_completed, 0, sizeof(is_completed));

    std::cout << std::setprecision(2) << std::fixed;

    std::cout << "Enter the number of processes: ";
    std::cin >> n;

    for(int i = 0; i < n; i++) {
        std::cout << "Enter arrival time of process " << i + 1 <<": ";
        std::cin >> p[i].arrival_time;
        std::cout << "Enter burst time of process "<< i + 1 <<": ";
        std::cin >> p[i].burst_time;
        std::cout <<"Enter priority of the process "<< i + 1 <<": ";
        std::cin >> p[i].priority;
        p[i].pid = i + 1;
        std::cout << std::endl;
    }

    int current_time = 0;
    int completed = 0;
    int prev = 0;

    while(completed != n) {
        int idx = -1;
        int mx = -1;
        for(int i = 0; i < n; i++) {
            if(p[i].arrival_time <= current_time && is_completed[i] == 0) {
                if(p[i].priority > mx) {
                    mx = p[i].priority;
                    idx = i;
                }
                if(p[i].priority == mx) {
                    if(p[i].arrival_time < p[idx].arrival_time) {
                        mx = p[i].priority;
                        idx = i;
                    }
                }
            }
        }
        if(idx != -1) {
            p[idx].start_time = current_time;
            p[idx].completion_time = p[idx].start_time + p[idx].burst_time;
            p[idx].turnaround_time = p[idx].completion_time - p[idx].arrival_time;
            p[idx].waiting_time = p[idx].turnaround_time - p[idx].burst_time;
            p[idx].response_time = p[idx].start_time - p[idx].arrival_time;
            
            total_turnaround_time += p[idx].turnaround_time;
            total_waiting_time += p[idx].waiting_time;
            total_response_time += p[idx].response_time;
            total_idle_time += p[idx].start_time - prev;

            is_completed[idx] = 1;
            completed++;
            current_time = p[idx].completion_time;
            prev = current_time;
        }
        else {
            current_time++;
        }
        
    }

    int min_arrival_time = 10000000;
    int max_completion_time = -1;
    for(int i = 0; i < n; i++) {
        min_arrival_time = std::min(min_arrival_time, p[i].arrival_time);
        max_completion_time = std::max(max_completion_time, p[i].completion_time);
    }

    avg_turnaround_time = (float)total_turnaround_time / n;
    avg_waiting_time = (float)total_waiting_time / n;
    avg_response_time = (float)total_response_time / n;
    cpu_utilisation = ((max_completion_time - total_idle_time) / (float) max_completion_time) * 100;
    throughput = float(n) / (max_completion_time - min_arrival_time);

    std::cout << std::endl << std::endl;

    std::cout<<"#P\t"<<"AT\t"<<"BT\t"<<"PRI\t"<<"ST\t"<<"CT\t"<<"TAT\t"<<"WT\t"<<"RT\t"<<"\n"<<std::endl;

    for(int i = 0; i < n; i++) {
        std::cout << p[i].pid<<"\t" << p[i].arrival_time << "\t" << p[i].burst_time << "\t" << p[i].priority << "\t" << p[i].start_time << "\t" << p[i].completion_time << "\t" << p[i].turnaround_time << "\t" << p[i].waiting_time << "\t" << p[i].response_time << "\t" << "\n" << std::endl;
    }
    std::cout << "Average Turnaround Time = " << avg_turnaround_time<< std::endl;
    std::cout << "Average Waiting Time = " << avg_waiting_time << std::endl;
    std::cout << "Average Response Time = " << avg_response_time << std::endl;
    std::cout << "CPU Utilization = " << cpu_utilisation << "%" << std::endl;
    std::cout << "Throughput = " << throughput << " process/unit time" << std::endl;

}

