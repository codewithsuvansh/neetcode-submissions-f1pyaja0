void dfs(int i, vector<int>& visited, vector<vector<int>>& graph){
    visited[i] = 1;
    for(auto &it: graph[i]){
        if(visited[it]==-1){
            dfs(it,visited,graph);
        }
    }   
    return;
}

class Solution {
public:
    int countComponents(int n, vector<vector<int>>& edges) {
        vector<vector<int>> graph(n,vector<int>());
        for(auto &it: edges){
            int a = it[0];
            int b = it[1];
            graph[a].push_back(b);
            graph[b].push_back(a);
        }
        vector<int> visited(n,-1);
        int ans = 0;
        for(int i=0;i<n;i++){
            if(visited[i]==-1){
                ans++;
                dfs(i,visited,graph);
            }
        }
        return ans;
    }
};
