#include <iostream>
#include <thread>
#include <atomic>
#include <vector>
#include <random>
#include <chrono>
#include <cmath>
#include <iomanip>
#include <omp.h>
using namespace std;
using Time = std::chrono::high_resolution_clock::time_point;
using Clock = std::chrono::high_resolution_clock;
using Duration = std::chrono::duration<float>;

void random_work(const int seed) {
/*
   Given a range of integers from 0 to number_count, use random number generation to fill a vector until all numbers within range are generated.
   Do not allow duplicate numbers.
   Fun fact: the function is inefficient on purpose.
*/
	const int number_count = 5'000;
	mt19937 rand(seed);
    uniform_int_distribution<int> dist(0, number_count - 1);
	vector<int> number_vector;
	while (number_vector.size() < number_count) {
		int rand_num = dist(rand);
		bool is_duplicate = false;
		for (int i = 0; i < number_vector.size(); i++) {
			if (number_vector.at(i) == rand_num) is_duplicate = true;
		}
		if (!is_duplicate) number_vector.push_back(rand_num);
	}
}

Duration get_duration(Time start_time) {
/*
   Helper function to quickly access duration because chrono is painful.
*/
	return Clock::now() - start_time;
}

int main(int argc, char* argv[]) {
	// Init
	cout << fixed << setprecision(3);
	vector<thread> thread_vector;
	int thread_count = 0;
	int seed = 0;
	try {
		if (argc > 1) seed = stoi(argv[1]);
	} catch (...) {
		cout << "The argument must be a number." << endl;
		return 1;
	}

	// OpenMP
	Time start_time = Clock::now();
	#pragma omp parallel 
	{
		#pragma omp single
		{
			thread_count = omp_get_num_threads();
		}
		random_work(seed);
	}
	float openmp_time = get_duration(start_time).count();
	cout << "OpenMP:  " << openmp_time << " s" << endl;

	// Threads
	start_time = Clock::now();
	for (int i = 0; i < thread_count; i++) {
		thread_vector.push_back(thread(random_work, seed));
	}
	for (int i = 0; i < thread_count; i++) {
		thread_vector.at(i).join();
	}
	float thread_time = get_duration(start_time).count();
	cout << "Threads: " << thread_time << " s" << endl << endl;

	// Summary
	if (thread_time < openmp_time) cout << "Threads is faster than OpenMP by ";
	else cout << "OpenMP is faster than Threads by ";
	float difference = fabs(thread_time - openmp_time) * 1000.0f;
	if (difference < 1.0f) cout << "less than one millisecond!" << endl;
	else cout << static_cast<int>(difference) << " ms" << endl;
	return 0;
}
