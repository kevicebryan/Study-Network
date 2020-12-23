#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define gtc getchar
// #define ll long long int


struct User {
  char name[255];
  char password[255];
  User *friends;
  User *next, *prev;
};


User *newUser(const char *name) {
  User *temp = (User*)malloc(sizeof(User));
  strcpy(temp->name, name);
  temp->next = temp->prev = NULL;
  return temp;
}

// push function
void push(User *&users, const char *name) {
  User *temp = newUser(name);
  temp->friends = NULL; // 
  if(!users) {
    users = temp;
  }
  else {
    temp->next = users;
    users->prev = temp;
    users = temp;
  }
}
// print users
void printUsers(User *&users) {
  // if there is no user, return
  if(!users) {
    puts("No users!");
    return;
  }
  User *temp = users;
  int i = 1; // indexing
  while(temp) {
    printf("%d. %s\n", i++, temp->name);
    temp = temp->next;
  }
}
// add friend
void addFriend(User *&friends, const char *name) {
  User *temp = newUser(name);
  if(!friends) {
    friends = temp;
  } else {
    temp->next = friends;
    friends->prev = temp;
    friends = temp;
  }

}

// remove friend belom slese T.T
void removeFriend(User *&friends, const char *name) {
  if(strcmp(friends->name, name) == 0) {
    User *temp = friends->next;
    friends->next = temp->prev = NULL;
    free(friends);
    friends = temp;
  } else {
    
  }
}



int main(){

  // sementara input manual
  User *users = NULL;
  push(users, "Oiko");
  push(users, "Adam");
  push(users, "Jokris");
  push(users, "Kevin");

  User *user = users->next; // choose current user (Jokris) <-- misal

  // display available user 
  User *temp = users;
  int num = 1;
  puts("Available users:");
  while(temp) {
    if(strcmp(temp->name, user->name) == 0) {
      temp = temp->next;
      continue;
    }
    printf("%d. %s\n", num++, temp->name);
    temp = temp->next;
  }

  // Choose A user to add to user's friend list
  char *name = (char*)malloc(sizeof(char));
  temp = users;
  while(true) {
    printf("username: ");
    scanf("%s", name); gtc();
    // search for user if available = add, else break
    bool exist = false;
    while(temp) {
      if(strcmp(temp->name, name) == 0) {
        addFriend(user->friends, temp->name);
        printf("Your request has been sent to %s\n", name);
        printf("Press enter to continue!"); gtc();
        exist = true;
        break;
      }
      temp = temp->next;
    }
    if(!exist) {
      printf("There is no user with such name!\nPress enter to re-enter the user!"); gtc();
    } else {
      break;
    }
  }

  // display user's friend list
  printf("friend:\n");
  printUsers(user->friends);
  return 0;
}