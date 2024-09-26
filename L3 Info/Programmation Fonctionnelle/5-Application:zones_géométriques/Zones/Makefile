##
# Project Title
#
# @file
# @version 0.1
#.suffixes:to.ml
.suffixes:.ml .mli .cmo .cmx

all: mycomplex.cmo zones.cmo images.cmo visu_zones.cmo

%.mli: %.ml
	ocamlc -i $< > $@

%.cmo: %.mli %.ml
	ocamlc -c $^

visu_zones.cmo: visu_zones.ml
	ocamlfind ocamlc -i -package graphics $< > visu_zones.mli
	ocamlfind ocamlc -c -package graphics  visu_zones.mli
	ocamlfind ocamlc -c -package graphics  $<

#mycomplex.mli: mycomplex.ml
#	ocamlc -i $< > $@

images.cmo: images.ml
	ocamlfind ocamlc -i -package graphics $< > images.mli
	ocamlfind ocamlc -c -package graphics  images.mli
	ocamlfind ocamlc -c -package graphics  images.ml


.phony:
clean:
	-rm -f a.out *.cma *.cmi *.o *.cmx *.cmo _tags *.mli
	-rm -rf _build
	-rm -f main
	-rm -f TAGS
# end
