compile: pregen
	@cat tree.h *.gen.h tree.cpp main.cpp > final_submission.cpp
	@clang -lm -lstdc++ -g final_submission.cpp -oPhase2
pregen:
	@echo 'datum<int,int> init[]     = {' >  init.gen.h
	@cat  test.init			          >> init.gen.h
	@echo '} ;'   					  >> init.gen.h
	@echo ---
	@echo 'datum<int,int> inserts[]  = {' >  inserts.gen.h
	@cat  test.ins 			          >> inserts.gen.h
	@echo '} ;'				          >> inserts.gen.h
	@echo ---
	@echo 'datum<int,int> dels   []  = {' >  dels.gen.h
	@cat  test.del  		          >> dels.gen.h
	@echo '} ;'				          >> dels.gen.h
	@echo ---
run:
	@./Phase2
debug:
	@gdb ./Phase2 -x init.gdb
ship:
	-@rm *zip -f
	zip mikey-$(shell date +"%H_%M").zip *.cpp *.h makefile init.gdb test.* *.txt
