#include <chrono>
using namespace std::chrono;

auto timerStart(void) {
    auto start = high_resolution_clock::now();
    return start;
}

void timerEnd(auto& start) {
    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Elapsed time: " << duration.count() << " us" << std::endl;
}