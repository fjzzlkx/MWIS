#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>

using namespace std;
#define V_NUMBER 20
#define V_number 20

typedef vector<vector<vector<int> > > vvvi;
typedef vector<vector<int> > vvi;
typedef vector<int> vi;
//求集合的所有子集
vvi get_subsets(vector<int>  a, int n){ //O(n2^n)
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

void print_subsets(vvi subsets){
    for(unsigned i=0; i<subsets.size(); ++i){
        vi subset = subsets[i];
        for(unsigned j=0; j<subset.size(); ++j){
            cout<<subset[j]<<" ";
        }
        cout<<endl;
    }
}

vvvi get_subsets_3(vvi subsets){ //O(n2^n)
    vvvi subsets_3;
    cout << "subsets.size() " << subsets.size() << endl;
    for(unsigned int i=0;i<subsets.size();i++){
        subsets_3.push_back(vector<vector<int> >());
        vvi temp2  = get_subsets(subsets[i],subsets[i].size());
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


int main(void){
    srand(time(0));
    //int V_number = 10;
    float distance_limit = 5.0;
    float distribution_length = 20;

    // ofstream write;
    // write.open("test.txt");
    // for(int i=0; i<10 ;i++){
    //     write << ("%5.2f",10 * rand()/32767.0) << "," << ("%5.2f",10 * rand()/32767.0) << ","
    //           << ("%5d",rand()/32767.0 *10) << endl;
    // }
    // write.close();
    float V_position[V_number][2];
    for(int i = 0; i < V_number; i++){
        for(int j = 0; j < 2; j++){
            V_position[i][j] =  rand() / ((double)(RAND_MAX)/distribution_length);
        }
    }
    for(int i = 0; i < V_number; i++){
        for(int j = 0; j < 2; j++){
            cout << V_position[i][j] << ' ';
        }
        cout << endl;
    }

    float V_weight[V_number];
    for(int i = 0; i < V_number; i++){
        V_weight[i] = rand() % 20 + 1;
    }

    cout << "weight:";
    for(int i = 0; i < V_number; i++){
        cout << V_weight[i] << " ";
    }
    cout << endl;
    // cout << position[1][1] << endl;
    cout << "-----------" << endl;

    /*生成相邻图矩阵
    * V_graph为一个i二维的数组
    * v_neighbor为一个二维的可变长度矩阵
    */
    vector<vector<int> > v_neighbor(V_number, vector<int>()); //每个顶点的相临顶点向量
    int V_graph[V_number][V_number];
    for(int i = 0; i < V_number; i++){
        v_neighbor[i].push_back(i);
        for(int j = 0; j < V_number; j++){
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
    for(int i = 0; i < V_number; i++){
        for(int j = 0; j < V_number; j++){
            cout << V_graph[i][j] << "  ";
        }
        cout << "over" << endl;
    }
    //打印这个矩阵的内容
    // for (int i = 0; i < V_number; i++){
    //     for(unsigned j = 0; j < v_neighbor[i].size() ; j++){
    //         cout << v_neighbor[i][j] << " ";
    //     }
    //     cout << "ddd " << endl;
    // }
    // cout << endl;
    /*
     *最初开始广播的生成的每个点和它邻居的全部解
    */

    //vector< vector <vector<int> > > Q_Solution(V_number,vector<vector<int> >(0,vector<int>()));
    //vector<vector<int> > v_neighbor(V_number, vector<int>());
    // for(int i = 0; i < V_number; i++){
    //     Q_Solution =
    //     for(unsigned j = 0; j < v_neighbor[i].size() ; j++){
    //
    //     }
    // }
    cout << "v_neighbor" << endl;
    print_subsets(v_neighbor);
    vvvi Q_Solution;
    Q_Solution = get_subsets_3(v_neighbor);
    print_subsets_3(Q_Solution);
    vvvi Q_Solution_state = get_state_3(Q_Solution,v_neighbor,V_graph);
    print_subsets_3(Q_Solution_state);


	return 0;

}
