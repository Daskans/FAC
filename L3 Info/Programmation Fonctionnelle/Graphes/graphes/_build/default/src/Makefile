##
# Project Title
#
# @file
# @version 0.1
#.suffixes:to.ml
.suffixes:
.suffixes:.ml .mli .cmo .cmx .cmi .cma
#OCAMLC=ocamlopt
OCAMLC=ocamlc
OBJ1 = utils.cmo dict.cmo graph.cmo graph_input.cmo data.cmo dot.cmo
#OBJ2 = graph_input2.cmo graph_output.cmo graph_utils.cmo galgo.cmo paths.cmo eulerian.cmo
OBJ = $(OBJ1) #$(OBJ2)

all: $(OBJ)

%.mli: %.ml
	$(OCAMLC) -i $< > $@

%.cmo: %.ml # %.mli
	$(OCAMLC) -c $^

.phony:
clean:
	-rm -f *~ \#*\# Extras/*~
	-rm -f a.out *.cma *.cmi *.o *.cmx *.cmo _tags *.mli g_*.dot g_*.pdf
	-rm -rf _build
	-rm -f TAGS

spotless:
	make clean
	-rm -f a.out g_*.dot g_*.pdf

# end
