CC=gcc

all:exit_example exit_differ wait2 wait_example wait_example2 wait_example3 get_status fork_test
.PHONY:all clean


fork_test:fork_test.c
	$(CC)  fork_test.c -o fork_test
exit_example:exit_example.c
	$(CC)  exit_example.c -o exit_example 
exit_differ:exit_differ.c
	$(CC)  exit_differ.c -o exit_differ 
wait2:wait.c
	$(CC)  wait.c -o wait2
wait_example:wait_example.c
	$(CC)  wait_example.c -o wait_example
wait_example2:wait_example2.c
	$(CC)  wait_example2.c -o wait_example2

wait_example3:wait_example3.c
	$(CC)  wait_example3.c -o wait_example3

get_status:get_status.c
	$(CC)  get_status.c -o get_status
clean:
	rm exit_example exit_differ wait2 wait_example wait_example2 wait_example3 get_status fork_test
