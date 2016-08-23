#include <time.h>
#include <vector>
#include "vectorAndState.h"
#include "protocol.h"
#include "initialization.h"
// #include <assert.h>
// #include <stdlib.h>
// #include <iostream>
// #include <stdio.h>
// #include <math.h>
// #include <fstream>
// #include <iomanip>
// using namespace std;
// using std::cout;
// using std::endl;
using std::swap;
typedef std::vector<std::vector<std::vector <int> > > vvvi;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;
typedef std::vector<unsigned int> vui;
typedef std::vector<float> vf;
typedef std::vector<std::vector<float> > vvf;

//寻找一个数字在向量里面的位置
int index_of_num(vi a, int num){
     int index = -1;
     for(unsigned i = 0; i < a.size(); i++){
         if(a[i] == num) {
             index = i;
             break;
         }
     }
     return index;
 }
//组合两个集合的节点
vi combination_Node(vi Node_1,vi Node_2){
     vi Node_combination = Node_1;
     for(unsigned i = 0; i < Node_2.size(); i++){
         if(index_of_num(Node_1, Node_2[i]) == -1){
             Node_combination.push_back(Node_2[i]);
         }
     }
     return Node_combination;
 }
//组合两个集合的状态
vvi combination_state(vvi Node_state_1, vi Node_1, vvi Node_state_2, vi Node_2, int V_graph[V_NUMBER][V_NUMBER]){
    vi Node_combination = Node_1;
    vi Node_not_repeat;
    vi Node_repeat;
    for(unsigned i = 0; i < Node_2.size(); i++){
        if(index_of_num(Node_1, Node_2[i]) == -1){
            Node_combination.push_back(Node_2[i]);
            Node_not_repeat.push_back(Node_2[i]);
        } else {
            Node_repeat.push_back(Node_2[i]);
        }
    }
    unsigned num_of_repeat = Node_repeat.size();
    unsigned Node_repeat_index[num_of_repeat][2];
    vvi state_combination;
    for(unsigned i = 0; i < num_of_repeat; i++){
        Node_repeat_index[i][0] = index_of_num(Node_1,Node_repeat[i]);
        Node_repeat_index[i][1] = index_of_num(Node_2,Node_repeat[i]);
    }
    vui not_repeat_index;
    for(unsigned i = 0; i < Node_not_repeat.size(); i++){
        unsigned temp_index = (unsigned)index_of_num(Node_2,Node_not_repeat[i]);
        not_repeat_index.push_back(temp_index);
    }

    //state_combination.push_back(vector<int>());
    for(unsigned i = 0; i < Node_state_1.size(); i++){
        for(unsigned j = 0; j < Node_state_2.size(); j++){
            bool compatible = true;
            for(unsigned m = 0; m < num_of_repeat; m++){
                bool temp = Node_state_1[i][Node_repeat_index[m][0]] == Node_state_2[j][Node_repeat_index[m][1]];
                //cout << temp << "------" << endl;
                compatible = compatible && temp;
            }
            if(compatible == true){
                vi state = Node_state_1[i];
                for(unsigned n = 0; n < not_repeat_index.size(); n++){
                    state.push_back(Node_state_2[j][not_repeat_index[n]]);
                }
                bool judgment = state_judgement(state,Node_combination,V_graph);
                if(judgment) state_combination.push_back(state);
            }
        }
    }
    return state_combination;
}
//把一个状态向量转换成Node
vi state_to_Node(vi state, vi Node){
    vi stateToNode;
    for(unsigned int i = 0; i < Node.size(); i++){
        if(state.at(i) == 1){
            stateToNode.push_back(Node.at(i));
        }
    }
    return stateToNode;
}
//求一个Node集合的权重
float compute_weigh(vi Node, float V_weight[V_NUMBER]){
    float sum = 0.0;
    for(unsigned int i = 0; i < Node.size(); i++){
        sum += V_weight[Node.at(i)];
    }
    return sum;
}
//求一个Node在state状态下的权重
float compute_weigh_state(vi state, vi Node, float V_weight[V_NUMBER]){
    float sum = 0.0;
    for(unsigned int i = 0; i < Node.size(); i++){
        if(state.at(i) == 1){
            sum += V_weight[Node.at(i)];
        }
    }
    return sum;
}

/*------找出前要截断的H个数据-------*/
//找出前H个数据的，及他们的下标
//将合并后的数组替换成截断后的这些
//求出state vector 对应的 weight vector
vf compute_weigh_state_vector(vvi state_vector, vi Node, float V_weight[V_NUMBER]){
    vf weight_state_vector;
    for(unsigned int i = 0; i < state_vector.size(); i++){
        float weight_state_I = compute_weigh_state(state_vector.at(i), Node, V_weight);
        weight_state_vector.push_back(weight_state_I);
    }
    return weight_state_vector;
}
//下调堆
void AdjustDown(float *a, unsigned int *index, unsigned int root, unsigned int size){ //下调//小堆
    unsigned int parent = root;
    unsigned int child = parent * 2 + 1;
    while (child < size){
        if (child + 1 < size && a[child] > a[child + 1]){
            ++child;
        }
        if (a[parent] > a[child]){
            swap(a[parent], a[child]);
            swap(index[parent], index[child]);//   fjzzlkx 交换下标
            parent = child;
            child = parent * 2 + 1;
        } else { //注意不满足交换条件时跳出本次循环
            break;
        }
    }
}
//获取最大的K个数的下标
vui GetTopk(const vf& weight, const vui& index, unsigned int n, unsigned int k){ //N个数中找最大的前k个数--小堆实现
    //assert(n > k);
    if(n <= k){
        // cout << "n <= k" << endl;
        return index;
    }
    float *TopkArray = new float[k];//通过前k个元素建立含有k个元素的堆
    unsigned int *TopkIndexArray = new unsigned int [k];
    for (unsigned int i = 0; i < k; i++){
        TopkArray[i] = weight[i];
        TopkIndexArray[i] = index[i];
    }
    for (int i = (k - 2) / 2; i >= 0; --i){ //建小堆
        AdjustDown(TopkArray, TopkIndexArray, i, k);
    }
    //从第k个元素开始到第n个元素分别与堆顶元素进行比较，较大数据入堆顶，再对整个堆进行下调，使堆顶存放最小元素（小堆）
    for (unsigned int i = k; i < n; ++i){
        if (weight[i]  > TopkArray[0]){
            TopkArray[0] = weight[i];
            TopkIndexArray[0] = index[i];
            AdjustDown(TopkArray, TopkIndexArray, 0, k);
        }
    }
    delete[] TopkArray;//注意释放TopkArray所占的内存
    TopkArray = NULL;
    vui return_index_vector;
    for(unsigned int i = 0; i < k; ++i){
        return_index_vector.push_back(TopkIndexArray[i]);
    }
    delete[] TopkIndexArray;
    TopkIndexArray = NULL;
    return return_index_vector;
}

//获取下一个状态
vvvi get_next_Q_Solution_protocol_state(vvvi current_Q_Solution_protocol_state, vvi v_neighbor,vvi current_Node_set, int V_graph[V_NUMBER][V_NUMBER]){
    vvvi next_Q_Solution_protocol_state;
    for(unsigned int i =0; i < V_NUMBER; i++){
        vvi next_Node_state = current_Q_Solution_protocol_state.at(i);
        vi next_Node = current_Node_set.at(i);
        for(unsigned int j = 0; j < v_neighbor.at(i).size(); j++){
            next_Node_state = combination_state(next_Node_state, next_Node,
                                                current_Q_Solution_protocol_state.at(v_neighbor.at(i).at(j)), current_Node_set.at(v_neighbor.at(i).at(j)),
                                                V_graph);
            next_Node = combination_Node(next_Node, current_Node_set.at(v_neighbor.at(i).at(j)));
        }
        next_Q_Solution_protocol_state.push_back(next_Node_state);
    }
    return next_Q_Solution_protocol_state;
}
//获取下一次包含节点集
vvi get_next_Node_set(vvi v_neighbor, vvi current_Node_set){
    vvi next_Node_set;
    for(unsigned int i =0; i < V_NUMBER; i++){
        vi next_Node_i = current_Node_set.at(i);
        for(unsigned int j = 0; j < v_neighbor.at(i).size(); j++){
            next_Node_i = combination_Node(next_Node_i, current_Node_set.at(v_neighbor.at(i).at(j)));
        }
        next_Node_set.push_back(next_Node_i);
    }
    return next_Node_set;
}
vvvi get_next_Q_state_trH(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi v_neighbor,vvi current_Node_set, int V_graph[V_NUMBER][V_NUMBER],unsigned int H){
    vvvi next_Q_Solution_protocol_state;
    for(unsigned int i =0; i < V_NUMBER; i++){
        vvi next_Node_state = current_Q_Solution_protocol_state.at(i);
        vi next_Node = current_Node_set.at(i);
        for(unsigned int j = 0; j < v_neighbor.at(i).size(); j++){
            next_Node_state = combination_state(next_Node_state, next_Node,
                                                current_Q_Solution_protocol_state.at(v_neighbor.at(i).at(j)), current_Node_set.at(v_neighbor.at(i).at(j)),
                                                V_graph);
            next_Node = combination_Node(next_Node, current_Node_set.at(v_neighbor.at(i).at(j)));
        }
        vui state_index_vector;
        for(unsigned int j = 0; j < next_Node_state.size(); j++){
            state_index_vector.push_back(j);
        }
        //vf weigh_state_vector = compute_weigh_state_vector(test_vvi, Node0, V_weight);
        vf weigh_state_vector = compute_weigh_state_vector(next_Node_state, next_Node, V_weight);
        vui topk_index = GetTopk(weigh_state_vector,state_index_vector,state_index_vector.size(),H);
        vvi next_Node_state_trH;
        for(unsigned int j = 0; j < topk_index.size(); j++){
            next_Node_state_trH.push_back(next_Node_state.at(topk_index.at(j)));
        }
        // if(next_Node_state_trH.size() != 0){
        //     next_Q_Solution_protocol_state.push_back(next_Node_state_trH);
        // }
        next_Q_Solution_protocol_state.push_back(next_Node_state_trH);
    }
    return next_Q_Solution_protocol_state;
}
vvvi get_max_weight(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi current_Node_set){
    vvvi max_state;
    for(unsigned int i =0; i < V_NUMBER; i++){
        vvi next_Node_state = current_Q_Solution_protocol_state.at(i);
        vi next_Node = current_Node_set.at(i);
        vui state_index_vector;
        for(unsigned int j = 0; j < next_Node_state.size(); j++){
            state_index_vector.push_back(j);
        }
        vf weigh_state_vector = compute_weigh_state_vector(next_Node_state, next_Node, V_weight);
        vui topk_index = GetTopk(weigh_state_vector,state_index_vector,state_index_vector.size(),1);
        vvi next_Node_state_trH;
        for(unsigned int j = 0; j < topk_index.size(); j++){
            next_Node_state_trH.push_back(next_Node_state.at(topk_index.at(j)));
        }
        max_state.push_back(next_Node_state_trH);
    }
    return  max_state;
}
float numberOfmax(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi current_Node_set){
    vvvi max_state;
    for(unsigned int i =0; i < V_NUMBER; i++){
        vvi next_Node_state = current_Q_Solution_protocol_state.at(i);
        vi next_Node = current_Node_set.at(i);
        vui state_index_vector;
        for(unsigned int j = 0; j < next_Node_state.size(); j++){
            state_index_vector.push_back(j);
        }
        vf weigh_state_vector = compute_weigh_state_vector(next_Node_state, next_Node, V_weight);
        vui topk_index = GetTopk(weigh_state_vector,state_index_vector,state_index_vector.size(),1);
        return weigh_state_vector.at(topk_index.at(0));
    }
    return  0;
}
vvi get_max_weight_vvi(float V_weight[V_NUMBER], vvvi current_Q_Solution_protocol_state, vvi current_Node_set){
    vvi max_state;
    for(unsigned int i =0; i < V_NUMBER; i++){
        vvi next_Node_state = current_Q_Solution_protocol_state.at(i);
        vi next_Node = current_Node_set.at(i);
        vui state_index_vector;
        for(unsigned int j = 0; j < next_Node_state.size(); j++){
            state_index_vector.push_back(j);
        }
        vf weigh_state_vector = compute_weigh_state_vector(next_Node_state, next_Node, V_weight);
        vui topk_index = GetTopk(weigh_state_vector,state_index_vector,state_index_vector.size(),1);
        vvi next_Node_state_trH;
        for(unsigned int j = 0; j < topk_index.size(); j++){
            next_Node_state_trH.push_back(next_Node_state.at(topk_index.at(j)));
        }
        max_state.push_back(next_Node_state_trH.at(0));
    }
    return  max_state;
}
