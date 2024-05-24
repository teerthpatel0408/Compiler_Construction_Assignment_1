#include<iostream>
#include <bits/stdc++.h>
using namespace std;

class Nfa{
	public:
	int numStates;
	set<int>states;
	set<int>finalStates;
	map<int,vector<set<int>>>transitions;

	Nfa(){
		numStates=0;
	}
    
    void transitionIntialization(){
		for(int i=0;i<numStates;i++){
			transitions[i]={{},{}};
		}
	}

	void statesInitialization(){
		for(int i=0;i<numStates;i++){
			states.insert(i);
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
			transitions[a].push_back(v1);
			transitions[a].push_back(v2);
		}
	}

	bool checkString(string& str){
		while(true){
			set<int> start={0};
			// string str;
			// cin>>str;
			for(auto k:str){
				set<int>end={};
				if(k=='a'){
					for(auto i:start){
						for(auto j:transitions[i][0]){
							end.insert(j);
						}
					}
				}
				else if(k=='b'){
					for(auto i:start){
						for(auto j:transitions[i][1]){
							end.insert(j);
						}
					}
				}
				else{
					return false;
				}
				start=end;
			}
			// bool var=false;
			for(auto i:start){
				if(finalStates.find(i)!=finalStates.end()){
					// cout<<"String Accepted"<<endl;
					// var=true;
					return true;
					// break;
				}
			}
			// if(!var){
				// cout<<"String Not Accepted"<<endl;
				return false;
			// }
			// cout<<"Input next string"<<endl;
		}
	}

};