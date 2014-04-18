
BecauseHW!SerialLib
===================

The "Because Hardware!" Serial Library.
    
An easy to use and HW friendly Windoze C/C++ serial port library.

    FEATURES:
        - Supports all kinds of serial ports, including USB, BT or virtual ones.      
        - baud rates up to 3Mbit/s
        - unlimited amount of simultaneous connections
        - supports DLE sequenced packet mechanism
        - supports x86 and x64 builds
        - comes with Code::Blocks IDE projects files 
        - hardware and -werker friendly 8)
        - ...


----------------------------------------------------------------------------------
## NOTES

  The [Code::Blocks][2] project files require an installation of [TDM-GCC][3].  
  Due to some unresolved issues in the 64 bit edition (TDM64-GCC), the
  32 bit (x86) build was done with the TDM(32)-GCC.

  The Toolchain names inside the Code::Blocks IDE were chosen to be: 

   - "TMD-GCC 32 Bit"
   - "TMD-GCC 64 Bit"

  Also, do not forget to link the proper "SerialCore" library in the "/lib" directory.  


----------------------------------------------------------------------------------
## TODO

  This library was derived from SiSeLi, the [Scilab Serial Interface][1].  
  Due to the fact that Scilab only allowed pointer arithmetic, there's (still)
  quite a lot of nonsense and baaad stuff in here...   
  But - it's sufficient for home and hardware use ;-)

    - docs
    - no defines for parity, stop bits, etc...
    - a lot of pointers
    - lot of C casts
    - packet send/receive/config
    - a lot more
    - ...


----------------------------------------------------------------------------------
## CHANGES

### V0.1 initial 
    - NEW: here we go...
    - NEW: should be up and running now
    - NEW: added a C interface

### V0.2 up and running
    - NEW: all C interface functions, except packet related stuff, implemented
    - NEW: added x64 Code::Blocks project file (for TDM64-GCC)
    - NEW: added baud rates 500000 and 512000 bits/s  


Have fun  
FMMT666(ASkr)


----------------------------------------------------------------------------------
[1]: http://www.askrprojects.net/software/siseli/index.html
[2]: http://www.codeblocks.org/
[3]: http://tdm-gcc.tdragon.net/
