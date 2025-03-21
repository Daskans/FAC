all: parser_visualiser.out ast_interpreter.out program_lexer.out interactive_parser.out

ast_interpreter.out: compiler/*/*.ml compiler/*/*.mli
	rm -rf ast_interpreter.out
	dune build
	ln -s _build/default/compiler/bin_ast_interpreter/main.exe ast_interpreter.out

program_lexer.out: compiler/course_language/Lexer.mll
	rm -rf program_lexer.out
	dune build
	ln -s _build/default/compiler/bin_program_lexer/main.exe program_lexer.out

interactive_parser.out : compiler/course_language/*
	rm -rf interactive_parser.out
	dune build
	ln -s _build/default/compiler/bin_interactive_parser/main.exe interactive_parser.out

parser_visualiser.out: td_4/bin/parser_visualiser.ml td_4/*/*.mly
	rm -rf parser_visualiser.out *.out _build parser_files
	dune build
	ln -s _build/default/td_4/bin/parser_visualiser.exe parser_visualiser.out
	mkdir -p parser_files
	cp _build/default/td_4/custom_parser/Parser.automaton parser_files/custom_parser.automaton 
	cp _build/default/td_4/custom_parser/Parser.conflicts parser_files/custom_parser.conflicts
	cp _build/default/td_4/custom_parser/Parser.dot parser_files/custom_parser.dot
	cp _build/default/td_4/dyck_parser/*.automaton parser_files/
	cp _build/default/td_4/dyck_parser/*.conflicts parser_files/
	cp _build/default/td_4/dyck_parser/*.dot parser_files/
	cp _build/default/td_4/eee_parser/Parser.automaton parser_files/eee_parser.automaton 
	cp _build/default/td_4/eee_parser/Parser.conflicts parser_files/eee_parser.conflicts
	cp _build/default/td_4/eee_parser/Parser.dot parser_files/eee_parser.dot
	cp _build/default/td_4/etf_parser/Parser.automaton parser_files/etf_parser.automaton 
	cp _build/default/td_4/etf_parser/Parser.conflicts parser_files/etf_parser.conflicts
	cp _build/default/td_4/etf_parser/Parser.dot parser_files/etf_parser.dot
	cp _build/default/td_4/first_parser/Parser.automaton parser_files/first_parser.automaton 
	cp _build/default/td_4/first_parser/Parser.conflicts parser_files/first_parser.conflicts
	cp _build/default/td_4/first_parser/Parser.dot parser_files/first_parser.dot
	cp _build/default/compiler/course_language/Parser.automaton parser_files/course_language.automaton 
	cp _build/default/compiler/course_language/Parser.conflicts parser_files/course_language.conflicts
	cp _build/default/compiler/course_language/Parser.dot parser_files/course_language.dot

.PHONY: clean
clean:
	rm -rf *.out doc.html
	dune clean

.PHONY: doc
doc: doc.html

doc.html:
	rm -f doc.html
	dune build @doc
	ln -s _build/default/_doc/_html/index.html doc.html