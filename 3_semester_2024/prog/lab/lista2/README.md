## unit tests

```bash
go test -coverprofile=coverage.out ./... && go tool cover -html=coverage.out -o coverage.html
```

## linter

```bash
golangci-lint run
```

## uml

Run `goplantuml` verbosely and theb `plantuml` to generate the *.png* output:

```bash
goplantuml -recursive -show-aggregations -show-aliases -show-compositions -show-connection-labels -show-options-as-note -title LibraryAPI . > diagram.puml && plantuml diagram.puml
```