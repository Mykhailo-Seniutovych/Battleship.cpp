# Compile Core into static lib
g++ -c src/core/**/*.cpp && mv *.o bin && ar crf bin/core.a bin/*.o && rm bin/*.o