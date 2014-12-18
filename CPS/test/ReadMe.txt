Instructions:
Important: The test.c file must remain in the test subdirectory in order for the makefile to work properly.

Typing "make clean" in the terminal while in the /proj4 directory cleans both proj4 and the test subdirectory.
To create the program, type "make" into the terminal in the /proj4 directory.

To run a test, type the following into the terminal:
	bash$ ./crazy #
where # is a number from 1 to 5, depending on the test number to be run.

To view the time it took for a program to execute, enter time before the program run call. Example: time ./crazy 4

Test 1: One student comes and asks 3 questions.
Test 2: One student comes and asks 10 questions.
Test 3: Ten students arrive and each student asks one question.
Test 4: 10 students arrive in 5 groups and each group has 2 students.In each group, the two students arrive and ask questions. After some time (which is long enough for professor to take a nap), the next group arrives.
Test 5: 100 students arrive and ask questions.

Important: The tests do not terminate; the professor naps until students show up again. To terminate the test, use ctrl+z. 
