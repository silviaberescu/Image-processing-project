Berescu Silvia-Maria

Image Processing Application

This project implements various image processing functionalities in C, 
including flipping, rotating, cropping, extending images, and applying filters. 
It supports basic operations on images in BMP format and provides a simple 
command-line interface to perform transformations on images.

Features
Flip Horizontal: Flip an image horizontally (mirror image).
Rotate Left: Rotate an image 90 degrees counterclockwise.
Crop: Crop an image to a specified rectangular region.
Extend: Add borders to an image with a custom color.
Paste: Paste one image onto another at a specified position.
Apply Filter: Apply a custom filter (e.g., blur, sharpen) to an image.
Save/Load BMP: Save images in BMP format and load images from BMP files.
Delete Image/Filter: Manage images and filters by deleting them from memory.

Files
imageprocessing.h: Header file containing function declarations for image 
processing operations.
bmp.h: Header file for handling BMP format read and write functions.
main.c: Main program file implementing the command-line interface to process 
images using various commands.

Command-line Interface
l: Load an image from a BMP file.
s: Save an image to a BMP file.
ah: Flip an image horizontally.
ar: Rotate an image 90 degrees to the left.
ac: Crop an image.
ae: Extend an image by adding borders.
ap: Paste one image onto another.
cf: Create a custom filter.
af: Apply a filter to an image.
di: Delete an image from memory.
df: Delete a filter from memory.
e: Exit the program and free all allocated memory.