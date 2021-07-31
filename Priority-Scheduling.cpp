/*
    Prioriy Scheduling (Non-preemptive version)
    Algo: Runs the process that has the highest priority. If two processes have the same priority, they are executed in the order they arrived.
*/

#include <bits/stdc++.h>
using   namespace  std ;

int main()
{
    
    // ** Input part
    int n ;
    cout << "Enter the number of process: " ;
    cin >> n ;
    
    vector<int> CPU_times(n), arrival_times(n), priority_values(n) ;
    cout << "Enter the CPU times" << endl ;
    for(auto &i : CPU_times)
        cin >> i ;
    cout << "Enter the arrival times" << endl ;
    for(auto &i : arrival_times)
        cin >> i ;
    cout << "Enter the priority values" << endl ;
    for(auto &i : priority_values)
        cin >> i ;
    // ** ** ** **

    int curr_time = 0 ;
    vector<int> waiting_times(n), turnaround_times(n) ;
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))

    deque<pair<int, int> > sorted_arrival ; // ? (arrival time, PID)
    for(int i = 0 ; i < n ; i++)
        sorted_arrival.push_back({arrival_times[i], i}) ;
    sort(sorted_arrival.begin(), sorted_arrival.end()) ;
    
    using pipii = pair<int, pair<int, int> > ;
    priority_queue<pipii, vector<pipii> , greater<pipii> > ready_queue ; // ? (priority value, (arrival time, PID))

    while(!sorted_arrival.empty() or !ready_queue.empty())
    {
        if(ready_queue.empty() and !sorted_arrival.empty() and curr_time < sorted_arrival.front().first)
            curr_time = sorted_arrival.front().first ;
        while(!sorted_arrival.empty() and sorted_arrival.front().first <= curr_time)
        {
            int pid = sorted_arrival.front().second ;
            ready_queue.push({priority_values[pid], {arrival_times[pid], pid}}) ;
            sorted_arrival.pop_front() ;
        }

        if(!ready_queue.empty())
        {
            int pid = ready_queue.top().second.second ;
            ready_queue.pop() ;
            if(curr_time < arrival_times[pid])
                curr_time = arrival_times[pid] ;
            waiting_times[pid] = curr_time - arrival_times[pid] ;
            turnaround_times[pid] = waiting_times[pid] + CPU_times[pid] ;
            gantt.push_back(make_pair(pid, make_pair(curr_time, curr_time + CPU_times[pid]))) ;
            curr_time += CPU_times[pid] ;
        }
    }

    int total_waiting_time = 0 ;
    for(auto &i : waiting_times)
        total_waiting_time += i ;
    int total_turnaround_time = 0 ;
    for(auto &i : turnaround_times)
        total_turnaround_time += i ;
    double average_waiting_time = (double) total_waiting_time / n ;
    double average_turnaround_time = (double) total_turnaround_time / n ;
    
    // ** Output part
    cout << "Gantt: <PID, start time, end time>" << endl ;
    for(auto i : gantt)
        cout << "<" << i.first << ", " << i.second.first << ", " << i.second.second << ">" << endl ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Process " << i << ": " ;
        cout << "Waiting/Response Time : " << waiting_times[i] << " Turnaround Time : " << turnaround_times[i] << endl ;
    }
    cout << "Average Waiting/Response Time : " << average_waiting_time << endl ;
    cout << "Average Turnaround Time : " << average_turnaround_time << endl ;
    // ** ** ** **

    return 0;
}

// ? Test Case 1:
// 3
// 5 7 9
// 4 0 2
// 0 2 1
