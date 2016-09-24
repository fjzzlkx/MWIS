Node_Number = 100;
state_keep_num = 50;
trH = state_keep_num;
distributed_length = 20;
weight_vec = rand(1,Node_Number);

dis_limit = 5;
V_position = rand(2,Node_Number) * distributed_length;
dis = [];
for i = 1:Node_Number
    dis = [dis;sqrt((V_position(1,:) - V_position(1,i)).^2 + (V_position(2,:) - V_position(2,i)).^2)];
end
dis;
V_graph  = zeros(Node_Number);
for i = 1:Node_Number
    for j = 1:Node_Number
        if dis(i,j) < dis_limit
            V_graph(i,j) = 1;
        end
    end
    %V_graph(i,i) = 0;
end
Node_all = 1:Node_Number;
%V_graph(Node_all,Node_all) = 0;


%初始化整个节点结构体信息
for i = 1:Node_Number
    Node_vec(i).Node_id = i;
    Node_vec(i).Node_weight = 0;
    %邻居的信息
    Node_vec(i).num_of_neighbor = 0;                        %邻居的个数
    Node_vec(i).index_in_neighbor = zeros(1,Node_Number);      %节点的邻居
    Node_vec(i).num_of_current_Node = 0;                %进行combination 所涉及节点的数量
    Node_vec(i).current_Node_ID_vec = zeros(1,Node_Number);    %当前的节点涉及的状态节点向量
    Node_vec(i).current_Node_weight_vec = zeros(1,Node_Number);%这些节点的权重向量
    %combination涉及节点的状态信息
    Node_vec(i).num_of_state_vec = 0;                       %保留的状态个数
    Node_vec(i).current_Node_state_vec = zeros(state_keep_num,Node_Number);;
    Node_vec(i).state_weight_sum_vector = zeros(1,state_keep_num);
    Node_vec(i).max_weight = 0;
    Node_vec(i).max_weight_Node_vec = zeros(1,Node_Number);
    Node_vec(i).max_weight_state_vec = zeros(1,Node_Number);
end

%初步的状态生成
for i = 1:Node_Number
    Node_vec(i).Node_weight = weight_vec(i);
    %邻居的信息
    Node_vec(i).num_of_neighbor = size(find(V_graph(i,:) == 1),2);                        %邻居的个数
    Node_vec(i).index_in_neighbor = [find(V_graph(i,:) == 1),zeros(1,Node_Number-Node_vec(i).num_of_neighbor)];      %节点的邻居
    Node_vec(i).num_of_current_Node = Node_vec(i).num_of_neighbor;                %进行combination 所涉及节点的数量
    
    %处理当前的节点
    Node_vec(i).current_Node_ID_vec = Node_vec(i).index_in_neighbor;              %当前的节点涉及的状态节点向量
    index_current_Node = 1:Node_vec(i).num_of_current_Node;
    Node_vec(i).current_Node_weight_vec(index_current_Node) = weight_vec(Node_vec(i).current_Node_ID_vec(index_current_Node));%这些节点的权重向量
    %对节点按权重排序
    temp_weight_vec =  Node_vec(i).current_Node_weight_vec(1:Node_vec(i).num_of_neighbor);
    unique_sort_vec = sort(unique(temp_weight_vec),'descend');
    index_vec = [];
    for j = 1:size(unique_sort_vec,2)
        index_vec = [index_vec,find(temp_weight_vec == unique_sort_vec(j))];
    end   
    Node_vec(i).current_Node_ID_vec(1:size(index_vec,2)) =  Node_vec(i).current_Node_ID_vec(index_vec);
    Node_vec(i).current_Node_weight_vec(index_current_Node) = sort(Node_vec(i).current_Node_weight_vec(index_current_Node),'descend');
    
    %调用函数生成节点可邻居的初始state_vec
    state_vec = compute_state_init(Node_vec(i).num_of_neighbor);
    state_weight_of_Node =[];
    for j = 1:size(state_vec,1)
        state_weight_of_Node = [state_weight_of_Node,state_vec(j,:) * Node_vec(i).current_Node_weight_vec(1:Node_vec(i).num_of_neighbor)'];
    end
    top_trH_index = [];
    sort_state_weight = sort(state_weight_of_Node,'descend');
    for j = 1:min(20,size(state_vec,1))
        top_trH_index = [top_trH_index,find(state_weight_of_Node == sort_state_weight(j))];
    end
    
    state_vec(top_20_index,:)
    
    %combination涉及节点的状态信息
    Node_vec(i).num_of_state_vec = 0;                       %保留的状态个数
    Node_vec(i).current_Node_state_vec = zeros(state_keep_num,Node_Number);
    Node_vec(i).state_weight_sum_vector = zeros(1,state_keep_num);
    Node_vec(i).max_weight = sort_state_weight(1);
    Node_vec(i).max_weight_Node_vec = zeros(1,Node_Number);
    Node_vec(i).max_weight_state_vec = zeros(1,Node_Number);
end


%最开始的state vec生成
%这部分简单替代 不一定准确




