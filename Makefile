.PHONY: clean All

All:
	@echo "----------Building project:[ 011_Alberi_binari_esercizi - Debug ]----------"
	@cd "011_Alberi_binari_esercizi" && "$(MAKE)" -f  "011_Alberi_binari_esercizi.mk"
clean:
	@echo "----------Cleaning project:[ 011_Alberi_binari_esercizi - Debug ]----------"
	@cd "011_Alberi_binari_esercizi" && "$(MAKE)" -f  "011_Alberi_binari_esercizi.mk" clean
