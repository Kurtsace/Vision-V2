Vision V2

--Kurt

----------------|

November 23, 2016 

	Few major changes.
	Added a masking operation to the thresholded image. 
		It detects a color that is in range for thresholding and contours it.
		it finds the contour with the largest area to draw. 
		The frame will now only draw the contents of whats INSIDE the contours. 
		Everything else on the outside of the contour / bounding box or bounding circle will be BLACK. 
	The final output frame will ONLY show a masked portion of the source frame. 
	The changes were made to the functions draw() and start(). 
	

November 14, 2016 

	A few major changes to the structure of the code --See variables
	Kernel x and y is a default size of 7. 
	Sigma x and y is a default size of 3.
	Added a [buggy] version of distance to object. 
		Distance formula works but has an uncertainty error. 
	

November 10, 2016

	Minor fixes concerning compatibility and compiler issues. 
	All [known] issues are fixed, if any other issues come up let me know ASAP. 
	
	The parameter src in the constructor will clone its image/frame into fin.
		You can now pass an empty final frame into the constructor as long as src has a frame/image. 

November 10, 2016

	This version of the vision is an object oriented version of the first Vision used.
	This is a working and functional version. 
	It is still missing a few features such as distance to object, but those will be added in later. 
	It is constantly being updated with better algorithms and optimization in functions. 
	A few more features will be added. 

	This version has no [known] bugs and is fully functional for use. 
