# Minechallenge

*I challenged myself to learn OpenGL with plain C and try to re-create minecraft with as much detail as I can in 3 days to see how quickly I could learn new libraries*
*I am proud of some of the code, while I absolutely despise some other code in this project.*
*But it still was very fun*

![alt text](https://github.com/Macs1324/Minechallenge/blob/master/screenshots/screen1.png?raw=true)
![alt text](https://github.com/Macs1324/Minechallenge/blob/master/screenshots/screen2.png?raw=true)
![alt text](https://github.com/Macs1324/Minechallenge/blob/master/screenshots/screen3.png?raw=true)

## Building this
*I still didn't know about CMake when I started this project, so I used a classic Makefile. It is definitely not as portable, and I only tested it on Linux (arch based)*
*If you want to build this on your own on a machine with another OS you'll probably have to do some work. I may or may not fix this in the future (I already learned CMake by now yay)*

### Build commands:
`make run`
*Compiles and runs the "game"*
`make game`
*Compiles the game*

## Dependencies
*Dependencies are reduced to a minimum:*
*-FastNoise for Perlin Noise*
*-cglm for vectors, projection etc etc*
*-glew to load the OpenGL API*
*-GLFW to handle cross-platform window creation*
*-stb (especially the stb_image module) to load textures from files*
*If you are having trouble with the dependencies, please try to download and build them separately, and put them in the thirdparty/ folder*
