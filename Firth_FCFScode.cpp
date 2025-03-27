//Zachary Firth
//COP4610
// 2/5/23
//Due Date: 2/20/23 
//Firth_FCFScode
//Purpose: To take a set of data from 9 processes that represent CPU burst
//times and I/O times to calculate the order these times and processes occur.
//This program also calculates the response times, waiting times, and turnaround times 
//for each process and the average, as well as calculate the CPU utilization
#include <cstdlib>
#include <iostream>
#include <deque>
#include <queue>
#include<vector>

using namespace std;
struct process {
	int pid;
	int arrival_time = 0;
	int total_btime = 0;
	int start_time;
	int btime;
	int completion_time;
	int tatime;
	int wtime;
	int rtime;
};

int main()
{
	struct process p[10];
	float tatime_avg;
	float wtime_avg;
	float rtime_avg;
	float cpu_utilization;
	int total_tatime = 0;
	int total_wtime = 0;
	int total_rtime = 0;
	int total_itime = 0;
	int ps[10][19] = { { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },//Standard size of process and its data
	{ 6, 41, 5, 42, 7, 40, 8, 38, 6, 44, 5, 41, 9, 31, 7, 43, 8, 0, 0 }, // process1
	{ 9, 24, 7, 21, 8, 36, 12, 26, 9, 31, 11, 28, 8, 21, 12, 13, 7, 11, 6 }, // process2
	{ 7, 21, 8, 25, 12, 29, 6, 26, 8, 33, 9, 22, 6, 24, 4, 29, 16, 0, 0 }, // process3
	{ 5, 35, 7, 41, 14, 45, 4, 51, 9, 61, 10, 54, 11, 82, 5, 77, 3, 0, 0 }, // process4
	{ 6, 33, 7, 44, 5, 42, 9, 37, 8, 46, 5, 41, 7, 31, 4, 43, 3, 0, 0 }, // process5
	{ 8, 24, 12, 21, 11, 36, 12, 26, 9, 31, 19, 28, 10, 21, 6, 13, 3, 11, 4 }, // process6
	{ 7, 46, 3, 41, 12, 42, 8, 21, 4, 32, 6, 19, 12, 33, 10, 0, 0, 0, 0 }, // process7
	{ 6, 14, 7, 33, 8, 51, 9, 63, 10, 87, 11, 74, 8, 0, 0, 0, 0, 0, 0}, // process8
	{ 4, 32, 5, 40, 6, 29, 4, 21, 5, 44, 6, 24, 4, 31, 5,33, 6, 0, 0 } }; // process9


	deque<int> burst[10], iotime[10], remainio[10];

	// init burst and iotime
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 19; j = j + 2)
		{
			if (ps[i][j] != 0)
			{
				burst[i].push_back(ps[i][j]);
				iotime[i].push_back(ps[i][j + 1]);
				remainio[i].push_back(ps[i][j + 1]);
			}
		}
	}


	// process in ready queue and io queue
	deque<int> ready, io, dequeue;
	for (int i = 1; i < 10; i++)
	{
		ready.push_back(i);
	}
	int currTime = 0;
	int currBurst = 0;
	int passTime = 0;
	int running; // running process
	int runningBurst = 0; // burst time of running process 
	int runningIO; // I/O time of running process

	int count = 0;
	while (ready.size() != 0 || io.size() != 0)
	{
		std::cout << "Current Time: " << currTime << endl;
		// Get a running process from theready queue
		if (ready.empty())
		{
			std::cout << "Ready queue empty\n";
		}
		else {
			running = ready.front(); ready.pop_front();
		}

		// Get burstime of a running process
		runningBurst = burst[running].front(); burst[running].pop_front();


		// Get iotime of a running process
		if (iotime[running].size() > 0) {
			runningIO = iotime[running].front(); iotime[running].pop_front();
		}
		// Shown running process
		std::cout << "\nNow running: P" << running << endl;
		std::cout << "..................................................\n" << endl;
		// Show the processes in ready queue along with their burst and I/O time
		std::cout << "Ready Queue: Process Burst" << endl;

		for (int i = 0; i < ready.size(); i++)
		{
			int rp = ready.at(i);
			int burstTime = burst[rp].front();
			std::cout << "             P" << rp << "      " << burstTime << endl;
		}
		// Show IO queue
		std::cout << "Now in I/O:  Process Remaining I/O time" << endl;

		if (io.size() == 0)
			std::cout << "             [empty]" << endl;
		else
		{
			for (int i = 0; i < io.size(); i++)
			{
				int iop = io.at(i);
				if (remainio[iop].size() > 0) {
					int remainTime = remainio[iop].front(); //
					std::cout << "             P" << iop << "      " << remainTime << endl;
				}
			}
		}

		// update ready queue, I/O queue
		// for each process in I/O queue, update the remaining I/O time
		// if remain time is < 0, push a new process in ready

		int size = io.size();

		for (int i = 0; i < size; i++)
		{
			int iop = io.front(); io.pop_front();
			int remainTime = remainio[iop].front(); remainio[iop].pop_front();//
			remainTime -= runningBurst;

			if (remainTime > 0) // still in I/O queue
			{
				io.push_back(iop);
				remainio[iop].push_front(remainTime);
			}
			else // push new process in ready queue
			{
				ready.push_back(iop);
			}
		}
		std::cout << "\n.................................................." << endl;
		std::cout << "..................................................\n" << endl;
		// push running process to I/O queue
		io.push_back(running);

		// update current time
		currTime += runningBurst;
	}
	for (int i = 0; i < 9; i++) 
	{
	    p[i].total_btime += p[i].btime;
		p[i].start_time = (i == 0) ? p[i].arrival_time : max(p[i - 1].completion_time, p[i].arrival_time);
		p[i].completion_time = p[i].start_time + p[i].btime;
		p[i].tatime = p[i].completion_time;
		p[i].wtime = p[i].tatime - p[i].total_btime;
		p[i].tatime = p[i].completion_time;
		p[i].rtime = p[i].start_time;

		total_tatime += p[i].tatime;
		total_wtime += p[i].wtime;
		total_rtime += p[i].rtime;
		total_itime += (i == 0) ? (p[i].arrival_time) : (p[i].start_time - p[i - 1].completion_time);
	}

	tatime_avg = (float)total_tatime / 9;
	wtime_avg = (float)total_wtime / 9;
	rtime_avg = (float)total_rtime / 9;
	cpu_utilization = ((p[8].completion_time - total_itime) / (float)p[8].completion_time) * 100;

	cout << "#P\t" << "RT\t" << "WT\t" << "TAT\t" << "\n" << endl;

	for (int i = 1; i < 10; i++) {
		cout << p[i].pid << "\t"
			<< "\t" << p[i].tatime << "\t"
			<< p[i].wtime << "\t" << p[i].rtime << "\t" << "\n" << endl;
	}

	//Display the times and CPU utilization

	std::cout << "Average Response: " << rtime_avg << endl;

	std::cout << "Average Turnaround Time = " << tatime_avg << endl;

	std::cout << "Average Waiting Time = " << wtime_avg << endl;

	std::cout << "CPU Utilization = " << cpu_utilization << "%" << endl;

	return 0;
}
