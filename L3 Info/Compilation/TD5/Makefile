all: ast_interpreter.out program_lexer.out interactive_parser.out analyser.out

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

analyser.out: compiler/*/*.ml compiler/*/*.mli
	rm -rf analyser.out
	dune build
	ln -s _build/default/compiler/bin_analyser/main.exe analyser.out

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