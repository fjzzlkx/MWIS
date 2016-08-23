#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <iomanip>
#include "initialization.h"

using std::cout;
using std::endl;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;

//初始化位置坐标
void initialize_position(float V_position[V_NUMBER][2], float distribution_length){
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < 2; j++){
            V_position[i][j] =  rand() / ((double)(RAND_MAX)/distribution_length);
        }
    }
}
//打印位置坐标
void print_positon(float V_position[V_NUMBER][2]){
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < 2; j++){
            cout << V_position[i][j] << ' ';
        }
        cout << endl;
    }
}

//初始化坐标的权重
void initialize_weight(float V_weight[V_NUMBER],float weight_range){
    for(int i = 0; i < V_NUMBER; i++){
        V_weight[i] = rand() / ((double)(RAND_MAX)/weight_range);
    }
}
//打印权重的内容
void print_weight(float V_weight[V_NUMBER]){
    for(int i = 0; i < V_NUMBER; i++){
        cout << V_weight[i] << ' ';
    }
    cout << endl;
}

//初始化干扰图的内容
void initialize_V_graph(int V_graph[V_NUMBER][V_NUMBER], float V_position[V_NUMBER][2], float distance_limit){
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < V_NUMBER; j++){
            float temp = pow(V_position[i][1] - V_position[j][1], 2) + pow(V_position[i][2] - V_position[j][2], 2);
            if(i != j && temp <= pow(distance_limit, 2)) {
                V_graph[i][j] = 1;
            } else {
                V_graph[i][j] = 0;
            }
        }
    }
}
//打印干扰图的内容
void print_V_graph(int V_graph[V_NUMBER][V_NUMBER]){
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < V_NUMBER; j++){
            cout << V_graph[i][j] << ' ';
        }
        cout << endl;
    }
    cout << endl;
}
//初始化相邻边的内容
void initialize_V_neighbor(vvi& v_neighbor, int V_graph[V_NUMBER][V_NUMBER]){
    for(int i = 0; i < V_NUMBER; i++){
        v_neighbor[i].push_back(i);
        for(int j = 0; j < V_NUMBER; j++){
            if(V_graph[i][j] == 1) {
                v_neighbor[i].push_back(j);
            }
        }
    }
}
//打印邻居变量
void print_V_neighbor(vvi v_neighbor){
    for(unsigned int i = 0; i < v_neighbor.size(); ++i){
        vi subset = v_neighbor.at(i);
        for(unsigned int j = 0; j < subset.size(); ++j){
            cout << subset.at(j) << " ";
        }
        cout << endl;
    }
}
//初始化所有的内容
void initialize_all(float V_position[V_NUMBER][2], float distribution_length,float V_weight[V_NUMBER],float weight_range,
                    int V_graph[V_NUMBER][V_NUMBER],float distance_limit,vvi& v_neighbor){
    srand(time(0));
    initialize_position(V_position, distribution_length);
    initialize_weight(V_weight, weight_range);
    initialize_V_graph(V_graph, V_position, distance_limit);
    initialize_V_neighbor(v_neighbor, V_graph);
}
