# Anywhere
A HTTP static server writern in c

## How to

```bash
# build `anywhere`
$ make anywhere

# install `anywhere` in /usr/local/bin
# so you can use it anywhere :)
$ make install

# remove binary file and the relevant file
$ make uninstall
```

## Options

```bash
anywhere # start a static server with default port 8000, current directory as base path
anywhere -p 8080 # change the port to 8080
anywhere -b /some/path # change base path
anywhere -log # print access log
```

## License
The MIT license.
