#include "AnytimeFrenetPlanner.h"
#include <mutex>
#include <thread>
#include <unistd.h>
#include <stdio.h> 
#include <math.h> 

using namespace std;


AnytimeFrenetPlanner::AnytimeFrenetPlanner() {
    run_workers = false;
    printf("AnytimeFrenetPlanner: Planner Initiated\n");
    mu = new mutex();
};

AnytimeFrenetPlanner::~AnytimeFrenetPlanner() {
    printf("AnytimeFrenetPlanner: Planner Destructed\n");
}
    
void AnytimeFrenetPlanner::asyncPlan() {
    run_workers = true;
    printf("AnytimeFrenetPlanner: Async Planning Started, Workers start working\n");

    threads.push_back(new thread(
                &AnytimeFrenetPlanner::calc_path_cost, this));
    threads.push_back(new thread(
                &AnytimeFrenetPlanner::calc_path_cost, this));    
}

void AnytimeFrenetPlanner::stopPlanning() {
    printf("AnytimeFrenetPlanner: Stop Planning\n");
    run_workers = false;
     // wait for all threads to finish computation    
    for (auto &t : threads) {
        t->join();
        delete t;
    }
    printf("Worker Threads Cleared\n");
    threads.clear();    
};

double AnytimeFrenetPlanner::getBestPath() {
    printf("AnytimeFrenetPlanner: Get Best Path\n");

    mu->lock();
    // select the best path
    double mincost = INFINITY;
    // for (double fpc : frenet_paths_cost) {
    //     if (fpc < mincost) 
    //         mincost = fpc;
    // }

    vector<double>::iterator it = frenet_paths_cost.begin();
    while (it != frenet_paths_cost.end()) {
        if (*it < mincost) {
            mincost = *it;
            ++it;
        } else {
            it = frenet_paths_cost.erase(it);
        }
    }

    
    mu->unlock();
    return mincost;
};

void AnytimeFrenetPlanner::calc_path_cost() {
    double cost = 100000.0; // for demonstrations
    while (run_workers) { 
        cost -= 0.05;
        mu->lock();
        frenet_paths_cost.push_back(cost);
        mu->unlock();        
        usleep(300000); // every 0.3 seconds
    }
}
