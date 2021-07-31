/*
    Round Robin Algorithm
    Type: Preemptive
    Algo: Runs the process that arrives earlier. If the current process runs longer than Q (which is predefined),
          it removes the current process and insert it at the end of the queue and switches context to the next process.
*/

#include <bits/stdc++.h>
using   namespace  std ;

int main()
{
    
    // ** Input part
    int Q = 3 ;
    cout << "Enter the Time Quantum: " ;
    cin >> Q ;
    int n ;
    cout << "Enter the number of process: " ;
    cin >> n ;
    
    vector<int> CPU_times(n), arrival_times(n) ;
    cout << "Enter the CPU times" << endl ;
    for(auto &i : CPU_times)
        cin >> i ;
    cout << "Enter the arrival times" << endl ;
    for(auto &i : arrival_times)
        cin >> i ;
    // ** ** ** **

    int curr_time = 0 ;
    vector<int> waiting_times(n), turnaround_times(CPU_times.begin(), CPU_times.end()) ;
    vector<pair<int, int> > response_times(n) ; // ? response_times[i] = <flag, response time> 
    vector<pair<int, pair<int, int> > > gantt ; // ? (PID, (start_time, finish_time))

    priority_queue<pair<double, int> , vector<pair<double, int> > , greater<pair<double, int> > > ready_queue ; // ? <arrival time, PID>
    for(int i = 0 ; i < n ; i++)
        ready_queue.push(make_pair((double) arrival_times[i], i)) ;

    while(!ready_queue.empty())
    {
        int pid = ready_queue.top().second ;
        ready_queue.pop() ;

        if(curr_time < arrival_times[pid])
            curr_time = arrival_times[pid] ;
        waiting_times[pid] += curr_time - arrival_times[pid] ;
        turnaround_times[pid] += curr_time - arrival_times[pid] ;

        if(response_times[pid].first == 0)
            response_times[pid] = make_pair(1, waiting_times[pid]) ;
        
        int execution_time = min(Q, CPU_times[pid]) ;
        gantt.push_back(make_pair(pid, make_pair(curr_time, curr_time + execution_time))) ;
        curr_time += execution_time ;
        CPU_times[pid] -= execution_time ;

        if(CPU_times[pid] > 0)
        {
            ready_queue.push(make_pair(curr_time + 0.1, pid)) ;
            arrival_times[pid] = curr_time ;
        }
    }

    int total_waiting_time = 0 ;
    for(auto &i : waiting_times)
        total_waiting_time += i ;
    int total_turnaround_time = 0 ;
    for(auto &i : turnaround_times)
        total_turnaround_time += i ;
    int total_response_time = 0 ;
    for(auto &i : response_times)
        total_response_time += i.second ;
    double average_waiting_time = (double) total_waiting_time / n ;
    double average_turnaround_time = (double) total_turnaround_time / n ;
    double average_response_time = (double) total_response_time / n ;

    // ** Output part
    cout << "Gantt: <PID, start time, end time>" << endl ;
    for(auto i : gantt)
        cout << "<" << i.first << ", " << i.second.first << ", " << i.second.second << ">" << endl ;
    for(int i = 0 ; i < n ; i++)
    {
        cout << "Process " << i << ": " ;
        cout << "Response Time : " << response_times[i].second << " Waiting Time : " << waiting_times[i] << " Turnaround Time : " << turnaround_times[i] << endl ;
    }
    cout << "Average Response Time : " << average_response_time << endl ;
    cout << "Average Waiting Time : " << average_waiting_time << endl ;
    cout << "Average Turnaround Time : " << average_turnaround_time << endl ;
    // ** ** ** **

    return 0;
}

// ? Test Case 1:
// 3
// 4
// 5 7 9 9
// 4 0 6 10

// ? Test Case 2:
// 4
// 6
// 8 8 6 10 13 6
// 17 16 6 0 12 8
