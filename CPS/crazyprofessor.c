#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

/*Each student has an id, the number of questions he/she wants to ask, and the question number that the student is on. */
struct student{
	int id;
	int numQuestions;
	int questionNum;
	struct student *next;
};

unsigned int condition, condition2;
unsigned int answeredQs;
unsigned int numStud;
unsigned int snack;
pthread_cond_t student, prof;
pthread_mutex_t lock, lock_t, lock_t2, lock_t3,lock_t4;
pthread_t P;
struct student *iterator = NULL, *head = NULL;

void * startProfessor();
void * startStudent(void * s);
void AnswerStart();
void AnswerDone();
void QuestionStart();
void QuestionDone();
void Nap();
void Snack();

/* This function starts the Professor thread that runs a loop calling AnswerStart and 
AnswerDone. If the professor answers 3 questions, he snacks on an Oreo. If no students are around, he naps.*/
void Professor(){
	// initialize the mutex
	pthread_mutex_init(&lock, NULL);
	pthread_mutex_init(&lock_t, NULL);
	pthread_mutex_init(&lock_t2, NULL);
	pthread_mutex_init(&lock_t3, NULL);
	pthread_mutex_init(&lock_t4, NULL);
	
	// initialize the condition variables
	pthread_cond_init(&prof, NULL);
	pthread_cond_init(&student, NULL);	
	
	// initialize the global variables
	snack = 0; 	//keeps track of the number of questions answered
	numStud = 0; 	//keeps track of the number of students
	condition = 0; //wakes up professor
	condition2 = 1;//wakes up student
	
	if (pthread_create(&P, NULL, startProfessor,NULL) != 0){
		perror("Thread creation failed");
		exit(0);
	}
	sleep(1);
}

/* The professor thread  */
void* startProfessor(){
	puts("\nCrazy Professor's office hours have begun!");
	condition = 1;
	//pthread_cond_signal(&student);
	while(1){
		
		if( numStud == 0 ){ Nap(); } // calls the nap function if there are no students
		
		pthread_cond_wait(&prof, &lock_t); // wait until a student asks a question
		
		condition = 0;
		if(head != NULL){ 
			AnswerStart(); 
			AnswerDone();
			
			// signal student that the question has been answered		
			while(condition2){ pthread_cond_signal(&student); }
			condition2 = 1;
			
			if(snack == 3){  // if 3 questions have been answered, snack
				pthread_cond_wait(&prof, &lock_t4); 
				snack = 0; 
				Snack();
			}
		}
	}
}

/*Creates a thread that represents a new student with identifier id that asks the professor a specific number of questions specified by numQuestions. ID can be expected to be >= 0.*/
void Student(int id, int numQuestions){
	struct student * newstud =  malloc(sizeof(struct student));
	
	newstud->id = id + 1;
	newstud->numQuestions = numQuestions;
	newstud->questionNum = 0;
	
	pthread_t S; // local stack variable
	
	//create thread
	if(pthread_create( &S, NULL, (void *) &startStudent, (void *)newstud ) != 0){
		perror("Thread creation failed");
		exit(0);
	}
}

/* The student thread */
void * startStudent(void * s){	
	struct student * stud = s;
	
	printf("Student %i is at the Professor's door and wants to ask %i questions.\n", stud->id, stud->numQuestions);
	
	pthread_mutex_lock(&lock_t3);
	numStud++; // increment the number of students
	
	if(head != NULL){ iterator = iterator->next = stud; } // add student to list
	else{ condition = 1; iterator = head = stud; }
	pthread_mutex_unlock(&lock_t3);
	
	//each student loops running the code for the number of questions he asks:	
	while(1){
		pthread_mutex_lock(&lock);

		if(head != NULL && numStud == 0){
			head = NULL;
			pthread_cond_signal(&prof);
		}
		
		if(head != NULL){ // if there are students in the queue
			QuestionStart();
			QuestionDone();
		}
		
		pthread_mutex_unlock(&lock);
	}
}

/*It is the turn of the student to ask his next question (his nth question). Wait to print out the message until it is really that student's turn.*/
void QuestionStart(){	
	(head->questionNum)++; // increment the question number
	(head->numQuestions)--; // decrement the number of questions left
	
	printf("Student %i asks question # %i.\n", head->id, head->questionNum);
	
	while(condition){ pthread_cond_signal(&prof); }
	condition = 1;
	
	pthread_cond_wait(&student, &lock_t2);
	condition2 = 0;
}

/*The student is satisfied with the answer. Since professors consider it rude for a student not to wait for an answer, QuestionDone() should not print anything until the professor has finished answering the question.*/
void QuestionDone(){
	printf("Student %i is satisfied.\n\n", head->id);
	
	while(snack == 3){ pthread_cond_signal(&prof); }
	
	if(head->numQuestions == 0){ // if the number of questions is zero, remove the student
		--numStud;
		free(head);
		head = head->next;
		// no more students
		if(head == NULL){ pthread_cond_signal(&prof); }
	}
}

/*The professor starts to answer the next (nth) question of student X.*/
void AnswerStart(){
	printf("Professor starts to answer question # %i for student %i.\n", head->questionNum, head->id);
}

/*The professor is done answering a question of a student. This should be done after a finite amount of time which you can simulate using a busy-wait call counting up to random number.*/
void AnswerDone(){	
	int rand = (random() % 1000) + 1;
	printf("Professor is done with answering question # %i for student %i. Answering took %i millisecond(s).\n",head->questionNum, head->id, rand); 
	usleep(rand);
	snack++;
}

/*The professor naps.*/
void Nap(){ puts("Professor is Napping ...\n"); }

/*The professor snacks on an oreo cookie because he has answered 3 questions in a row with no break.*/
void Snack(){
	puts("Professor snacks on an oreo cookie.\n");
}
