# CMAKE generated file: DO NOT EDIT!
# Generated by "NMake Makefiles" Generator, CMake Version 3.20

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

!IF "$(OS)" == "Windows_NT"
NULL=
!ELSE
NULL=nul
!ENDIF
SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = C:\workspace\DCC012\ED2021

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = C:\workspace\DCC012\ED2021\cmake-build-debug

# Include any dependencies generated for this target.
include ED2021\CMakeFiles\ED2021.dir\depend.make
# Include the progress variables for this target.
include ED2021\CMakeFiles\ED2021.dir\progress.make

# Include the compile flags for this target's objects.
include ED2021\CMakeFiles\ED2021.dir\flags.make

ED2021\CMakeFiles\ED2021.dir\ED2021.cpp.obj: ED2021\CMakeFiles\ED2021.dir\flags.make
ED2021\CMakeFiles\ED2021.dir\ED2021.cpp.obj: ..\ED2021\ED2021.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=C:\workspace\DCC012\ED2021\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object ED2021/CMakeFiles/ED2021.dir/ED2021.cpp.obj"
	cd C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoCMakeFiles\ED2021.dir\ED2021.cpp.obj /FdCMakeFiles\ED2021.dir\ /FS -c C:\workspace\DCC012\ED2021\ED2021\ED2021.cpp
<<
	cd C:\workspace\DCC012\ED2021\cmake-build-debug

ED2021\CMakeFiles\ED2021.dir\ED2021.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/ED2021.dir/ED2021.cpp.i"
	cd C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe > CMakeFiles\ED2021.dir\ED2021.cpp.i @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E C:\workspace\DCC012\ED2021\ED2021\ED2021.cpp
<<
	cd C:\workspace\DCC012\ED2021\cmake-build-debug

ED2021\CMakeFiles\ED2021.dir\ED2021.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/ED2021.dir/ED2021.cpp.s"
	cd C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021
	C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\cl.exe @<<
 /nologo /TP $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) /FoNUL /FAs /FaCMakeFiles\ED2021.dir\ED2021.cpp.s /c C:\workspace\DCC012\ED2021\ED2021\ED2021.cpp
<<
	cd C:\workspace\DCC012\ED2021\cmake-build-debug

# Object files for target ED2021
ED2021_OBJECTS = \
"CMakeFiles\ED2021.dir\ED2021.cpp.obj"

# External object files for target ED2021
ED2021_EXTERNAL_OBJECTS =

ED2021\ED2021.exe: ED2021\CMakeFiles\ED2021.dir\ED2021.cpp.obj
ED2021\ED2021.exe: ED2021\CMakeFiles\ED2021.dir\build.make
ED2021\ED2021.exe: ED2021\CMakeFiles\ED2021.dir\objects1.rsp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=C:\workspace\DCC012\ED2021\cmake-build-debug\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable ED2021.exe"
	cd C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021
	"C:\Program Files\JetBrains\CLion 2021.2.3\bin\cmake\win\bin\cmake.exe" -E vs_link_exe --intdir=CMakeFiles\ED2021.dir --rc=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\rc.exe --mt=C:\PROGRA~2\WI3CF2~1\10\bin\100190~1.0\x86\mt.exe --manifests -- C:\PROGRA~2\MICROS~3\2019\COMMUN~1\VC\Tools\MSVC\1429~1.301\bin\Hostx86\x86\link.exe /nologo @CMakeFiles\ED2021.dir\objects1.rsp @<<
 /out:ED2021.exe /implib:ED2021.lib /pdb:C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021\ED2021.pdb /version:0.0 /machine:X86 /debug /INCREMENTAL /subsystem:console  kernel32.lib user32.lib gdi32.lib winspool.lib shell32.lib ole32.lib oleaut32.lib uuid.lib comdlg32.lib advapi32.lib 
<<
	cd C:\workspace\DCC012\ED2021\cmake-build-debug

# Rule to build all files generated by this target.
ED2021\CMakeFiles\ED2021.dir\build: ED2021\ED2021.exe
.PHONY : ED2021\CMakeFiles\ED2021.dir\build

ED2021\CMakeFiles\ED2021.dir\clean:
	cd C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021
	$(CMAKE_COMMAND) -P CMakeFiles\ED2021.dir\cmake_clean.cmake
	cd C:\workspace\DCC012\ED2021\cmake-build-debug
.PHONY : ED2021\CMakeFiles\ED2021.dir\clean

ED2021\CMakeFiles\ED2021.dir\depend:
	$(CMAKE_COMMAND) -E cmake_depends "NMake Makefiles" C:\workspace\DCC012\ED2021 C:\workspace\DCC012\ED2021\ED2021 C:\workspace\DCC012\ED2021\cmake-build-debug C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021 C:\workspace\DCC012\ED2021\cmake-build-debug\ED2021\CMakeFiles\ED2021.dir\DependInfo.cmake --color=$(COLOR)
.PHONY : ED2021\CMakeFiles\ED2021.dir\depend

