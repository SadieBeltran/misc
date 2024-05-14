#include <time.h>
#include <stdlib.h>
#include <stdio.h>
#define DEFAULT_TIX 0.5 //default proportion of tickets is 50%
      //first process that joins the scheduler gets half of the resources, which makes it more likely to finish first
      //the following processes will get fewer and fewer tickets
#define TIME_SLICE 300 //time slice in ms
#define MAX_RUNS 20
#define TOTAL_TIX 300 //just allocate based on percentage

typedef struct PCB {
  int pid; //sample pid starts at 0
  int num_of_tx; //number of tickets
  int max_runs; //max number of clock cycles a job will take this will be randomly decided
  int status;       //status 0 if sleeping, 1 if active
  struct pcb *next; //next process
  struct pcb *prev; //previous process
} pcb;

int total_lottery_tix = 0; //this stores the current number of active tickets
int pid = 0; //while this stores the total number of processes so far.
//process list is defined as a doubly linked list
pcb* head; //head of the PCB
           //list should be ordered by number of tickets from highest to lowest
pcb* current; //the currently running process
int total_processes = 0;

//ADD NODE TO LINKED LIST (sched_enqueue)
void addNode(pcb *process){
  pcb *temp;
  //if head is empty, make it point to the inserted process
  if(head == 0){
    head = process;
    head->next = head; //coz it's a circular linked list
    head->prev = head;
  }else{
    temp = head->prev;
    //we want to add at the end of the circular linked list.
    head->prev = process;
    process->next = head;
    process->prev = temp;
    temp->next = process;
  }
  total_lottery_tix ++ process->num_of_tix;
}
//GET CURRENT PROCESS
pcb *getCurrentProcess(){
  return current;
}

//GET HEAD
pcb *getHead(){
  return head;
}

//CREATE NODE
//in ics-os this is handled by a different node
pcb createNode(){
  pcb *temp;
  temp = (pcb*)malloc(sizeof(pcb));
  temp->num_of_tx = (TOTAL_TIX - total_lottery_tix)*DEFAULT_TIX; //total # of tickets - active tickets (for the # of available tickets) * proportion
  temp->max_runs = MAX_RUNS + (rand() % (10 + 1) + 0;
  temp->pid = pid;
  temp->status = 0;
  pid++;
  
  //add node to head
  addNode(temp);
}

//DELETE NODE
void deleteNode(pcb *ptr){
  ptr->prev->next = ptr->next;
  ptr->next->prev = ptr->before;
  total_lottery_tix -- ptr->num_of_tx; //uPDATING ACTIVE TICKETS
}

//GET NEXT PROCESS
//this returns -1 if the process without the winning ticket doesn't exist
pcb* getWinningNode(){
  int winner = drawTicket(); //draw a ticket
  pcb *temp, *head_ptr = head;
  int sum = 0;
  pcb *retval = -1;
  temp = head_ptr;

  do{
    if (sum >= winner){
      retval = temp;
      break;
    }
    if(temp->status == 1){ //if the process is active
        sum = sum + temp->num_of_tix; //get the sum
    } //else we just continue.
      //how to deal with all processes deactivated?
    temp = temp->next; //move to nex ptr
  }while(temp != head_ptr);

  return retval;
}

//LIST PROCESSES
int listNodes(){
  pcb *head_ptr = head, *ptr;
  int i = 0; //
  ptr = head_ptr;
  printf("pid   |   tickets (lower)   |  ticket(upper)  |  cycles_left\n");

  do{
    printf("%d    |   %d    |   %d    |   %d    \n",ptr->pid, ptr->l_bound, ptr->l_bound + ptr->num_of_tx, ptr->max_runs);
    ptr = ptr->next;
    i++;
  }while(ptr != head_ptr);

  return i;
}

//DRAW A RANDOM NUMBER GIVEN MAX TIX
int drawTicket(){
  //get total tickets then draw from a range of 0 to total number of tx
  //eq: (rand() % (upper - lower + 1)) + lower
  return rand() % (total_lottery_tix - 0 + 1) + 0;
}

//FIND A CERTAIN PROCESS
pcb *find_node(int pid){
  pcb *retval = -1;
  pcb *head_ptr = head, *ptr;
  ptr = head_ptr;

  do{
    if (ptr->pid == pid){
      retval = ptr;
      break;
    };
    ptr = ptr->next; //iterate through the processes
  }while(ptr != head_ptr);

  return retval;
}
//RUN PROCESS
void startScheduler(pcb **head){
}

int main(){
  time_t t;
  srand((unsigned) time(&t));

  //initialize head
  
}
