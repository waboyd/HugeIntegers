.PHONY: clean All

All:
	@echo "----------Building project:[ TestUnsignedHugeInt - Debug ]----------"
	@cd "TestUnsignedHugeInt" && "$(MAKE)" -f  "TestUnsignedHugeInt.mk"
clean:
	@echo "----------Cleaning project:[ TestUnsignedHugeInt - Debug ]----------"
	@cd "TestUnsignedHugeInt" && "$(MAKE)" -f  "TestUnsignedHugeInt.mk" clean
