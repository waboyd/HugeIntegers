.PHONY: clean All

All:
	@echo "----------Building project:[ PrimeGenerator - Debug ]----------"
	@cd "PrimeGenerator" && "$(MAKE)" -f  "PrimeGenerator.mk"
clean:
	@echo "----------Cleaning project:[ PrimeGenerator - Debug ]----------"
	@cd "PrimeGenerator" && "$(MAKE)" -f  "PrimeGenerator.mk" clean
