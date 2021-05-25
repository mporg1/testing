#include<bits/stdc++.h>
using namespace std;
 
string read(string s){
    int i = 0;
    string domain = "";
    while(i < s.length() && s[i] != '/'){
        domain += s[i];
        i++;
    }
    return domain;
}
 
//readup
string read_up(string s){
    int i=0;
    string ip="";
    string up="";
    while(i < s.length() && s[i] != '/'){
        i++;
    }
    i++;
    while(i < s.length() && s[i] != '/' && s[i] != '?')
    {
        up+=s[i];
        i++;
    }
    i++;
    if(up == "machine_up" && i < s.length() && s[i-1] == '?'){
        i += 3;
        while(i < s.length()){
            ip += s[i];
            i++;
        }
    }
    return ip;
}
 
//readdown
string read_down(string s){
    int i = 0;
    string ip = "";
    string down = "";
    while(i < s.length() && s[i] != '/'){
        i++;
    }
    i++;
    while(i < s.length() && s[i] != '/' && s[i] != '?'){
        down += s[i];
        i++;
    }
    i++;
    if(down == "machine_down" && i < s.length() && s[i-1] == '?'){
        i += 3;
        while(i < s.length()){
            ip += s[i];
            i++;
        }
    }
    return ip;
}
int main(){
    int n, urlcnt, count, queries;
    string url_s, s, p;
    vector<string> soo;
    map<string, vector<string> > mp;
    map<string, queue<string> > mp1;
    cin >> n;
    for(int i = 0;i < n; i++){
        cin >> p;
        mp[p] = vector<string>();
        soo.push_back(p);
    }
 
    cin >> urlcnt;
    for(int i = 0; i < urlcnt; i++){
        cin >> url_s;
        cin >> count;
        queue<string> q;
        for(int j = 0; j < count; j++){
            cin >> s;
            q.push(s);
        }
        mp1[url_s] = q;
    }
    cin >> queries;
    for(int i = 0;i < queries; i++){
        cin >> s;
        // cout<<"query***"<<endl;
        // cout<<s<<endl;
        string domain = read(s);
        string up = read_up(s);
        string down = read_down(s);
        if(up != ""){
            queue<string> q = mp1[domain];
            q.push(up);
            string temp = q.front();
            q.pop();
            q.push(temp);
            mp1[domain]=q;
        }
        else if(down != ""){
            queue<string> modified;
            queue<string> q = mp1[domain];
            //cout<<“down”<<down<<endl;
            while(!q.empty() && q.front()!=down){
                //cout<<q.front()<<endl;
                modified.push(q.front());
                q.pop();
            }
            q.pop();
            while(!q.empty()){
                //cout<<q.front()<<endl;
                modified.push(q.front());
                q.pop();
            }
            // string temp = modified.front();
            // modified.pop();
            // modified.push(temp);
            mp1[domain] = modified;
        }
        else{
            queue<string> q = mp1[domain];
 
            string machine = q.front();
            q.pop();
            // if s contains mp_down or mp_up, then don't push that query
            if(s.find("machine_up") != std::string::npos || s.find("machine_down") != std::string::npos){
                mp[machine].push_back(domain + "/get/users");
            }
            else{
                mp[machine].push_back(s);
            }
            q.push(machine);
            mp1[domain] = q;
        }
        // else{
        //     int a = 1 / 0;
        // }
 
    }
 
    for(auto it : soo){
        cout << it << endl;
        // vector<string> vec = it.second;
        vector<string> vec = mp[it];
        for(auto it1 : vec)
            cout << it1 <<endl;
    }
    return 0;
}