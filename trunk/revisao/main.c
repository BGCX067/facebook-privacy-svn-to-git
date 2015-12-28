#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct{
	char fb_id[20];
	int visitor_id;
	int friends[2000];
	int n_friends;
}user;

int users=0;

int main(int argv, char **argc){

	FILE *visitors, *friends;
	visitors=fopen(argc[1], "r");
	friends=fopen(argc[2], "r");
	
	int visitor_id;
	char fb_id[20];

	//aux
	int a, b, mark, ishere, fhere;


	user graph[1000];
	for(a=0;a<1000;a++)
		graph[a].n_friends=0;


	if(!visitors || !friends){
		printf("input file error\n");
		exit(1);
	}
	while(!feof(visitors)){
		mark=0;
		fscanf(visitors,"%d %s", &visitor_id, fb_id);
		for(b=1;b<=users;b++){
			if(strcmp(fb_id, graph[b].fb_id)==0){
			mark=1;
			graph[b].visitor_id=visitor_id;
			//printf("repeated %s on position %d\n", fb_id, b);
			break;
			}
		}
		if(mark==0){
			users++;
			//printf("inserted %s on position %d\n", fb_id, users);
			strcpy(graph[users].fb_id, fb_id);
			graph[users].visitor_id=visitor_id;
		}
	}

	//it seems right, 743 users. sort & uniq return 425 users from visitors_table, this is weird

	//printf("unique users: %d\n", users);

	while(!feof(friends)){
		fscanf(friends, "%d %[^\n]", &visitor_id, fb_id);
		mark=-1;
		ishere=0;
		fhere=0;
		//find visitor_id and check if fb_id is on the list
		for(a=1;a<=users;a++){
			if(graph[a].visitor_id==visitor_id)
				mark=a;
			if(strcmp(graph[a].fb_id, fb_id)==0)
				ishere=a;
		}
		//add on friend list
		if(ishere>0 && mark>0){
			for(b=0;b<graph[mark].n_friends;b++)
				//if(strcmp(fb_id,graph[mark].friends[b])==0){
				if(ishere==graph[mark].friends[b]){
					fhere=1;
					break;
				}
			//add at the end
			if(!fhere){
				graph[mark].friends[graph[mark].n_friends++]=ishere;
				//strcpy(graph[mark].friends[graph[mark].n_friends++], ishere);
			}
		}
	}

	printf("*Vertices %d\n", users);
	for(a=1;a<=users;a++)
		printf("%d %d\n", a, a);

	printf("*Edges\n");
	for(a=1;a<=users;a++){
		if(graph[a].n_friends>0)
			for(b=0;b<graph[a].n_friends;b++){
				printf("%d %d\n", a, graph[a].friends[b]);
				printf("%d %d\n", graph[a].friends[b], a);
			}
	}	

/*	for(a=1;a<=users;a++){
		printf("%3d", a);
		if(graph[a].n_friends>0)
			printf(", ");
		for(b=0;b<graph[a].n_friends;b++)
			printf("%3d ", graph[a].friends[b]);
		printf("\n");
	}*/
	//this print a directed graph!

	return 0;
}
