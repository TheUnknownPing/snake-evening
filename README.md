![picture](<img/picture.png>)

# Snake Evening
The classic Snake game in your terminal made in just one evening. Do whatever you want with this code, it is quite tiny (about 160 lines of C code) and flexible so maybe try study it and implement a new feature or incorporate into your own project (credit is not neccessary but appreciated). Some things you could do would be...

### Challenges
- Add multiple players
- Add some type of windowing (SDL, GLFW, etc.)
- Make it run on a micro controller
- Port it to other platforms (pretty good learning opportunity)

## Building
### UNIX-like
Download source code.\
```$ git clone SOURCE```\
```$ cd SOURCE-name```

Compile it using gcc.\
```$ gcc snake.c -o snake -lpthread```

Run the binary.\
```$ ./snake```

### Windows
Run it under WSL or alternatively port it to Windows. If you are going for the porting route, I would suggest looking at alternatives to `unistd.h`, `termios.h` and `pthread.h` since these header files does not exist on Windows. Good Luck!

## Bugs
If you find any bugs, create an issue and I might fix it. You can also go ahead and fix it yourself and create a pull request and I will check it out.
