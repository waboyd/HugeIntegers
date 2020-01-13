.PHONY: clean All

All:
	@echo "----------Building project:[ HugeIntegers - Debug ]----------"
	@cd "PrimeGenerator" && "$(MAKE)" -f  "HugeIntegers.mk"
clean:
	@echo "----------Cleaning project:[ HugeIntegers - Debug ]----------"
	@cd "PrimeGenerator" && "$(MAKE)" -f  "HugeIntegers.mk" clean
