CC=gcc

all:create_pipe  parent_pipe_child sizeof_strlen sibling_pipe
.PHONY:all clean

create_pipe:create_pipe.c
	$(CC)  create_pipe.c -o create_pipe

parent_pipe_child:parent_pipe_child.c
	$(CC)  parent_pipe_child.c -o parent_pipe_child

sizeof_strlen:sizeof_strlen.c
	$(CC)  sizeof_strlen.c -o sizeof_strlen

sibling_pipe:sibling_pipe.c
	$(CC)  sibling_pipe.c -o sibling_pipe

clean:
	rm create_pipe parent_pipe_child sizeof_strlen sibling_pipe
