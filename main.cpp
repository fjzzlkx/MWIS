#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include<assert.h>

using namespace std;
#define V_NUMBER 50
#define TRU_H 10

typedef vector<vector<vector<int> > > vvvi;
typedef vector<vector<int> > vvi;
typedef vector<int> vi;
typedef vector<unsigned int> vui;
typedef vector<float> vf;
typedef vector<vector<float> > vvf;

//判断一个向量是否能满足指定干扰图的要求
bool judgment_Vector(vi a, int V_graph[V_NUMBER][V_NUMBER]){
    for(unsigned int i = 0; i < a.size(); i++){
        for(unsigned int j = i; j < a.size(); j++){
            if(V_graph[a[i]][a[j]] == 1) return false;
        }
    }
    return true;
}
////判断一个向量的状态是否能满足指定干扰图的要求
bool state_judgement(vi state, vi Node_all, int V_graph[V_NUMBER][V_NUMBER]){
    vi Node_vector;
    for(unsigned int i = 0; i < state.size(); i++){
        if(state.at(i) == 1) {
            Node_vector.push_back(Node_all.at(i));
        }
    }
    return judgment_Vector(Node_vector,V_graph);
}
//求集合的所有子集
vvi get_subsets(vector<int>  a){
    int n = a.size();
    vvi subsets;
    int max = 1<<n;
    for(int i=0; i<max; ++i){
        vi subset;
        int idx = 0;
        int j = i;
        while(j > 0){
            if(j&1){
                subset.push_back(a[idx]);
            }
            j >>= 1;
            ++idx;
        }
        subsets.push_back(subset);
    }
    return subsets;
}
//求所有满足协议内容的所有子集
vvi get_subsets_protocol(vector<int>  a, int V_graph[V_NUMBER][V_NUMBER]){
    vvi subsets;
    int n = a.size();
    int max = 1<<n;
    for(int i=0; i<max; ++i){
        vi subset;
        int idx = 0;
        int j = i;
        while(j > 0){
            if(j&1){
                subset.push_back(a[idx]);
            }
            j >>= 1;
            ++idx;
        }
        if(judgment_Vector(subset,V_graph)){
            subsets.push_back(subset);
        }
    }
    return subsets;
}
//打印输出这个二维的向量
void print_subsets(vvi subsets){
    for(unsigned i=0; i<subsets.size(); ++i){
        vi subset = subsets[i];
        for(unsigned j=0; j<subset.size(); ++j){
            cout<<subset[j]<<" ";
        }
        cout<<endl;
    }
}
//从二维向量获取三维向量
vvvi get_subsets_3(vvi subsets){ //O(n2^n)
    vvvi subsets_3;
    cout << "subsets.size() " << subsets.size() << endl;
    for(unsigned int i=0;i<subsets.size();i++){
        subsets_3.push_back(vector<vector<int> >());
        // vvi temp2  = get_subsets(subsets[i],subsets[i].size());
        vvi temp2  = get_subsets(subsets[i]);
        for(unsigned int m=0;m<temp2.size();m++){
            subsets_3[i].push_back(vector<int>());
            for(unsigned int n=0;n<temp2[m].size();n++){
                // cout << temp2[m][n] << "--";
                subsets_3[i][m].push_back(temp2[m][n]);
            }
        }
    }
    return subsets_3;
}
//获取满足协议内容的三维数组
vvvi get_subsets_3_protocol(vvi subsets, int V_graph[V_NUMBER][V_NUMBER]){
    vvvi subsets_3;
    cout << "subsets.size() " << subsets.size() << endl;
    for(unsigned int i=0;i<subsets.size();i++){
        subsets_3.push_back(vector<vector<int> >());
        vvi temp2  = get_subsets_protocol(subsets[i],V_graph);
        for(unsigned int m=0;m<temp2.size();m++){
            subsets_3[i].push_back(vector<int>());
            for(unsigned int n=0;n<temp2[m].size();n++){
                // cout << temp2[m][n] << "--";
                subsets_3[i][m].push_back(temp2[m][n]);
            }
        }
    }
    return subsets_3;
}
//打印三维向量的内容
void print_subsets_3(vvvi vec){
    for(unsigned int i=0;i<vec.size();i++){
        for(unsigned int j=0;j<vec[i].size();j++){
            std::cout<<"Vec "<<i<<" "<<j<<":  ";
            for(unsigned int k=0;k<vec[i][j].size();k++){
                cout << vec[i][j][k] << " ";
                // std::cout<<"Vec "<<i<<" "<<j<<" "<<k<<" == "<<vec[i][j][k]<<std::endl;
            }
            cout << endl;
        }
    }
}
//获取从数组中获取一个三维的数组来储存该状态
vvvi get_state_3(vvvi vec_3, vvi vec_2, int V_graph[V_NUMBER][V_NUMBER]){
    vvvi state_3;
    for(unsigned int i=0;i<vec_3.size();i++){
        state_3.push_back(vector<vector<int> >());
        for(unsigned int m=0;m<vec_3[i].size();m++){
            state_3[i].push_back(vector<int>());
            int state = 0;
            for(unsigned int n=0;n<vec_2[i].size();n++){
                // cout << temp2[m][n] << "--";
                // if(V_graph[i][m] == 1){
                //     state_3[i][m].push_back(1);
                // } else {
                //     state_3[i][m].push_back(0);
                // }

                for(unsigned int x = 0; x < vec_3[i][m].size(); x++){
                    if(vec_2[i][n] == vec_3[i][m][x]){
                        state = 1;
                        break;
                    }
                }
                state_3[i][m].push_back(state);
                state = 0;
            }
        }
    }
    return state_3;
}
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
//求一个Node集合的去权重
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

void AdjustDown(float *a, unsigned int *index, unsigned int root, unsigned int size){ //下调//小堆
    unsigned int parent = root;
    unsigned int child = parent * 2 + 1;
    while (child < size)
    {
        if (child + 1 < size && a[child] > a[child + 1])
        {
            ++child;
        }
        if (a[parent] > a[child])
        {
            swap(a[parent], a[child]);
            swap(index[parent], index[child]);//   fjzzlkx 交换下标
            parent = child;
            child = parent * 2 + 1;
        }
        else//注意不满足交换条件时跳出本次循环
        {
            break;
        }
    }
}
// void CreateRetPacket(vector<float>& weight, vector<unsigned int>& index){ //创建N个数
//     srand((unsigned int)time(NULL));
//     //srand(time(0));
//     weight.reserve(N);
//     for (unsigned int i = 0; i<N; i++)
//     {
//         weight.push_back(rand() % 1000);//产生N个随机值
//         index.push_back(i);
//     }
//     for (unsigned int i = K; i < N; ++i)
//     {
//         weight[i] *= 1;
//     }
// }
vector<unsigned int> GetTopk(const vector<float>& weight, const vector<unsigned int>& index, unsigned int n, unsigned int k)//N个数中找最大的前k个数--小堆实现
{
    assert(n>k);
    float *TopkArray = new float[k];//通过前k个元素建立含有k个元素的堆
    unsigned int *TopkIndexArray = new unsigned int [k];


    for (unsigned int i = 0; i < k; i++)
    {
        TopkArray[i] = weight[i];
        TopkIndexArray[i] = index[i];
    }
    for (int i = (k - 2) / 2; i >= 0; --i)//建小堆
    {
        AdjustDown(TopkArray, TopkIndexArray, i, k);
    }
    //从第k个元素开始到第n个元素分别与堆顶元素进行比较，较大数据入堆顶，再对整个堆进行下调，使堆顶存放最小元素（小堆）
    for (unsigned int i = k; i < n; ++i)
    {
        if (weight[i]  > TopkArray[0])
        {
            TopkArray[0] = weight[i];
            TopkIndexArray[0] = index[i];
            AdjustDown(TopkArray, TopkIndexArray, 0, k);
        }
    }
    unsigned int count = 0;
    for (unsigned int i = 0; i < k; ++i)//打印k个最大数据，即堆中所有元素
    {
        cout << TopkArray[i] << " ";
        ++count;
        if (count % 10 == 0)
        {
            cout << endl;
        }
    }
    for (unsigned int i = 0; i < k; ++i)//打印k个最大数据，即堆中所有元素
    {
        cout << TopkIndexArray[i] << " ";
        ++count;
        if (count % 10 == 0)
        {
            cout << endl;
        }
    }
    cout << endl;
    delete[] TopkArray;//注意释放TopkArray所占的内存
    TopkArray = NULL;
    vector<unsigned int> return_index_vector;
    for(unsigned int i = 0; i < k; ++i){
        return_index_vector.push_back(TopkIndexArray[i]);
    }
    delete[] TopkIndexArray;
    TopkIndexArray = NULL;
    return return_index_vector;
}



//找出state下的最大的前n个数


int main(void){
    srand(time(0));
    //int V_NUMBER = 10;
    float distance_limit = 5.0;
    float distribution_length = 20;
    float V_position[V_NUMBER][2];
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < 2; j++){
            V_position[i][j] =  rand() / ((double)(RAND_MAX)/distribution_length);
        }
    }
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < 2; j++){
            cout << V_position[i][j] << ' ';
        }
        cout << endl;
    }

    float V_weight[V_NUMBER];
    for(int i = 0; i < V_NUMBER; i++){
        V_weight[i] = rand() % 20 + 1;
    }

    cout << "weight:";
    for(int i = 0; i < V_NUMBER; i++){
        cout << V_weight[i] << " ";
    }
    cout << endl;
    // cout << position[1][1] << endl;
    cout << "-----------" << endl;

    /*生成相邻图矩阵
    * V_graph为一个i二维的数组
    * v_neighbor为一个二维的可变长度矩阵
    */
    vvi v_neighbor(V_NUMBER, vector<int>()); //每个顶点的相临顶点向量
    int V_graph[V_NUMBER][V_NUMBER];
    for(int i = 0; i < V_NUMBER; i++){
        v_neighbor[i].push_back(i);
        for(int j = 0; j < V_NUMBER; j++){
            float temp = pow(V_position[i][1] - V_position[j][1], 2) + pow(V_position[i][2] - V_position[j][2], 2);
            if(i != j && temp <= pow(distance_limit, 2)) {
                V_graph[i][j] = 1;
                v_neighbor[i].push_back(j);
            } else {
                V_graph[i][j] = 0;
            }
        }
    }
    //打印这个数组的内容
    for(int i = 0; i < V_NUMBER; i++){
        for(int j = 0; j < V_NUMBER; j++){
            cout << V_graph[i][j] << "  ";
        }
        cout << "over" << endl;
    }

    cout << "v_neighbor" << endl;
    print_subsets(v_neighbor);
    vvvi Q_Solution;
    Q_Solution = get_subsets_3(v_neighbor);
    // print_subsets_3(Q_Solution);
    vvvi Q_Solution_state = get_state_3(Q_Solution,v_neighbor,V_graph);
    //print_subsets_3(Q_Solution_state);

    cout << "------------------------------------"  << endl;
    vvvi Q_Solution_protocol;
    Q_Solution_protocol = get_subsets_3_protocol(v_neighbor,V_graph);
    print_subsets_3(Q_Solution_protocol);
    cout << Q_Solution_protocol.size() << "+" << Q_Solution_protocol[0].size() << "+" << Q_Solution_protocol[0][0].size() << endl;
    cout << "------------------------------------"  << endl;
    vvvi Q_Solution_protocol_state = get_state_3(Q_Solution_protocol,v_neighbor,V_graph);
    cout << Q_Solution_protocol_state.size() << "+" << Q_Solution_protocol_state[0].size() << "+" << Q_Solution_protocol_state[0][0].size() << endl;
    print_subsets_3(Q_Solution_protocol_state);

    cout << "-----------------test_vvi----------------" << endl;
    //测试combination_Node 和 combination_state
    vvi test_vvi = combination_state(Q_Solution_protocol_state[0],v_neighbor[0],Q_Solution_protocol_state[1],v_neighbor[1],V_graph);
    // print_subsets(test_vvi);
    print_subsets(Q_Solution_protocol_state[0]);
    cout << endl;
    print_subsets(Q_Solution_protocol_state[1]);
    cout << endl;
    print_subsets(test_vvi);
    cout << "-----------------Node----------------" << endl;
    vi Node0 = combination_Node(v_neighbor[0],v_neighbor[1]);
    vi Node1 = combination_Node(v_neighbor[1],v_neighbor[1]);
    vvi Node;
    Node.push_back(Node0);
    Node.push_back(Node1);
    print_subsets(Node);
    cout << Q_Solution_protocol_state[0].size() << endl;
    cout << Q_Solution_protocol_state[1].size() << endl;
    cout << test_vvi.size() << endl;

    float weight_Node0 = compute_weigh(Node0,V_weight);
    cout << "weight is " <<   weight_Node0 << endl;
    cout << test_vvi[0].size() << "----" <<  Node0.size() << endl;
    float weight_Node1 = compute_weigh_state(test_vvi[1],Node0,V_weight);
    cout << "weight is " <<   weight_Node1 << endl;

    cout << Q_Solution_protocol_state[0].size() << "----" <<  test_vvi[0].size() << endl;

    vf weigh_state_vector = compute_weigh_state_vector(test_vvi, Node0, V_weight);
    vui state_index;
    for(unsigned i = 0; i < test_vvi.size(); i++){
        state_index.push_back(i);
    }
    vui topk = GetTopk(weigh_state_vector,state_index,state_index.size(),10);





	return 0;

}
