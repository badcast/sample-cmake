# sample-cmake
Sample from cmake project, Export and Import data
<br/>
How to compile & run? 

<br/>
Step 1. Clone

```bash
git clone https://github.com/badcast/sample-cmake.git
```

<br/>
Step 2. Set as top directory 

```bash
cd sample-cmake
```

<br/>
<br/>
Step 3. Compilling 

<br/>

```bash
cmake -DCMAKE_BUILD_TYPE=Release -B ./build 
cd ./build
cmake --build . --clean-first
```
<br/>
Step 4. Run 

<br/>

```bash
./sample_bin 
```

