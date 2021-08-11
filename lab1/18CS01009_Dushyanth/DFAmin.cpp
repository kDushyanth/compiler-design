#include<bits/stdc++.h>
#include<cstdlib>
using namespace std;
typedef struct node{
char s1,s2;
struct node *next;
}node;
//function to display dependent list
void dispadj(node adj[],int l){
for(int i=0;i<l;i++){
    node *temp = adj[i].next;
    cout<<"("<<adj[i].s1<<","<<adj[i].s2<<")";
    while(temp!=NULL){
        cout<<"->"<<"("<<temp->s1<<","<<temp->s2<<")";
        temp = temp->next;
    }cout<<endl;
}
}
//function to return first element of queue
int firstOne(pair<int, int> p)
{
    int f = p.first;
    int s = p.second;
    return f*100+s;
}
int main(){
    int n;
    cout<<"enter number of states in DFA:";
    cin>>n;
    int mat[n-1][n-1];
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            mat[i][j]=0;
        }
    }
    //0-> Equivalent states; 1-> Distinguishable states.
    char delta[n][3];
    cout<<"enter transition function of DFA in terms of A....Z\n";
    for(int i=0;i<n;i++){
        cin>>delta[i][0]>>delta[i][1]>>delta[i][2];
    }
    int f;
    cout<<"enter no:of final states:";
    cin>>f;
    cout<<"enter the final state(s):\n";
    char fina[f];
    for(int i=0;i<f;i++){
        cin>>fina[i];
    }
    //matrix initialization
    for(int i=0;i<f;i++){
        int j = fina[i]-'A';
        for(int y=j;y<n-1;y++){
            mat[y][j]=1;
        }
        for(int k=0;k<j;k++){
            mat[fina[i]-'A'-1][k]=1;
        }
    }
    for(int i=0;i<f;i++){
        for(int j=i+1;j<f;j++){
            mat[fina[j]-'A'-1][fina[i]-'A']=0;
        }
    }

  char x,y,t;
     node adj[n*(n-1)/2];
    queue < pair<char, char> > q;int found=0;
    int i=0,j=1;
    //dependent list creation
    for(int i1=0;i1<n*(n-1)/2;i1++){
        if(j==n){
            i++;
            j=i+1;
        }
        adj[i1].s1='A'+i;
        adj[i1].s2='A'+j;
        adj[i1].next = NULL;
        j++;
    }
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
        if(delta[i][1]!=delta[j][1] ){
        x = delta[i][1];
        y = delta[j][1];
        if(x>y) {
            t= x;
            x = y;
            y =t;
        }
            if(!(x==delta[i][0] && y==delta[j][0])){
           node *nn = (node *)malloc(sizeof(node));

           nn->next=NULL;
           nn->s1 = delta[i][0];
           nn->s2 = delta[j][0];
           nn->next = adj[n*(n-1)/2 - ('A'+n-1-x)*('A'+n-x)/2 + (y-x-1)].next;
           adj[n*(n-1)/2 - ('A'+n-1-x)*('A'+n-x)/2 + (y-x-1)].next = nn;
        }
        }
        if(delta[i][2]!=delta[j][2] ){
        x = delta[i][2];
        y = delta[j][2];
        if(x>y) {
            t= x;
            x = y;
            y =t;
        }
        if(!(x==delta[i][0] && y==delta[j][0])){
           node *nn = (node *)malloc(sizeof(node));
           nn->next=NULL;
           nn->s1 = delta[i][0];
           nn->s2 = delta[j][0];
           nn->next = adj[n*(n-1)/2 - ('A'+n-1-x)*('A'+n-x)/2 + (y-x-1)].next;
           adj[n*(n-1)/2 - ('A'+n-1-x)*('A'+n-x)/2 + (y-x-1)].next = nn;
        }
        }
    }
    }

    //queue initialization
    pair<char,char> temp;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(mat[i][j]==1){
                 x = 'A'+1+i;
                 y = 'A'+j;
                if(x>y){
                    t=x;
                    x=y;
                    y=t;
                }
                temp.first = x;
                temp.second = y;
                q.push(temp);
            }

        }
    }
    node *nxt;
    char a,b;
    int ab;
    //processing queue
    while(q.empty()==0){
        ab = firstOne(q.front());
        a = ab/100;
        b = ab%100;
        temp.first = a;
        temp.second = b;
        nxt = adj[n*(n-1)/2 - ('A'+n-1-temp.first)*('A'+n-temp.first)/2 + (temp.second-temp.first-1)].next;
        while(nxt!=NULL){
        if(mat[nxt->s2-'A'-1][nxt->s1-'A']==0){
            mat[nxt->s2-'A'-1][nxt->s1-'A']=1;
            temp.first = nxt->s1;
            temp.second = nxt->s2;
            q.push(temp);
        }
        nxt = nxt->next;
        }
        q.pop();
    }
    int equicount=0;
    vector< pair< char , char > > equi;
    for(int i=0;i<n;i++){
            temp.second = temp.first = i+'A';
            equi.push_back(temp);

    }
    for(int i=0;i<n-1;i++){
        for(int j=0;j<=i;j++){
            if(mat[i][j]==0){
                equi[i+1].second = j+'A';
                equi[j].second = i+1+'A';
                equicount++;
            }
        }

    }
    int v[n];
    for(int i=0;i<n;i++){
        v[i]=INT_MAX;
    }
    int k=0;

    for(int i=0;i<n;i++){
        if(v[equi[i].first-'A']==INT_MAX){
            v[equi[i].first-'A']=k;
            j= equi[i].second-'A';
            while(v[j]==INT_MAX){
                v[j]=k;
                j=equi[j].second-'A';
            }
            k++;
        }
    }

        int visit[k]={0};
    char minidelta[k][3];
    int k1=0;
    //populate the new transition table
    for(int i=0;i<n;i++){
        if(visit[v[delta[i][0]-'A']]==0){
            minidelta[k1][0] = 'A'+v[delta[i][0]-'A'];
            minidelta[k1][1] = 'A'+v[delta[i][1]-'A'];
            minidelta[k1][2] = 'A'+v[delta[i][2]-'A'];
            visit[v[delta[i][0]-'A']]=1;
            k1++;
        }
    }
    cout<<"Minimized DFA:"<<endl;
    cout<<"|minidelta|0|1|"<<endl;
    for(int i=0;i<k;i++){
        cout<<"     "<<minidelta[i][0]<<"     "<<minidelta[i][1]<<" "<<minidelta[i][2]<<endl;
    }
}