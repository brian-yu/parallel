set terminal png
set output "parallelFire.png"
plot "parallelData.txt" u 1:2 w l notitle
