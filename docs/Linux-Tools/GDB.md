> # GDB

参考：

* [100个GDB小技巧](https://github.com/hellogcc/100-gdb-tips/blob/master/src/index.md)
* [Debugging with GDB](https://sourceware.org/gdb/onlinedocs/gdb/)

---

[TOC]

# 1. Install GDB in Ubuntu

```shell
$ sudo apt install gdb
```

# 2.Invoking GDB

Invoke GDB by running following commands

```shell
$ gdb

# run result
GNU gdb (Ubuntu 8.1-0ubuntu3.1) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
(gdb)
```

## 2.1 Invoking GDB without any information

```shell
$ gdb -q
(gdb)
```

Another method is edit file `~/.bashrc`, set an alias for command `gdb`

```shell
sudo vim ~/.bashrc
# add a new line at the end of the file
alias gdb="gdb -q"
source ~/.bashrc
```

#3 Check Version of GDB

To check the version of GDB, type the following command:

```shell
(gdb) show version

# run result
GNU gdb (Ubuntu 8.1-0ubuntu3.1) 8.1.0.20180409-git
Copyright (C) 2018 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
<http://www.gnu.org/software/gdb/documentation/>.
For help, type "help".
Type "apropos word" to search for commands related to "word".
```

#4 Check Permission for Copying GDB

To check information about permission for copying GDB, type the following commands:

```shell
(gdb) show copying
(gdb) info copying
```

#5 Quitting GDB

To exit GDB, use command `quit` or `q`or type an end-of-file character`Ctrl + d`. `Ctrl + c`does not exit from GDB, it will terminate the action of any command that is in progress and returns to GDB command level.



# GDB退出时不显示提示信息

# 输出信息多时不会暂停输出



