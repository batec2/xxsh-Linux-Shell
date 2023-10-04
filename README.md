# xxsh Linux shell
This is the shell implementation for CMPT 360 Lab 2.

## Group members:
- Crush Bate
- Dakota Doolaege

# Building
The project is divided into multiple modules which can be found in the
subdirectories of the main directory.

Each module can be built independently by navigating to its directory and 
running:

```
make
```

NOTE: These modules are not standalone applications and will require either the
testing program to use them or the main shell (xxshModule).

The whole project can be made at once from the top directory by running: 

```
make
```

# Running
Building the project results in a main shell executable called xxsh being
generated in the main directory.

```
./xxsh
```

## Supported commands
- export:     Sets environmental variables.
- env:        Lists environmental variables.
- history:    Displays recently typed commands. Defaults to storing five 
            entries
            The number of entries to store can be changed by exporting
            HISTSIZE.
- quit:       Returns from shell.
- exit:       Returns from shell.

# Testing
Modules support automatic testing. Testing can be done for each module or for
the entire application by running the following recipe in the module directory
or the main directory to run all tests:

```
make test
```
