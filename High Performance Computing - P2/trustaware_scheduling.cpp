#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <fstream>
#include <ctime> 
using namespace std;

// Define constants
const double BASE = 3.0; // Base value for cost calculation
const double BR = 10.0;   // Brand constant for cost calculation
const double K = 10.0;    // Constant for relative deadline calculation
double dtDatadeno=40.0,dtDatanumo=20.0;

// Define structures for task and Fog node
struct Task {
    int id;                 // Task ID
    double arrivalTime;     // Arrival time of the task
    double executionTime;   // Execution time of the task
    int userId;             // User ID associated with the task
    double deadline;        // Deadline of the task
    double reliabilityRequirement;  // Reliability requirement of the task
};
// struct user{
//     int userid;
// };

struct FogNode {
    int id;                     // Node ID
    double sharedTrust;         // Shared trust value of the node
    vector<double> directTrust; // Direct trust values from each user
    vector<pair<double,double>> dTData;   //assuming dtData.first as total tasks and second as succesful tasks for each user
    double cost;                // Cost of unit execution time on the node
    double failureRate;         // Failure rate of the node
};

// Function to update shared trust of a Fog node
void updateSharedTrust(FogNode &node) {
    double sumDirectTrust = 0.0;
    for (double trust : node.directTrust) {
        sumDirectTrust += trust;
    }
    node.sharedTrust = sumDirectTrust / node.directTrust.size();
}
// double updateDirectTrust(bool ok) {
//     if(ok)
//     {
//         dtn
//         return 
//     }
// }
// Function to calculate cost of executing a task on a Fog node
double calculateCost(const FogNode &node) {
    return BASE + BR * pow(node.sharedTrust, 2);
}

// Function to check if a task meets reliability requirement
bool meetsReliabilityRequirement(const Task &task, const FogNode &node) {
    return node.directTrust[task.userId-1] >= task.reliabilityRequirement;

}

// Function to find the best node for task execution based on cost and reliability
int findBestNode(const Task &task, const vector<FogNode> &nodes) {
    double minCost = numeric_limits<double>::max();
    int bestNode = -1;
    for (int i = 0; i < nodes.size(); ++i) {
        if (nodes[i].cost < minCost && meetsReliabilityRequirement(task, nodes[i])) {
            minCost = nodes[i].cost;
            bestNode = i;
        }
    }
    return bestNode;
}


// Function to schedule tasks on Fog nodes
void scheduleTasks(vector<Task> &tasks, vector<FogNode> &nodes) {
    double costi=0;
    // vector<double>rnd(tasks.size());
    // for(auto & r:rnd){
    //     r=(rand() % 10)/10.0;
    //     cout<<r<<" ";
    // }
    srand(time(nullptr));
     double a;
    for (Task &task : tasks) {
        int bestNode = findBestNode(task, nodes);
        if (bestNode != -1) {
            // Task can be executed on the best node
            // cout << "Task " << task.id+1 << " scheduled on Fog node " << nodes[bestNode].id << endl;
            // Update shared trust and cost of the node
            a=(rand()%10)/10.00;
            cout<<a<<endl;
            double sucessrate = exp(-nodes[bestNode].failureRate * task.executionTime);
            if(a<=sucessrate){
                nodes[bestNode].dTData[task.userId-1].first++;
                nodes[bestNode].dTData[task.userId-1].second++;
                nodes[bestNode].directTrust[task.userId-1]=(nodes[bestNode].dTData[task.userId-1].second)/(nodes[bestNode].dTData[task.userId-1].first);
                updateSharedTrust(nodes[bestNode]);
                costi+=calculateCost(nodes[bestNode]);
                 cout << "Task " << task.id+1 << " sucessfully scheduled on Fog node " << nodes[bestNode].id << endl;
                 cout << "New direct reliblity of user:"<<task.userId<<" is:"<<nodes[bestNode].directTrust[task.userId-1]<< endl;
            }else{
                nodes[bestNode].dTData[task.userId-1].first++;
                //nodes[bestNode].dTData[task.userId-1].second++;
                nodes[bestNode].directTrust[task.userId-1]=(nodes[bestNode].dTData[task.userId-1].second)/(nodes[bestNode].dTData[task.userId-1].first);; 
                updateSharedTrust(nodes[bestNode]);
                costi+=1; 
                 cout << "Task " << task.id+1 << " Not scheduled on Fog node (faliur in execution) " << nodes[bestNode].id << endl; 
                  cout << "New direct reliblity of user:"<<task.userId<<" is:"<<nodes[bestNode].directTrust[task.userId-1]<< endl;
            }
            
            nodes[bestNode].cost = calculateCost(nodes[bestNode]);
            
        } else {
            cout << "Task " << task.id+1 << " cannot be scheduled due to reliability requirement not met." << endl;
        }
    }
    cout<<"Total cost is :"<<costi;
}



int main() {
    // Input processing
    // int numTasks, numNodes, numUsers;
    // cout << "Enter the number of Users: ";
    // cin >> numUsers;
    // cout << "Enter the number of tasks: ";
    // cin >> numTasks;
    // vector<Task> tasks(numTasks);
    // for (int i = 0; i < numTasks; ++i) {
    //     cout << "Enter details for task " << i + 1 << ":\n";
    //     Task task;
    //     task.id = i;
    //     cout << "Arrival time: ";
    //     cin >> task.arrivalTime;
    //     cout << "Execution time: ";
    //     cin >> task.executionTime;
    //     cout << "User ID: ";
    //     cin >> task.userId;
    //     cout << "Reliability requirement: ";
    //     cin >> task.reliabilityRequirement;
    //     task.deadline = task.arrivalTime + K;
    //     tasks[i] = task;
    // }

    // cout << "Enter the number of Fog nodes: ";
    // cin >> numNodes;
    // vector<FogNode> nodes(numNodes);
    // for (int i = 0; i < numNodes; ++i) {
    //     cout << "Enter details for Fog node " << i + 1 << ":\n";
    //     FogNode node;
    //     node.id = i;
    //     node.sharedTrust = 0.5;// Initially set to 0.5
    //     node.cost=BASE + BR * pow(node.sharedTrust, 2); 
    //     node.directTrust.resize(numUsers, 0.5); // Initially set to 0.5 for all users
    //     cout << "Failure rate: ";
    //     cin >> node.failureRate;
    //     nodes[i] = node;
    // }

    // // Schedule tasks
    // scheduleTasks(tasks, nodes);

    //  ifstream inputFile("input.txt"); // Open the input file
    ifstream inputFile("input.txt");
    if (!inputFile) {
        cerr << "Error: Unable to open input file!" << endl;
        return 1;
    }

    // Input processing
    int numUsers, numTasks, numNodes;
    inputFile >> numUsers;
    inputFile >> numTasks;
    vector<Task> tasks(numTasks);
    for (int i = 0; i < numTasks; ++i) {
        Task task;
        inputFile >> task.arrivalTime >> task.executionTime >> task.userId >> task.reliabilityRequirement;
        task.id = i;
        task.deadline = task.arrivalTime + K;
        tasks[i] = task;
    }

    inputFile >> numNodes;
    vector<FogNode> nodes(numNodes);
    for (int i = 0; i < numNodes; ++i) {
        FogNode node;
        inputFile >> node.failureRate;
        node.id = i;
        node.sharedTrust = 0.5; // Initially set to 0.5
        node.cost = BASE + BR * pow(node.sharedTrust, 2);
        node.directTrust.resize(numUsers, 0.5); // Initially set to 0.5 for all users
        node.dTData.resize(numUsers, {dtDatadeno, dtDatanumo});
        nodes[i] = node;
    }

    // Schedule tasks
    scheduleTasks(tasks, nodes);

    inputFile.close(); // Close the input file
    return 0;

    return 0;
}
