# Bomb Scoring System
Bomb Scoring is a system that functions to determine whether a bomb falls on a target or not. In this brief explanation, I want to explain several sections:

- References
- Methodology
- Discussion
- Results and Conclusions.

<h2>Reference</h2>
In this system I used 4-point correspondence [Hartley] , Hough Transform for circle detection [Yuen90], and Background Subtraction.

><h3>4-Point Correspondence</h3>

><h3>Hough Transform for Circle Detection</h3>

><h3>Background Subtraction</h3>

<h2>Methodology</h2>
First, I used 4-point correspondence for choose 4 point in image reference and image camera.

Second, I used Hough Transform to detect target position and radius.

Third, I used Background Subtraction for remove a background that is target object. And I want to detect different in the background target object.

Final, I used Hough transform again in the image tranform after remove background Subtraction for detect bomb in the image and measure the radius and angle from the target.
<h2>Discussion</h2>

<h2>Results and Conclusions</h2>

<h2>Bibliography</h2>
[Hartley04] R. Hartley and A. Zisserman, Multiple View Geometry in Computer Vision. Cambridge: Cambridge University Press, 2004.

[Yuen90] Yuen, H. K. and Princen, J. and Illingworth, J. and Kittler, J., Comparative study of Hough transform methods for circle finding. Image Vision Comput. 8 1, pp 71–77 (1990).
[3]
