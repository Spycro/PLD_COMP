# PLD Compiler

## How to build

### Ubuntu

```sh
make
```

or

```sh
chmod +x compile_ubuntu.sh
./compile_ubuntu.sh
```

### IF

```sh
chmod +x compile_if.sh
./compile_if.sh
```

### Docker

```sh
chmod +x compile_docker.sh
./compile_docker.sh
```

## Run tests

```sh
make test
```

Running `make tests` will return an exit code different from 0 if one of the tests fails.