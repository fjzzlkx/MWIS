#ifndef __PRORTOCOL_H
#define __PRORTOCOL_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include <assert.h>
#include "vectorAndState.h"
#include "initialization.h"

typedef std::vector<std::vector<std::vector <int> > > vvvi;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;
typedef std::vector<unsigned int> vui;
typedef std::vector<float> vf;
typedef std::vector<std::vector<float> > vvf;

//寻找一个数字在向量里面的位置
int index_of_num(vi a, int num);
//组合两个集合的节点
vi combination_Node(vi Node_1,vi Node_2);
//组合两个集合的状态
vvi combination_state(vvi Node_state_1, vi Node_1, vvi Node_state_2, vi Node_2, int V_graph[V_NUMBER][V_NUMBER]);
//把一个状态向量转换成Node
vi state_to_Node(vi state, vi Node);
//求一个Node集合的权重
float compute_weigh(vi Node, float V_weight[V_NUMBER]);
//求一个Node在state状态下的权重
float compute_weigh_state(vi state, vi Node, float V_weight[V_NUMBER]);
//求出state vector 对应的 weight vector
vf compute_weigh_state_vector(vvi state_vector, vi Node, float V_weight[V_NUMBER]);
//下调堆  用于下一步的GetTopk
void AdjustDown(float *a, unsigned int *index, unsigned int root, unsigned int size);
//获取最大的K个数的下标
vui GetTopk(const vf& weight, const vui& index, unsigned int n, unsigned int k);
//获取下一次的状态
vvvi get_next_Q_Solution_protocol_state(vvvi current_Q_Solution_protocol_state, vvi v_neighbor,vvi current_Node_set, int V_graph[V_NUMBER][V_NUMBER]);
//获取下一次的包含节点集
vvi get_next_Node_set(vvi v_neighbor, vvi current_Node_set);
//在截断值为H的情况下，获取下一时刻的状态值
vvvi get_next_Q_state_trH(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi v_neighbor,vvi current_Node_set, int V_graph[V_NUMBER][V_NUMBER],unsigned int H);
//获取最大的weight 三维的形式  数组只是2维的vector但是这里用三维存储了
vvvi get_max_weight(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi current_Node_set);
//获取每个节点上最大的weight 2维的形式，但是担心为空的时候会出现错误
vvi get_max_weight_vvi(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi current_Node_set);
//获取最大的数值
float numberOfmax(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi current_Node_set);


#endif
