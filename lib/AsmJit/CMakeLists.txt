# Reguire minimum version of CMake
CMake_Minimum_Required(VERSION 2.6)

# AsmJit C++ sources
Set(ASMJIT_SOURCES
  Assembler.cpp
  AssemblerX86X64.cpp
  CodeGenerator.cpp
  Compiler.cpp
  CompilerX86X64.cpp
  CpuInfo.cpp
  Defs.cpp
  DefsX86X64.cpp
  Logger.cpp
  MemoryManager.cpp
  Operand.cpp
  OperandX86X64.cpp
  Platform.cpp
  Util.cpp
)

# AsmJit C++ headers
Set(ASMJIT_HEADERS
  ApiBegin.h
  ApiEnd.h
  AsmJit.h
  Assembler.h
  AssemblerX86X64.h
  Build.h
  CodeGenerator.h
  Compiler.h
  CompilerX86X64.h
  Config.h
  CpuInfo.h
  Defs.h
  DefsX86X64.h
  Logger.h
  MemoryManager.h
  Operand.h
  OperandX86X64.h
  Platform.h
  Util.h
  Util_p.h
)

# pthread library is needed for non-windows OSes.
If(NOT WIN32)
  Link_Libraries(pthread)
EndIf(NOT WIN32)

# Build-Type.
If(${CMAKE_BUILD_TYPE})
  If(${CMAKE_BUILD_TYPE} MATCHES "Debug")
    Add_Definitions(-DASMJIT_DEBUG)
  Else()
    Add_Definitions(-DASMJIT_NO_DEBUG)
  EndIf()
EndIf()

Add_Library(AsmJit STATIC ${ASMJIT_SOURCES} ${ASMJIT_HEADERS})

