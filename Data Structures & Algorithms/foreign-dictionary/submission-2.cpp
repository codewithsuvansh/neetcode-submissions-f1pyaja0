void dfs(int i, vector<int> &visited,vector<vector<int>>& ulta,map<int,char>& intToChar,string &temp){
    if(visited[i]!=-1){
        return;
    }
    visited[i] = 1;
    //run dfs thtough all it members 
    for(auto &it: ulta[i]){
        dfs(it,visited,ulta,intToChar,temp);
    }
    //now append the string and return 
    temp.push_back(intToChar[i]);
    return;
}

void dfs1(int i, vector<int>& visited, vector<vector<int>>& ulta, bool &cd){
    if(visited[i]==1){
        visited[i] = 0;
        cd = true;
        return;
    }
    if(visited[i] == 0){
        return;
    }
    visited[i] = 1;
    for(auto &it: ulta[i]){
        //dfs inla 
        dfs1(it,visited,ulta,cd);
    }
    visited[i] = 0;
    return;
}

bool isPossible (vector<vector<int>>& ulta, int &n){
    //detect cycle in directed graph
    vector<int> visited(n,-1);
    for(int i=0;i<n;i++){
        if(visited[i]!=-1){
            continue;
        }
        bool cycleDetected = false;
        dfs1(i,visited,ulta,cycleDetected);
        if(cycleDetected){
            return false;
        }
    }
    return true;
}

class Solution {
public:
    string foreignDictionary(vector<string>& words) {
    //    if(!isPossible(words)){//to create this function use detect cycle in directed graph
    //     return "";
    //    } 
       //now it is possble to constuct a sequence 
        map<char,int> charToInt;
        map<int,char> intToChar;
        charToInt[(words[0])[0]] = 0;
        intToChar[0] = (words[0])[0]; //pehla is considered 0 always
        int currInt= 1;
        for(auto &it: words){
            for(int j=0;j<it.size();j++){
                if(it[j] == (words[0])[0]){
                    continue;
                }
                else if(charToInt[it[j]] > 0){
                    //already done 
                    continue;
                }
                //now assign currint to this particular char
                charToInt[it[j]] = currInt;
                intToChar[currInt] = it[j];
                currInt++;
            }
        }
        int n = charToInt.size();
        vector<vector<int>> ulta(n,vector<int>());
        for(int i=words.size()-2;i>=0;i--){
            string pichla = words[i];
            string agla = words[i+1];
            if(pichla == agla){
                continue;
            }
            //agar dono same and length difference hai to don't take into account 
            char diff = '-';
            char diff2= '-';
            for(int k=0;k<min(pichla.size(),agla.size());k++){
                if(pichla[k] == agla[k]){
                    continue;
                }
                else{
                    diff = pichla[k];
                    diff2 = agla[k];
                    break;
                }
            }
            if(diff == '-' && pichla.size()>agla.size()){
                return "";
            }
            else if(diff == '-'){
                continue;
            }
            //now we have a to c mapping 
            //a is diff and c is diff2 
            ulta[charToInt[diff]].push_back(charToInt[diff2]);
        }
        if(!isPossible(ulta,n)){//to create this function use detect cycle in directed graph
        return "";
       } 
        //now we have ulta table created 
        //need to run dfs to find the final string 
        vector<int> visited(n,-1);
        string ans = "";
        for(int i=0;i<n;i++){
            if(visited[i]!=-1){
                continue;
            }
            string temp = "";
            dfs(i,visited,ulta,intToChar,temp);
            ans+=temp;
        }
        reverse(ans.begin(),ans.end());
        return ans;
    }
};
