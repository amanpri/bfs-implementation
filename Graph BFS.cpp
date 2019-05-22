#include<iostream>
#include<queue>
#include<vector>
#include<algorithm>
using namespace std;

class node
{
    public:
    int data;
    node* next;
    node()
    {
        next=NULL;
    }
    node(int d)
    {
        data=d;
        next=NULL;
    }
};

queue<int> q;
vector<int> visited;

class Graph
{
    public:
    node **relation;
    int vertex_count;
    void initialise(int element[])
    {
        for(int i=0;i<vertex_count;i++)
        {
            node* newnode=new node(element[i]);
            relation[i]=newnode;        ///here all the link list have first node as parent
        }

    }
    bool is_empty()
    {
        for(int i=0;i<vertex_count;i++)
        {
            if(relation[i]!=NULL)
                return false;
        }
        return true;
    }
    public:
        Graph(int count,int ele[])
        {
            vertex_count=count;
            relation=new node*[count];
            initialise(ele);
        }
        int find_index(int ele)
        {
            for(int i=0;i<vertex_count;i++)
            {
                if(relation[i]->data==ele)
                    return i;
            }
            return -1;
        }
        bool insert_edge(int parent,int child)
        {
            int p,c;
            p=find_index(parent);
            c=find_index(child);
            if(p==-1 | c==-1)
                return false;
            node* temp=relation[p];
            while(temp->next!=NULL)
            {
                temp=temp->next;
            }
            node* newnode=new node(child);
            temp->next=newnode;
            return true;
        }
        void BFS_print()
        {
            if(is_empty())
                return;
            node* temp=relation[0];
            q.push(temp->data);
                while(!q.empty())
                {
                    node* temp=relation[find_index(q.front())];
                    q.pop();

                    if(std::count(visited.begin(), visited.end(), temp->data))
                        continue;
                    cout<<temp->data<<" ";
                    visited.push_back(temp->data);

                    temp=temp->next;        ///skipping th parent
                    while(temp!=NULL)
                    {
                        q.push(temp->data);
                        temp=temp->next;
                    }
                }
        }

        void print()
        {
            bool flag=false;
            for(int i=0;i<vertex_count;i++)
            {
                flag=false;
                if(relation[i]!=NULL)
                {
                    node* temp;
                    temp=relation[i];
                    cout<<"Element:-"<<temp->data<<endl;   ///printing the parent
                    temp=temp->next;            ///skipping the parent
                    while(temp!=NULL){
                        flag=true;
                        cout<<"\thas an edge to:- "<<temp->data<<endl;
                        temp=temp->next;
                    }
                    if(!flag)
                        cout<<"\tdoesn't have any edge"<<endl;
                }

            }
            cout<<endl;
        }
};
int main()
{
 int b[]={0,1,2,3,4,5};    ///the elements in the graph
    int countele=6;         ///total elements in graph

    Graph G(countele,b);
    G.insert_edge(0,1);
    G.insert_edge(0,5);
    G.insert_edge(1,2);
    G.insert_edge(1,4);
    G.insert_edge(2,3);
    G.insert_edge(4,3);
    G.insert_edge(5,4);
    G.insert_edge(5,3);
    G.print();

    cout<<"BST-:"<<endl;
    G.BFS_print();
}
