.PHONY: clean All

All:
	@echo "----------Building project:[ HugeIntegersStaticLibraryCreator - Debug ]----------"
	@cd "HugeIntegers" && "$(MAKE)" -f  "HugeIntegersStaticLibraryCreator.mk"
clean:
	@echo "----------Cleaning project:[ HugeIntegersStaticLibraryCreator - Debug ]----------"
	@cd "HugeIntegers" && "$(MAKE)" -f  "HugeIntegersStaticLibraryCreator.mk" clean
