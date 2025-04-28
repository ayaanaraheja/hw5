#ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please

#endif

#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;

// Add prototypes for any helper functions here
bool helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& worked,
    size_t day
);

// Add your implementation of schedule() and other helper functions here
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.empty()) {
        return false;
    }
    
    sched.clear();
    size_t n = avail.size(); // days
    sched.resize(n);
    vector<size_t> worked(avail[0].size(), 0);

    return helper(avail, dailyNeed, maxShifts, sched, worked, 0);
}

bool helper( // usc schedule helper lol
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<size_t>& worked,
    size_t day
)
{
    if (day >= avail.size()) { return true; }

    if (sched[day].size() == dailyNeed) {
        return helper(avail, dailyNeed, maxShifts, sched, worked, day + 1);
    }

    size_t numWorkers = avail[0].size();

    for (size_t worker = 0; worker < numWorkers; ++worker) {
        if (!avail[day][worker]) { continue; }

        if (find(sched[day].begin(), sched[day].end(), worker) != sched[day].end()) { continue; }

        if (worked[worker] >= maxShifts) { continue; }

        sched[day].push_back(worker);
        worked[worker]++;

        if (helper(avail, dailyNeed, maxShifts, sched, worked, day)) {
            return true;
        }

        worked[worker]--; // backtrack
        sched[day].pop_back();
    }
    return false;
}
