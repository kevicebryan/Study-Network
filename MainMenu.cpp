#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
clock_t begin = clock();
struct Node{
  char name[255];
  char password[255];
  int no;
  Node *next,*prev;
}*head,*tail,*curr;
//gw buat struct buat nampilin username yang udah ada
Node *createNode (const char *name, const char *password, int no){
  Node *newNode = (Node*)malloc(sizeof(Node));
  strcpy(newNode->name,name);
  strcpy(newNode->password,password);
  newNode->no = no;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

void pushHead(const char *name,const char *pass,int no){
  Node *temp = createNode(name,pass,no);
  if(!head){
    head = tail = temp;
  } else {
    temp->next = head;
    head->prev = temp;
    head = temp;
  }
}

void pushTail(const char *name,const char *pass, int no){
  Node *temp = createNode(name,pass,no);
  if(!head){
    head = tail = temp;
  } else {
    temp->prev = tail;
    tail->next = temp;
    tail = temp;
  }
}

void pushMid(const char *name,const char *pass, int no){
  Node *temp = createNode(name,pass,no);
  if(!head){
    head = tail = temp;
  } else if (strcmp(name,head->name) < 0){
    pushHead(name,pass,no);
  } else if (strcmp(name,tail->name) > 0){
    pushTail(name,pass,no);
  } else {
    Node *curr = head;
    while(strcmp(name, curr->name) > 0){
      curr = curr->next;
    }
    temp->prev = curr->prev;
    temp->next = curr;
    temp->prev->next = temp;
    curr->prev = temp;
  }
}

void cls(){
  for(int i = 0 ; i < 32 ; i++){
    puts("");
  }
}

void exitMenu(){
  exit(0);
}

void loginMenu();

void menu(){
  while(1){
    cls();// ini cls buat clear screen doang kok, functionny ada diatas
    puts("Oo==========================================oO");
    puts("                   STUDY NETWORK              ");
    puts("Oo==========================================oO");
    puts("");
    puts("[All User]");
    puts("");
    printf ("No.  ");
    printf ("Username\n");// dibagian sini butuh data jadi gw sedian struct dl aja ya, kalo salah ganti aja oke? wkwkw
    curr = head;
    while(curr){
      printf ("%-4d %-10s\n",curr->no,curr->name);
      curr = curr->next;
    }
    puts("");
    puts("---------------------------");
    puts("[1] Register");
    puts("[2] Login");
    puts("[3] Exit");
    puts("---------------------------");
    puts("Press 0 and enter to abort an operation");
    puts("---------------------------");
    printf (">> ");
    int choose;
    scanf ("%d", &choose);
    puts("---------------------------");
    if(choose == 1){
    //  regis();
    } else if(choose == 2){ // lanjutin dari sini aja functionnya
   //   login();
    } else if(choose == 3){
      exitMenu();
    } else if(choose == 0){
      exitMenu();
    } 
      else if (choose == 4){ //--> ini ngetest buat masuk ke login menu doang
       loginMenu();
     }
  }
}

void loginMenu(){
  time_t t;
  time(&t);
  while(1){
    cls();
    puts   ("Oo==========================================oO");
    printf ("Welcome,              \n");// ini gw blm bisa lanjutin soalnya perlu nama setelah login
    puts   ("Oo==========================================oO");
    printf ("Logged in: %s\n",ctime(&t));
    puts("---------------------------");
    puts("");
    printf ("[All Friends of \n");// ini gw jg blm bisa lanjutin, harus setelah login
    puts("---------------------------");
    puts("          >>Menu<<         ");
    puts("---------------------------");
    puts("[1] Add Friend");
    puts("[2] Remove Friend");
    puts("[3] View Inbox");
    puts("[4] View Sent Requests");
    puts("[5] Add Edit, Announce, Delete Note");
    puts("[6] Logout");
    puts("---------------------------");
    printf (">> ");
    int c;
    scanf ("%d", &c);
    if(c == 1){

    } else if( c == 2 ){

    } else if( c == 3 ){

    } else if ( c == 4 ){

    } else if ( c == 5 ){

    } else if ( c == 6 ){
      clock_t end = clock();
      double timeUsed = (double) (end-begin)/CLOCKS_PER_SEC;
      printf ("You Have Used Our Application for %lf second\nPress Any Key to Return...",timeUsed);
      char c;
      scanf ("%c", &c);
      getchar();
      return;
    }

    puts("---------------------------");
  }
}

int main(){
  //pushTail("Denny","Denny123",1); --> ini ngetest doang, kalo mau cek uncommand deh
  menu();
  return 0;
}