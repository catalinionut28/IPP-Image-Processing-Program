Image Processing Program 🌟
A powerful and interactive C program designed for performing image processing tasks. This tool supports various operations like image loading, transformations, filtering, and saving, all while managing multiple images efficiently.

✨ Features
📂 Image Handling
Load Images: Import BMP images into memory using read_from_bmp.
Save Images: Export processed images back to BMP format using write_to_bmp.
🔄 Image Transformations
Horizontal Flip (ah): Mirror an image along its horizontal axis.
Rotate Left (ar): Rotate an image 90° counter-clockwise.
Crop (ac): Extract a specific rectangular section of an image.
Extend (ae): Add colorful borders to your image.
Paste (ap): Overlay one image onto another at a desired position.
🎨 Filters
Create Filters (cf): Define custom filter matrices.
Apply Filters (af): Apply filters to images for creative effects.
Delete Filters (df): Free up memory by removing filters when no longer needed.
🛠️ Memory Management
Dynamically allocate and deallocate memory for images and filters.
Ensures efficient and safe memory usage, even when working with multiple images and filters.
🖥️ Usage
The program is controlled via an intuitive command-line interface. Each command corresponds to a specific operation.

🔑 Commands List
Command	Description	Example
l	Load an image. Provide dimensions (height, width) and file path.	l 100 200 input.bmp
s	Save an image to a specified file path.	s 0 output.bmp
ah	Flip an image horizontally.	ah 0
ar	Rotate an image 90° counter-clockwise.	ar 0
ac	Crop an image. Provide top-left corner and crop dimensions.	ac 0 10 10 50 50
ae	Extend an image by adding borders. Specify border size and color.	ae 0 5 5 255 255 255
ap	Paste one image onto another at a specific position.	ap 0 1 30 30
cf	Create a filter by specifying its size and values.	cf 3 0.1 0.2 0.1 0.2 0.4 0.2 0.1 0.2 0.1
af	Apply a filter to an image.	af 0 0
df	Delete a filter to free memory.	df 0
di	Delete an image from memory.	di 0
e	Exit the program gracefully, freeing all memory.	e
