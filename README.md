Image Processing Program
This repository contains a C program designed to perform various image processing tasks. It supports operations like image loading, transformations, filtering, and saving, with functionalities for handling multiple images simultaneously.
Features
The program provides the following functionality:

Load Images: Load BMP images into memory using read_from_bmp.
Save Images: Save processed images back to BMP format using write_to_bmp.
Transformations:
Horizontal Flip: Mirror an image along the horizontal axis.
Rotate Left: Rotate an image 90 degrees counter-clockwise.
Crop: Extract a rectangular section of an image.
Extend: Add borders to an image.
Paste: Overlay one image onto another.
Filters:
Create and apply custom filters to images.
Remove filters from memory.
Memory Management:
Dynamic memory allocation and deallocation for images and filters.
Usage
Commands
The program uses a command-line interface with specific commands to perform operations. Below is a list of available commands:
"l" - Load an image. Provide dimensions (height, width) and file path.
"s" - Save an image to a specified file path.
"ah" - Flip an image horizontally.
"ar" - Rotate an image 90° counter-clockwise.
"ac" - Crop an image. Provide top-left corner and dimensions of the crop area.
"ae" - Extend an image by adding borders. Provide dimensions for borders and color values.
"ap" - Paste one image onto another at a specified position.
"cf" - Create a filter by providing its size and matrix values.
"af" - Apply a filter to an image.
"df" - Delete a filter.
"di" - Delete an image.
"e" -  Exit the program.
Build and Run
Requirements
GCC or any compatible C compiler.
bmp.h and imageprocessing.h headers, with their respective implementation files.
Running
./interactive
