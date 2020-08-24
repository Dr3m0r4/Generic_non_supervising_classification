# Generic non supervising classification

* Generic machine learning algorithm made for n-dimensionnal images
    * Non supervising classification
    * Using [CImg] for the images
    * CMake and G++ are used to compile the project
* You can use the [launcher.sh][launcher.sh] file to compile and run the project.

***

## Content
In the main folder, you can find the file [launcher.sh], that allow you to compile and execute the main file.\
You should be aware that if you want to change the name inside the [CMakeLists][cmakel], you have to change it inside the [launcher][launcher.sh].
### [Sources][src]
You can find there all the headers of the project. The last version of the CImg.h file could be find [here][CImg].\
This folder is only used for the library. Each files inside this folder should be an header and will be used to build the library.
### [Test][test]
The main.cpp file is here to test the project. In this folder, the files are not necessary to build the library.
### [Images][image]
It's the folder where you can usually find thes images used to compute. I didn't put them on GitHub due to the storage space.\
There is a list of the different images I used to test the project:

![color squares][square]

![random images][random]

![textures][text]

![dragon][dragon]

### [Build][build]
You should build (*compile*) the project there.
### [Archive][arch]
In this folder, you would find all the last version of the project.
### [Documents][doc]
You can find the needed informations to write the algorithms.

[CImg]: www.cimg.eu
[MLPack]: www.mlpack.org
[src]: Current_version/src/
[image]: Current_version/images/
[build]: Current_version/build/
[doc]: Documents/
[arch]: Archive/
[test]: test/
[cmakel]: Current_version/CMakeLists.txt
[launcher.sh]: Current_version/launcher.sh
[text]: Current_version/images/texture_test.jpeg
[square]: Current_version/images/square.jpeg
[dragon]: Current_version/images/dragon.jpeg
[random]: Current_version/images/test.jpeg
