#include <bits/stdc++.h>

using namespace std;

const int delta=8;
const int chi=3;

struct graph
{
    vector<int> nbInColorClass;
};

bool operator<(const graph& lhs, const graph& rhs){
    return lhs.nbInColorClass < rhs.nbInColorClass;
}

void printGraph(graph g)
{
    for(int i=0; i<chi; i++)
    {
        cout << g.nbInColorClass[i] << " ";
    }
    cout << endl;
}

vector<graph> allGraphs;

void recursivelyGeneratePartitions(vector<int> &nbInColorClass, int idx, int sum)
{
    if(idx==chi)
    {
        if(sum==0) return;
        graph g;
        g.nbInColorClass=nbInColorClass;
        allGraphs.push_back(g);
        return;
    }
    for(int now=0; now+sum<=delta; now++)
    {
        nbInColorClass[idx]=now;
        recursivelyGeneratePartitions(nbInColorClass,idx+1,now+sum);
    }
}

void addAllGraphs()
{
    allGraphs.clear();
    vector<int> nbInColorClass(chi,0);
    recursivelyGeneratePartitions(nbInColorClass,0,0);
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

vector< map<state, int> > statesOrderedPerDistance;
vector< map<state, state> > previousState;

int debCtr=0;
void recursivelyGenerateStates(int newNbOfVertices, int currDist, state &prevState, graph &currGraph)
{
    debCtr++;

    // check if the edges can be added

    // are all the degrees from the previous layer satisfied?
    bool allDegreesSatisfied=true;
    int n1=0;
    for(int i=0; i<chi; i++)
    {
        n1+=prevState.g.nbInColorClass[i];
    }
    int n2=0;
    for(int i=0; i<chi; i++)
    {
        n2+=currGraph.nbInColorClass[i];
    }

    for(int i=0; i<chi; i++)
    {
        if(prevState.g.nbInColorClass[i]>0 && prevState.degreePerVertex[i]+n1-prevState.g.nbInColorClass[i]+n2-currGraph.nbInColorClass[i]<delta)
        {
            allDegreesSatisfied=false;
        }
    }
    if(allDegreesSatisfied)
    {
        state newState;
        newState.distanceToU=currDist;
        newState.g=currGraph;
        vector<int> newDegrees(chi,0);
        for(int i=0; i<chi; i++)
        {
            newDegrees[i]=n1-prevState.g.nbInColorClass[i];
            if(currGraph.nbInColorClass[i]==0) newDegrees[i]=0;
        }
        newState.degreePerVertex=newDegrees;
        if(statesOrderedPerDistance[currDist].count(newState)==0 || statesOrderedPerDistance[currDist][newState]>newNbOfVertices)
        {
            statesOrderedPerDistance[currDist][newState]=newNbOfVertices;
            previousState[currDist][newState]=prevState;
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
    cerr << "allGraph.size(): " << allGraphs.size() << endl;

//vector< map<state, int> > statesOrderedPerDistance;
//vector< map<state, pair<state, edgeSetBetweenConsecutiveLayers> > > previousState;
    int totNbGraphs=allGraphs.size();

    int caseNumber=-1;
    for(int firstLayerID=0; firstLayerID<totNbGraphs; firstLayerID++)
    {
        int nFirstLayer=0;
        for(int i=0; i<chi; i++)
        {
            nFirstLayer+=allGraphs[firstLayerID].nbInColorClass[i];
        }
        for(int secondLayerID=0; secondLayerID<totNbGraphs; secondLayerID++)
        {
            int nSecondLayer=0;
            for(int i=0; i<chi; i++)
            {
                nSecondLayer+=allGraphs[secondLayerID].nbInColorClass[i];
            }
            if(delta==8 && nFirstLayer+nSecondLayer>=7) continue;
            caseNumber+=1;
            if(caseNumber%modd!=ress) continue;

            // first reset all datastructures
            statesOrderedPerDistance.clear();
            previousState.clear();

            // initialization : first state vector consists of 1 state (1-vertex graph)
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
                sF.degreePerVertex.assign(chi,0);
                int nFirst=0;
                for(int i=0; i<chi; i++)
                {
                    nFirst+=g.nbInColorClass[i];
                }
                statesOrderedPerDistance[0][sF]=nFirst;

                map<state, state> firstMapStateToPrev;
                previousState.push_back(firstMapStateToPrev);
                state s2;
                previousState[0][sF]=s2; 
            }  

            //cout << statesOrderedPerDistance[0].size() << " " << totalNumberOfVertices[0].size() << " " << previousState[0].size() << " " << transitions[0].size() << endl;
              

            // initialization : second state vector does not need to respect transition rules
            map<state, int> secondMapStateTot;
            statesOrderedPerDistance.push_back(secondMapStateTot);
            
            map<state, state> secondMapStateToPrev;
            previousState.push_back(secondMapStateToPrev);

            double maxx=-1;
            // iterate over each graph
            int graphCtr=-1;
            for(graph g : allGraphs)
            {
                graphCtr++;
                if(graphCtr != secondLayerID) continue;
                for(auto it : statesOrderedPerDistance[0])
                {
                    state prevState=it.first;

                    state newState;
                    newState.distanceToU=1;
                    newState.g=g;
                    vector<int> newDegrees(chi,0);
                    int n1=0;
                    for(int i=0; i<chi; i++)
                    {
                        n1+=prevState.g.nbInColorClass[i];
                    }
                    for(int i=0; i<chi; i++)
                    {
                        newDegrees[i]=n1-prevState.g.nbInColorClass[i];
                        if(g.nbInColorClass[i]==0) newDegrees[i]=0;
                    }
                    newState.degreePerVertex=newDegrees;
                    int newNbOfVertices=it.second;
                    for(int i=0; i<chi; i++)
                    {
                        newNbOfVertices+=g.nbInColorClass[i];
                    }
                    statesOrderedPerDistance[1][newState]=newNbOfVertices;
                    previousState[1][newState]=prevState;
                }
            }
            
            //cout << statesOrderedPerDistance[1].size() << " " << totalNumberOfVertices[1].size() << " " << previousState[1].size() << " " << transitions[1].size() << endl;

            // recursive case
            int dist=2;
            while(dist<=3000)
            {
                cout << "dist: " << dist << endl;
                
                map<state, int> IthMapStateTot;
                statesOrderedPerDistance.push_back(IthMapStateTot);
                
                map<state, state> IthMapStateToPrev;
                previousState.push_back(IthMapStateToPrev);

                //cerr << "dist: " << dist << endl;
                int someOtherCtr=0;
                for(graph g : allGraphs)
                {
                    for(auto it : statesOrderedPerDistance[dist-1])
                    {
                        state prevState=it.first;
                        // heuristic: no 4 followed by 4
                        /*if(dist-1==1)
                        {
                            cerr << "previous graph number of vertices: " << prevState.g.adjacencyList.size() << endl;
                        }*/
                        
                        int newNbOfVertices=it.second;
                        for(int i=0; i<chi; i++)
                        {
                            newNbOfVertices+=g.nbInColorClass[i];
                        }
                        someOtherCtr++;
                        /*if(someOtherCtr%100==0)
                        {
                            cerr << "someOtherCtr: " << someOtherCtr << endl;
                            cerr << "call made, old layer has " << prevState.g.adjacencyList.size() << " vertices and new layer has " << g.adjacencyList.size() << " vertices" << endl;
                        }*/
                        recursivelyGenerateStates(newNbOfVertices,dist,prevState,g);
                    }
                }


                for(auto it : statesOrderedPerDistance[dist])
                {
                    // current graph should be equal to the graph that was added in the second layer
                    // and previous graph should be equal to 1-vertex-graph
                    int currDist=dist;
                    state currState=it.first;
                    graph currGraph=currState.g;
                    if(currGraph.nbInColorClass!=allGraphs[secondLayerID].nbInColorClass) continue;
                    state prevState=previousState[currDist][currState];
                    graph prevGraph=prevState.g;
                    if(prevGraph.nbInColorClass!=allGraphs[firstLayerID].nbInColorClass) continue;
                    int nCurrGraph=0;
                    for(int i=0; i<chi; i++)
                    {
                        nCurrGraph+=currGraph.nbInColorClass[i];
                    }
                    int nbVertices=it.second;
                    if((1.0*(dist-1)/(nbVertices-1-nCurrGraph)-maxx) >= -1e-9)
                    {
                        maxx=1.0*(dist-1)/(nbVertices-1-nCurrGraph);
                        cout << "dist and nbVertices: " << " " << dist-1 << " " << nbVertices-1-nCurrGraph << endl;
                        if(maxx>globalMaxx)
                        {
                            globalMaxx=maxx;
                            correspondingGlobalTeller=dist-1;
                            correspondingGlobalNoemer=nbVertices-1-nCurrGraph;
                        }
                        if(currDist<=200)
                        {
                            while(currDist>=0)
                            {
                                state prevState=previousState[currDist][currState];
                                cout << "Current graph: " << endl;
                                printGraph(currState.g);
                                currDist--;
                                currState=prevState;
                            }
                        }
                        else
                        {
                            cout << "Graph not printed, because too long" << endl;
                        }
                    }
                }

                //cerr << statesOrderedPerDistance[dist].size() <<  " " << previousState[dist].size() << endl; 
                dist+=1;
            }
        }
    }
    
    cout << "globalMaxx, numerator and denominator: " << globalMaxx << " " << correspondingGlobalTeller << " " << correspondingGlobalNoemer << endl;
    //cerr << caseNumber << endl;
    return 0;
}
