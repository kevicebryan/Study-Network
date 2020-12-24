#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

struct UserNode{
  char name[255];
  char password[255];
  int no;
  UserNode *next,*prev;
}*userhead,*usertail,*usercurr;


int filter(char str[]){
	int len = strlen(str);
	for ( int i = 0; i < len; i++){
		if (!isalnum(str[i])){
			return 1;
		}
	}
	return -1;
}


//gw buat struct buat nampilin username yang udah ada
UserNode *createNode (const char *name, const char *password, int no){
  UserNode *newNode = (UserNode*)malloc(sizeof(UserNode));
  strcpy(newNode->name,name);
  strcpy(newNode->password,password);
  newNode->no = no;
  newNode->next = newNode->prev = NULL;
  return newNode;
}

void pushUserHead(const char *name,const char *pass,int no){
  UserNode *temp = createNode(name,pass,no);
  if(!userhead){
    userhead = usertail = temp;
  } else {
    temp->next = userhead;
    userhead->prev = temp;
    userhead = temp;
  }
}

void pushUserTail(const char *name,const char *pass, int no){
  UserNode *temp = createNode(name,pass,no);
  if(!userhead){
    userhead = usertail = temp;
  } else {
    temp->prev = usertail;
    usertail->next = temp;
    usertail = temp;
  }
}

void pushUserMid(const char *name,const char *pass, int no){
  UserNode *temp = createNode(name,pass,no);
  if(!userhead){
    userhead = usertail = temp;
  } else if (strcmp(name,userhead->name) < 0){
    pushUserHead(name,pass,no);
  } else if (strcmp(name,usertail->name) > 0){
    pushUserTail(name,pass,no);
  } else {
    UserNode *usercurr = userhead;
    while(strcmp(name, usercurr->name) > 0){
      usercurr = usercurr->next;
    }
    temp->prev = usercurr->prev;
    temp->next = usercurr;
    temp->prev->next = temp;
    usercurr->prev = temp;
  }
}

void menu();
void loginMenu();
//Fungsi Validasi Registrasi
void Regis(){
  char tempusername[255];
  char temppassword[255];
  int flagregis = 1;
  int flagada = 0;
  int flagabort = 0;
  int flagpassword = 1;
  int tempno = 1;
  UserNode *checknode = userhead;
  while ( flagregis == 1){
    puts("Username (lowercase 1-24char): ");
    scanf("%[^\n]", tempusername);
    getchar();
    if (strcmp(tempusername, "0") == 0){//0 to abort
      flagregis = 0;
      flagabort = 1;
        menu();//return ke menu
    }
    if (flagabort == 0){
      while (userhead){
       if (strcmp(tempusername, checknode->name)==0){
          puts("[X] Sorry, Username taken!");
         flagada = 1;
          break;
        }
        checknode = checknode->next;
        tempno++;
      }
    }
    if (flagabort == 0 && flagada == 0 && strlen(tempusername)<=24 && filter(tempusername) == -1){
      flagregis = 0;
      puts("[V] Username OK, Insert Password!");
    }else{
      puts("[X] Username TooLong and/or Contains Non AlphaNum");
    }
  }   
  while (flagpassword == 1 && flagregis == 0){
      printf("Password: ");
      scanf("%[^\n]", temppassword);
      getchar();
      if (strcmp(temppassword, "0")==0){
        flagabort = 1;
        flagpassword = 0;
        menu();//return ke  menu();
      }
      if (flagabort == 0 && strlen(temppassword)<= 24 && filter(temppassword)== -1){
        flagpassword = 0;
      }else{
        puts("[X] Please re-enter Password (1-24 Char) Alphanumeric");
      }
  }
  if (flagpassword == 0 & flagregis == 0){//No Kesalahan baru masukkan
    pushUserMid(tempusername, temppassword, tempno);
    puts("[V] Username & Password Registered");
    int any;
    puts("Enter any number to return to menu!");
    scanf("%d", &any);
    getchar();
    menu();
  }

}

//Fungsi Validasi Login
void Login(){
  char tempname[255];
  char temppass[255];
  int flaglogin = 1;
  int flagada = 0;
  int flagabort = 0;
  int flagpassword = 1;
  UserNode *testlogin = userhead;
  while(flaglogin == 1){
    printf("Username: ");
    scanf("%[^\n]", tempname);
    getchar();
    if (strcmp(tempname, "0")==0){//Checking Abort
      flagabort = 1;
      flaglogin = 0;
      menu();
    }
    if (flagabort == 0){
      while (testlogin){
        if (strcmp (testlogin->name, tempname)== 0){//Checking Username
          flagada = 1;
          break;
        }
       testlogin = testlogin->next;
      }
    }
     if (flagabort = 0 && flagada == 0){
      puts("[X] Invalid Username, Try Again!");
    }
  }
 
  if (flagabort == 0 && flagada == 1 && flaglogin == 0){
      while(flagpassword = 1){
        printf("Passowrd: ");
        scanf("%[^\n]",temppass);
        getchar();
        if (strcmp(temppass, "0")==0){//Checking abort
          flagabort = 1;
          menu();
        }

        if (strcmp(temppass, testlogin->password)==0){
          flagpassword = 0;//password benar!
        }else{
          puts("[X] Wrong Password, try Again!");
        }
      }
  }
  if (flaglogin == 0 && flagpassword == 0){//Jadikan CurrUser
    usercurr = testlogin;
    loginMenu();
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
  clock_t begin = clock();
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
    usercurr = userhead;
    while(usercurr){
      printf ("%-4d %-10s\n",usercurr->no,usercurr->name);
      usercurr = usercurr->next;
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
    getchar();
    puts("---------------------------");
    if(choose == 1){
    Regis();
    } else if(choose == 2){ // lanjutin dari sini aja functionnya
    Login();
    } else if(choose == 3){
      exitMenu();
    } else if(choose == 0){
      exitMenu();
    } 
      else if (choose == 4){ //--> ini ngetest buat masuk ke login menu doang
       loginMenu();
       clock_t end = clock();
       double timeUsed = (double) (end-begin)/CLOCKS_PER_SEC;
       printf ("You Have Used Our Application for %.2lf second\nPress Any Key to Return...",timeUsed*3600);
       char c;
       scanf ("%c", &c);
       getchar();
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
      return;
    }

    puts("---------------------------");
  }
}

int main(){
  // pushTail("Denny","Denny123",1); //--> ini ngetest doang, kalo mau cek uncommand deh
  // menu();
  Regis();

  return 0;
}
