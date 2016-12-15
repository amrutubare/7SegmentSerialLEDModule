Example of Spi 7 Segment Module for [distortos](http://distortos.org/) - an advanced real-time operating system 
for deeply embedded targets.

Configuration & building
------------------------

1. Clone repository:
`git clone --recursive https://github.com/CezaryGapinski/7SegmentSerialLEDModule`.
2. Configure distortos - you can either create new configuration (with `make menuconfig`) or use an existing one;
3. Execute `make configure CONFIG_PATH=<path-to-distortosConfiguration.mk>` to select the configuration you
created/chose above;
4. Execute `make` (if you use *GNU Make*) or `tup` (if you use *tup*);

To update *distortos* submodule to latest version use `git submodule update --remote` command.

### Quick example

Following commands may be executed in POSIX-compatible shell (e.g. *Bash*).

#### 1. Download

Clone the repository:

    $ git clone --recursive https://github.com/CezaryGapinski/7SegmentSerialLEDModule
    $ cd 7SegmentSerialLEDModule

#### 2. Configure

Either use one of existing configurations:

    $ make configure CONFIG_PATH=SpiLed7SegmentModule

or create a new one from scratch:

    $ make menuconfig
    ... edit some options, save the configuration as distortosConfiguration.mk ...
    $ make configure

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
