CU := $(PWD)
CODEFILES := $(shell find ./src/ -type d -name out -prune -type d -name downlib -prune -o -type f \( -iname \*.cpp -o -iname \*.cc -o -iname \*.hpp \))
#all:
#	echo "$(CU)" 
#	mkdir -p $(CU)/build

buildtest:
	@mkdir -p "$(CU)/build"
	@mkdir -p "$(CU)/ext/downlib"
	gcc $(CODEFILES) -lcurl -fconcepts -lstdc++ -o "$(CU)/src"
	@chmod +x "$(CU)/build"
	@cd "$(CU)"
	
cleantest:
	@rm -rfv $(CU)./build
	@rm -fv boostsdk.tar.gz
	@rm -rfv "$(CU)/src/sdk"