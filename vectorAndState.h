#ifndef __VECTORANDSTATE_H
#define __VECTORANDSTATE_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <vector>
#include<assert.h>
#include "initialization.h"
#define V_NUMBER 10
// #define TRU_H 10

typedef std::vector<std::vector<std::vector <int> > > vvvi;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;

//判断一个向量是否能满足指定干扰图的要求
bool judgment_Vector(vi a, int V_graph[V_NUMBER][V_NUMBER]);
//判断一个向量的状态是否能满足指定干扰图的要求
bool state_judgement(vi state, vi Node_all, int V_graph[V_NUMBER][V_NUMBER]);
//求向量集合的所有子集
vvi get_subsets(vi a);
//求所有满足协议内容的所有子集
vvi get_subsets_protocol(vi a, int V_graph[V_NUMBER][V_NUMBER]);
//从二维向量获取三维向量
vvvi get_subsets_3(vvi subsets);
//获取满足协议内容的三维数组
vvvi get_subsets_3_protocol(vvi subsets, int V_graph[V_NUMBER][V_NUMBER]);
//获取从数组中获取一个三维的数组来储存该状态
vvvi get_state_3(vvvi vec_3, vvi vec_2, int V_graph[V_NUMBER][V_NUMBER]);

/*---------------打印数据函数----------------*/
//打印输出这个二维的向量
void print_subsets(vvi subsets);
//打印三维向量的内容
void print_subsets_3(vvvi vec);


#endif
