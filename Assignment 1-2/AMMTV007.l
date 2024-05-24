%{


#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<math.h>
    
int k1 = 0, k2=0, k3=0, k4=0, cnt = 0, ctuple = 0;
bool check = false, fromID = false;
char StudID[31];
FILE *fp;
    
struct studentCourse {
	char course[31];
	int credit;
	char grade[31];
};
    
struct studentCourse sc[1000];
struct studentCourse currCourse;


%}


%x y
%x consume
%x custID
%x startTuple
%x courses
%x unit
%x grades
%x endTuple
%x consumeSpace1
%x consumeSpace2


%%


[$][' '\t]* {
	BEGIN(custID);
}
[^$] {
	unput(yytext[0]); 
	BEGIN(y);
}


<y>[$] {
	cnt = 0; 
	unput('$');
	BEGIN(INITIAL);
}
<y>[\n] {
	cnt = 0; 
	BEGIN(INITIAL);
}
<y>. { 	
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);
		}
		else{
			BEGIN(y);
		}
	}
	else {
		cnt = 0;
		BEGIN(y);
	}
}


<consume>. {
	BEGIN(consume);
}
<consume>\n {
	BEGIN(INITIAL);
}


<custID>[A-Z]+[0-9]+ {
	ctuple = 0;
        if(cnt != 0){
        	cnt = 0;
        	BEGIN(y);
        }
        else{
		if(strcmp(StudID,yytext) == 0){
			check = true;
		}
		else{
			check = false;	
		}
		fromID = true;
		BEGIN(startTuple);
	}
}
<custID>[$] {
	cnt = 0; 
	unput('$');
	BEGIN(INITIAL);
}
<custID>[\n] {
	cnt = 0; 
	BEGIN(INITIAL);
}
<custID>. { 
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);	
		}
		else{
			BEGIN(custID);
		}
	}
	else{
		cnt = 0;
		BEGIN(y);
	}
}


<startTuple>[<] {
	if(cnt != 0 && fromID){
		BEGIN(INITIAL);
	}
	else{
		BEGIN(courses);
	}
	cnt = 0;
	fromID = false;
}
<startTuple>[$] {
		cnt = 0; 
		unput('$');
		BEGIN(INITIAL);
}
<startTuple>\n {
	cnt = 0; 
	BEGIN(INITIAL);
}
<startTuple>. {
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);	
		}
		else{
			BEGIN(startTuple);
		}
	}
	else if(strcmp(yytext, " ") == 0){
		cnt = 0;
		BEGIN(startTuple);
	}
	else{
		if(fromID){
			BEGIN(y);
		}
		else{
			cnt = 0;
			BEGIN(startTuple);
		}
	}
}


<courses>[A-Z]+[0-9]+ {
	if(cnt != 0){
		cnt = 0;
		BEGIN(startTuple);
	}
	else{
		strcpy(currCourse.course,yytext);
		BEGIN(consumeSpace1);
	}
}
<courses>\n {
	cnt = 0; 
	BEGIN(INITIAL);
}
<courses>. {
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);	
		}
		else{
			BEGIN(courses);
		}
	}
	else if(strcmp(yytext, " ") == 0){
		cnt = 0;
		BEGIN(courses);
	}
	else{
		BEGIN(startTuple);
	}
}

   
<unit>[2-4] {
	if(cnt != 0){
		cnt = 0;
		BEGIN(startTuple);
	}
	else{
		currCourse.credit = yytext[0] - '0';
		BEGIN(consumeSpace2);
	}
}
<unit>\n {
	cnt = 0; 
	BEGIN(INITIAL);
}
<unit>. {
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);	
		}
		else{
			BEGIN(unit);
		}
	}
	else{
		cnt = 0;
		BEGIN(startTuple);
	}
}


<grades>[A-B][\-]?|[C] {
	if(cnt != 0){
		cnt = 0;
		BEGIN(startTuple);
	}
	else{
		strcpy(currCourse.grade,yytext);
		BEGIN(endTuple);
	}
}
<grades>\n {
	cnt = 0; 
	BEGIN(INITIAL);
}
<grades>. { 
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);	
		}
		else{
			BEGIN(grades);
		}
	}
	else{
		cnt = 0;
		BEGIN(startTuple);
	}
}


<endTuple>[>] {
	if(cnt != 0){
		cnt = 0;
		BEGIN(startTuple);
	}
	else{
		if(check){
			ctuple++;
			bool flag = false;
			for(int i=0;i<k3;i++)
			{
				if(strcmp(currCourse.course,sc[i].course)==0)
				{
					strcpy(sc[i].grade,currCourse.grade);
					flag = true;
					break;
				}
			}
			if(!flag)
			{
				strcpy(sc[k3].course,currCourse.course);
				sc[k3].credit=currCourse.credit;
				strcpy(sc[k3].grade,currCourse.grade);
				k3++;
			}
			if(ctuple == 1){
				k1++;
			}
			BEGIN(startTuple);
		}
		else{
			k1++;
			BEGIN(y);
		}
	}
}
<endTuple>\n {
	cnt = 0; 
	BEGIN(INITIAL);
}
<endTuple>. {
	if(strcmp(yytext, "/") == 0){
		cnt++;
		if(cnt == 2){
			cnt = 0;
			k2++;
			BEGIN(consume);	
		}
		else{
			BEGIN(endTuple);
		}
	}
	else if(strcmp(yytext, " ") == 0){
		cnt = 0;
		BEGIN(endTuple);
	}
	else{
		BEGIN(startTuple);
	}
}


<consumeSpace1>[' '\t]+ {
	BEGIN(unit);
}
<consumeSpace1>\/\/ {
	BEGIN(consume);
}
<consumeSpace1>\n {
	BEGIN(INITIAL);
}
<consumeSpace1>. {
	BEGIN(startTuple);
}

<consumeSpace2>[' '\t]+ {
	BEGIN(grades);
}
<consumeSpace2>\/\/ {
	BEGIN(consume);
}
<consumeSpace2>\n {
	BEGIN(INITIAL);
}
<consumeSpace2>. {
	BEGIN(startTuple);
}


%%


int yywrap(){
	return 1;
}


void main(){
	fp = fopen("input.txt","r");
	fscanf(fp,"%s", StudID);
	fclose(fp);
	yyin = fopen("data.txt","r");

	fp = fopen("output.txt", "w+");
	yylex();
	
	float num =0 ,den =0;
	for(int i=0;i<k3;i++){
	    	den+=sc[i].credit;
	    	if(strcmp(sc[i].grade,"A")==0){
	    		num=num + (sc[i].credit*10);
	    	}
	    	else if(strcmp(sc[i].grade,"A-")==0){
	    		num=num + (sc[i].credit*8);
	    	}
	    	else if(strcmp(sc[i].grade,"B")==0){
	    		num=num + (sc[i].credit*6);
	    	}
	    	else if(strcmp(sc[i].grade,"B-")==0){
	    		num=num + (sc[i].credit*4);
	    	}
	    	else{
	    		num=num + (sc[i].credit*2);
	    	}
	}
	
	if(k3){
		float temp = (num/den)*100;
		k4 = round(temp);
	}
    
	fprintf(fp, "@%d@%d@%d@%d#\n", k1, k2, k3, k4);
	fclose(fp);  
     
	return;
}
