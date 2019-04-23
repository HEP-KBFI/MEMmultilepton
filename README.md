# MEMmultilepton
Matrix Element Method for multilepton final states in High Energy Physics

Authors: Nicolas Chanon (IPNL) with the help of Jing Li (PKU) and Nicolas Tonon (IPHC)

## Installation (standalone)

### Dependencies

Install and configure LHAPDF (here, on lxplus6). See http://lhapdf.hepforge.org/install.html

```bash
wget http://www.hepforge.org/archive/lhapdf/LHAPDF-6.2.1.tar.gz -O- | tar xz
cd LHAPDF-6.2.1
./configure --prefix=$PWD/../LHAPDF-6.2.1-install \ 
--with-boost=/afs/cern.ch/sw/lcg/external/Boost/1.55.0_python2.7/x86_64-slc6-gcc47-opt
make -j2
make install
```

Get the NNPDF3.0 LO pdf set at leading order:
```bash
cd $PWD/../LHAPDF-6.2.1-install
cd share/LHAPDF
wget http://www.hepforge.org/archive/lhapdf/pdfsets/6.2/NNPDF30_lo_as_0118.tar.gz -O- | tar xz
cd ../../../
```

### Setting up the environment

Source LHAPDF environmental variables:

```bash
# when using cshell
setenv LHAPDF $PWD/LHAPDF-6.2.1-install
setenv LHAPATH $LHAPDF/share/LHAPDF/
setenv LHAPDF_BIN $LHAPDF/bin
setenv PATH ${PATH}:${LHAPDF_BIN}
setenv LD_LIBRARY_PATH ${LD_LIBRARY_PATH}:$LHAPDF/lib

# when using bash
export LHAPDF=$PWD/LHAPDF-6.2.1-install
export LHAPATH=$LHAPDF/share/LHAPDF/
export LHAPDF_BIN=$LHAPDF/bin
export PATH=${PATH}:${LHAPDF_BIN}
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:$LHAPDF/lib
```

Setup ROOT (most importantly, it has to be installed with GSL and Minuit2 dependences)

```bash
# when using cshell
source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.csh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root/bin/thisroot.csh

# when using bash
source /afs/cern.ch/sw/lcg/external/gcc/4.9/x86_64-slc6-gcc49-opt/setup.sh
source /afs/cern.ch/sw/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh

# when you have no access to /afs/cern.ch/sw/lcg (cshell):
source /cvmfs/sft.cern.ch/lcg/external/gcc/4.9.1/x86_64-slc6/setup.csh
source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root/bin/thisroot.csh

# when you have no access to /afs/cern.ch/sw/lcg (bash):
source /cvmfs/sft.cern.ch/lcg/external/gcc/4.9.1/x86_64-slc6/setup.sh
source /cvmfs/sft.cern.ch/lcg/app/releases/ROOT/6.06.06/x86_64-slc6-gcc49-opt/root/bin/thisroot.sh
```

### Building

Configure MEMmultilepton (mostly compilations)

```bash
git clone https://github.com/nchanon/MEMmultilepton
cd MEMmultilepton
./installMEM.sh
```

### Example run

```bash
./bin/simpleMEManalyzer ./test/config.cfg
```

Expected output:
```
Simple example of MEM weight computation
-------- MEM RESULTS --------
MEM hypothesis TTHsl weight=1e-300 kinfitscore=1e-300
MEM hypothesis TTW weight=1.15219e-13 kinfitscore=1.76085e-16
MEM hypothesis TTbarsl weight=3.53898e-09 kinfitscore=1.25728e-10
MEM hypothesis THJ weight=1.17852e-13 kinfitscore=1.87691e-21
MEM hypothesis TTH weight=1e-300 kinfitscore=1e-300
MEM hypothesis TTbar weight=3.53898e-09 kinfitscore=1.25728e-10
SimpleMEManalyzer: Real Time = 383.07 seconds Cpu Time = 382.81 seconds
```

Please use `config/config.cfg` instead of `test/config.cfg` if your interface the MEM with your own code (contains absolute path to the transfer functions and Madgraph directory)


## Installation (CMSSW)

Here are the instruction for using library in an `fwlite` executable:

```bash
git clone https://github.com/nchanon/MEMmultilepton $CMSSW_BASE/src/$TOPLEVEL/$SUBDIR
cd $_
scram b -j8
```
where `$TOPLEVEL` and `$SUBDIR` respectively refer to unique top level directory and its subdirectory in `$CMSSW_BASE/src`.
For instance, you could clone the package into `$CMSSW_BASE/src/analysis/MEMmultilepton`.
The two-level directory structure is necessary for `scram` to recognize the project and build it.

### Example run

```bash
# execute in $CMSSW_BASE/src/analysis/MEMmultilepton
simpleMEManalyzer test/config.cfg
```

Expected output:
```
-------- MEM RESULTS --------
MEM hypothesis TTHsl weight=1e-300 kinfitscore=1e-300
MEM hypothesis TTbarsl weight=3.65043e-09 kinfitscore=4.15046e-11
MEM hypothesis TTH weight=1e-300 kinfitscore=1e-300
MEM hypothesis TTbar weight=3.65043e-09 kinfitscore=4.15046e-11
SimpleMEManalyzer: Real Time =  28.76 seconds Cpu Time =  28.75 seconds
```

### Interfacing

If you want to hook this package up with your own, add the following lines to your CMSSW `BuildFile.xml`:
```xml
<use   name="analysis/MEMmultilepton"/>
```
