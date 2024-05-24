#include<iostream>
#include <bits/stdc++.h>
using namespace std;

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
			for(auto i:start){
				if(finalStates.find(i)!=finalStates.end()){
					return true;
				}
			}
				return false;
		}
	}

};


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

set<int>transitionFuncEnfa(EpsilonNfa*enfa,set<int>st,int inputSymbol){
	set<int>output;
    for(auto i:st){
        for(auto j:enfa->transitions[i][inputSymbol]){
            output.insert(j);
        }
    }
    return output;
}

set<int>epsilonClosure(set<int>st,EpsilonNfa*enfa){    
    while(true){
        set<int>start=st;
        for(auto i:st){
            for(auto j:enfa->transitions[i][2]){
                st.insert(j);
            }
        }
        if(st==start){
            break;
        }
    }
    return st;
}

void decideFinalStatesEnfa(Nfa*n,EpsilonNfa*enfa){
    set<int>output;
    for(auto i:enfa->states){
        set<int>s=epsilonClosure({i},enfa);
        for(auto j:enfa->finalStates){
            if(s.find(j)!=s.end()){
                output.insert(i);
                break;
            }
        }
    }
    n->finalStates=output;
    return;
}

Nfa* enfaToNfa(EpsilonNfa*enfa){
    Nfa*n=new Nfa();
    n->numStates=enfa->numStates;
    n->states=enfa->states;
    for(auto i:enfa->transitions){
        set<int>s1=epsilonClosure({i.first},enfa);

        set<int>s2=transitionFuncEnfa(enfa,s1,0);
        set<int>s3=transitionFuncEnfa(enfa,s1,1);

        set<int>s4=epsilonClosure(s2,enfa);
        set<int>s5=epsilonClosure(s3,enfa);

        n->transitions[i.first].push_back(s4);
        n->transitions[i.first].push_back(s5);
    }
    decideFinalStatesEnfa(n,enfa);
    return n;
}

set<int>transitionFunc(Nfa*n,map<int,set<int>>&mp,int stateCnt,int inputSymbol){
	set<int>vect;
	set<int>arr=mp[stateCnt];
	for(auto i:arr){
		set<int>temp=n->transitions[i][inputSymbol];
		for(auto j:temp){
			vect.insert(j);
		}
	}
	return vect;
}



void printNfa(Nfa*n){
	cout<<"No. of States: "<<n->numStates<<endl;
	cout<<"Printing States: ";
	for(auto i:n->states){
		cout<<i<<" ";
	}
	cout<<"Printing Transitions"<<endl;
	for(auto i:n->transitions){
		cout<<i.first<<"    ";
		for(auto j:i.second[0]){
			cout<<j<<" ";
		}
		cout<<"    ";
		for(auto j:i.second[1]){
			cout<<j<<" ";
		}
		cout<<endl;
	}
	cout<<"Final States: ";
	for(auto i:n->finalStates){
		cout<<i<<" ";
	}
}

void printEnfa(EpsilonNfa*d){
	cout<<"No. of States: "<<d->numStates<<endl;
	cout<<"Printing States: ";
	for(auto i:d->states){
		cout<<i<<" ";
	}
	cout<<"Printing Transitions"<<endl;
	for(auto i:d->transitions){
		cout<<i.first<<"    ";
		for(auto j:i.second[0]){
			cout<<j<<" ";
		}
		cout<<"..";
		for(auto j:i.second[1]){
			cout<<j<<" ";
		}
		cout<<"..";
		for(auto j:i.second[2]){
			cout<<j<<" ";
		}
		cout<<endl;
	}
	cout<<"Final States: ";
	for(auto i:d->finalStates){
		cout<<i<<" ";
	}
    cout<<endl<<endl;
}

string infixToPostfix(string& regularExp){
    for(int i=0;regularExp[i]!='\0';i++){
        if(regularExp[i]==')' && regularExp[i+1]=='('){
            regularExp.insert(i+1,".");
            i++;
        }
    }
    stack<char>stk;
    string postfix="";
    for(auto i:regularExp){
        if(isalpha(i)){
            postfix+=i;
        }
        else if(i=='('){
            stk.push('(');
        }
        else if(i==')'){
            while(stk.top()!='('){
                postfix+=stk.top();
                stk.pop();
            }
            stk.pop();
        }
        else{
            if(i=='|'){
                while(stk.top()=='*' || stk.top()=='.' || stk.top()=='|' || stk.top()=='+' || stk.top()=='?'){
                    postfix+=stk.top();
                    stk.pop();
                }
                stk.push('|');
            }
            else if(i=='.'){
                while(stk.top()=='*' || stk.top()=='.' || stk.top()=='+' || stk.top()=='?'){
                    postfix+=stk.top();
                    stk.pop();
                }
                stk.push('.');
            }
            else if(i=='*'){
                while(stk.top()=='*' || stk.top()=='+' || stk.top()=='?'){
                    postfix+=stk.top();
                    stk.pop();
                }
                stk.push('*');
            }
            else if(i=='+'){
                while(stk.top()=='*' || stk.top()=='+' || stk.top()=='?'){
                    postfix+=stk.top();
                    stk.pop();
                }
                stk.push('+');
            }
            else if(i=='?'){
                while(stk.top()=='*' || stk.top()=='+' || stk.top()=='?'){
                    postfix+=stk.top();
                    stk.pop();
                }
                stk.push('?');
            }
        }
    }
    return postfix;
}

EpsilonNfa*createNfa(char symbol){
    EpsilonNfa*enfa=new EpsilonNfa();
	
    enfa->numStates=2;
	enfa->statesInitialization();
	enfa->transitionIntialization();
    enfa->finalStates={1};
    if(symbol=='a'){
        enfa->transitions[0]={{1},{},{}};
    }
    else if(symbol=='b'){
        enfa->transitions[0]={{},{1},{}};
    }
    return enfa;
}

EpsilonNfa*concate(EpsilonNfa*enfa1,EpsilonNfa*enfa2){
    EpsilonNfa*enfa=new EpsilonNfa();
    int n1=enfa1->numStates;
    int n2=enfa2->numStates;
	
    enfa->numStates=n1+n2;
	enfa->statesInitialization();
	enfa->transitionIntialization();
	for(auto& i:enfa1->transitions){
        enfa->transitions[i.first]=enfa1->transitions[i.first];
    }
    for(auto& i:enfa2->transitions){
        set<int>s1;
        for(auto& j:i.second[0]){
           s1.insert(j+n1);
        }
		set<int>s2;
        for(auto& j:i.second[1]){
            s2.insert(j+n1);
        }
        set<int>s3;
        for(auto& j:i.second[2]){
            s3.insert(j+n1);
        }
        enfa->transitions[i.first+n1]={s1,s2,s3};
    }
	
    enfa->transitions[n1-1][2].insert(n1);
	
    enfa->finalStates={n1+n2-1};
	
    return enfa;
}

EpsilonNfa*add(EpsilonNfa*enfa1,EpsilonNfa*enfa2){
    EpsilonNfa*enfa=new EpsilonNfa();
	
    int n1=enfa1->numStates;
    int n2=enfa2->numStates;
    enfa->numStates=n1+n2+2;
	enfa->statesInitialization();
	enfa->transitionIntialization();

    enfa->transitions[0]={{},{},{1,n1+1}};

    for(auto& i:enfa1->transitions){
        set<int>s1;
        for(auto j:i.second[0]){
            s1.insert(j+1);
        }
        set<int>s2;
        for(auto j:i.second[1]){
            s2.insert(j+1);
        }
        set<int>s3;
        for(auto j:i.second[2]){
            s3.insert(j+1);
        }
        enfa->transitions[i.first+1]={s1,s2,s3};
    }
    for(auto& i:enfa2->transitions){
        set<int>s1;
        for(auto j:i.second[0]){
            s1.insert(j+n1+1);
        }
        set<int>s2;
        for(auto j:i.second[1]){
            s2.insert(j+n1+1);
        }
        set<int>s3;
        for(auto j:i.second[2]){
            s3.insert(j+n1+1);
        }
        enfa->transitions[i.first+n1+1]={s1,s2,s3};
    }
    enfa->transitions[n1][2].insert(n1+n2+1);
    enfa->transitions[n1+n2][2].insert(n1+n2+1);
    enfa->finalStates={n1+n2+1};
    return enfa;
}

EpsilonNfa*star(EpsilonNfa*enfa1){
    EpsilonNfa*enfa=new EpsilonNfa();
	
    int n=enfa1->numStates;
    enfa->numStates=enfa1->numStates+2;
	enfa->statesInitialization();
	enfa->transitionIntialization();
    for(auto& i:enfa1->transitions){
        set<int>s1;
        for(auto j:i.second[0]){
            s1.insert(j+1);
        }
        set<int>s2;
        for(auto j:i.second[1]){
            s2.insert(j+1);
        }
        set<int>s3;
        for(auto j:i.second[2]){
            s3.insert(j+1);
        }
        enfa->transitions[i.first+1]={s1,s2,s3};
    }
    enfa->transitions[0][2].insert(1);
    enfa->transitions[1][2].insert(n);
    enfa->transitions[n][2].insert(1);
    enfa->transitions[n][2].insert(n+1);
	enfa->finalStates={n+1};
    return enfa;
}

EpsilonNfa*positiveClosure(EpsilonNfa*enfa1){
    EpsilonNfa*enfa=new EpsilonNfa();
	
    int n=enfa1->numStates;
    enfa->numStates=enfa1->numStates;
	enfa->statesInitialization();
	enfa->transitionIntialization();
    for(auto& i:enfa1->transitions){
        enfa->transitions[i.first]=enfa1->transitions[i.first];
    }
    enfa->transitions[n-1][2].insert(0);
	enfa->finalStates=enfa1->finalStates;
    return enfa;
}

EpsilonNfa*questionMark(EpsilonNfa*enfa1){
    EpsilonNfa*enfa=new EpsilonNfa();
	
    int n=enfa1->numStates;
    enfa->numStates=enfa1->numStates;
	enfa->statesInitialization();
	enfa->transitionIntialization();
    for(auto& i:enfa1->transitions){
        enfa->transitions[i.first]=enfa1->transitions[i.first];
    }
    enfa->transitions[0][2].insert(n-1);
	enfa->finalStates=enfa1->finalStates;
    return enfa;
}

EpsilonNfa*finalEnfa(string postFix){
    stack<EpsilonNfa*>stk;
    for(auto i:postFix){
        EpsilonNfa*test;
        if(isalpha(i)){
            test=createNfa(i);
            stk.push(test);
        }
        else if(i=='*'){
            EpsilonNfa*temp=stk.top();
            stk.pop();
            test=star(temp);
            stk.push(test);
			
        }
        else if(i=='|'){
            EpsilonNfa*temp1=stk.top();
            stk.pop();
            EpsilonNfa*temp2=stk.top();
            stk.pop();
            test=add(temp2,temp1);
            stk.push(test);
			
        }
        else if(i=='.'){
            EpsilonNfa*temp1=stk.top();
            stk.pop();
            EpsilonNfa*temp2=stk.top();
            stk.pop();
            test=concate(temp2,temp1);
            stk.push(test);
        }
        else if(i=='+'){
            EpsilonNfa*temp=stk.top();
            stk.pop();
            test=positiveClosure(temp);
            stk.push(test);
        }
        else if(i=='?'){
            EpsilonNfa*temp=stk.top();
            stk.pop();
            test=questionMark(temp);
            stk.push(test);
        }
    }
    return stk.top();
}

int check(vector<Nfa*>&vect,string& str){
    int cnt=1;
    for(auto i:vect){
        if(i->checkString(str)){
            return cnt;
        }
        cnt++;
    }
    return -1;
}

int main(){
    ifstream inputFile("input4.txt");
    if (!inputFile.is_open()) {
        cout << "Error opening file!" << endl;
        return 1;
    }

    string str;
    getline(inputFile, str);

    str.erase(std::remove_if(str.begin(), str.end(), ::isspace), str.end());
    vector<Nfa*>vect;
    string regularExp;
    while(getline(inputFile,regularExp)){
        string postFix=infixToPostfix(regularExp);
        EpsilonNfa* enfa=finalEnfa(postFix);
        Nfa* n=enfaToNfa(enfa);
        vect.push_back(n);
    }
    inputFile.close();
    string ans="";
    int si=0,ei=str.size()-1;
    while(true){
        if(si==str.size())  break;
        string s=str.substr(si,ei-si+1);
        int val=check(vect,s);
        if(val!=-1){
            ans+=("<"+s+","+to_string(val)+">");
            si=ei+1;
            ei=str.size()-1;
        }
        else{
            if(s.size()==1){
                ans+=("<"+s+",0"+">");
                si=ei+1;
                ei=str.size()-1;
                continue;
            }
            ei--;
        }
    }
    ofstream outputFile("output.txt");

    if (!outputFile.is_open()) {
        cout << "Error opening output file!" << endl;
        return 1;
    }

    outputFile << ans; 
    outputFile.close();
    return 0;
}