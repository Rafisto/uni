pacman -S opam
opam init -y
opam install dune ocaml-lsp-server odoc ocamlformat utop
opam exec -- dune build
opam exec -- dune exec ocaml