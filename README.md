Example of simple counter with 1 second period with usage of Spi 7 Segment Module
for [distortos](http://distortos.org/) - an advanced real-time operating system 
for deeply embedded targets.

This example use NUCLEO-L073RZ evaluation board and 4 digits 7 Segment Module based on two connected
8-bit serial-in, serial or parallel-out shift registers with output latches - 74HC595

Configuration & building
------------------------

Following commands may be executed in POSIX-compatible shell (e.g. *Bash*).

#### 1. Download

Clone the repository:

    $ git clone --recursive https://github.com/CezaryGapinski/7SegmentSerialLEDModule
    $ cd 7SegmentSerialLEDModule

#### 2. Configure

Either use one of existing configurations:

    $ make configure CONFIG_PATH=configurations/NUCLEO-L073RZ_CUSTOM

#### 3. Build

Build the project with *make*:

    $ make

or do the same with *tup*:

    $ tup

#### 4. Edit configuration & rebuild

To edit any option in the selected configuration just run *kconfig* tool again:

    $ make menuconfig
    ... edit some options, overwrite configuration file ...

You can rebuild the project immediatelly by running *make*:

    $ make

or *tup*:

    $ tup
