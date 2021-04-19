/**
 * A simplified version of Anytime Frenet Planner we had
 * 
 */ 

#include <mutex>
#include <thread>
#include <vector>

using namespace std;


class AnytimeFrenetPlanner{
public:
    AnytimeFrenetPlanner();  // simplified, no arg
    ~AnytimeFrenetPlanner();
    
    void asyncPlan(); // for start planning
    void stopPlanning(); // for stop planning

    double getBestPath(); // modified here, just return the value
    // instead having a full Frenet Path object here, let's just see if it works  

private:
    mutex *mu;
    bool run_workers;
    vector<thread *> threads;
    void calc_path_cost();
    vector<double> frenet_paths_cost;
// private methods and data not included for now
};