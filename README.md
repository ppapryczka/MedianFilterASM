# MedianFilterASM
Simple implementation of median filter(https://en.wikipedia.org/wiki/Median_filter) at x86 assembly. Filter have size 3x3, used selection sort to find median and it works with BMP files with header in BITMAPINFOHEADER format. In `example` folder is placed image with salt-and-pepper noise to demonstrate how filter works. Story behind chosen image: http://www.lenna.org/.

---
Program usage:
`program  <input file path> <output file path>`

Used technologies:
- C
- nasm
- make
