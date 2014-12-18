Crazy-Professor-Synchronization
===============================

Multi threading in C

You have been hired by the School of Computer Science at FIU to write code to help synchronize a crazy professor and his/her students during office hours. The crazy professor is quite crazy (indeed!). He has a fetish for oreos. He must snack on an oreo cookie after he has answered 3 student questions in a row. Moreover, he takes a nap if no students are around to ask questions; if there are students who want to ask questions, they must synchronize with each other and with the professor so that (i) only one person is speaking at a time, (ii) each student question is answered by the professor and student must wait until the professor answers his/her question, (iii) no student asks another question before the professor is done answering the previous one (which can sometimes take a LOOONG but always finite amount of time), and (iv) all students must wait for the Professor to snack on an oreo cookie whenever he feels the urge before speaking up. Not doing any of the above will incur the wrath of the crazy professor, which no one would like to experience.

You are to provide the following functions:

Professor. This functions starts a thread that runs a loop calling AnswerStart() and AnswerDone(). See below for the specification of these two functions.AnswerStart() blocks when there are no students around but calls Nap() before blocking. When the professor thread is created, print ...
Crazy Professor's office hours have begun!

Student(int id, int numQuestions). This function creates a thread that represents a new student with identifier id that asks the professor a specific number of questions specified by numQuestions. Each student loops running the code QuestionStart() and QuestionDone() for the number of questions that he/she wants to ask. The identifier given to your function can be expected to be greater or equal to zero. Print ...
Student x is at the Professor's door and wants to ask K questions.

AnswerStart(). The professor starts to answer the next (nth)question of student x. Print ...
Professor starts to answer question # n for student x.

AnswerDone(). The professor is done answering a question of a student.This should be done after a finite amount of time which you can simulate using a busy-wait call counting up to random number. Print ...
Professor is done with answer question # n for student x. Answering took y time units. 

QuestionStart(). It is the turn of the student to ask his/her next question (his nth question). Wait to print out the message until it is really that student's turn. Print ...
Student x asks question # n.

Nap(). Professor Naps. Print ...
Professor Napping ...

QuestionDone(). The student is satisfied with the answer. Since professors consider it rude for a student not to wait for an answer, QuestionDone() should not print anything until the professor has finished answering the question. Print ...
Student x is satisfied.

Snack(). The professors snacks on an oreo cookie because he has answered 3 questions in a row with no break. Print ...
Professor snacks on an oreo cookie.

In the above descriptions, "x" is a placeholder for the student identifier which always increases when the next student arrives and y is a placeholder for time taken to answer a question. For testing purposes, call the appropriate functions from test routines that you will put in a different "test" directory. Your test programs should engage the dynamic nature of a typical professor's office hours where student arrive either in batches or individually and questions take either a long time or short. 

Test Suite

We will be using the following the following test cases for grading:

Test 1: One student comes and asks 3 questions.
Test 2: One student comes and asks 10 questions.
Test 3: Ten students come in a row and each student just asks one question.
Test 4: 10 students come in 5 groups and each group has 2 students.In each group, the two students come in a row and ask questions.After some time(which is long enough for professor to take a nap), the next group comes.
Test 5: 100 students come and ask questions.