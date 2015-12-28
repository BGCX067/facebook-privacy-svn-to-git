//A way to simulate the information spread on a OSN taking into account privacy settings 
//@param number_users
//@number_users = number of users of the OSN 

//Library 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>


/* Probabilities */
int read,sharing,dig,initialFocus,browse,login; 


//Definition of boolean type
enum boolean{
	false = 0,
	true =  1
};

//To let it be declared as a normal type
typedef enum boolean bool; 

// To keep track of the spread
int Nreached=0;

//To define a max number of unread msgs
#define maxMsg 50


//Defines what is an user
typedef struct{
	int *friends;
	bool read,shared;
	short int privacy;
	int news, nFriends; 
}user;


/*********************************************/
/* Functions regarding the simulation itself */
/*********************************************/


//To report errors and abort simulation
void error(char *msg){

	printf("\033[22;31m\n%s\n",msg);

	//change output back to black		
	printf("\033[22;30m");
	exit(1);
}

//To tell how to use the simulator
void usage(){

	printf("Usage: \n ./simulation <input data> <days of simulation>\n"); 
	printf("\t input data: \t \tPath to the file which contains the OSN data\n"); 
	printf("\t days of simulation: \tNumber of days to be simulated"); 

}

//Read the user's data
void buildGraph(user graph[], FILE *input, int nClient){
	
	char line[2048], tmp[2048];	
	int i, friend, cnt_friend;
	
	i=1;
	if(input!=NULL){
		while(!feof(input)){
			fscanf(input, "%hd,", &graph[i].privacy);//setting the privacy
			//printf("Salvei %hd\n", graph[i].privacy);
			fscanf(input, "%2048[^\n]\n", line);
			strcpy(tmp,line);
			char *_tmp=strtok(line, " ,.-");
			cnt_friend=0;
			while(_tmp!=NULL){
				cnt_friend++;
				_tmp=strtok(NULL, " ,.-");
			}
			graph[i].nFriends=cnt_friend;//setting the number of friends
			graph[i].friends=malloc((cnt_friend+1)*sizeof(int));//malloc the list of friends
			_tmp=strtok(tmp, " ,.-");
			cnt_friend=1;
			while(_tmp!=NULL){
				friend=atoi(_tmp);
				graph[i].friends[cnt_friend]=friend; //setting the friends
				_tmp=strtok(NULL, " ,.-");
				cnt_friend++;
			}
			//initialize variables
			graph[i].read=0;
			graph[i].shared=0;
			graph[i].news=0;
			i++;
		}
	}
// ###	printf("I have built a graph with %d users.\n", i-1);
}

//function to tell user's personal information
void userInfo(user graph[], int id){
	printf("ID: %4d\nRead bit: %d\nShared bit: %d\nPrivacy Setting: %hd\nNumber of friends: %d\n", 
			id, graph[id].read, graph[id].shared, graph[id].privacy, graph[id].nFriends);
}

//Shows the last status of the graph
void status(user graph[], int nClient){
	int i;
	printf("%d of %d users were reached by the information spread\n", Nreached,nClient); 
}


//Send a msg for each of the specific user's friends
void sendNews(user graph[], int writer){
	
	int iterator;

	for( iterator=1; iterator <= howManyFriends(graph,writer); iterator++){
		
		if( graph[writer].friends[iterator] != writer && howManyUnread(graph,writer) < maxMsg){
			graph[graph[writer].friends[iterator]].news += 1;
		}		

	}
}

//To store the information about which users were reached by the info spread
void reaches(user graph[], int id){

	if( graph[id].read == 0){
		Nreached += 1;
		graph[id].read =1;
	}
}

//probabilistic model to read Msgs 
int readProbability(){

	int num= rand() % 10;
	int retorno = 0;

//	printf("Read: %d\n",num);
//	printf("Read: %d\n",read);

	if( num >= read ) retorno = 1;
	return retorno;
}

//probabilistic model to share the Msg/Url 
int shareProbability(){
	
	int num= rand() % 10;
	int retorno = 0;

//	printf("Like: %d\n",num);
//	printf("share: %d\n",sharing);
	
	if( num >= sharing) retorno = 1;
	return retorno;
}

//probabilistic model to logging in the OSN
int logginProbability(){
	
	int num= rand() % 10;
	int retorno = 0;

//	printf("Wake: %d\n",num);
//	printf("Wake: %d\n",login);

	if( num >= login ) retorno = 1;
	return retorno;
}

//probabilistic model to browsing in the OSN
int browseProbability(){
	
	int num= rand() % 10;
	int retorno = 0;

//	printf("browse: %d\n",num);

	if( num >=  browse ) retorno = 1;
	return retorno;
}

//probabilistic model to keep diging the OSN
int digProbability(){
	
	int num= rand() % 10;
	int retorno = 0;

//	printf("Dig: %d\n",num);

	//from Fabricio's paper..20% 
	if( num >= dig ) retorno = 1;
	return retorno;
}

//inicial spread
void initialSpread(user graph[], char *inicials)
{	
	//printf("inicials: %s\n", inicials);	

	//assuming an represention of a user's id as char* of maximum 100 characters
	char temp[100];
	
	strcpy(temp,inicials);

	char *inicial = strtok(temp," ,.-");
	int foco;


	while (inicial != NULL)
	{
	//##	printf ("Initial focus: %s\n",inicial);
		foco = atoi(inicial);
		sendNews(graph,foco);
		reaches(graph,foco);
		inicial = strtok (NULL," ,.-");
	}
}



/*********************************************/
/* Functions regarding the user's behavior   */
/*********************************************/

//To tell how many users does a person have
int howManyFriends(user graph[], int id){
	return graph[id].nFriends;
}

//asks how many unreaded msg does a person have
int howManyUnread(user graph[], int id){
	return graph[id].news;
}

//To verify if there is any news to read
int checkNews(user graph[], int id){
	int retorno=0;

	if(graph[id].news > 0){
   		graph[id].news -= 1;
		retorno = 1;
	}

	return retorno;
}

//Rotine to share something in the simulation
void share(user *graph, int id)
{

	if(graph[id].shared == 0){
   		graph[id].shared = 1;
	}
	sendNews(graph, id);

}

//select a friend from user's friends
int randomFriend(user *graph, int id){
	
	int num = rand() % howManyFriends(graph,id) + 1;

	return graph[id].friends[num];
}

int isFriend(user graph[], int user, int friend){
	int a;
	for(a=1;a<=howManyFriends(graph, user);a++){
		if(graph[user].friends[a]==friend)
			return 1;
	}
	return 0;
}

int friendOfFriend(user graph[], int user, int friend){
	int a;
	for(a=1;a<=howManyFriends(graph, user);a++){
		if(isFriend(graph,graph[user].friends[a], friend))
			return 1;
	}
	return 0;
}

int checkProfile(user graph[], int user, int selectedProfile){

	if(graph[selectedProfile].shared){ 
		if(graph[selectedProfile].privacy == 1 &&  isFriend(graph,user,selectedProfile)){
			return 1;
		}else if(graph[selectedProfile].privacy == 2 && friendOfFriend(graph,user,selectedProfile)){
			return 1;
		}
	}
	return 0;	
}

//new behaviour
void behaviour(user graph[], int user){

	int rFriend, newsFriend;
	int viewingUser = user;

	while(graph[user].news > 0){ //news feed loop
		if(readProbability()){
			reaches(graph, user);
			if(shareProbability()){
				share(graph, user);
			}
		}
		graph[user].news--;
	}

	while(browseProbability() == 1){
		rFriend=randomFriend(graph,viewingUser);
		
		if(checkProfile(graph,user,rFriend) && readProbability()){
			reaches(graph,user);
			if(shareProbability()) share(graph,user);
		}
		if( digProbability() ) viewingUser=rFriend;
	}
}

//Simulation itself
void simulation(user graph[], int nClient, int iterations){
	
	int i,j;
	for(i=0; i<iterations; i++){
		for(j=1; j<=nClient; j++){
			if(logginProbability()){
				behaviour(graph,j);
				//printf("The user %d is awake.\n",j);
			}
		}	
	}
}




/*********************************************/
/*********************************************/
int main(int argc, char *argv[]){

	//Checks the usage
	if (argc != 9) {
		usage();	
		error("Invalid numbers of arguments.");	 
	}

	//initial declarations
	FILE *input = fopen(argv[1],"r");
	int nClient;
	fscanf(input,"%d\n", &nClient);
	struct timeval time1, time2;
	user *graph = malloc((nClient + 1)* sizeof(user));
	//gather probabilities
	login= (int)( (1 - atof(argv[4])) * 10 + 0.5);
	read= (int)( (1 - atof(argv[5])) * 10 + 0.5);
	sharing=(int)( (1 - atof(argv[6])) * 10 + 0.5);
	browse= (int)( (1 - atof(argv[7])) * 10 +0.5);
	dig= (int) ( (1 - atof(argv[8])) * 10 + 0.5);
	
//	printf("login %d\n",login);
//	printf("read %d\n",read);
//	printf("shaering %d\n",sharing);
//	printf("browse %d\n",browse);
//	printf("dig %d\n",dig);
    	
	//get the time
	gettimeofday(&time1,NULL);
	
	buildGraph(graph,input,nClient);
	
	srand(time(NULL));


	/*        	          *	 
	 *    Initial spread   	  *	
	 * 		          */

	//initialSpread(graph, "1");
	initialSpread(graph, argv[3]);


	//Starts the simulation
	simulation(graph,nClient,atoi(argv[2]));
	
	//Shows the result
	status(graph,nClient);
	
	//Check the time
	gettimeofday(&time2,NULL);


	//Shows the time spended 
//	printf("tempo total up: : %f s\n" , (float) ( time2.tv_sec - time1.tv_sec + (time2.tv_usec - time1.tv_usec)/1000000.0) );
}
