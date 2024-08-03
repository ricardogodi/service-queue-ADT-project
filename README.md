## Service Queue ADT Implementation

### Project Overview

This project presents an advanced implementation of a Service Queue Abstract Data Type (ADT), designed to efficiently manage a queue of "buzzers" as used in a restaurant setting without reservations. The core of the implementation lies in a hybrid data structure that effectively combines linked lists, dynamically resizable arrays, and node indexing to achieve optimal performance.

### Features

- **Dynamic Array Integration**: Utilizes dynamically resizable arrays to handle buzzer management, ensuring efficient memory allocation and O(1) amortized runtime for buzzer issuance.
- **Linked List Operations**: Employs doubly-linked lists for maintaining the queue of buzzers, supporting constant-time operations for enqueue and dequeue processes.
- **Node Indexing**: Incorporates a node indexing strategy to directly access nodes in the queue, significantly speeding up operations like buzzer removal and priority adjustment.
- **Complex State Management**: Handles complex state conditions with precision, ensuring robust management of the queue state across various operations.
- **Resource Reuse**: Implements mechanisms for buzzer reuse to optimize resource allocation, minimizing the need for new memory allocation by reutilizing buzzers that are no longer in the queue.

### Technical Description

The Service Queue ADT is structured around several key components:

- **Service Queue Structure**: Defined in `sq.c`, it includes pointers to the front and back of the queue, a dynamically resizable array for direct node access, and a separate list to manage available (recycled) buzzers.
- **Runtime Efficiency**: All critical operations—such as adding to the queue (`sq_give_buzzer`), serving the next buzzer (`sq_seat`), and removing a buzzer (`sq_kick_out`)—are designed to run in O(1) time, fulfilling stringent performance requirements.
- **Error Handling and Debugging**: Comprehensive error checking ensures that operations such as buzzer reassignments and queue modifications behave correctly under all conditions, including edge cases like attempting to remove a buzzer not currently in the queue.

### Compilation and Running

This project includes a Makefile that simplifies the compilation and execution process. Here’s how you can compile and run the program:


### Compile the Program
```bash
make all
```
This command compiles all necessary source files and links them into an executable named service_queue.


### Run the Program
```bash
make run
```
This executes the service_queue program, which starts an interactive session where you can perform operations like issuing a buzzer, seating a buzzer, and removing a buzzer from the queue.


### Clean the Build
```bash
make clean
```
Removes all compiled object files and the executable to clean up the directory.

### Source Files and Headers

- **driver.c**: Contains the main function and the interactive command loop.
- **sq.c**: Implements the service queue operations as defined in sq.h.
- **llist.c**: Provides the linked list functionality used by the service queue.
- **sq.h**: Header file for service queue functions and definitions.
- **list.h**: Header file for linked list operations and structures.
