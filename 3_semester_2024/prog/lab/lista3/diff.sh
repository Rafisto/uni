for folder in abstractfactory  adapter  bridge  builder  chainofresponsability  command  composite  decorator  facade  factorymethod  flyweight  iterator  mediator  memento  observer  prototype  proxy  singleton  state  strategy  visitor; do
    echo "Creating patch for $folder"
    git diff --cached -- $folder > "${folder}_diff.patch"
done

find . -name "*_diff.patch" -type f -empty -exec rm -f {} +   