#include<iostream>
#include <bits/stdc++.h>
using namespace std;

class EpsilonNfa{
	public:
	int numStates;
	set<int>states;
	set<int>finalStates;
	map<int,vector<set<int>>>transitions;

	EpsilonNfa(){
		numStates=0;
	}


	void statesInitialization(){
		for(int i=0;i<numStates;i++){
			states.insert(i);
		}
	}

	void transitionIntialization(){
		for(int i=0;i<numStates;i++){
			transitions[i]={{},{},{}};
		}
	}

	void finalStatesInput(){
		do
		{
			int a;
			cin >> a;
			if(a==-1)   break;
			finalStates.insert(a);
		}while  ( cin.get() != '\n');
	}

	void transitionInput(){
		for(int i=0;i<numStates;i++){
			int a;
			cin>>a;
			set<int>v1={};
			do
			{	
				int b;
				cin >> b;
				if(b==-1)   break;
				v1.insert(b);
			}while  ( cin.get() != '\n');
			set<int>v2={};
			do
			{	
				int c;
				cin >> c;
				if(c==-1)   break;
				v2.insert(c);
			}while  ( cin.get() != '\n');
            set<int>v3={};
			do
			{	
				int d;
				cin >> d;
				if(d==-1)   break;
				v3.insert(d);
			}while  ( cin.get() != '\n');
			transitions[a].push_back(v1);
			transitions[a].push_back(v2);
            transitions[a].push_back(v3);
		}
	}

};