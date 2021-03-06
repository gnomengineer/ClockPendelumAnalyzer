# Clock Pendelum Analyzer
a PAWI project of HSLU about a clock pendelum analyzer

![hardware counter M1](docs/images/gesamtansicht_small.png)

## Documentation
the repo uses a latex documentation located at [docs/](docs/)  
the pdf is not included and has to be generated with following code
```
cd docs/pmp
pdflatex PMP_ClockPendulumAnalyzer.tex
cd ../sysspec
pdflatex SysSpec_ClockPendulumAnalyzer.tex
```
or built with an apropriate tool like TeXStudio

for a transparent development process is a prereleased version of the documentation available at [dropbox](https://www.dropbox.com/sh/e3s0njjdiqjc6j6/AACY37FKJ-w6JLD9rKbB_oXha?dl=0)

> Note: the documentation is entirely in german!

### external documents
as this is a project for the HSLU it comes with various PDFs which are saved and accessable in [dropbox](https://www.dropbox.com/sh/23kg7c6czmhmzml/AADuSR9a3MtVxtYaETB6SMMga?dl=0)

## Usage
### Target System

The application is developed for a **Raspberry Pi 3** with c++ compiler and GPIO access.

### How To Compile

The project doesn't deliver binary instead the source code can be built manually by following these instructions. Works on linux and with Cygwin maybe also on windows.
```
git clone https://github.com/gnomengineer/ClockPendelumAnalyzer.git
cd ClockPendelumAnalyzer
mkdir build
cd build
cmake ..
make
```

to just execute the unit test use
```
make clockpendulum_analyzer_unit_tests
```
or to just execute the application without the tests
```
make clockpendulum_analyzer
```
### How To Run

Once the source code is built, the application can be started as *root* with the following command. The binary file is located in $PROJECTDIR$/build/bin.

```
# bin/clockpendulum_analyzer clockname [false]
```
The 2nd parameter defines if the application waits for a user input to be closed properly. It is per default *true* (autonomous run) and needs to be specified only for *false*.
