##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=HugeIntegers
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/Seeker/Documents/programming/HugeIntegers
ProjectPath            :=C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Seeker
Date                   :=14/02/2020
CodeLitePath           :="C:/Program Files/CodeLite"
LinkerName             :=C:/MinGW/bin/g++.exe
SharedObjectLinkerName :=C:/MinGW/bin/g++.exe -shared -fPIC
ObjectSuffix           :=.o
DependSuffix           :=.o.d
PreprocessSuffix       :=.i
DebugSwitch            :=-g 
IncludeSwitch          :=-I
LibrarySwitch          :=-l
OutputSwitch           :=-o 
LibraryPathSwitch      :=-L
PreprocessorSwitch     :=-D
SourceSwitch           :=-c 
OutputFile             :=$(IntermediateDirectory)/$(ProjectName)
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="HugeIntegers.txt"
PCHCompileFlags        :=
MakeDirCommand         :=makedir
RcCmpOptions           := 
RcCompilerName         :=C:/MinGW/bin/windres.exe
LinkOptions            :=  
IncludePath            :=  $(IncludeSwitch). $(IncludeSwitch). 
IncludePCH             := 
RcIncludePath          := 
Libs                   := 
ArLibs                 :=  
LibPath                := $(LibraryPathSwitch). 

##
## Common variables
## AR, CXX, CC, AS, CXXFLAGS and CFLAGS can be overriden using an environment variables
##
AR       := C:/MinGW/bin/ar.exe rcu
CXX      := C:/MinGW/bin/g++.exe
CC       := C:/MinGW/bin/gcc.exe
CXXFLAGS := -std=c++17 -Wall -g -O0 -Wall $(Preprocessors)
CFLAGS   :=  -g -O0 -Wall $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix) $(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix) $(IntermediateDirectory)/hugeIntTests.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(OutputFile)

$(OutputFile): $(IntermediateDirectory)/.d $(Objects) 
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(LinkerName) $(OutputSwitch)$(OutputFile) @$(ObjectsFileList) $(LibPath) $(Libs) $(LinkOptions)

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


$(IntermediateDirectory)/.d:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix): UnsignedHugeInt.cpp $(IntermediateDirectory)/UnsignedHugeInt.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers/UnsignedHugeInt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnsignedHugeInt.cpp$(DependSuffix): UnsignedHugeInt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UnsignedHugeInt.cpp$(DependSuffix) -MM UnsignedHugeInt.cpp

$(IntermediateDirectory)/UnsignedHugeInt.cpp$(PreprocessSuffix): UnsignedHugeInt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnsignedHugeInt.cpp$(PreprocessSuffix) UnsignedHugeInt.cpp

$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix): HugeIntWord.cpp $(IntermediateDirectory)/HugeIntWord.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers/HugeIntWord.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HugeIntWord.cpp$(DependSuffix): HugeIntWord.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HugeIntWord.cpp$(DependSuffix) -MM HugeIntWord.cpp

$(IntermediateDirectory)/HugeIntWord.cpp$(PreprocessSuffix): HugeIntWord.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HugeIntWord.cpp$(PreprocessSuffix) HugeIntWord.cpp

$(IntermediateDirectory)/hugeIntTests.cpp$(ObjectSuffix): hugeIntTests.cpp $(IntermediateDirectory)/hugeIntTests.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers/hugeIntTests.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/hugeIntTests.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/hugeIntTests.cpp$(DependSuffix): hugeIntTests.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/hugeIntTests.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/hugeIntTests.cpp$(DependSuffix) -MM hugeIntTests.cpp

$(IntermediateDirectory)/hugeIntTests.cpp$(PreprocessSuffix): hugeIntTests.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/hugeIntTests.cpp$(PreprocessSuffix) hugeIntTests.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


