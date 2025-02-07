#include <bits/stdc++.h>

using namespace std;

const int delta=6;

struct graph
{
    vector< vector<int> > adjacencyList;
};

bool operator<(const graph& lhs, const graph& rhs){
    return lhs.adjacencyList < rhs.adjacencyList;
}

void addEdge(graph &g, int a, int b)
{
    g.adjacencyList[a].push_back(b);
    g.adjacencyList[b].push_back(a);
}

void printGraph(graph &g)
{
    cout << "n=" << g.adjacencyList.size() << endl;
    cout << "Edges follow:" << endl;
    for(int i=0; i<g.adjacencyList.size(); i++)
    {
        for(int neigh : g.adjacencyList[i])
        {
            cout << i << " " << neigh << endl;
        }
    }
}

bool isIndependent(graph &g)
{
    for(int i=0; i<g.adjacencyList.size(); i++)
    {
        if(g.adjacencyList[i].size() != 0) return false;
    }
    return true;
}

// assumption: g consists of 4 vertices
bool isCycle(graph &g)
{
    if(g.adjacencyList.size()!=4)
    {
        cout << "Assumption violated!" << endl;
    }
    for(int i=0; i<g.adjacencyList.size(); i++)
    {
        if(g.adjacencyList[i].size()!=2) return false;
    }
    return true;
}

bool isStar(graph &g)
{
    int n=g.adjacencyList.size();
    int numDegNMinus1=0;
    int numDeg1=0;
    for(int i=0; i<n; i++)
    {
        if(g.adjacencyList[i].size()==1)
        {
            numDeg1+=1;
        }
        else if(g.adjacencyList[i].size()==n-1)
        {
            numDegNMinus1+=1;
        }
    }
    return ((numDegNMinus1==1) && (numDeg1==n-1));
}

bool allowed4Versus4(graph &g1, graph &g2)
{
    bool isStarG1=isStar(g1);
    if(isStarG1)
    {
        return isStar(g2);
    }
    if(isIndependent(g1))
    {
        return (isIndependent(g2)||isCycle(g2));
    }
    if(isCycle(g1))
    {
        return isIndependent(g2);
    }
    return false;
}

vector<graph> allGraphs;

void addAllGraphs()
{
    vector<int> emp;

    // connected graphs

    // graph 1: 1-vertex graph
    graph g1;
    g1.adjacencyList.assign(1,emp);
    allGraphs.push_back(g1);

    // graph 2: 2-vertex graph
    graph g2;
    g2.adjacencyList.assign(2,emp);
    addEdge(g2,0,1);
    allGraphs.push_back(g2);

    // graph 3: 3-vertex graph, path
    graph g3;
    g3.adjacencyList.assign(3,emp);
    addEdge(g3,0,1);
    addEdge(g3,1,2);
    allGraphs.push_back(g3);

    // graph 4: 3-vertex graph, triangle
    graph g4;
    g4.adjacencyList.assign(3,emp);
    addEdge(g4,0,1);
    addEdge(g4,1,2);
    addEdge(g4,0,2);
    allGraphs.push_back(g4);

    // graph 5: 4-vertex graph, path
    graph g5;
    g5.adjacencyList.assign(4,emp);
    addEdge(g5,0,1);
    addEdge(g5,1,2);
    addEdge(g5,2,3);
    allGraphs.push_back(g5);

    // graph 6: 4-vertex graph, cycle
    graph g6;
    g6.adjacencyList.assign(4,emp);
    addEdge(g6,0,1);
    addEdge(g6,1,2);
    addEdge(g6,2,3);
    addEdge(g6,0,3);
    allGraphs.push_back(g6);

     // graph 7: 4-vertex graph, triangle+edge
    graph g7;
    g7.adjacencyList.assign(4,emp);
    addEdge(g7,0,1);
    addEdge(g7,1,2);
    addEdge(g7,2,3);
    addEdge(g7,0,2);
    allGraphs.push_back(g7);

    // graph 8: 4-vertex graph, 2 triangles
    graph g8;
    g8.adjacencyList.assign(4,emp);
    addEdge(g8,0,1);
    addEdge(g8,1,2);
    addEdge(g8,2,3);
    addEdge(g8,0,2);
    addEdge(g8,1,3);
    allGraphs.push_back(g8);

    // graph 9: 4-vertex graph, star
    graph g9;
    g9.adjacencyList.assign(4,emp);
    addEdge(g9,0,1);
    addEdge(g9,0,2);
    addEdge(g9,0,3);
    allGraphs.push_back(g9);

    // disconnected graphs
    // graph 10: 2-vertex graph
    graph g10;
    g10.adjacencyList.assign(2,emp);
    allGraphs.push_back(g10);

    // graph 11: 3-vertex graph : 2-path + K1
    graph g11;
    g11.adjacencyList.assign(3,emp);
    addEdge(g11,0,1);
    allGraphs.push_back(g11);

    // graph 12: 3-vertex graph : 3K1
    graph g12;
    g12.adjacencyList.assign(3,emp);
    allGraphs.push_back(g12);

    // graph 13: 4-vertex graph : 4K1
    graph g13;
    g13.adjacencyList.assign(4,emp);
    allGraphs.push_back(g13);

    // graph 14: 4-vertex graph : K2+2K1
    graph g14;
    g14.adjacencyList.assign(4,emp);
    addEdge(g14,0,1);
    allGraphs.push_back(g14);

    // graph 15: 4-vertex graph : 2K2
    graph g15;
    g15.adjacencyList.assign(4,emp);
    addEdge(g15,0,1);
    addEdge(g15,2,3);
    allGraphs.push_back(g15);

    // graph 16: 4-vertex graph : P3+K1
    graph g16;
    g16.adjacencyList.assign(4,emp);
    addEdge(g16,0,1);
    addEdge(g16,1,2);
    allGraphs.push_back(g16);

    // graph 17: 4-vertex graph : K3+K1
    graph g17;
    g17.adjacencyList.assign(4,emp);
    addEdge(g17,0,1);
    addEdge(g17,1,2);
    addEdge(g17,0,2);
    allGraphs.push_back(g17);

    // graph 18: 5-vertex-graph : K3,2
    graph g18;
    g18.adjacencyList.assign(5,emp);
    addEdge(g18,0,2);
    addEdge(g18,0,3);
    addEdge(g18,0,4);
    addEdge(g18,1,2);
    addEdge(g18,1,3);
    addEdge(g18,1,4);
    allGraphs.push_back(g18);

}

struct state
{
    int distanceToU;
    graph g;
    vector<int> degreePerVertex;
};

bool operator<(const state& lhs, const state& rhs){
    return tie(lhs.distanceToU, lhs.g, lhs.degreePerVertex)
             < tie(rhs.distanceToU, rhs.g, rhs.degreePerVertex);
}

struct edgeSetBetweenConsecutiveLayers
{
    set< pair<int, int> > edgesBetweenAAndAPlus1;
};

vector< map<state, int> > statesOrderedPerDistance;
vector< map<state, pair<state, edgeSetBetweenConsecutiveLayers> > > previousState;


bool hasK4(vector< set<int> > &adjList)
{
    for(int a=0; a<adjList.size(); a++)
    {   
        for(int b : adjList[a])
        {
            if(a>=b) continue;
            for(int c : adjList[b])
            {
                if(a>=c) continue;
                if(b>=c) continue;
                if(adjList[a].count(c)==0) continue;
                for(int d : adjList[c])
                {
                    if(a>=d) continue;
                    if(b>=d) continue;
                    if(c>=d) continue;
                    if(adjList[a].count(d)==0) continue;
                    if(adjList[b].count(d)==0) continue;
                    return true;
                }
            }
        }
    }
    return false;
}

int debCtr=0;
void recursivelyGenerateStates(int newNbOfVertices, int currDist, state &prevState, edgeSetBetweenConsecutiveLayers &es, graph &currGraph, int edgeRemovalIndex)
{
    debCtr++;

    // check if the edges can be added

    // does it create a K4?
    // are all the degrees from the previous layer satisfied?
    bool createsK4=false;
    bool allDegreesSatisfied=true;

    int n1=prevState.g.adjacencyList.size();
    int n2=currGraph.adjacencyList.size();
    int totNbVertices=n1+n2;
    vector<int> emp;

    vector< set<int> > newGraph(totNbVertices);
    // previous layer
    for(int i=0; i<n1; i++)
    {
        for(int neigh : prevState.g.adjacencyList[i])
        {
            newGraph[i].insert(neigh);
        }
    }
    // current layer    
    for(int i=0; i<n2; i++)
    {
        for(int neigh : currGraph.adjacencyList[i])
        {
            newGraph[n1+i].insert(n1+neigh);
        }
    }
    // edges between
    for(pair<int, int> pa : es.edgesBetweenAAndAPlus1)
    {
        newGraph[pa.first].insert(n1+pa.second);
        newGraph[n1+pa.second].insert(pa.first);
    }
    if(hasK4(newGraph)) createsK4=true;
    
    vector<int> degreesPrevLayer(n1,0);
    vector<int> degreesCurrLayer(n2,0);
    for(int i=0; i<totNbVertices; i++)
    {
        if(i<n1)
        {
            degreesPrevLayer[i]=newGraph[i].size()+prevState.degreePerVertex[i];
            if(degreesPrevLayer[i]<delta)
            {
                allDegreesSatisfied=false;
            }
        }
        else
        {
            degreesCurrLayer[i-n1]=newGraph[i].size()-currGraph.adjacencyList[i-n1].size();
        }
    }
    
    // degree condition should be ignored for currDist==1
    if(!allDegreesSatisfied && currDist>1) return;
    if(createsK4)
    {
        for(int i=edgeRemovalIndex;i<n1*n2;i++)
        {
            pair<int, int> pa=make_pair(i/n2,i%n2);
            es.edgesBetweenAAndAPlus1.erase(pa);
            recursivelyGenerateStates(newNbOfVertices,currDist,prevState,es,currGraph,i+1);
            es.edgesBetweenAAndAPlus1.insert(pa);
        }
        return;
    }
    else
    {
        state newState;
        newState.distanceToU=currDist;
        newState.g=currGraph;
        newState.degreePerVertex=degreesCurrLayer;

        if(statesOrderedPerDistance[currDist].count(newState)==0 || statesOrderedPerDistance[currDist][newState]>newNbOfVertices)
        {
            statesOrderedPerDistance[currDist][newState]=newNbOfVertices;
            previousState[currDist][newState]=make_pair(prevState,es);
        }
    }
}

int ress, modd;

int main(int argc, char *argv[])
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    if(argc!=3)
    {
        cout << "The arguments ress and modd should be provided!" << endl;
        exit(0);
    }
    int ress=atoi(argv[1]);
    int modd=atoi(argv[2]);

    double globalMaxx=-1;
    int correspondingGlobalTeller;
    int correspondingGlobalNoemer;


    addAllGraphs();

//vector< map<state, int> > statesOrderedPerDistance;
//vector< map<state, pair<state, edgeSetBetweenConsecutiveLayers> > > previousState;
    int totNbGraphs=allGraphs.size();


    int caseCtr=-1;
    for(int firstLayerID=0; firstLayerID<totNbGraphs; firstLayerID++)
    {
        if(allGraphs[firstLayerID].adjacencyList.size()>2) continue;
        for(int secondLayerID=0; secondLayerID<totNbGraphs; secondLayerID++)
        {
            caseCtr++;
            if(caseCtr%modd != ress) continue;
            // first reset all datastructures
            statesOrderedPerDistance.clear();
            previousState.clear();

            // initialization : first state vector

            int firstCtr=-1;
            for(graph g : allGraphs)
            {
                firstCtr++;
                if(firstCtr!=firstLayerID) continue;
                map<state, int> firstMapStateTot;
                statesOrderedPerDistance.push_back(firstMapStateTot);
                state sF;
                sF.distanceToU=0;
                sF.g=g;
                sF.degreePerVertex.assign(g.adjacencyList.size(),0);
                statesOrderedPerDistance[0][sF]=g.adjacencyList.size();

                map<state, pair<state, edgeSetBetweenConsecutiveLayers> > firstMapStateToPrev;
                previousState.push_back(firstMapStateToPrev);
                state s2;
                edgeSetBetweenConsecutiveLayers firstEdgeSet;
                previousState[0][sF]=make_pair(s2,firstEdgeSet); 
            } 

            //cout << statesOrderedPerDistance[0].size() << " " << totalNumberOfVertices[0].size() << " " << previousState[0].size() << " " << transitions[0].size() << endl;
          
            //cout << statesOrderedPerDistance[1].size() << " " << totalNumberOfVertices[1].size() << " " << previousState[1].size() << " " << transitions[1].size() << endl;

            // recursive case
            int dist=1;
            while(dist<=18*18+5)
            {
                cout << "dist: " << dist << endl;
                
                map<state, int> IthMapStateTot;
                statesOrderedPerDistance.push_back(IthMapStateTot);
                
                map<state, pair<state, edgeSetBetweenConsecutiveLayers> > IthMapStateToPrev;
                previousState.push_back(IthMapStateToPrev);

                //cerr << "dist: " << dist << endl;
                int someOtherCtr=0;
                int graphCtr=-1;
                for(graph g : allGraphs)
                {
                    graphCtr+=1;
                    if(dist==1&&secondLayerID!=graphCtr) continue;
                    for(auto it : statesOrderedPerDistance[dist-1])
                    {
                        state prevState=it.first;
                        if(g.adjacencyList.size()==5 && !isIndependent(prevState.g)) continue;
                        if(prevState.g.adjacencyList.size()==5 && !isIndependent(g)) continue;
                        if(g.adjacencyList.size()==4 && prevState.g.adjacencyList.size()==4 && !allowed4Versus4(g,prevState.g)) continue;
                        edgeSetBetweenConsecutiveLayers es;
                        for(int i=0; i<prevState.g.adjacencyList.size(); i++)
                        {
                            for(int j=0; j<g.adjacencyList.size(); j++)
                            {
                                es.edgesBetweenAAndAPlus1.insert(make_pair(i,j));
                            }
                        }
                        int newNbOfVertices=it.second+g.adjacencyList.size();
                        someOtherCtr++;
                        /*if(someOtherCtr%100==0)
                        {
                            cerr << "someOtherCtr: " << someOtherCtr << endl;
                            cerr << "call made, old layer has " << prevState.g.adjacencyList.size() << " vertices and new layer has " << g.adjacencyList.size() << " vertices" << endl;
                        }*/
                        recursivelyGenerateStates(newNbOfVertices,dist,prevState,es,g,0);
                    }
                }


                double maxx=-1;
                for(auto it : statesOrderedPerDistance[dist])
                {
                    // current graph should be equal to the graph that was added in the second layer
                    // and previous graph should be equal to graph corresponding with firstLayerID
                    int currDist=dist;
                    state currState=it.first;
                    graph currGraph=currState.g;
                    if(currGraph.adjacencyList!=allGraphs[secondLayerID].adjacencyList) continue;
                    state prevState=previousState[currDist][currState].first;
                    graph prevGraph=prevState.g;
                    if(prevGraph.adjacencyList!=allGraphs[firstLayerID].adjacencyList) continue;

                    int nbVertices=it.second;
                    if((1.0*(dist-1)/(nbVertices-1-currGraph.adjacencyList.size())-maxx) >= -1e-9)
                    {
                        maxx=1.0*(dist-1)/(nbVertices-1-currGraph.adjacencyList.size());
                        cout << "dist and nbVertices: " << " " << dist-1 << " " << nbVertices-1-currGraph.adjacencyList.size() << endl;
                        if(maxx>globalMaxx)
                        {
                            globalMaxx=maxx;
                            correspondingGlobalTeller=dist-1;
                            correspondingGlobalNoemer=nbVertices-1-currGraph.adjacencyList.size();
                        }
                        while(currDist>=0)
                        {
                            state prevState=previousState[currDist][currState].first;
                            edgeSetBetweenConsecutiveLayers prevEdgeSet=previousState[currDist][currState].second;
                            cout << "Current graph: " << endl;
                            printGraph(currState.g);
                            cout << "Edges between current graph and previous graph: " << endl;
                            for(pair<int, int> pa : prevEdgeSet.edgesBetweenAAndAPlus1)
                            {
                                cout << pa.first << " " << pa.second << endl;
                            }
                            currDist--;
                            currState=prevState;
                        }
                    }
                    //cerr << nbVertices << " " << dist << endl;
                    /*if(nbVertices==845 && dist==421)
                    {
                        state currState=it.first;
                        int currDist=dist;
                        while(currDist>=400)
                        {
                            state prevState=previousState[currDist][currState].first;
                            edgeSetBetweenConsecutiveLayers prevEdgeSet=previousState[currDist][currState].second;
                            cout << "Current graph: " << endl;
                            printGraph(currState.g);
                            cout << "Edges between current graph and previous graph: " << endl;
                            for(pair<int, int> pa : prevEdgeSet.edgesBetweenAAndAPlus1)
                            {
                                cout << pa.first << " " << pa.second << endl;
                            }
                            currDist--;
                            currState=prevState;
                        }
                        exit(0);
                    }*/
                }

                //cerr << statesOrderedPerDistance[dist].size() <<  " " << previousState[dist].size() << endl; 
                dist+=1;
            }
        }
    }
    cout << "globalMaxx, numerator and denominator: " << globalMaxx << " " << correspondingGlobalTeller << " " << correspondingGlobalNoemer << endl;
    //cerr << "caseCtr: " << caseCtr << endl;
    return 0;
}
