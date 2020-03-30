##
## Auto Generated makefile by CodeLite IDE
## any manual changes will be erased      
##
## Debug
ProjectName            :=HugeIntegersStaticLibraryCreator
ConfigurationName      :=Debug
WorkspacePath          :=C:/Users/Seeker/Documents/programming/HugeIntegers
ProjectPath            :=C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers
IntermediateDirectory  :=./Debug
OutDir                 := $(IntermediateDirectory)
CurrentFileName        :=
CurrentFilePath        :=
CurrentFileFullPath    :=
User                   :=Seeker
Date                   :=29/03/2020
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
OutputFile             :=$(IntermediateDirectory)/libHugeIntegers.lib
Preprocessors          :=
ObjectSwitch           :=-o 
ArchiveOutputSwitch    := 
PreprocessOnlySwitch   :=-E
ObjectsFileList        :="HugeIntegersStaticLibraryCreator.txt"
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
CXXFLAGS :=  -g $(Preprocessors)
CFLAGS   :=  -g $(Preprocessors)
ASFLAGS  := 
AS       := C:/MinGW/bin/as.exe


##
## User defined environment variables
##
CodeLiteDir:=C:\Program Files\CodeLite
Objects0=$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix) $(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix) $(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(ObjectSuffix) 



Objects=$(Objects0) 

##
## Main Build Targets 
##
.PHONY: all clean PreBuild PrePreBuild PostBuild MakeIntermediateDirs
all: $(IntermediateDirectory) $(OutputFile)

$(OutputFile): $(Objects)
	@$(MakeDirCommand) $(@D)
	@echo "" > $(IntermediateDirectory)/.d
	@echo $(Objects0)  > $(ObjectsFileList)
	$(AR) $(ArchiveOutputSwitch)$(OutputFile) @$(ObjectsFileList) $(ArLibs)
	@$(MakeDirCommand) "C:\Users\Seeker\Documents\programming\HugeIntegers/.build-debug"
	@echo rebuilt > "C:\Users\Seeker\Documents\programming\HugeIntegers/.build-debug/HugeIntegersStaticLibraryCreator"

MakeIntermediateDirs:
	@$(MakeDirCommand) "./Debug"


./Debug:
	@$(MakeDirCommand) "./Debug"

PreBuild:


##
## Objects
##
$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix): HugeIntWord.cpp $(IntermediateDirectory)/HugeIntWord.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers/HugeIntWord.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/HugeIntWord.cpp$(DependSuffix): HugeIntWord.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/HugeIntWord.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/HugeIntWord.cpp$(DependSuffix) -MM HugeIntWord.cpp

$(IntermediateDirectory)/HugeIntWord.cpp$(PreprocessSuffix): HugeIntWord.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/HugeIntWord.cpp$(PreprocessSuffix) HugeIntWord.cpp

$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix): UnsignedHugeInt.cpp $(IntermediateDirectory)/UnsignedHugeInt.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers/UnsignedHugeInt.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnsignedHugeInt.cpp$(DependSuffix): UnsignedHugeInt.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnsignedHugeInt.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UnsignedHugeInt.cpp$(DependSuffix) -MM UnsignedHugeInt.cpp

$(IntermediateDirectory)/UnsignedHugeInt.cpp$(PreprocessSuffix): UnsignedHugeInt.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnsignedHugeInt.cpp$(PreprocessSuffix) UnsignedHugeInt.cpp

$(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(ObjectSuffix): UnsignedHugeIntValue.cpp $(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(DependSuffix)
	$(CXX) $(IncludePCH) $(SourceSwitch) "C:/Users/Seeker/Documents/programming/HugeIntegers/HugeIntegers/UnsignedHugeIntValue.cpp" $(CXXFLAGS) $(ObjectSwitch)$(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(ObjectSuffix) $(IncludePath)
$(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(DependSuffix): UnsignedHugeIntValue.cpp
	@$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) -MG -MP -MT$(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(ObjectSuffix) -MF$(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(DependSuffix) -MM UnsignedHugeIntValue.cpp

$(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(PreprocessSuffix): UnsignedHugeIntValue.cpp
	$(CXX) $(CXXFLAGS) $(IncludePCH) $(IncludePath) $(PreprocessOnlySwitch) $(OutputSwitch) $(IntermediateDirectory)/UnsignedHugeIntValue.cpp$(PreprocessSuffix) UnsignedHugeIntValue.cpp


-include $(IntermediateDirectory)/*$(DependSuffix)
##
## Clean
##
clean:
	$(RM) -r ./Debug/


