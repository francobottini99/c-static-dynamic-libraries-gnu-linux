# C Language Practices in GNU/Linux

This repository aims to familiarize users with the design and implementation of static and dynamic libraries using the GNU Toolchain and Linux Software development environment. The activities involve command-line argument handling, implementing a static library (cJSON), and a dynamic library functioning as a _plugin_.

### Authors:
- **Bottini, Franco Nicolas**

### 1. Command Line Arguments

A C program was designed and implemented to perform the following actions when executed with specific arguments:

1. If run with the _-s_ option, it executes Exercise 1 from Lab 2.
2. If run with the _-a_ option, it executes Exercise 2 from Lab 2.

### 2. Static Library (cJSON)

The cJSON static library was implemented in the project, enabling:

2.1. If the _-j_ option is added along with the options from **point 1**, the program uses the cJSON static library and displays the result in JSON format.

### 3. Dynamic Library

A dynamic library was designed and implemented as a _plugin_, extending options and allowing:

- Dynamic loading when run with the _-d_ option.

- Using the cJSON library from **point 2** to display information about the filesystems supported by the current kernel (/proc/filesystems).

### 4. Questionnaire

#### 4.1. What types of type descriptors can be found in /proc//fd?

When a file is opened, the operating system creates an entry representing it and stores information about it. So if there are 100 open files, there will be 100 entries in the OS (somewhere in the kernel). These entries are represented by integer numbers (100, 101, 102). This entry number is the file descriptor, uniquely representing an open file within a process. If a process opens 10 files, its process table will have 10 entries for file descriptors. There are four types of file descriptors: standard input, standard output, standard error, and file descriptor.

#### 4.2. Assuming a user is running process with pid 1212, is it valid to run the following command from a new terminal? % echo “Hello, world.” >> /proc/1212/fd/1

Yes, executing the command is valid. The result will write the message "Hello, world" to the file referenced by the selected file descriptor. If we open two terminal instances and then execute the command in one terminal, referencing the input file descriptor of the other, we can observe how "Hello, world" is written from the first terminal to the second.

![Screenshot of 2022-09-09 08-51-22](https://user-images.githubusercontent.com/101523922/189353428-36587fe4-b1dd-4356-a762-feaaa5fdec02.png)

#### 4.3. What is the difference between hard and soft limits?

In Linux, process or session resource access can be limited. There are two types of limits: hard limits and soft limits. Hard limits are set using superuser privileges and represent the maximum resource availability for any process or session. These cannot be exceeded. On the other hand, soft limits can be used by users or processes to self-limit resource usage, as long as these limits are less than or equal to the imposed hard limit. Thus, a hard limit establishes the upper bound, and soft limits allow users or processes to set self-limits within this bound.
