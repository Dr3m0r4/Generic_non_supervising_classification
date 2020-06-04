# Generic non supervising classification

* Generic machine learning algorithm made for n-dimensionnal images
  * Non supervising classification
  * Using [CImg] for the images
  * Using [MLPack] for the Machine Learning part
  * CMake and G++ are used to compile the project
* You can use the launcher.sh file

***

## Content
In the main folder, you can find the file [launcher.sh], that allow you to compile and execute the main file.
### [src]
You can find there all the C++ files.
### [image]
It's the folder where you can usually find thes images used to compute. I didn't put them on GitHub due to the storage space. You can access to the images I firstly used [here][mnist_png]
### [build]
You can find there all the executables you need.

[CImg]: www.cimg.eu
[MLPack]: www.mlpack.org
[src]: src/
[image]: images/
[build]: build/
[launcher.sh]: launcher.sh
[mnist_png]: https://github.com/myleott/mnist_png
