#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <fstream>
#include <vector>
#include <assert.h>
#include <iomanip>
#include "vectorAndState.h"
using namespace std;
using std::cout;
using std::endl;
typedef std::vector<std::vector<std::vector <int> > > vvvi;
typedef std::vector<std::vector<int> > vvi;
typedef std::vector<int> vi;
typedef std::vector<unsigned int> vui;
typedef std::vector<float> vf;
typedef std::vector<std::vector<float> > vvf;

//判断一个向量是否能满足指定干扰图的要求
bool judgment_Vector(vi a, int V_graph[V_NUMBER][V_NUMBER]){
    for(unsigned int i = 0; i < a.size(); i++){
        for(unsigned int j = i; j < a.size(); j++){
            if(V_graph[a[i]][a[j]] == 1) return false;
        }
    }
    return true;
}
//判断一个向量的状态是否能满足指定干扰图的要求
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
vvi get_subsets(vi  a){
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
vvi get_subsets_protocol(vi a, int V_graph[V_NUMBER][V_NUMBER]){
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
