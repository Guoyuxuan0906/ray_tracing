# 生成渐变图像  
算法流程  
1.  
给出图像宽(width)和纵横比(aspect ratio=width/height), 
计算图像长(height=width/aspect ratio),
注意图像**长宽必须为整数且大于1**  
2.  
确定camera位置(0,0,0);  
给出视口(viewport)长,确定长宽,确保视口长宽与图像分辨率比例**完全相同**,可为小数;  
确定焦距(focal_length),即视口到camera点的距离;  
**We'll also have the y-axis go up, the x-axis to the right, and the negative z-axis pointing in the viewing direction.**  
![alt text](fig-1.03-cam-geom-1.jpg)  
3.  
计算视口两个方向向量;  
计算像素间距间隔向量;  
计算视口和像素起点坐标;  
4.  
遍历每个像素点坐标，根据位置关系计算出对应像素光线的颜色