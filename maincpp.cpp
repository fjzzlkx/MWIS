#include <iostream>
#include <math.h>
#include <time.h>
#include <vector>
#include "initialization.h"
#include "vectorAndState.h"
#include "protocol.h"
// #include <iomanip>
// #include <fstream>
// #include <assert.h>
// #include <stdio.h>
// #include <stdlib.h>

// using namespace std;
using std::cout;
using std::endl;
typedef std::vector<std::vector<std::vector <int> > > vvvi;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;
typedef std::vector<unsigned int> vui;
typedef std::vector<float> vf;
typedef std::vector<std::vector<float> > vvf;


int main(void){
    srand(time(0));
    //int V_NUMBER = 10;
    float distance_limit = 6;
    float distribution_length = 10.0;
    float V_position[V_NUMBER][2];
    float weight_range = 1.0;
    float V_weight[V_NUMBER];
    vvi v_neighbor(V_NUMBER, vi()); //每个顶点的相临顶点向量
    int V_graph[V_NUMBER][V_NUMBER];
    initialize_all(V_position, distribution_length, V_weight, weight_range,V_graph, distance_limit, v_neighbor);
    print_positon(V_position);
    print_weight(V_weight);
    print_V_graph(V_graph);
    print_V_neighbor(v_neighbor);

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
    // print_subsets_3(Q_Solution_protocol_state);

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
    vvi temp_vvi;
    for(unsigned int i = 0; i < topk.size(); i++){
        temp_vvi.push_back(test_vvi.at(topk.at(i)));
    }
    test_vvi.clear();
    // cout << "after clear" << endl;
    test_vvi = temp_vvi;
    //cout.width(10);
    // cout << "after width" << endl;
    for(unsigned int i = 0; i < weigh_state_vector.size(); i++){
        cout.width(3);
        cout << weigh_state_vector.at(i) << " ";
        if ((i+1) % 50 == 0){
            cout << endl;
        }
    }
    cout << endl;
    cout << "----weigh_state_vector---" << endl;
    print_subsets(test_vvi);
    cout << "---top K weight---" << endl;
    for(unsigned int i = 0; i < topk.size(); i++){
        cout << weigh_state_vector.at(topk.at(i)) << " ";
    }
    cout <<"current state" << endl;
    print_subsets_3(Q_Solution_protocol_state);
    vvi current_Node_set = v_neighbor;
    vvvi next_Q_Solution_protocol_state = get_next_Q_Solution_protocol_state(Q_Solution_protocol_state, v_neighbor, current_Node_set, V_graph);
    cout <<"next state" << endl;
    print_subsets_3(next_Q_Solution_protocol_state);
    cout <<"current Node set" << endl;
    print_subsets(v_neighbor);
    cout <<"next Node set" << endl;
    vvi next_Node_set = get_next_Node_set(v_neighbor,current_Node_set);
    print_subsets(next_Node_set);


    cout <<"after n times  inter" << endl;
    // // vvvi next_Q_Solution_protocol_state2 = get_next_Q_Solution_protocol_state(next_Q_Solution_protocol_state, v_neighbor, current_Node_set, V_graph);
    // for(unsigned int i = 0; i < 10; i++){
    //     next_Q_Solution_protocol_state = get_next_Q_Solution_protocol_state(next_Q_Solution_protocol_state, v_neighbor, next_Node_set, V_graph);
    //     next_Node_set = get_next_Node_set(v_neighbor,next_Node_set);
    //     // next_Node_set.clear();
    //     // next_Node_set = temp_Node_set;
    //     cout <<"after " << i << " times  inter" << endl;
    //     next_Node_set = get_next_Node_set(v_neighbor,next_Node_set);
    // }
    // cout <<"after 10 times  inter state" << endl;
    // print_subsets_3(next_Q_Solution_protocol_state);
    // cout <<"after 10 times  inter Node set" << endl;
    // print_subsets(next_Node_set);
    // // vvvi max_weight = get_max_weight(V_weight, next_Q_Solution_protocol_state, next_Node_set);
    // // print_subsets_3(max_weight);
    // vvi max_weight = get_max_weight_vvi(V_weight, next_Q_Solution_protocol_state, next_Node_set);
    // print_subsets(max_weight);
    // float number_max_weight = numberOfmax(V_weight, next_Q_Solution_protocol_state, next_Node_set);
    //  cout<<"numberOfmax"<<setprecision(6) << number_max_weight << endl;  //改为位小数


    /*--------------------------进行了截取
    cout <<"after n times state" << endl;
    // print_subsets_3(next_Q_Solution_protocol_state);
    for(unsigned int i = 0; i < next_Q_Solution_protocol_state.size(); i++){
        cout << next_Q_Solution_protocol_state.at(i).size() << " ";
        if(i%40 == 39) cout << endl;
    }
    cout << endl;
    vvvi next_Q_state_trH = Q_Solution_protocol_state;
    vvi next_Node_set_trH = v_neighbor;
    cout <<"after n times  trH" << endl;
    for(unsigned int i = 0; i < 100; i++){
        next_Q_state_trH = get_next_Q_state_trH(V_weight, next_Q_state_trH, v_neighbor, next_Node_set_trH, V_graph, 10000);
        cout <<"after " << i << " times  trH" << endl;
        next_Node_set_trH = get_next_Node_set(v_neighbor,next_Node_set_trH);
    }
    // print_subsets_3(next_Q_state_trH);
    vvvi max_weight = get_max_weight(V_weight, next_Q_state_trH, next_Node_set_trH);
    print_subsets_3(max_weight);
    ---------------------------------------*/


    cout << endl;
	return 0;

}
