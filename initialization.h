#ifndef __INITIALIZATION_H
#define __INITIALIZATION_H


#define V_NUMBER 10
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>


typedef std::vector<std::vector<std::vector <int> > > vvvi;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;
typedef std::vector<unsigned int> vui;

//初始化位置坐标
void initialize_position(float V_position[V_NUMBER][2], float distribution_length);
//打印位置坐标
void print_positon(float V_position[V_NUMBER][2]);
//初始化坐标的权重
void initialize_weight(float V_weight[V_NUMBER],float weight_range);
//打印权重的内容
void print_weight(float V_weight[V_NUMBER]);
//初始化干扰图的内容
void initialize_V_graph(int V_graph[V_NUMBER][V_NUMBER], float V_position[V_NUMBER][2], float distance_limit);
//打印干扰图的内容
void print_V_graph(int V_graph[V_NUMBER][V_NUMBER]);
//初始化相邻边的内容
void initialize_V_neighbor(vvi& v_neighbor, int V_graph[V_NUMBER][V_NUMBER]);
//打印邻居变量
void print_V_neighbor(vvi v_neighbor);
//初始化所有的内容
void initialize_all(float V_position[V_NUMBER][2], float distribution_length,float V_weight[V_NUMBER],float weight_range,
                    int V_graph[V_NUMBER][V_NUMBER],float distance_limit,vvi& v_neighbor);


#endif
