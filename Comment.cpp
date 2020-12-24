#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct NodeComment{
	int like = 0;
	char comment[255];
  int time = 0;//udh sorted based on newest entry, jika like sama
	NodeComment *next, *prev;
}*headcomment, *tailcomment;

int filter(char str[]){
	int len = strlen(str);
	for ( int i = 0; i < len; i++){
		if (!isalnum(str[i])){
			return 1;
		}
	}
	return -1;
}

//Create Node Buat Comment (ordered by likes)
struct NodeComment* createComment( const char *comm, int likes){
    NodeComment *temp = (NodeComment*)malloc(sizeof(NodeComment));
    strcpy (temp->comment, comm);
    temp->like = likes;
    temp->time = 0;
    temp->next = temp->prev = NULL;
    return temp;
}


void pushHeadComment(const char *comm, int likes){
  NodeComment *temp = createComment(comm, likes);
  if (!headcomment){
    headcomment = tailcomment = temp;
  }else{
    headcomment->prev = temp;
    temp->next = headcomment;
    headcomment = temp;
  }
}

void pushTailComment(const char *comm, int likes){
  NodeComment *temp = createComment(comm, likes);
  if (!headcomment){
    headcomment = tailcomment = temp;
  }else{
    temp->prev = tailcomment;
    tailcomment->next = temp;
    tailcomment = temp;
  }
}


void pushMidComment(const char *comm, int likes){
  NodeComment *temp = createComment(comm, likes);
  if (!headcomment){
    headcomment = tailcomment = temp;
  }
  else if (likes >= headcomment->like){//Comment Terbaru yang like sama duluan
    pushHeadComment(comm, likes);
  }
  else if (likes < tailcomment->like){//Ngebug disini
    pushTailComment(comm, likes);
  }
  else{
    NodeComment *curr = headcomment;
    while (curr!= NULL && likes < curr->like){
      curr = curr->next;
    }
    temp->prev = curr->prev;
    temp->next = curr;
    curr->prev->next = temp;
    curr->prev = temp;
  }
}

//Validasi Comment beserta scan Comment
void WriteComment(){
	puts("[O] Leave a Comment (1-255 Alphanumeric)");
	char str[500];
	int flag = 1;
	while ( flag == 1){
		scanf("%[^\n]", str);
		getchar();
		if ( strlen(str)>255){
			puts("[X] Comment too Long, Please Re-enter Comment!");
			flag = 1;
		}
		else if (filter(str) == 1){
			puts("[X] Your Comment Contains Non Alphanumeric Characters, Please Re-enter Comment!");
			flag = 1;
		}
		else{
			flag = 0;
		}
	}
  int likes = 0;
  puts("[V] Comment Registered!, How many Likes would you like to give?");
    scanf("%d", &likes);
    getchar();
	printf("[V] Uploaded: %s\n", str);
  printf("[V] With %d <3\n",likes);
  pushMidComment(str, likes);
}

void printCommentLinkedList(){
  if(!headcomment){
    puts("No Comments!");
    return;
  }
  NodeComment *curr = headcomment;
  puts("Comments:");
  while (curr){
    printf("%d <3 :: %s\n", curr->like, curr->comment);
    curr = curr->next;
  }
  puts("===========");
}

int main (){
	WriteComment();
  printf("tail: %d %s\n", tailcomment->like, tailcomment->comment);
  printCommentLinkedList();
  WriteComment();
  printf("tail: %d %s\n", tailcomment->like, tailcomment->comment);
  printCommentLinkedList();
  WriteComment();
  printf("tail: %d %s\n", tailcomment->like, tailcomment->comment);
  printCommentLinkedList();
	return 0;
}
