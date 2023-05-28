# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Default target executed when no arguments are given to make.
default_target: all
.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

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

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/denis/CLionProjects/os_unix_server_bot

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/denis/CLionProjects/os_unix_server_bot

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache
.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake --regenerate-during-build -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache
.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/denis/CLionProjects/os_unix_server_bot/CMakeFiles /home/denis/CLionProjects/os_unix_server_bot//CMakeFiles/progress.marks
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/denis/CLionProjects/os_unix_server_bot/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean
.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named os_unix_brownian_server_bot

# Build rule for target.
os_unix_brownian_server_bot: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 os_unix_brownian_server_bot
.PHONY : os_unix_brownian_server_bot

# fast build rule for target.
os_unix_brownian_server_bot/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/build
.PHONY : os_unix_brownian_server_bot/fast

#=============================================================================
# Target rules for targets named os_unix_brownian_client

# Build rule for target.
os_unix_brownian_client: cmake_check_build_system
	$(MAKE) $(MAKESILENT) -f CMakeFiles/Makefile2 os_unix_brownian_client
.PHONY : os_unix_brownian_client

# fast build rule for target.
os_unix_brownian_client/fast:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/build
.PHONY : os_unix_brownian_client/fast

client/main.o: client/main.c.o
.PHONY : client/main.o

# target to build an object file
client/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/client/main.c.o
.PHONY : client/main.c.o

client/main.i: client/main.c.i
.PHONY : client/main.i

# target to preprocess a source file
client/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/client/main.c.i
.PHONY : client/main.c.i

client/main.s: client/main.c.s
.PHONY : client/main.s

# target to generate assembly for a file
client/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/client/main.c.s
.PHONY : client/main.c.s

common/config_reading.o: common/config_reading.c.o
.PHONY : common/config_reading.o

# target to build an object file
common/config_reading.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/common/config_reading.c.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/common/config_reading.c.o
.PHONY : common/config_reading.c.o

common/config_reading.i: common/config_reading.c.i
.PHONY : common/config_reading.i

# target to preprocess a source file
common/config_reading.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/common/config_reading.c.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/common/config_reading.c.i
.PHONY : common/config_reading.c.i

common/config_reading.s: common/config_reading.c.s
.PHONY : common/config_reading.s

# target to generate assembly for a file
common/config_reading.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/common/config_reading.c.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/common/config_reading.c.s
.PHONY : common/config_reading.c.s

common/logger.o: common/logger.c.o
.PHONY : common/logger.o

# target to build an object file
common/logger.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/common/logger.c.o
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/common/logger.c.o
.PHONY : common/logger.c.o

common/logger.i: common/logger.c.i
.PHONY : common/logger.i

# target to preprocess a source file
common/logger.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/common/logger.c.i
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/common/logger.c.i
.PHONY : common/logger.c.i

common/logger.s: common/logger.c.s
.PHONY : common/logger.s

# target to generate assembly for a file
common/logger.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/common/logger.c.s
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_client.dir/build.make CMakeFiles/os_unix_brownian_client.dir/common/logger.c.s
.PHONY : common/logger.c.s

server/main.o: server/main.c.o
.PHONY : server/main.o

# target to build an object file
server/main.c.o:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/server/main.c.o
.PHONY : server/main.c.o

server/main.i: server/main.c.i
.PHONY : server/main.i

# target to preprocess a source file
server/main.c.i:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/server/main.c.i
.PHONY : server/main.c.i

server/main.s: server/main.c.s
.PHONY : server/main.s

# target to generate assembly for a file
server/main.c.s:
	$(MAKE) $(MAKESILENT) -f CMakeFiles/os_unix_brownian_server_bot.dir/build.make CMakeFiles/os_unix_brownian_server_bot.dir/server/main.c.s
.PHONY : server/main.c.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... os_unix_brownian_client"
	@echo "... os_unix_brownian_server_bot"
	@echo "... client/main.o"
	@echo "... client/main.i"
	@echo "... client/main.s"
	@echo "... common/config_reading.o"
	@echo "... common/config_reading.i"
	@echo "... common/config_reading.s"
	@echo "... common/logger.o"
	@echo "... common/logger.i"
	@echo "... common/logger.s"
	@echo "... server/main.o"
	@echo "... server/main.i"
	@echo "... server/main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
