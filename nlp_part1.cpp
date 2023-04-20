#include <bits/stdc++.h>
using namespace std;
int main() {
    bool last = 0;
    string s = "breakthrough drug for schizophrenia\nnew schizophrenia drug\nnew approach for treatment of schizophrenia\nnew hopes for schizophrenia patients";
    //string s = "new home sales top forecasts\nhome sales rise in july\nincrease in home sales in july\njuly new home sales rise";
    if(s[0] == 'n')
        last = 1;
    else
        last = 0;
    set<string>ss;
    string temp = "";
    vector<string>v,vv;
    vector<map<string,int>>vp(4);
    for(int i = 0; i<s.length(); i++){
        if(s[i+1] == '\0')
            temp+=s[i];
        if(s[i] == ' ' || s[i] == '\n' || s[i+1] == '\0'){
            if(ss.find(temp) == ss.end())
                vv.push_back(temp);
            ss.insert(temp);
            v.push_back(temp);
            temp = "";
        }
        else
            temp+=s[i];
    }
    cout<<"tokens : "<<v.size()<<" , "<<"terms : "<<ss.size()<<'\n'<<"-------------------------------------------------------\n";
    cout<<"unique words : \n";
    int cnt = 0;
    for(auto &x : vv)
        cout<<++cnt<<"- "<<x<<'\n';
    int inc= 0,inc1=0;
    vector<int>mx(4,0);
    for(int i = 0; i<s.length();i++){
        if(s[i] == '\n') {
            vp[inc][v[inc1]]++;
            ++inc1;
            inc++;
        }
        if(s[i] == ' '|| s[i+1] == '\0') {
            vp[inc][v[inc1]]++;
            ++inc1;
        }
    }
    inc = 0;
    for(auto &x : vp){
        for(auto &y : x)
            mx[inc] = max(mx[inc],y.second);
        ++inc;
    }
    inc = 0;
    cout<<"------------------------------------\n"<<"tf : \n";
    vector<map<string,double>>part7(4);
    for(auto &x : vp){
        cout<<"------------"<<'\n';
        cout<<"Doc "<<inc+1<<": "<<'\n';
        for(auto &y : x) {
            cout << y.first << " : " << y.second <<" / "<<mx[inc]<<" = ";
            double dd = 1.0*y.second / mx[inc];
            part7[inc][y.first] = dd;
            cout<<fixed<<setprecision(3)<<dd<<'\n';
            //printf("%lf\n",&dd);
        }
        ++inc;
    }
    cout<<"-----------------------------------------\n"<<"tf-idf : \n";
    //vector<vector<int>>idf(4,vector<int>(ss.size()));
    map<string,int>mp2;//the term appeared on how many documents
    //for(int i = 0; i<4; i++){
    for(auto &x : vp){
        for(auto &y : vv){
            mp2[y]+=x[y]>0;
        }
    }
    inc = 0;
    vector<map<string,double>>lastPart(4);
    for(auto &x : mp2) {
        cout << x.first << " : ";
        inc = -1;
        int incs = 0;
        for(auto &y : vp){
            inc++;
            for(auto &w : y){
                if(x.first == w.first){
                    //cout<<fixed<<setprecision(3)<<part7[inc][x.first]<<' ';
                    cout<<fixed<<setprecision(3)<<log2(1.0*4/x.second)*part7[inc][x.first]<<" | ";
                    lastPart[incs][x.first] = log2(1.0*4/x.second)*part7[inc][x.first];
                    ++incs;
                }
            }
            //inc = 0;
        }
        incs=0;
        cout<<'\n';
        //cout<<"tf : "<<x.second<<" | ";
        //cout<<"idf : "<<fixed<<setprecision(3)<<log2(1.0*4/x.second)<<'\n';
    }
    cout<<"--------------------------------\n"<<"cosine sim : \n";

    vector<pair<string,vector<int>>>Q(4);
    inc = 0;
    for(int i = 0; i<4; i++){
        for(auto &y : vv){
            Q[i].first = "Doc ";
            Q[i].first+= to_string(i+1);
            Q[i].first += " : ";
            Q[i].second.push_back(vp[i][y]);
        }
    }
    vector<double>finally(vv.size());
    if(!last){
        for(int i = 0; i<vv.size(); i++){
            if(vv[i] == "schizophrenia" || vv[i] == "drug" || vv[i] == "approach")
                finally[i] = 1;
            else
                finally[i]=0;
        }
    }
    else{
        for(int i = 0; i<vv.size(); i++){
            if(vv[i] == "july" || vv[i] == "home" || vv[i] == "increase")
                finally[i] = 1;
            else
                finally[i]=0;
        }
    }
    long double sum = 0;
    long double p = 0;
    for(int i = 0; i<4;i++){
        for(int j = 0; j<vv.size(); j++){
            sum+=1.0*finally[j]*lastPart[i][vv[j]];
            p+=lastPart[i][vv[j]];
        }
        cout<<fixed<<setprecision(3)<<1.0*sum/sqrt(9*p*p)<<'\n';
        sum=0;p=0;
    }
    return 0;
}